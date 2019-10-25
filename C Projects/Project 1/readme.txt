Tema 1 - Programarea calculatoarelor - seria CC

Nume: Stratila Vladislav
Grupa: 312CC

Task 1
    Aici, am o variabila de tip char* numita result, care va reprezenta sirul
codificat. Parcurg sirul dat ca parametru de intrare (str): daca am dat de un
spatiu, adaug 0 in result, daca am dat de 1, apelez tolower ca sa fac caracterul
mic si adaug 1 in result. Vad in ce buton ar fi caracterul la care ma aflu (vad
range-ul caracteristic unui buton -> 'a' - 'c' reprezinta butonul 2), vad ce
caracter am intr-un for ca sa stiu de cate adaug cifra butonului la result (pentru
 'a' adaug 2 o data, pentru 'c' adaug 2 de trei ori) si verific daca urmatorul
caracter se afla de pe acelasi buton -> daca da si in plus daca ignore == 0 (legat
de taskul 4 aici, unde trebuie sa nu adaug #), adaug # la sir. Aceeasi schema o
aplic pentru restul butoanelor.

Task 2
    La acest task, am 3 variabile: sameNextChar (daca urmatoarea cifra e la fel
sau nu), sameChar (numarul de cifre consecutive identice) si upper (daca am dat
de majuscula sau nu). Iterez prin sirul dat ca parametru, daca dau de 0 adaug
spatiu, daca dau de 1 -> upper = 1 (am gasit majuscula). Apoi verific daca urmatoarea
cifra e la fel sau nu -> daca e la fel, incremenetez sameChars (numarul de aparitii)
si sameNextChar = 1, altfel sameNextChar = 0. Daca am sameNextChar = 0, fac sameChars
% modulo, deoarece pot sa am, de exemplu, 5 aparitii de 2, care sunt de fapt 2 aparitii
de 2 (avem 3 litere pe butonul 2, deci avem modulo 3). Dupa aceea, vad ce cifra
 am, adica ce buton am, adun litera de baza de la buton minus 1 cu numarul de apasari
facut prin modulo si afisez pe ecran ce litera am.

Task 3
    Aici, sparg mesajul dupa spatiu, iterez prin fiecare cuvant. La fiecare
iteratie de cuvant, iterez dictionarul ca sa verific daca cuvantul respectiv
este corect sau nu. Daca vad ca nu este corect, lipesc versiunea corecta a
cuvantului la sirul corectat, altfel lipesc cuvantul pur si simplu. Dupa aceea,
codific sirul de cuvinte folosindu-ma de taskul 1.

Task 4
    Aici, sparg in cuvinte sirul primit, il codific folosind taskul 1, apoi 
convertesc fiecare cuvant codificat la long long, cu sprintf, care imi elimina
automat trailling zeros. Afisez componentele, apoi caut componenta maxima in
vectorul de componente si o afisez. Dupa aceea, fac o dubla iteratie (una in
alta) ca sa verific element cu element daca fiecare pereche de componente
are cel mai mare divizor comun pe 1 (adica sa fie prime intre ele). Daca nu
am componente prime intre ele, afisez 1, altfel afisez 0. Dupa aceea, lipesc
componentele intr-un sir de caracter, punand dupa fiecare componenta (cu
exceptia ultimei componente) 0 la final (le inmultesc cu 10, ca era mai
flexibil prin acest mod), apoi adun toate cifrele din toate componentele
(convertite din char la int: '3' -> 3, prin '3' - '0'), apoi verific daca
lungimea mesajului creat prin concatenarea de componente este divizibil
cu suma tuturor cifrelor: daca nu, afisez 0 si ies din functie, altfel continui.
Stabilitesc o lungime de partitionare, impartind lungimea mesajului format
prin alipirea componentelor la suma cifrelor, sparg mesajul in componente
de lungime egala cu partitionarea mentionata anterior, sortez componentele,
ca apoi sa le afisez.