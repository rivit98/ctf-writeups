# CursedNova, Welcome to CursedNova, web

## Description
Welcome to CursedNova! Please register - and don't forget to read the rules!

## Solution

Visit: https://uni1.cursednova.securing.pl/index.php?page=rules and get the flag.

Flag: `CURSEDNOVA{The_game_is_on!_Douy3bah}`

Let's also write scrapper which allows us to obtain all of the files from the remote (via source browser), so we can easily compare them later.
Check [dumper.py](./dumper.py). Tool is really hacky & simple - it gets file paths from the local git repo [github](https://github.com/steemnova/steemnova/tree/d6dd148) and tries to download them.
It also strips the line endings, whitespaces etc, so it is easier to use diff tools (for example WinMerge).