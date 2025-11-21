import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///pomodoro.db")


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
    """Show History of Pomodoros"""

    rows = db.execute(
        "SELECT * FROM pomodoros WHERE users_id = ? ORDER BY timestart DESC",
        session["user_id"]
    )

    if len(rows) == 0:
        return render_template("index.html", result=[], total=0)

    total = 0

    for row in rows:
        timestart = datetime.fromisoformat(row["timestart"])
        timeend = datetime.fromisoformat(row["timeend"])
        timespent = (timeend - timestart).total_seconds() / 60
        row["timespent"] = round(timespent, 2)
        total += timespent

    return render_template("index.html", result=rows, total=round(total, 2))

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

@app.route("/account", methods=["GET", "POST"])
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

@app.route("/start", methods=["POST"])
@login_required
def start():
    """Start a new pomodoro"""

    # remember start time in session
    timestart = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    session["pomodoro_start"] = timestart

    return redirect("/")

@app.route("/stop", methods=["POST"])
@login_required
def stop():
    """Stop current pomodoro"""

    # get start time from session
    timestart = session.get("pomodoro_start")

    # if no pomodoro in progress, just go back
    if not timestart:
        return redirect("/")

    timeend = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    db.execute(
        "INSERT INTO pomodoros (users_id, timestart, timeend) VALUES (?, ?, ?)",
        session["user_id"],
        timestart,
        timeend
    )

    # clear session state
    session["pomodoro_start"] = None

    return redirect("/")
