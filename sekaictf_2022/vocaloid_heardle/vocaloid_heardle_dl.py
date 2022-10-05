import requests
import random
import string

resources = requests.get("https://sekai-world.github.io/sekai-master-db-diff/musicVocals.json").json()

def get_resource(mid):
    return random.choice([i for i in resources if i["musicId"] == mid])["assetbundleName"]

def get_resources(mid):
    return [i for i in resources if i["musicId"] == mid]

def download(mid):
    resources = get_resources(mid)
    resources = list(map(lambda res: res["assetbundleName"], resources))
    print(mid, resources)
    for resource in resources:
        r = requests.get(f"https://storage.sekai.best/sekai-assets/music/short/{resource}_rip/{resource}_short.mp3")
        filename = f"tracks/{mid}__{resource}.mp3"
        print(filename)
        with open(filename, "wb") as f:
            f.write(r.content)


def dl_all():
    for i in map(ord, string.printable):
        download(i)
