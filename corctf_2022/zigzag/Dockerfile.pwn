FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive 
ENV DISPLAY=192.168.56.1:0

RUN apt-get update -y && apt-get install -y --no-install-recommends python3 python3-pip python3-setuptools git gcc python3-dev libpython3.8-dev python3.8-distutils curl wget build-essential texinfo libgmp-dev libreadline-dev gdb terminator

RUN rm /usr/bin/python3 && ln -s /usr/bin/python3.8 /usr/bin/python3
RUN alias python=python3
RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && python3.8 get-pip.py

RUN pip install -U pip
RUN pip install wheel pwntools

RUN git clone https://github.com/pwndbg/pwndbg && cd pwndbg && ./setup.sh
RUN apt-get install -y --no-install-recommends gdbserver
