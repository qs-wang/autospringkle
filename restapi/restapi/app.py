#!/usr/bin/env python3

import logging
import os


from flask import Flask, request
from flask_api import FlaskAPI
from restapi.rf import sendcode

app = FlaskAPI(__name__)


@app.route('/', methods=["GET"])
def api_root():
    return {
        "url": request.url + "home/( 1111(on) | 9999 (off) )/"
    }


@app.route('/home/<code>', methods=["GET", "POST"])
def api_leds_control(code):
    headers = request.headers
    auth = headers.get("X-Api-Key")
    expect_key = os.environ.get('HOMEAUTO_API_KEY')
    if auth == expect_key and request.method == "POST":
        sendcode(int(code))
    else:
        print('Not authorized')

    return code


if __name__ == "__main__":
    app.run(ssl_context=('cert.pem', 'key.pem'))
