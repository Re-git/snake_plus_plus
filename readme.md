# Snake + +


## Tutoriale i dokumentacja

1. [Przykłady](https://www.raylib.com/examples.html)
2. [Referencja](https://www.raylib.com/cheatsheet/cheatsheet.html) spis wszystkich dostepnych funkcji w bibliotece

## Wymagania do pracy nad projektem:

1. Zainstaluj kompilator c++ Mingw [Download](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/)
2. Upewnij się, że kompilator jest dodany do PATH. Uruchom okno lini poleceń i wpisz `g++` jeśli otrzymasz informacje zwrotną `g++: fatal error: no input files
compilation terminated.` to wszystko gra
3. Uruchom skrypt compile.bat - gra powinna się skompilować i uruchomić. Jeśli zadziałało to super. Witamy. Jeśli nie to napisz, że masz problem i co się dzieje.
4. Zaloguj się na swój github.
5. Wyślij mi wiadomość ze swoją nazwą konta na github to dodam cię jako "collaborator".
6. Jeśli masz pomysł co dodać do naszej gry napisz o tym na tablicy https://github.com/Re-git/snake_plus_plus/projects.
7. Jeśli nie masz pojęcia jak używać Git zobacz jakiś tutorial. np: [Github for Poets](https://www.youtube.com/playlist?list=PLRqwX-V7Uu6ZF9C0YMKuns9sLDzK6zoiV)
8. zrób gałąź, dodaj nową funkcjonalność i poproś o pull request.

## Przykład jak to robić z konsoli(linia poleceń):
Żeby pobrać projekt na swój komputer, robimy sobie folder na kompie, następnie odpalamy konsole gita w tym katalogu (klikamy prawym w tym katalogu i wybieramy "Open git bash here"
Następnie wpisujemy 

`git clone https://github.com/Re-git/snake_plus_plus.git`
Ta komenda pobrała całe repozytorium na twoj komputer.

Jeśli chcesz rozpocząć pracę nad nową funkcjonalnością (dopisać trochę kodu)
Najpierw zrób nową gałąź, nazwij ją np. super-eksplozje
1. `git checkout -b super-eksplozje`

następnie zakoduj super eksplozje. Jeśli wszystko działa to zatwierdź zmiany w repozytorium lokalnym na twoim kompie przez wpisanie

**Opcjonalnie - jeśli dodałeś nowe pliki do repo to** `git add *` 

2. `git commit -m "dodałem super mega explozje jak snek uderzy w granice mapy. Kabooom!"`

Teraz wyślemy nasze zmiany na serwer GitHub gdzie inni będą mogli je zobaczyć

3. `git push -u origin super-eksplozje`

Ostatnim krokiem jest poproszenie o tzw. pull request czyli dodanie zmian do gałęzi Master naszego projektu

4. Na stronie git kliknij add pull request

Twoja prośba pojawi się w zakładce pull requests i będzie czekała na akceptację przez innych członków zespołu.

5. Jeśli chesz powrócić do gałęzi Master `git checkout master`

Teraz możesz utworzyć kolejną gałąź wracając do punktu 1 i dodać nową funkcjonalność, nowy level lub jeszcze więcej eksplozji i innych fajnych rzeczy.
