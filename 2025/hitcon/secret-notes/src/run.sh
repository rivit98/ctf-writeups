#!/bin/bash

set -e

cd "$(dirname ${BASH_SOURCE[0]})"

ulimit -m 8192
ulimit -d 131072

exec ./chal
