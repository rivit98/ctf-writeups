# CursedNova, Disabled, web 

## Description

Excuse me Sir, our workers say they have no clue how to build the Metal Mine. Can you help them with that task?

## Solution

This one is simple. The "Build" link is greyed out. After checking the page source, we notice that button has wrong type. The type should be set to `submit` (because button is in the `form`) instead of just `button`.

[button](./img/button.png)

After changing type to `submit` the flag is visible.


Flag: `CURSEDNOVA{Do_not_trust_frontend_security_puch8Air}`