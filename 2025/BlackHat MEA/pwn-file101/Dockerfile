FROM ubuntu:24.04@sha256:4f1db91d9560cf107b5832c0761364ec64f46777aa4ec637cca3008f287c975e AS base
WORKDIR /app
COPY --chmod=555 chall2 run
RUN echo "FLAG{*** REDACTED ***}" > /flag.txt
RUN mv /flag.txt /flag-$(md5sum /flag.txt | awk '{print $1}').txt

FROM pwn.red/jail
COPY --from=base / /srv
ENV JAIL_TIME=120 JAIL_CPU=100 JAIL_MEM=10M
