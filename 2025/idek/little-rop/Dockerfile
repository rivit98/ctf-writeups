FROM ubuntu:22.04@sha256:1ec65b2719518e27d4d25f104d93f9fac60dc437f81452302406825c46fcc9cb

RUN apt update && apt install -y socat

RUN /usr/sbin/useradd --no-create-home -u 1001 user

COPY flag.txt /
COPY chall /home/user/chall

CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:\"/home/user/chall\""]