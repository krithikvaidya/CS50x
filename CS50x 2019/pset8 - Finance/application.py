import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    records = db.execute("SELECT symbol, sum(shares), sum(total_price) FROM purchases GROUP BY symbol, user_id HAVING user_id = :user_id;", user_id=session["user_id"])
    table = []
    
    i = 0
    tot = 0.0
    
    for record in records:
        if float(record['sum(shares)']) != 0:
            table.append({})
            table[i]['symbol'] = record['symbol']
            
            quote = lookup(record['symbol'])
            
            table[i]['name'] = quote['name']
            table[i]['shares'] = record['sum(shares)']
            
            table[i]['price'] = usd(float(record['sum(total_price)']) / float(record['sum(shares)']))
            
            table[i]['total'] = usd(float(record['sum(total_price)']))
            
            tot += float(record['sum(total_price)'])
            i += 1
    
    cash = db.execute("SELECT cash FROM users WHERE id = :userid;", userid=session["user_id"])
    
    tot += float(cash[0]['cash'])
    
    total = usd(tot)

    return render_template("index.html", records=table, cash=usd(float(cash[0]['cash'])), total=total)
    
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    #if the form was submitted
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        
        try:
            hmm = int(shares)
        except:
            return apology("enter a valid, integral number of shares", 400)
        
        # get the details of the stock with the given symbol from the IEX API
        stock_details = lookup(symbol)
        
        if not stock_details:
            return apology("invalid symbol", 400)
            
        if not shares:
            return apology("please enter the number of shares", 400)
            
        if int(shares) < 1:
            return apology("please enter a valid number of shares", 400)
            
        balance = db.execute("SELECT cash FROM users WHERE id = :userid;", userid=session["user_id"])
        
        if (float(stock_details["price"]) * int(shares)) > balance[0]['cash']:
            return apology("you do not have sufficient funds", 403)

        try:
            success = db.execute("INSERT INTO purchases (user_id, symbol, shares, total_price) VALUES (:user_id, :symbol, :shares, :tp);", 
                                 user_id=session["user_id"], symbol=symbol.upper(), shares=shares, tp=int(shares) * stock_details["price"])
            
            if not success:
                return apology("the purchase could not be made", 403)
                
        except RuntimeError:
            return apology("the purchase could not be made", 403)
            
        db.execute("UPDATE users SET cash = :balance WHERE id = :user_id;", balance=(balance[0]['cash'] - (float(stock_details["price"]) * int(shares))), user_id=session["user_id"])
        
        flash('Purchase Successful.')
        return redirect("/")
        
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get('username')
    
    # Check if the username already exists
    rows = db.execute("SELECT * FROM users WHERE username = :username", 
                                username=username)
    
    if len(username) >= 1 and not rows:
        return jsonify(True)
    else:
        return jsonify(False)
    
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    records = db.execute("SELECT symbol, shares, total_price, datetime FROM purchases WHERE user_id = :user_id;", user_id=session["user_id"])
    
    i = 0;
    
    for record in records:
        records[i]['total_price'] = usd(float(records[i]['total_price']))
        i += 1    
        
    return render_template("history.html", records=records)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        
        if not quote:
            return apology("must provide a valid stock", 400)
            
        stock_name = quote['name']
        price = quote['price']
        
        price_in_USD = usd(price)
    
        return render_template("quoted.html", stock_name=stock_name, price=price_in_USD)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any currently logged in user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
            
        elif not request.form.get("confirmation"):
            return apology("must re-enter password", 400)
            
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("the password and confirmation password do not match", 400)
        
        Hash = generate_password_hash(request.form.get("password"))
        
        # Insert the details of the new user into the db
        rows = db.execute("INSERT INTO users (username, hash, cash) VALUES(:username, :hash, 10000);",
                          username=request.form.get("username"), hash=Hash)

        # Login the user after their registration
        x = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
                          
        session["user_id"] = x[0]['id']
  
        # Redirect user to home page
        flash('Registration successful! You are now logged in.')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #if the form was submitted
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        
        # get the details of the stock with the given symbol from the IEX API
        stock_details = lookup(symbol)
        
        if not stock_details:
            return apology("invalid symbol", 400)
            
        if not shares:
            return apology("please enter number of shares", 400)
            
        if int(shares) < 1:
            return apology("please enter a valid number of shares", 400)

        user_shares = db.execute("SELECT sum(shares) FROM purchases GROUP BY symbol, user_id HAVING user_id = :user_id AND symbol = :symbol;", user_id=session["user_id"], symbol=symbol)
        
        if not user_shares:
            return apology("you do not own that stock.")
        
        if int(shares) > int(user_shares[0]['sum(shares)']):
            return apology("you do not possess sufficient shares", 400)
        
        balance = db.execute("SELECT cash FROM users WHERE id = :userid;", userid=session["user_id"])
        
        try:
            success = db.execute("INSERT INTO purchases (user_id, symbol, shares, txn_type, total_price) VALUES (:user_id, :symbol, :shares, 0, :tp);", 
                                 user_id=session["user_id"], symbol=symbol, shares=-1*(int(shares)), tp=-1.0 * float(int(shares)) * stock_details["price"])
            
            if not success:
                return apology("the sale could not be made", 403)
                
        except RuntimeError:
            return apology("the sale could not be made", 403)
            
        db.execute("UPDATE users SET cash = :balance WHERE id = :user_id;", balance=(balance[0]['cash'] + (float(stock_details["price"]) * int(shares))), user_id=session["user_id"])
        
        flash('Sale Successful.')
        return redirect("/")
        
    else:
        symbols = db.execute("SELECT symbol FROM purchases GROUP BY symbol, user_id HAVING user_id = :user_id;", user_id=session["user_id"])
        return render_template("sell.html", symbols=symbols)
        
@app.route("/changepw", methods=["GET", "POST"])
@login_required
def changepw():
    """Additional Functionality of Changing Password"""
    
    if request.method == "POST":
        oldpw = request.form.get("prevpw")
        newpw = request.form.get("newpw")
        conf_newpw = request.form.get("conf_newpw")
        
        # Query database for user
        rows = db.execute("SELECT hash FROM users WHERE id = :user_id",
                          user_id=session["user_id"])

        # Ensure username exists and password is correct
        if not check_password_hash(rows[0]["hash"], oldpw):
            return apology("the entered current password is incorrect", 403)
            
        if newpw != conf_newpw:
            return apology("the confirmation password is incorrect", 403)
        
        
        Hash = generate_password_hash(newpw)
        
        # Insert the details of the new user into the db
        rows = db.execute("UPDATE users SET hash = :hash WHERE id = :user_id;",
                          hash=Hash, user_id=session["user_id"])
                          
        flash('Password Change Successful!')
        return redirect("/")
        
    else:
        return render_template("changepw.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
