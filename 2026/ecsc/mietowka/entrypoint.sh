#!/bin/sh

socat tcp-listen:3737,fork,reuseaddr exec:./run.sh
