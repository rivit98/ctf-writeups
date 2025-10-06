
from ubuntu@sha256:fecdb5b9bf8874108b4fc23fac669b10968e54c450382b20d7db92565e7655ed AS app

FROM pwn.red/jail

COPY --from=app / /srv

COPY main /srv/app/run
COPY flag.txt libc.so.6* ld-linux-x86-64.so.2* /srv/app/

RUN chmod +x /srv/app/run


