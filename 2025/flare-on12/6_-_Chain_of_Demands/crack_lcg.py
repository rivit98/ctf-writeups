from math import gcd
from functools import reduce



def modinv(b, n):
    return pow(b, -1, n)

def crack_unknown_increment(states, modulus, multiplier):
    increment = (states[1] - states[0]*multiplier) % modulus
    return modulus, multiplier, increment

def crack_unknown_multiplier(states, modulus):
    multiplier = (states[2] - states[1]) * modinv(states[1] - states[0], modulus) % modulus
    return crack_unknown_increment(states, modulus, multiplier)

def crack_unknown_modulus(states):
    diffs = [s1 - s0 for s0, s1 in zip(states, states[1:])]
    zeroes = [t2*t0 - t1*t1 for t0, t1, t2 in zip(diffs, diffs[1:], diffs[2:])]
    modulus = abs(reduce(gcd, zeroes))
    return crack_unknown_multiplier(states, modulus)


class prng_lcg:
    m = 67192040330448629411569469148996452347135994600540722067180373767878044185647  # the "multiplier"
    c = 99227336246447563326081778635314136420514626764135112597502806801041930961679  # the "increment"
    n = 70162817795225084397164488661004836433247754877528881959579355413849190882383  # the "modulus"

    def __init__(self):
        self.state = 33997266682902850140225272282449387868635715365752160122430153597255539852627  # the "seed"

    def next(self):
        self.state = (self.state * self.m + self.c) % self.n
        return self.state
    

if __name__ == "__main__":
    lcg = prng_lcg()
    vals = []
    for _ in range(6):
        vals.append(lcg.next())
        print(vals[-1])
    print(crack_unknown_modulus(vals))


    print(crack_unknown_modulus([72967016216206426977511399018380411256993151454761051136963936354667101207529, 49670218548812619526153633222605091541916798863041459174610474909967699929824, 71280768003266775309606950462778030896956536610993788270598595159221463714935, 52374492464889938543708223275193226150102478572181009159069287723157087096395, 46151066309228226342793435233510111804521449597151473094879900544455543844821, 27616895455297410644582736481740143600211650471053558274523739523026009484149, 20017674779830364175685710279350076931283727675441675047445679766035806574277]
                                ))