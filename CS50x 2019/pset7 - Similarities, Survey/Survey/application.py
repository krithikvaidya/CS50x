import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Form Fields
names = []
genders = []
age_ranges = []
fav_tvseriess = []


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Main Page
@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")

# Form Page
@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")

# On submitting the form
@app.route("/form", methods=["POST"])
def post_form():

    if not request.form["name"] or not request.form["gender"] or not request.form["age_range"] or not request.form["fav_tvseries"]:  # server-side validation
        return render_template("error.html", message="Please fill all the fields!")

    with open('survey.csv', 'a') as csvfile:  # opening survey.csv as a csv file in 'append' mode

        fieldnames = ['name', 'gender', 'age_range', 'fav_tvseries']  # the fields that will be stored in the CSV file, in proper order
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()  # writes the 'fieldnames' to the header of the CSV files
        writer.writerow({'name': request.form["name"], 'gender': request.form["gender"],
                         'age_range': request.form["age_range"], 'fav_tvseries': request.form["fav_tvseries"]
                         })  # creates a new row to accomodate the new form entry

    return redirect("/sheet")  # redirects to sheet.html


@app.route("/sheet", methods=["GET"])
def get_sheet():

    with open('survey.csv', mode='r') as csv_file:  # opening survey.csv as a csv file in read mode

        csv_reader = csv.DictReader(csv_file)

        for row in csv_reader:  # loop through all the row (excluding the header) of the CSV file
            names.append(f"{row['name']}")
            genders.append(f"{row['gender']}")
            age_ranges.append(f"{row['age_range']}")
            fav_tvseriess.append(f"{row['fav_tvseries']}")

        return render_template("sheet.html", names=names, genders=genders, age_ranges=age_ranges, fav_tvseriess=fav_tvseriess)
