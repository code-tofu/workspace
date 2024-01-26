import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        #should query id from db instead. no auto increment but primary key exists
        id = request.form.get("id")
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        db.execute("INSERT INTO birthdays (id, name,month,day) VALUES(?, ?,?,?)", id, name,month,day)
        return redirect("/")

    else:

        # returns json array: [{'id': 1, 'name': 'Harry', 'month': 7, 'day': 31}, {'id': 2, 'name': 'Ron', 'month': 3, 'day': 1}, {'id': 3, 'name': 'Hermione', 'month': 9, 'day': 19}]
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)



# When the / route is requested via GET, your web application should display, in a table, all of the people in your database along with their birthdays.
# First, in app.py, add logic in your GET request handling to query the birthdays.db database for all birthdays. Pass all of that data to your index.html template.
# Then, in index.html, add logic to render each birthday as a row in the table. Each row should have two columns: one column for the person’s name and another column for the person’s birthday.
# When the / route is requested via POST, your web application should add a new birthday to your database and then re-render the index page.
# First, in index.html, add an HTML form. The form should let users type in a name, a birthday month, and a birthday day. Be sure the form submits to / (its “action”) with a method of post.
# Then, in app.py, add logic in your POST request handling to INSERT a new row into the birthdays table based on the data supplied by the user.

# sqlite> .schema birthdays
# CREATE TABLE birthdays (
#     id INTEGER,
#     name TEXT,
#     month INTEGER,
#     day INTEGER,
#     PRIMARY KEY(id)
# );