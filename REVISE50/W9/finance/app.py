import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime


from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter to format currency into 0.2f USD
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# finance/ $ sqlite3 finance.db
# sqlite> .schema
# CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);
# CREATE TABLE sqlite_sequence(name,seq);
# CREATE UNIQUE INDEX username ON users (username);

# sqlite> .tables
# users
# sqlite> .schema users
# CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);
# CREATE UNIQUE INDEX username ON users (username);


# configures Flask to store sessions on the local filesystem (i.e., disk)
# instead of storing them inside of digitally signed cookies, which is Flask’s default.
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required # flask view decorators https://flask.palletsprojects.com/en/2.3.x/patterns/viewdecorators/
def index():
    """Show portfolio of stocks"""
    user = db.execute("SELECT username,cash FROM users WHERE id = ?",session["user_id"])
    username = user[0].get("username")
    cash = user[0].get("cash")

    rows = db.execute("SELECT symbol, SUM(shares) AS holdings FROM holdings WHERE username = ? GROUP BY symbol",username)
    # which stocks the user owns, the numbers of shares owned, the current price of each stock, and the total value of each holding
    # [{'share': 'MSFT', 'holdings': 2}, {'share': 'NFLX', 'holdings': 3}]
    print(rows)
    total = 0
    for holding in rows:
        quote = lookup(holding.get("symbol"))
        holding["price"] = quote.get("price")
        holding["name"] = quote.get("name")
        subtotal = quote.get("price") * holding.get("holdings")
        holding["total"] = subtotal
        total += subtotal
    return render_template("index.html",username=username,cash=cash,total= cash + total,holdings=rows)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if (symbol == ""):
            return apology("SYMBOL IS EMPTY",400)
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("PLEASE INPUT INTEGER",400)
        if (shares <= 0):
            return apology("PLEASE INPUT INTEGER MORE THAN 0",400)
        quote = lookup(symbol)
        if (quote is None): #None is case sensitive
            return apology("NO SUCH SYMBOL",400)
        # should be transactional
        user = db.execute("SELECT username FROM users WHERE id = ?",session["user_id"])
        username = user[0].get("username")
        rows = db.execute("SELECT cash FROM users WHERE username = ?",username)
        if(rows[0].get("cash") < quote.get("price") * shares):
            return apology("YOU POOR",400)

        db.execute("INSERT INTO transactions (username,transaction_time,symbol,transaction_amount,transaction_price,transaction_type) VALUES(?,?,?,?,?,?)",username,datetime.now(),symbol,shares,quote.get("price"),"BUY")
        transact(username,symbol,shares)
        db.execute("UPDATE users SET cash = ? WHERE username = ?", rows[0].get("cash") - (quote.get("price") * shares), username)

        return redirect("/")
    return apology("INVALID REQUEST METHOD",400)

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user = db.execute("SELECT username FROM users WHERE id = ?",session["user_id"])
    username = user[0].get("username")
    rows = db.execute("SELECT id, transaction_time, symbol, transaction_amount, transaction_price, transaction_type from transactions WHERE username = ?",username)
    return render_template("history.html",transactions=rows)

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
        # for SELECT returns a list of dict objects, each of which represents a row in the result set
        # https://cs50.readthedocs.io/libraries/cs50/python/?highlight=execute%20sql#cs50.SQL.execute
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in by storing into session
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
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if (symbol == ""):
            return apology("SYMBOL IS EMPTY",400)
        quote = lookup(symbol)
        if (quote is None): #None is case sensitive
            return apology("NO SUCH SYMBOL",400)
        return render_template("quoted.html",quote = quote)
    return apology("INVALID REQUEST METHOD",400)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if(username == "" or password == "" or confirmation == ""):
            return apology("PLEASE FILL UP ALL FIELDS",400)
        if(password != confirmation):
            return apology("PASSWORDS DO NOT MATCH",400)
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if(len(rows) > 0):
            return apology("USERNAME ALREADY EXISTS",400)
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username,generate_password_hash(password))
        return render_template("register-success.html")
    return apology("INVALID REQUEST METHOD",400)
    # apology(message, code=400):

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = db.execute("SELECT username FROM users WHERE id = ?",session["user_id"])
    username = user[0].get("username")
    if request.method == "GET":
        holdings = db.execute("SELECT symbol,shares FROM holdings WHERE username = ?",username)
        return render_template("sell.html",holdings=holdings)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if (symbol == ""):
            return apology("SYMBOL IS EMPTY",400)
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("PLEASE INPUT INTEGER",400)
        if (shares <= 0):
            return apology("PLEASE INPUT INTEGER MORE THAN 0",400)
        row = db.execute("SELECT shares FROM holdings WHERE symbol = ? AND username = ?",symbol,username)
        if(len(row) == 0):
            return apology("YOU DO NOT OWN THAT STOCK",400)
        holding = row[0].get("shares")
        if (holding < shares):
            return apology("YOU DO NOT OWN THAT MANY SHARES",400)
        print(symbol,shares)
        transact(username, symbol,-shares)
        return redirect("/")

@app.route("/topup", methods=["GET", "POST"])
@login_required
def topup():
    if request.method == "GET":
        return render_template("topup.html")
    if request.method == "POST":
        user = db.execute("SELECT username,cash FROM users WHERE id = ?",session["user_id"])
        username = user[0].get("username")
        cash = user[0].get("cash")
        try:
            topup = float(request.form.get("topup"))
        except ValueError:
            return apology("PLEASE INPUT INTEGER",400)
        db.execute("UPDATE users SET cash = ? WHERE username = ?", cash+topup, username)
        return redirect("/")

def transact(username, symbol,shares):
    row = db.execute("SELECT shares FROM holdings WHERE symbol = ? AND username = ?",symbol,username)
    holding = 0
    if(len(row) == 0):
        db.execute("INSERT INTO holdings (username, symbol,shares) VALUES (?,?,?)",username, symbol, shares)
    if(len(row) > 0):
        holding += row[0].get("shares")
        if(-holding == shares):
            db.execute("DELETE FROM holdings WHERE username = ? and symbol = ?",username, symbol)
        else:
            db.execute("UPDATE holdings SET shares = ? WHERE username = ? and symbol = ?", holding + shares,username, symbol)



# TODO
# CREATE TABLE holdings (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL,symbol REAL NOT NULL,shares INTEGER NOT NULL)
# CREATE TABLE transactions (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, transaction_time DATETIME.sche NOT NULL, symbol REAL NOT NULL, transaction_amount INT NOT NULL, transaction_price REAL NOT NULL, transaction_type VARCHAR(4));
