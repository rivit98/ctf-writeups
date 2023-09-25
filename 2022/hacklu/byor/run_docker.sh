#!/bin/bash
docker build -t byor:latest .
docker run --rm -p 4444:4444 -i -t byor:latest $@
