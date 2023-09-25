import os
import hashlib

from flask import Flask, session, request, render_template, redirect
from werkzeug.exceptions import Forbidden

app = Flask(__name__)
# TODO change when deploying to production
app.config['SECRET_KEY'] = b"\xCC" * 16


@app.route('/login', methods=['POST'])
def route_login():
    session['user'] = 'admin'
    # session['user'] = None
    pwd_hash = hashlib.sha256(request.form["password"].encode('utf-8')).hexdigest()

    hs = {
        "admin": "010c141e8a863d7a54baad18f3c91bae812e485fd3c8ace3f4da25be1bdcf79d",
        "user": "04f8996da763b7a969b1028ee3007569eaf3a635486ddab211d512c85b9df8fb"
    }

    if hs.get(request.form["user"], 'x') == pwd_hash:
        session['user'] = request.form["user"]

    #set session cookie on challenge login page 

    return redirect('/user')


@app.route('/user')
def route_user():
    if not session.get('user'):
        raise Forbidden('Not authenticated.')

    with open('flag.txt') as f:
        flag = f.read().strip()

    return render_template('user.html', user=session['user'], flag=flag)


@app.route('/')
def route_main():
    return render_template('index.html')

app.run()