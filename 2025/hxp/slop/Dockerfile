FROM debian:trixie-20251208-slim@sha256:e711a7b30ec1261130d0a121050b4ed81d7fb28aeabcf4ea0c7876d4e9f5aca2

RUN useradd --shell /bin/bash --no-create-home ctf

COPY --chown=root:1337 --chmod=2555 readflag /readflag
COPY --chown=root:1337 --chmod=0040 flag.txt /flag.txt
COPY --chown=root:root --chmod=0005 slop /slop

RUN find / -ignore_readdir_race -path /sys -prune -o -type f \( -perm -4000 -o -perm -2000 \) -not \( -wholename /readflag \) -exec rm -f {} \;
USER ctf
RUN ! find / -writable -or -user $(id -un) -or -group $(id -Gn|sed -e 's/ / -or -group /g') 2> /dev/null | grep -Ev -m 1 '^(/dev/|/run/|/proc/|/sys/|/tmp|/var/tmp|/var/lock)'

EXPOSE 1024
ENTRYPOINT /slop
