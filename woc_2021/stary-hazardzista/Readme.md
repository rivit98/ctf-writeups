# Różdżka chaosu, Stary hazardzista, pwn

## Opis
"Starzec, co widział już dwa millenia, dwa stulecia i trzy dekady. Po niezliczonych rozgrywkach opracował niespotykany na skalę światową system gier liczbowych. Czy potrafisz z nim wygrać?

Starca możesz spotkać w podgrodziu."

## Rozwiązanie

Oryginalny kod zadania znajduje się [tutaj](./chal.cpp). Jak widać musimy zgadnąć 999 liczb pod rząd, aby dostać flagę.

Widzimy, że na początku programu alokowane są dwa obszary na stercie (będą do siebie przylegać - to ważne). Z tych danych będzie obliczany seed dla generatora liczb losowych. Jeśli znalibyśmy seed to możemy łatwo wygenerować sobie kolejne liczby. W tym przypadku wystarczy, że podamy odpowiednio długą naszą nazwę (zmienna `name`), to nadpiszemy zmienną `flag`, a skoro seed jest obliczany ze złożenia dwóch wartości `name` oraz `flag` to będziemy go znać. Należy pamiętać, że chunki na heapie będą miały 32 bajty (0x20), czyli potrzebujemy łącznie 64 bajty, żeby nadpisać oba chunki.

W pliku [numbers](./numbers.txt) zostały wygenerowane kolejne liczby dla seeda 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB' (aby je otrzymać wystarczyło odpowiednio zmodyfikować oryginalny plik ze źródłem do zadania).

Teraz wystarczy tylko podać starcowi kolejne liczby i zgarnąć flagę.

![flag](./img/flag.png)


