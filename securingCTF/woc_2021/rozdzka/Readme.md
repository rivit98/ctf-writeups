# Różdżka chaosu, Różdżka?, mobile

## Opis
"A było już tak blisko... Przeklęta czarownica. Czy uda Ci się odblokować różdżkę?"

## Rozwiązanie

Zadanie jest dostępne po rozwiązaniu zadania 'Las'.
Otrzymujemy plik .apk, dekompilujemy go za pomocą Jadx (output został trochę oczyszczony, ponieważ było sporo plików)

Po krótkiej analizie zauważyłem, że w [tym](./mobile_source_from_JADX/sources/biz/securing/wandofchaos/BuildConfig.java) pliku jest klasa, która posiada dwa obiekty z metodami `toString()`, które nazywają się: `BABAJAGA_FLAG_1` oraz `BABAJAGA_FLAG_2`. Bez większego namysłu stworzyłem nowy projekt w środowisku IntelliJ IDEA, uruchomiłem zdekompilowany kod i ukazały się obie flagi (druga do zadania "Zaklęcie"):
`WOC{22F3ABBCEEA4F8101BAE65E491E6E1D68E26436916A5FAE0D8ED22F2808A2162}`
`WOC{47DFBDDD23AB81582127FA06BB1EE98489FAC017E2362B9D6E2620EE1FC6D20A}`

Kod programu: [Main.java](./Main.java)

Wygląda na to, że obiekty BABAJAGA_FLAG_* zawierały w jakiś sposób zobfuskowany kod, ale dekompilator (lub kompilator) go zoptymalizował i zinline'owal w jednego returna

