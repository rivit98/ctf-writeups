# CursedNova, Communication Breakdown, network

## Description

"I can't do it anymore", thought Twardowski. "Being a prisoner is one thing, I can handle being alone. But these attacks... I don't deserve this. I'm still suffering from a stupid mistake I made two centuries ago..."

## Solution

We got the .pcap file with FTP communication, we extract the flag.zip file, but it is password protected, but there is no password in the pcap file.
So let's bruteforce it using `fcrackzip` (or hashcat) with `rockyou.txt` dictionary. After a while we got the password which is `godzilla` and we are able to unpack the zip file.

Flag: `CURSEDNOVA{FtP_N0t_s0_s4f3_oops}`