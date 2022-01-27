# Projekt do kurzu Multiplatformní programování - Zadání číslo 5 (vlastní zadání)
Autor: Jakub Trubka (j_trubka@utb.cz)

Tento adresář obsahuje projekt do předmetu AK7MP - Multiplatformí programování. Jako zadání jsme zvolil možnost číslo 5 - vlastní zadání. Jako vlastní zadání jsem zvolil vizualizaci algoritmu pro [optimalizaci hejnem částic](https://www.intechopen.com/chapters/69586). Program byl vyvíjen na operačním systému Linux (distribuce Ubuntu) ve vývojovém prostředí CLion od JetBrains. 

## Závislosti
Pro spuštění aplikace je potřeba mít nainstalovaný QT5, g++ a cmake (>= 3.17). Projekt je možno přeložit následujícími příkazy:
```
mkdir build
cd build
cmake ..
make
```
Aplikaci je následně možné spustit příkazem ./PSOgui .

## Použití
Po spuštění programu zabírá hlavní plochu programu vykreslená funkce určená k optimalizaci (vykreslené hodnoty jsou spočteny za běhu, nejedná se obrázek). Pro vykreslení grafu je použita externí knihovna [qcustomplot](https://www.qcustomplot.com/) umístěna ve složce libs. Hodnoty v grafu jsou zaneseny pomocí tepelné mapy. Osy x a y určují polohu a barva určuje hodnotu fitness funkce v daném bodě. Po pravé straně se nachází ovládací prvky programu. Je možno nastavit:
* Number of steps - počet kroků simulace, k každém kroku dojde k pohybu všech částic
* Select function - dropdown menu pro výběr funkce která bude optimalizována, je dostupných 15 funkcí
* Number of particles - počet částic využitých v simulaci
* Speed limit - maximální rychlost pohybu částice, hodnotu je vhodné zvolit na základě měřítka
* Error - rozdíl oproti ideální hodnotě, která je považována za akceptovatelný výsledek, simulace je ukonřena po nalezení bodu jehož hodnota se liší o maximálně tuto hodnotu od výsledku
* Grayscale - přepínač mezi barevnou a černobílou tepelnou mapou, některé funkce jsou špatně rozeznatelné s barevnou tepelnou mapou
* Auto-sim - vypnutí a zapnutí automatické simulace, pokud je políčko zaškrtnuto, provede se simulace automaticky okamžitě až do nalezené výsledku či splnění poštu kroků, pokud pole není zvoleno, uživtel může jednotlivé kroky provádět tlačítkem Next Step či automaticky dokončit simulaci tlačítkem Finish simulation

