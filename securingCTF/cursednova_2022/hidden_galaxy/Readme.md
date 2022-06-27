# CursedNova, Hidden Universe, web

## Description
Are we really alone in time and space? Is it only Nekla? Try to discover hidden universes.

## Solution

Let's inspect the login page with chrome dev tools:
[devtools](./img/devtools.png)

As we can see - somebody is hiding something ;) this is a good sign.

Having the sources downloaded we can look up how the login page handles the data from the login form. Logic is located in: `includes\pages\login\ShowLoginPage.class.php` and using the diff tool we see the additional `if`:

```
        $uni = HTTP::_GP('uni', '');

        if ($uni == $LNG['SECRET_UNIVERSE']) {
            HTTP::redirectTo('index.php?code=' . $LNG['W2_HIDDEN_UNIVERSE']);
        }
```

All clear now, lets try to find the hidden universe. Script used: [solve.py](./solve.py)

The bonus knowledge is that they are storing the `$LNG` global for storing flags, so grepping by `$LNG['W` shows 7 matches, which simplifies some things :)

Flag: `CURSEDNOVA{I've_a_feeling_we're_not_in_Kansas_anymore_wua7Rua1}`