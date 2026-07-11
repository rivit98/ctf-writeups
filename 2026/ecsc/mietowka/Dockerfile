FROM ubuntu:24.04 AS base

RUN apt update -y

FROM base AS builder

RUN apt install -y binutils build-essential cmake e2fsprogs gcc git nasm

WORKDIR /build
RUN git clone https://github.com/mentos-team/MentOS

WORKDIR /build/MentOS

# newest commit as I'm writing this
RUN git checkout 82f43144ffab3638e6207539b9c4c1425e51c1ab

COPY kernel.diff .
COPY userspace.diff .
COPY filesystem.diff .

# This diff file adds functionality necessary to run the challenge remotely and increases the keyboard buffer size (to 1024).
# It *shouldn't* introduce any new vulnerabilities...
RUN git apply kernel.diff

# This diff file adds support for longer commands in the shell and adds a program that might be useful for uploading your exploit.
RUN git apply userspace.diff

RUN mkdir build && cd build && cmake .. && make

RUN git apply filesystem.diff
COPY flag.txt filesystem/root/flag.txt
RUN chown -R 0:0 filesystem
RUN chown -R 1000:1000 filesystem/home/user
RUN chmod -R 755 filesystem/bin
RUN chmod -R 644 filesystem/etc && chmod 755 filesystem/etc
RUN chmod -R 600 filesystem/home/user && chmod 700 filesystem/home/user
RUN chmod -R 600 filesystem/root && chmod 700 filesystem/root
RUN chmod -R 644 filesystem/usr && chmod 755 filesystem/usr && chmod 755 filesystem/usr/share && chmod 755 filesystem/usr/share/man

RUN cd build && make filesystem

WORKDIR /output
RUN cp /build/MentOS/build/rootfs.img .
RUN cp /build/MentOS/build/mentos/bootloader.bin .
RUN cp /build/MentOS/build/mentos/kernel.bin .

FROM base

RUN apt install -y coreutils qemu-system-x86 socat

WORKDIR /app

COPY --from=builder /output .
COPY entrypoint.sh .
COPY run.sh .

RUN chmod +x entrypoint.sh
RUN chmod +x run.sh

CMD ["./entrypoint.sh"]
