import os
from pathlib import Path
import requests
from bs4 import BeautifulSoup


COOKIE = '3fd54d59e0b418538b9188d551aa996d'
BASE_PATH = "../steemnova"
BASE_LINK = "https://uni1.cursednova.securing.pl/source.php?file="


def strip_orig_file(rel_p):
    fpath = Path('../steemnova') / rel_p
    try:
        with open(fpath, "rt", encoding='utf8') as f:
            cont = f.read()

        with open(fpath, "wt", encoding='utf8') as f:
            f.write(cont.strip())
    except:
        print(f"Cannot strip {fpath}")

if __name__ == '__main__':
    old_dir = os.getcwd()
    os.chdir(BASE_PATH)
    files_to_dl = []
    for root, subdirs, files in os.walk('.'):
        # print(root, subdirs, files)
        for f in files:
            p = Path(root) / f
            if p.suffix in {'.jpg', '.png', '.gif', '.css', '.mp3', '.txt', '.ico', '.swf'}: continue
            files_to_dl.append(p)

    os.chdir(old_dir)

    for f in files_to_dl:
        strip_orig_file(f)
        norm = str(f).replace("\\", "/")
        url = f'{BASE_LINK}{norm}'
        print(url)
        resp = requests.get(url, cookies={'2Moons': COOKIE})
        if resp.status_code == 200:
            os.makedirs(f.parent.absolute(), exist_ok=True)
            with open(f, "wt", encoding='utf8') as fout:
                bs = BeautifulSoup(resp.text.replace('&nbsp;', ' '), 'html.parser')
                for br in bs('br'):
                    br.replace_with('\n')

                cd = list(bs('code'))
                if cd:
                    une = cd[0].getText().strip()
                    fout.write(une)
                else:
                    alltext = bs.getText()
                    if 'path forbidden' not in alltext and 'file forbidden' not in alltext:
                        print(f, "bad")
                        fout.write(bs.getText())
        else:
            print(f'{resp.status_code} - {f}')