#!/bin/sh
nohup sudo -E gunicorn  --certfile ../certs/cert.pem --keyfile ../certs/key.pem -b 0.0.0.0:8001 app:app >> homeautomation.log &
