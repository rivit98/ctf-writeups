# Różdżka chaosu, Subskrybcja, web

## Opis
"Ciekawe, co słychać w lokalnej gazecie?"

## Rozwiązanie

Za pomocą mechanizmu podglądania źródła strony sprawdzamy plik `newspaper.php`.
Interesujący nas fragment znajduje się w pliku [newspaper.php](./newspaper.php).

```php
    if(md5($secretCode) == "0e938153791264385292992237641232") {
        $subscription = True;
    }
```

klasyka CTF'ów - PHP i operator '==' (loose comparison). Wystarczy znaleźć ciąg znaków, który po zahaszowaniu algorytmem MD5 da ciąg znaków zaczynający się od `0e`, wtedy obie wartości zostaną skonwertowane na liczby - w tym przypadku `0` i warunek będzie spełniony.

Ciągiem takim jest np. `s878926199a`, wystarczy go ustawić jako wartość ciasteczka o kluczu `subscription`.

![solve](./solve.png)
