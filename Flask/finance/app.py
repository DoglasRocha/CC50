import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd
import re

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    summ = 0
    
    # gets the cash of the user and puts it into the data that is going to be displayed
    cash = get_cash()
    summ += cash
    symbol = 'CASH'
    
    table_cell = {
        'total': cash,
        'symbol': symbol,
        'shares': '',
        'name': '',
        'price': ''
    }
    data = [table_cell]
    
    # gets the stocks from the user
    movements = db.execute('SELECT stock, shares FROM stocks where id = ?',
                           session['user_id'])
    
    # iterates over the stocks
    for move in movements:
        
        symbol = move['stock']
        shares = move['shares']
        response = lookup(symbol)
        
        # error checking
        if not response:
            
            return apology('Server Error')
        
        # puts the data into the list of values that are going to be displayed
        table_cell = {}
        
        name = response['name']
        price = response['price']
        total = price * shares
        summ += total
        
        table_cell['symbol'] = symbol
        table_cell['name'] = name
        table_cell['shares'] = shares
        table_cell['price'] = price
        table_cell['total'] = total
        
        data.append(table_cell)
    
    return render_template('index.html', data=data, total_cash=summ)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        
        stock = request.form.get('stock')
        shares = float(request.form.get('shares'))
        
        response = lookup(stock)
        
        if not response:
            
            return apology('Invalid stock')
        
        price = response['price']
        required_cash = price * shares
        
        cash = get_cash()
        
        if (required_cash > cash):
            
            return apology('Insufficient cash!')
        
        updated_cash = cash - required_cash
        update_cash(updated_cash)
        
        user_stocks_from_company = get_stocks_from_user_by_company(stock)
        if (not user_stocks_from_company):
            
            db.execute('INSERT INTO stocks VALUES (?, ?, ?)',
                       session['user_id'],
                       stock,
                       shares)
            
            db.execute('INSERT INTO history VALUES (?, ?, ?, ?, ?)',
                       session['user_id'],
                       stock, 
                       shares,
                       price,
                       datetime.today())
            
        else:
            
            current_shares = int(user_stocks_from_company[0]['shares'])
            updated_shares = current_shares + shares
            
            db.execute('UPDATE stocks SET shares = ? WHERE id = ? AND stock = ?',
                       updated_shares,
                       session['user_id'],
                       stock)
            
            db.execute('INSERT INTO history VALUES (?, ?, ?, ?, ?)',
                       session['user_id'],
                       stock, 
                       shares,
                       price,
                       datetime.today())
        
        flash('Bought!')
        return redirect('/')
    
    return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute('SELECT * FROM history WHERE id = ?', session['user_id'])
    
    return render_template('history.html', data=data)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Logged in!')
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
    
    message = None
    
    if request.method == 'POST':

        stock = request.form.get('stock')
        response = lookup(stock)
        
        if not response:
            
            return apology('Connection Error')
        
        name = response['name']
        price = response['price']
        
        message = f'A share of {name} ({stock}) costs {usd(float(price))}'
        return render_template('quote.html', message=message)    
        
    return render_template('quote.html', message=message)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        
        username = request.form.get('username')
        password = request.form.get('password')
        confirm_password = request.form.get('confirm_password')
        
        # user did not fill the form
        if (not username
            and not password
            and not confirm_password):
  
                return apology('You have to fulfill the form!')
            
        # user did not fill the username field
        if (not username):
            
            return apology('You have to create a username!')
        
        # user did not fill the password field
        if (not password):
            
            return apology('You have to create a password!')
        
        # user did not fill the confirm password field
        if (not confirm_password):
            
            return apology('You have to confirm the password!')
        
        # password has to have more than 8 characters
        if (not re.search('[a-zA-Z0-9]{8,}', password)):
            
            return apology('The password has to have more than 8 characters!')
        
        # password and password confirmation do not match
        if (password != confirm_password):
            
            return apology('The passwords have to match!')
        
        # generates the hash and puts the user into the db
        hash_password = generate_password_hash(password)
        db.execute('INSERT INTO users(username, hash) VALUES (?, ?)', username, hash_password)
        
        return redirect('/login')
            
    else:
    
        return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'POST':
        
        stock = request.form.get('stock')
        shares = float(request.form.get('shares'))
        
        response = lookup(stock)
        
        if not response:
            
            return apology('Invalid stock')
        
        price = response['price']
        profit = price * shares
        
        cash = get_cash()
        
        updated_cash = cash + profit
        update_cash(updated_cash)
        
        user_stocks_from_company = get_stocks_from_user_by_company(stock)
        if (not user_stocks_from_company):
            
            return apology('You do not own the requested stock!')
            
        else:
            
            current_shares = int(user_stocks_from_company[0]['shares'])
            updated_shares = current_shares - shares
            
            db.execute('UPDATE stocks SET shares = ? WHERE id = ? AND stock = ?',
                       updated_shares,
                       session['user_id'],
                       stock)
            
            db.execute('INSERT INTO history VALUES (?, ?, ?, ?, ?)',
                       session['user_id'],
                       stock, 
                       -shares,
                       price,
                       datetime.today())
        
        flash('Bought!')
        return redirect('/')
    
    return render_template('sell.html')


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


def get_cash():
    '''gets the cash from the user'''
    return float(db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0]['cash'])


def update_cash(new_amount) -> None:
    '''updates the amount of cash of the user'''
    db.execute('UPDATE users SET cash = ? WHERE id = ?', 
               new_amount,
               session['user_id'])    


def get_stocks_from_user_by_company(company):
    '''gets the stocks that the user has of a determined company'''
    query = db.execute('''SELECT shares FROM stocks
                              WHERE id = ?
                              AND stock = ?''',
                       session['user_id'],
                       company)
    
    return query
    

# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
