FROM ubuntu@sha256:d86db849e59626d94f768c679aba441163c996caf7a3426f44924d0239ffe03f AS base

FROM pwn.red/jail
COPY --from=base / /srv

COPY ./home/ /srv/app/

ENV JAIL_TIME=120
