import concurrent
from concurrent.futures import ThreadPoolExecutor

import numpy as np
import librosa as lr
import scipy
import os
from vocaloid_heardle_dl import dl_all

def _fft(audio1):
    y, sr = lr.load(audio1)
    X = scipy.fftpack.fft(y)
    X_mag1 = np.absolute(X)
    X_len = len(X_mag1)//2
    fft_data = X_mag1[0:X_len]
    return fft_data

def worker(path):
    return path, _fft(path)

fft_s = {}
with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
    futures = [executor.submit(worker, f'./tracks2/{file}') for file in os.listdir('tracks2')]
    for future in concurrent.futures.as_completed(futures):
        file, challenge = future.result()
        fft_s[file] = challenge


# split file into multiple parts with 3 second length 
# ffmpeg -i flag.mp3 -f segment -segment_time 3 -c copy flag_%03d.mp


dl_all()

# then trim all downloaded files to first three seconds
# find . -type f | xargs -i  sh -c 'ffmpeg -i {} -filter_complex atrim=end=3 {}.mono.mp3 && rm {}'


for chunk in os.listdir("."):
    if chunk.startswith("flag_"):
        chunk_fft = _fft(f'./{chunk}')

        vals = []
        for k, v in fft_s.items():
            err_mean = np.square(chunk_fft[:30000] - v[:30000]).mean()
            vals.append((k, err_mean))

        fname_min = min(vals, key=lambda t: t[1])[0]
        letter = fname_min.split("__")[0].split('/')[-1]
        letter = chr(int(letter))
        print(letter, end='')

