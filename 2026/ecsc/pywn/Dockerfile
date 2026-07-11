FROM python:3.14.5-slim-trixie@sha256:af79f947dee1c929919b0488d20db7200d8737e00f68ee4abeef1fcf1fe05939 AS builder

WORKDIR /build

COPY pywn .

RUN pip install -U pip && pip install build
RUN python3 -m build

WORKDIR /output
RUN cp -r /build/dist .

FROM python:3.14.5-slim-trixie@sha256:af79f947dee1c929919b0488d20db7200d8737e00f68ee4abeef1fcf1fe05939 AS base

WORKDIR /app

COPY challenge.py run flag.txt .
COPY --from=builder /output/dist/pywn-0.1-cp314-cp314-linux_x86_64.whl .
RUN pip install pywn-0.1-cp314-cp314-linux_x86_64.whl

FROM pwn.red/jail

COPY --from=base / /srv
