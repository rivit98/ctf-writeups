data = open("./yacm", "rb").read()
to_replace = open("./to_patch", "rb").read().strip()
replace_with = open("./replace_with", "rb").read().strip()

if len(replace_with) > len(to_replace):
    print("payload too long")
    exit(1)

replace_with += (len(to_replace) - len(replace_with)) * b' '

with open("./yacm_patched", "wb") as fout:
    print(data.find(to_replace))
    fout.write(data.replace(to_replace, replace_with))

import os
os.system("cp ./yacm_patched '/home/rivit/VirtualBox VMs/shared/'")
