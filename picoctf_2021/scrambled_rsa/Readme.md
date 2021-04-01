# PicoCTF 2021, Scrambled RSA, crypto

## Description
Hmmm I wonder if you have learned your lesson... Let's see if you understand RSA and how the encryption works.

## Solution

Connect to the server and we are given: ciphertext, e, n. Ciphertext is really huge number, n is really small compared to ciphertext. Okay, so flag is probably encrypted letter by letter and ciphertexts of every letters was concatenated. We can encrypt whatever we want, so I tried various strings: 'a', 'b', 'aa', 'ab' and repeat it multiple times. I figured out that sometimes output from 'aa' vary, but why? Well, they do ciphering based on position of letter in string, so if I encode 'a' and 'aa' the ciphertext of 'aa' contains ciphertext of 'a'. So now I started writing script which calculating flag letter by letter.

To calculate e.g. third letter of flag we encrypt all strings of length two which looked like this 'xx' where x is letter or digit (or _, {, }) and next we do the same but for strings of length 3. Now we can subtract ciphertexts. If we subtract ciphertext of 'aa' from 'aaa' we got ciphertext of letter 'a' on third position! Now we can do this for every character possible and check if result is in ciphertext of flag (from beginning of challenge). After some failures I figured out that subtracting texts might be wrong (one of string can overlap too much on next), so I wrote recursion-based error correction. Script was running for ~4 minutes and I got disconnect :( Since we can calculate letters independently I decided to add some caching of already guessed letters.


Solve: [rsa.py](./rsa.py)

Note: there is [rsa2.py](./rsa2.py) but it used very ineffective method and if we got disconnected then we have to calculate everything from the beginning.
