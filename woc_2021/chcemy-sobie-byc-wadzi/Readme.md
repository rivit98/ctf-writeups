# Różdżka chaosu, Chcemy być sobie wadzi?, misc

## Opis
"Czasami warto udać się do Biblioteki i poczytać poezję."

## Rozwiązanie

Udajemy się do biblioteki i sprawdzamy jedyny wpis, który tam jest - wiersz Jana Kochanowskiego - Pieśni, Księgi pierwsze: Pieśń IX. Na pierwszy rzut oka tekst ([given](./given.txt)) jest okej, ale gdy porównamy go z oryginałem ([oryginał](./original.txt)) okazuje się, że w każdym wierszu występuje zmiana (lub usunięcie) jednego słowa.

Pierwszy pomysł - wzięcie każdego indeksu zmienionego słowa, złączenie razem i próby odkodowania (np. ROT, szyfr afiniczny itp.).

Niestety pomimo wielu spędzonych godzin, nie udało się rozwiązać zadania. Poprawnym rozwiązaniem było wzięcie długości zmienionych słów, złączenie ich i zdekodowanie jako ascii. Skrypt rozwiązujący: [solve.py](./solve.py)
