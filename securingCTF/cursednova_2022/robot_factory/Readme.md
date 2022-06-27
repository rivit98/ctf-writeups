# CursedNova, Robot factory, web 

## Description

My grandpa always told me to never trust robots. You never know what's inside their silicon brains. However in these harsh times of need, we would gladly accept any helping hand - even if it's made out of steel and copper wire. Unfortunately building the Robot Factory needs an additional authorization key. Can you help us find the key and build the factory?

## Solution

Viewing the source of the "Buildings" page reveals some obfuscated javascript code:

```
function _0x3063() {
    const _0x25506c = [
        'In order to build a robot factory you need to prove that you are not a robot!',
        '12xxXNIR',
        '6473430RqGldN',
        '3374RjFsXE',
        '576e09d1183e3df45ded91f0a112c48b',
        '9e8692953cca7e329e8198ae0247ab48',
        '1mXBvqr',
        '2337848ukbUJl',
        '4625060rmtGKW',
        '9eQvFUA',
        '3a11129c3467b1bcf46522b8e2ab3328',
        'Surely only humanoids are able to crack this complex code.',
        '540695IlwGhM',
        'length',
        '46704Msmrhn',
        'c2f3f489a00553e7a01d369c103c7251',
        'a8655da06c5080d3f1eb6af7b514e309',
        '7fa3b767c460b54a2be4d49030b349c7',
        '42552ddmaIa',
        '8cee5050eeb7c783e8bfaa73003ced3a',
        '33d88f7fc055a0e698152ac91a71ddef',
        '6756PBjLAs',
        'c83f077534a373cb63a0a91969fdce54',
        'Beep Beep... Boop Boop'
    ];
    _0x3063 = function () {
        return _0x25506c;
    };
    return _0x3063();
}
function _0x3fca(_0x4df076, _0x30ca91) {
    const _0x3063f7 = _0x3063();
    _0x3fca = function (_0x3fca64, _0x147873) {
        _0x3fca64 = _0x3fca64 - 0x182;
        let _0x482b18 = _0x3063f7[_0x3fca64];
        return _0x482b18;
    };
    return _0x3fca(_0x4df076, _0x30ca91);
}
(function (_0x2362b0, _0x2a69b1) {
    const _0x4a4ed6 = _0x3fca;
    const _0x43917e = _0x2362b0();
    while (!![]) {
        try {
            const _0xcffc67 = -parseInt(_0x4a4ed6(0x185)) / 0x1 * (parseInt(_0x4a4ed6(0x191)) / 0x2) + parseInt(_0x4a4ed6(0x18d)) / 0x3 + -parseInt(_0x4a4ed6(0x198)) / 0x4 * (-parseInt(_0x4a4ed6(0x18b)) / 0x5) + -parseInt(_0x4a4ed6(0x194)) / 0x6 * (-parseInt(_0x4a4ed6(0x182)) / 0x7) + parseInt(_0x4a4ed6(0x186)) / 0x8 * (-parseInt(_0x4a4ed6(0x188)) / 0x9) + -parseInt(_0x4a4ed6(0x199)) / 0xa + parseInt(_0x4a4ed6(0x187)) / 0xb;
            if (_0xcffc67 === _0x2a69b1) {
                break;
            } else {
                _0x43917e['push'](_0x43917e['shift']());
            }
        } catch (_0x4c0121) {
            _0x43917e['push'](_0x43917e['shift']());
        }
    }
}(_0x3063, 0x53937));
function A() {
    const _0x25f525 = _0x3fca;
    x = [
        _0x25f525(0x195),
        _0x25f525(0x193),
        '3605c251087b88216c9bca890e07ad9c',
        'ad7532d5b3860a408fbe01f9455dca36',
        _0x25f525(0x183),
        _0x25f525(0x197),
        _0x25f525(0x190),
        _0x25f525(0x18f),
        'f0b9503d19c4340380b3105a1948bbf0',
        _0x25f525(0x189),
        _0x25f525(0x192),
        '4e67af4d9f8ced24cc2feead828efbf6',
        _0x25f525(0x196),
        _0x25f525(0x18a),
        '5c855e094bdf284e55e9d16627ddd64b',
        _0x25f525(0x18e),
        _0x25f525(0x184)
    ];
    key = [
        0x3,
        0xc,
        0xe,
        0xf,
        0xd,
        0x1,
        0xb,
        0x10,
        0xa,
        0x7,
        0x4,
        0x5,
        0x0,
        0x2,
        0x9,
        0x6,
        0x8
    ];
    let _0x4f99d3 = [];
    for (var _0x54629b = 0x0; _0x54629b < key[_0x25f525(0x18c)]; _0x54629b++) {
        _0x4f99d3[key[_0x54629b]] = x[_0x54629b];
    }
}
```

After trying invocation of `A` function and printing the contents of a `_0x4f99d3` array we see this:

```
[
  'Beep Beep... Boop Boop',
  'In order to build a robot factory you need to prove that you are not a robot!',
  'Surely only humanoids are able to crack this complex code.',
  'c83f077534a373cb63a0a91969fdce54',
  '8cee5050eeb7c783e8bfaa73003ced3a',
  '4e67af4d9f8ced24cc2feead828efbf6',
  'c2f3f489a00553e7a01d369c103c7251',
  '3a11129c3467b1bcf46522b8e2ab3328',
  '9e8692953cca7e329e8198ae0247ab48',
  '5c855e094bdf284e55e9d16627ddd64b',
  'f0b9503d19c4340380b3105a1948bbf0',
  '7fa3b767c460b54a2be4d49030b349c7',
  '33d88f7fc055a0e698152ac91a71ddef',
  '576e09d1183e3df45ded91f0a112c48b',
  '3605c251087b88216c9bca890e07ad9c',
  'ad7532d5b3860a408fbe01f9455dca36',
  'a8655da06c5080d3f1eb6af7b514e309'
]
```

First thougt - md5 hashes. Using [crackstation.net](https://crackstation.net) we are able to recover the plaintext:

[crackstation](./img/crackstation.png)

Flag: `CURSEDNOVA{I_am_not_a_robot}`