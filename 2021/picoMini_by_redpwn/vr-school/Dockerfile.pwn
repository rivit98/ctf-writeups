FROM ubuntu@sha256:2aeed98f2fa91c365730dc5d70d18e95e8d53ad4f1bbf4269c3bb625060383f0
ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update -y && apt-get install -y --no-install-recommends lib32stdc++6 python3.8 python3-pip python3-setuptools git gcc python3.8-dev libpython3.8-dev python3.8-distutils curl wget build-essential texinfo libgmp-dev libreadline-dev gdb terminator

RUN rm /usr/bin/python3 && ln -s /usr/bin/python3.8 /usr/bin/python3
RUN alias python=python3
RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && python3.8 get-pip.py

RUN wget https://ftp.gnu.org/gnu/gdb/gdb-11.2.tar.gz -O gdb-11.2.tar.gz  \
    && tar -xvzf gdb-11.2.tar.gz  \
    && cd gdb-11.2 \
    && ./configure --prefix=/usr --with-system-readline --with-python=/usr/bin/python3  \
    && make -j4 CXXFLAGS="-static-libstdc++" \
    && make install \
    && gdb --version \
    && cd .. \
    && rm -r gdb-11.2 gdb-11.2.tar.gz

RUN pip install -U pip
RUN pip install wheel pwntools

RUN git clone https://github.com/pwndbg/pwndbg && cd pwndbg && ./setup.sh

ENV DISPLAY=192.168.56.1:0

