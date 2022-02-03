import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps
from datetime import datetime


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://cloud.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}"
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    if (type(value) == float
        or type(value) == int):
        return f"${value:,.2f}"
    
    return value


def get_cash(db, session) -> float:
    '''gets the cash from the user'''
    return float(db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0]['cash'])


def update_cash(db, session, new_amount) -> None:
    '''updates the amount of cash of the user'''
    db.execute('UPDATE users SET cash = ? WHERE id = ?', 
               new_amount,
               session['user_id'])    


def get_stocks_from_user_by_company(db, session, company) -> list:
    '''gets the stocks that the user has of a determined company'''
    query = db.execute('''SELECT shares FROM stocks
                              WHERE id = ?
                              AND stock = ?''',
                       session['user_id'],
                       company)
    
    return query


def put_in_the_history(db, session, stock, shares, price) -> None:
    '''puts the stock bought or sold into the history table'''
    
    db.execute('INSERT INTO history VALUES (?, ?, ?, ?, ?)',
                       session['user_id'],
                       stock, 
                       shares,
                       price,
                       datetime.today())
    
    
def update_stocks_number(db, session, shares, stock) -> None:
    '''updates the number of a determined stock'''
    
    if (shares == 0):
    
        db.execute('DELETE FROM stocks WHERE id = ? AND stock = ?',
                   session['user_id'],
                   stock)
    
    else:
        
        db.execute('UPDATE stocks SET shares = ? WHERE id = ? AND stock = ?',
                   shares,
                   session['user_id'],
                   stock)
