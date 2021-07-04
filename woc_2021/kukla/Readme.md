# Różdżka chaosu, Kukła, web

## Opis
"Dobrze byłoby z kimś potrenować. Kto wie, jakie potworności czekają na Ciebie w lesie... Udaj się do Areny Walk i porozmawiaj z Wojownikiem."

## Rozwiązanie

Interesujący fragment kodu źródłowego skrzynki znajduje się w pliku [battle.php](./battle.php). W zadaniu chodzi o zgadnięcie losowej liczby i przesłanie jej w zmienneg `fight`.
Po krótkiej analizie widzimy, że możemy czytać dowolne maile za pośrednictwem tego kawałka kodu:
```php
		srand(hexdec(substr(md5($randomString + substr(time(), 0, 5)), 0, 8)));
```
a konkretniej:
```php
$randomString + substr(time(), 0, 5)
```

Generator liczb pseudolosowych jest seedowany połączeniem wartości `$randomString` oraz pięciu pierwszych cyfr z czasu, który zwraca funkcja `time`. Został użyty tutaj operator `+`, który skonwertuje obie wartości na liczby całkowite. Pierwsze pięć cyfr z czasu nie zmienia się często, więc możemy założyć, że na czas rozwiązywania zadania jest stałe. Natomiast `$randomString` będzie równe zero, gdy funkcja `RandomString` jako pierwszy znak wylosuje nie-literę (ponieważ taki string zostanie zrzutowany na typ całkowitoliczbowy).

W takim wypadku wystarczy lokalnie sprawdzić jaka wartość zostanie wygenerowana po zeseedowaniu generatora.

```php
     srand(hexdec(substr(md5($randomString + substr(time(), 0, 5)), 0, 8)));  
     $win = rand();
```
i jest to (na czas pisania tego writeupa): 448119532

Wysyłamy następujący request [https://vallheru.rozdzka.securing.pl/battle.php?action=dummy&fight=448119532](https://vallheru.rozdzka.securing.pl/battle.php?action=dummy&fight=448119532) i otrzymujemy flagę (czasem trzeba wysłać kilka razy z uwagi na losową wartosć pierwszego znaku, wspomnianą wcześniej):

![solve](./solve.png)

