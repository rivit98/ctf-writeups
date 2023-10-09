FROM ubuntu:22.04@sha256:b492494d8e0113c4ad3fe4528a4b5ff89faa5331f7d52c5c138196f69ce176a6 AS base
WORKDIR /app
RUN  echo "FLAG{*** REDACTED ***}" > /flag.txt
RUN  mv /flag.txt /flag-$(md5sum /flag.txt | awk '{print $1}').txt
RUN apt-get update -y && apt-get install -y --no-install-recommends python3 python3-pip git gcc curl wget build-essential texinfo gdb terminator
RUN alias python=python3
COPY memstream run

RUN pip install pwntools

RUN git clone https://github.com/pwndbg/pwndbg && cd pwndbg && ./setup.sh

ENV LC_CTYPE=C.UTF-8
ENV DISPLAY=:0

# FROM pwn.red/jail
# COPY --from=base / /srv
# ENV JAIL_TIME=180 JAIL_CPU=500 JAIL_MEM=10M
