#!/bin/bash

mkdir -p /sys/fs/cgroup/{cpu,memory,pids}/NSJAIL

echo "flag" > /pwn/flag

# 10 minute time limit
exec nsjail \
    --mode l \
    --port 3000 \
    --user 65534:65534 \
    --group 65534:65534 \
    --chroot / \
    --cwd /pwn \
    --time_limit 600 \
    -T /tmp \
    -E LC_ALL \
    -- /pwn/chall
