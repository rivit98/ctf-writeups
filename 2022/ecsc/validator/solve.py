import requests
import ed25519

seed = open("key.bin", "rb").read()
privKey = ed25519.SigningKey(seed)

msg = b'flag'
signature = privKey.sign(msg)

resp = requests.post('https://validator.ecsc22.hack.cert.pl/', json={
	"id": msg.decode(),
	"signature": list(signature)
})

print(resp.status_code)
print(resp.text)
