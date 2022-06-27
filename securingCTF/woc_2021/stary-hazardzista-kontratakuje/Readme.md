# Różdżka chaosu, Stary hazardzista kontratakuje, pwn

## Opis
"Starzec, co widział już dwa millenia, dwa stulecia i trzy dekady. Po niezliczonych rozgrywkach opracował niespotykany na skalę światową system gier liczbowych. Czy potrafisz z nim wygrać?

Starca możesz spotkać w podgrodziu."

## Rozwiązanie

Oryginalny kod zadania znajduje się [tutaj](./chal_orig.cpp). Tym razem musimy zdobyć flagę z makra `FLAG_HARD`. Pomysł bazuje na rozwiązaniu zadania "Stary hazardzista" - także wykorzystamy nadpisywanie kawałka flagi.

Całość opiera się na leakowaniu flagi bajt po bajcie. Ważną informacją jest, że funkcja scanf dodaje null byte na koniec naszego stringa co troche komplikuje sprawę.

Pomysł jest następujący:
- nadpisujemy częściowo flagę, która została użyta do seedowania generatora i pobieramy pierwszą liczbę od starca
- lokalnie brutujemy jeden znak flagi tak, żeby po zaseedowaniu generatora pierwsza liczba się zgadzała
- skracamy payload nadpisujący flagę (patrz pkt 1) o jeden znak i powtarzamy działanie

Przykład: (znak `_` oznacza null byte)

pierwsza iteracja:
```
 flaga na serwerze: WOC{FLAGANASERWERZE}_
 payload          : AAAAAAAAAAAAAAAAAA
 flaga do seeda   : AAAAAAAAAAAAAAAAAA_}_
 pierwsza liczba  : 136                ^
```

widzimy, że nasz payload nadpisał tylko część flagi, z której został policzony seed. Mając takie informacje możemy lokalnie zbrutować jeden znak, który za znakiem null byte (znak ten został oznaczony za pomocą znaku `^`). Aby to zrobić ustawiamy początek flagi na taki jak payload, następnie doklejamy null byte, dodajemy znak, który brutujemy, a na koniec doklejamy znaki, które już znamy (w pierwszej iteracji jeszcze nie ma takich znaków). Czyli dane dla lokalnego programu liczącego to: `AAAAAAAAAAAAAAAAAAAc_`  jeśli sprawdzany aktualnie jest znak `c`. Bierzemy pierwszą liczbę z generatora i porównujemy ją z tą z outputu z serwera. Jeśli są równe - znaleźliśmy znak. Po chwili powinniśmy otrzymać informację, że szukanym znakiem jest `}`

```
druga iteracja:
 flaga na serwerze: WOC{FLAGANASERWERZE}_
 payload          : AAAAAAAAAAAAAAAAA
 flaga do seeda   : AAAAAAAAAAAAAAAAA_E}_
 pierwsza liczba  : 531               ^
```

Analogicznie jak w poprzednim przypadku - do serwera wysyłamy ciąg znaków o jeden krótszy niż poprzednio, pobieramy pierwszą liczbę od starca i lokalnie brutujemy jeden znak. Dane dla lokalnego programu: `AAAAAAAAAAAAAAAAAAc}_` (klamra ponieważ znamy już jeden znak).

itd.

do lokalnego brutowania wykorzystałem program [chall.c](./chal.cpp) (przerobiony oryginalny kod zadania).

Skrypt rozwiązujący: [solve.py](./solve_hard.py)
Po dłuższej chwili dostajemy flagę: WOC{RADOMNUMB4R}
