import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute(
        "SELECT symbol, SUM(amount) AS amount FROM buys WHERE users_id = ? GROUP BY symbol HAVING SUM(amount) > 0",
        session["user_id"]
    )

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    total = cash

    for row in rows:
        quote = lookup(row["symbol"])
        row["price"] = quote["price"]
        row["total"] = row["amount"] * row["price"]
        total += row["total"]

    return render_template("index.html", result=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if symbol is None:
            return apology("Not a valid symbol")

        if request.form.get("shares") == "":
            return apology("Shares is empty", 400)

        if not request.form.get("shares").isdigit():
            return apology("Shares is not all digits", 400)

        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Amount of shares to be bought must be positive integer", 400)

        price = symbol["price"]

        rows = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )

        if rows[0]["cash"] < (price * shares):
            return apology("Not enough money")

        db.execute("UPDATE users SET cash = cash - ?  WHERE id = ?",
                   price * shares, session["user_id"])
        db.execute(
            "INSERT INTO buys (users_id, symbol, amount, price, timestamp) VALUES (?, ?, ?, ?, datetime('now'))", session[
                "user_id"], symbol["symbol"], shares, price
        )

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute(
        "SELECT symbol, amount, price, timestamp FROM buys WHERE users_id = ? ", session["user_id"]
    )
    print(rows)
    return render_template("history.html", rows=rows)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        symbol = lookup(request.form.get("symbol"))
        if symbol is None:
            return apology("Invalid", 400)

        return render_template("quoted.html", symbol=symbol)
    else:
        result = request.form
        return render_template("quote.html", result=result)


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide two password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) == 1:
            return apology("username already exists", 400)
        else:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
                    "username"), generate_password_hash(request.form.get("password"))
            )

        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("No stock selected", 400)

        if request.form.get("shares") == "":
            return apology("No shares selected", 400)

        if not request.form.get("shares").isdigit():
            return apology("Share is not digits", 400)

        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Shares must be a positive number", 400)

        rows = db.execute(
            "SELECT SUM(amount) AS amount FROM buys WHERE users_id = ? AND symbol = ?",
            session["user_id"], symbol
        )

        if rows[0]["amount"] is None or rows[0]["amount"] < shares:
            return apology("More shares selected than available.", 400)

        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid selection.", 400)

        price = stock["price"]

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            price * shares, session["user_id"]
        )

        db.execute(
            "INSERT INTO buys (users_id, symbol, amount, price, timestamp) VALUES (?, ?, ?, ?, datetime('now'))",
            session["user_id"], symbol, -shares, price
        )

        return redirect("/")

    else:
        symbols = db.execute(
            "SELECT symbol FROM buys WHERE users_id = ? GROUP BY symbol HAVING SUM(amount) > 0",
            session["user_id"]
        )
        return render_template("sell.html", symbols=symbols)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change user password"""
    if request.method == "GET":
        return render_template("password.html")
    else:
        rows = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        stored_hash = rows[0]["hash"]

        if not check_password_hash(stored_hash, request.form.get("oldpassword")):
            return apology("Old Password incorrect", 403)

        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Must provide new password twice", 403)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("New passwords do not match", 403)

        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?",
            generate_password_hash(request.form.get("password")),
            session["user_id"]
        )

        return redirect("/")
