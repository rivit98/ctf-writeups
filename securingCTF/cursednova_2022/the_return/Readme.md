# CursedNova, The return, web 

## Description

You didn't have to wait long for Twardowski's ships to appear on your radar. When he got off the spacecraft, you could tell he was incredibly happy.

"You did it! You have beat the devil!", he shouted as soon as he saw you.

"No problem, Twardowski! He fooled me too... And hundreds of other innocent people", you said. "Now tell me... Is there any way to go back to Earth? I miss my family, especially my mom's pierogis".

"How do you think? I had 100 years to come up with a way to return to Earth, and there's nothing my heart desires more", said Twardowski. "Let's go back to my ship".

## Solution

In this challenge we got the jpg image

[together](./img/together.jpg)

Using exiftool we can see some interesting data:

```
XP Comment                      : eJwtxU0oQ3EAAPD/X7a/t80UzUctWvNQ8pHGyl+SA4flwOwgq83jgINMMyy01PNRwkGRJAcHRS0c3lMje8rXx+s5LLlMzddmUSvtjbbswO/y0zs97mI1SFWe5Mc3wZ/y/yXGAqVM7O7cfqQ5/9fC0zlLs6KVKHKGyTDj7bn/lQy9eDvMVRO1Z/EWrsn9LTe/DwjqH17jCeVZ6vq0yJ6933VtQ0hDG9o+TaHV3j1Dq8+OY9GKW9fHzHTwYvHtiNq5G362tXPsVBDXKCiG0B0eJ5aqUzYmddoVUyDiJ7PmydHcA2ak4bSkMeFT7brG1uZerTf8w+XybI60EhKDAMkhgIXSCIKZxozAevNW6ZU+itMcuGxcUCn6ZTBWb0kHIAmwjWb0
XP Subject                      : Password: 7W4rD0W5K1
```

Comment is base64 encoded, after decoding it we got a binary file which is: `zlib compressed data`. Unpack it with: `zlib-flate -uncompress <sth.zlib > out.7z` and unpack the 7zip archive using the password from the exiftool.

Flag: `CURSEDNOVA{Home_is_where_the_heart_is}`