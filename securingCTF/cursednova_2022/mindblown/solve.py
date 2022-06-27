import requests
from bs4 import BeautifulSoup
import re

COOKIE = '0196fadeaada0c12fcabba9fbf9bbb65'

def main():
    resp = requests.get('https://uni1.cursednova.securing.pl/game.php?page=messages&category=1', cookies={'2Moons': COOKIE})
    bs = BeautifulSoup(resp.text, 'html.parser')
    for br in bs('td'):
        tdtext = str(br).replace('&gt;', '>').replace('&lt;', '<')
        if len(tdtext) > 200:
            matches = re.findall(r'<!-- (.*?) -->', tdtext)
            if matches:
                print(''.join(matches))


if __name__ == '__main__':
    main()