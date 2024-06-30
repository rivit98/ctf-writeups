FROM patryk4815/nsjail:23.04
EXPOSE 3000
WORKDIR /pwn

RUN apt-get update -y && apt-get install -y --no-install-recommends python3 python3-pip git gcc curl wget build-essential texinfo gdb terminator python-is-python3 gdbserver
RUN pip install --break-system-packages pwntools

# RUN git clone https://github.com/pwndbg/pwndbg && cd pwndbg && ./setup.sh

RUN wget https://github.com/pwndbg/pwndbg/releases/download/2024.02.14/pwndbg_2024.02.14_amd64.deb && apt install ./pwndbg_2024.02.14_amd64.deb

ENV LC_CTYPE=C.UTF-8
ENV DISPLAY=:0

COPY chall ./
COPY entrypoint.sh ./
# CMD /pwn/entrypoint.sh

