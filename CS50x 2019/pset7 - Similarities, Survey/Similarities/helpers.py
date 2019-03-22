from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    dup_lines = []  # the required list of duplicate lines
    curr_index_a = 0  # stores the starting index of each line in string a
    curr_index_b = 0

    while curr_index_a < len(a):
        next_index_a = a.find('\n', curr_index_a)
        if next_index_a == -1:
            next_index_a = len(a)

        curr_index_b = 0

        while curr_index_b < len(b):
            next_index_b = b.find('\n', curr_index_b)
            if next_index_b == -1:
                next_index_b = len(b)
            if (a[curr_index_a: next_index_a] == b[curr_index_b: next_index_b]):
                dup_lines.append(a[curr_index_a: next_index_a])
                break
            curr_index_b = next_index_b + 1

        curr_index_a = next_index_a + 1
    return dup_lines  # finally returns the duplicate lines list


def sentences(a, b):
    """Return sentences in both a and b"""

    sent_list_a = sent_tokenize(a, language='english')
    sent_list_b = sent_tokenize(b, language='english')
    dup_sents = []

    for sent in sent_list_a:
        if sent in sent_list_b:
            if not (sent in dup_sents):
                dup_sents.append(sent)

    return dup_sents


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    start_index = 0
    dup_substr = []

    while (start_index + n) <= len(a):

        if b.find(a[start_index: start_index + n], 0) != -1:
            if not (a[start_index: start_index + n] in dup_substr):
                dup_substr.append(a[start_index: start_index + n])
        start_index += 1

    return dup_substr
