FROM ubuntu:25.04

RUN apt update
RUN apt install -y \
    socat

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd
WORKDIR /home/ctf
USER ctf
COPY ./main_no_flag /home/ctf/main


EXPOSE 32100
ENTRYPOINT socat tcp-l:32100,fork,reuseaddr exec:'./main' && /bin/bash