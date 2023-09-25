FROM ubuntu:23.04
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get install -y \
        autoconf bison flex gcc g++ libprotobuf-dev libnl-route-3-dev \
        libtool make pkg-config protobuf-compiler git && \
    rm -rf /var/lib/apt/lists/*
RUN git clone https://github.com/google/nsjail && \
    cd /nsjail && make && mv nsjail /bin/nsjail

WORKDIR /home/pwn
COPY vectors entrypoint.sh ./ 
COPY flag.txt ./

EXPOSE 4000/tcp
CMD /home/pwn/entrypoint.sh