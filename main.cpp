#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void rzutKoscmi();                                                  //deklaracja funkcji void, ktora bedzie symulowac rzut koscmi
int graczPierwszy();                                                //deklaracja funkcji void, ktora zawiera instrukcje dla pierwszego rzutu dla gracza pierwszego
int graczDrugi();                                                   //deklaracja funkcji void, ktora zawiera instrukcje dla pierwszego rzutu dla gracza drugiego
void kolejnaRunda();                                                //deklaracja funkcji void, krota zepnie w sobie pozostale funkcje void
int kolejnyRzut(int ktoryGracz);                                    //deklaracja funkcji void, ktora obejmie przypadek gdy nikt nie wygra przy pierwszym rzucie
void wyswietlanieKostki(int liczbaOczek);                           //deklaracja funkcji void, ktora „graficznie” wyswietli wylosowana kostke
void ktoWygral(int czyGracz1, int czyGracz2);                       //deklaracja funkcji void, ktora sprawdzi, ktory gracz wygral, przydzieli odpowiedniej osobie pieniadze, ewentualnie stwierdzi, ze byl remis. wyswietli tez odpowiednie komunikaty
int wylosowanaLiczba1, wylosowanaLiczba2, suma;                     //Zmienne wykorzystywane przy rzucie kostka
int punktyGracz1, kwotaGracz1 = 100;                                //Zmienne wykorzystywane dla gracza 1.
int punktyGracz2, kwotaGracz2 = 100;                                //Zmienne wykorzystywane dla gracza 2.
bool koniec;                                                        //zmienna sprawdzająca czy gra powinna się skonczyc
int pomocnicza1, pomocnicza2;                                       //zmienne, ktore ulatwia sprawdzanie warunku
int gracz;                                                          //zmienna pomocnicza do funkcji kolejnyRzut

int main ()
{
    srand(time(0));
    cout << setw(40) << "()()()()()()()()()"<< endl;
    cout << setw(40) << "() Gra w kosci. ()"<< endl;
    cout << setw(40) << "()()()()()()()()()"<< endl;
    cout << endl;
    cout << "Zasady gry:" << endl;
    cout << "GRACZE rzucaja dwie kosci i licza ich sume." << endl;
    cout << "Jesli suma przy pierwszym rzucie w rundzie wynosi: " << endl;
    cout << "  1. 7 lub 11 to GRACZ wygrywa runde i otrzymuje od przeciwnika 20 zl." << endl;
    cout << "  2. 2, 3 lub 12 to GRACZ przegrywa runde i musi oddac przeciwnikowi 20 zl. " << endl;
    cout << "  3. W przypadku innej sumy, staje sie ona punktami GRACZA." << endl;
    cout << "     Aby wygrac runde musza ponownie wyrzucic taka sama liczbe oczek." << endl;
    cout << "     Jesli komus sie uda to otrzymuje on od przeciwnika 20 zl." << endl;
    cout << "     Jesli ktorys z GRACZY wyrzuci sume oczek rowna 7, to przegrywa runde i oddaje przeciwnikowi 20 zl." << endl;
    cout << endl;
    cout << "Gra trwa 10 rund. "<< endl;
    cout << endl;
    cout << "Nacisnij ENTER, aby rozpoczac gre." << endl;
    cin.ignore();                                                                          //zatrzymanie programu, zeby uzytkownik mogl na spokojnie przeczytacz zasady gry
    for(int i = 1; i <= 10; i++)                                                           //ta petla sprawi, ze bedziemy miec maksymalnie 10 rund
    {
        if (kwotaGracz1 > 0 && kwotaGracz2 > 0)                                            //sprawdzanie, czy gracze maja pieniadze, by grac dalej
        {
            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;          //Takie linijki sprawiaja, ze wyswietlane informacje sa przyjazniejsze dla oka
            cout << setw(40) << "Runda " << i << endl;
            cout << endl;
            cout << endl;
            koniec = 0;
            kolejnaRunda();                                                                //wywolanie funkcji, która spina w sobie cala gre
            cout << "Pozostala kwota dla GRACZA 1: " << kwotaGracz1 << endl;               //wyswietlanie ile graczom zostalo pieniedzy
            cout << "Pozostala kwota dla GRACZA 2: " << kwotaGracz2 << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;
            cout << "Nacisnij ENTER, aby kontynuowac." << endl;
            cin.ignore();                                                                  //mozna przyjrzec sie rundzie i pozostalym kwotom przed przejsciem do kolejnej rundy
        }
        else                                                                               //instrukcje, ktore wykonja sie, gdy ktoremus z graczy skoncza sie pieniadze
        {
            cout << "Jednemu z GRACZY skonczyly sie pieniadze, koniec gry." << endl;
            if(kwotaGracz1 > kwotaGracz2)
            {
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOoOo" << endl;
                cout << setw(40) << "oO GRACZ 1 wygral! Oo" << endl;
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOoOo" << endl;
            }
            else
            {
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOoOo" << endl;
                cout << setw(40) << "oO GRACZ 2 wygral! Oo" << endl;
                cout << setw(40) << "oOoOoOoOoOoOoOoOoOoOo" << endl;
            }
            cout << "-----------------------------------------------------------------------------------------------" << endl;
            break;                                                                         //break; przerwie petle for, jednemu z graczy skoczyly sie pieniadze, wiec nie ma o co grac
        }
    }
    return 0;
}

void kolejnaRunda()
{
    cout << "Nacisnij ENTER, aby rzucic kostki dla GRACZA 1." << endl;
    cin.ignore();                                                               //takie linijki to iluzja interaktywnosci, mogloby ich nie byc ale wtedy od razu wyswietlilyby sie wszystkie rundy, trzebaby bylo scrollowac zeby je wszystkie zobaczyc i zanalizowac
    cout << endl;
    pomocnicza1 = graczPierwszy();
    cout << "Nacisnij ENTER, aby rzucic kostki dla GRACZA 2." << endl;
    cin.ignore();
    pomocnicza2 = graczDrugi();
    ktoWygral(pomocnicza1, pomocnicza2);
    while(koniec == 0)
    {
        cout << "Nacisnij ENTER, aby kontynuowac." << endl;
        cin.ignore();
        cout << "Kostki dla kolejnego rzutu GRACZA 1." << endl;
        gracz = 1;
        pomocnicza1 = kolejnyRzut(gracz);
        cout << endl;
        cout << "Nacisnij ENTER, aby kontynuowac." << endl;
        cin.ignore();
        cout << "Kostki dla kolejnego rzutu GRACZA 2." << endl;
        gracz = 2;
        pomocnicza2 = kolejnyRzut(gracz);
        ktoWygral(pomocnicza1, pomocnicza2);
    }
}

void ktoWygral(int czyGracz1, int czyGracz2)                            //funkcja przyjmuje wartosci zwrocone przez funkcje graczPierwszy, graczDrugi, a przy kolejnych rzutach kostka wartosci zwrocone przez funkcje kolejnyRzut. mocno mi tutaj pomogly zmienne pomocnicza1, pomocnicza2
{
    if (czyGracz1 == 1 && (czyGracz2 == 2 || czyGracz2 == 3))           //instrukcje dla przypadku, w ktorym gracz pierwszy wygral, a drugi przegral lub nie wylosowal odpowiedniej liczby
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ GRACZ 1. wygral te runde. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        kwotaGracz1 +=20;
        kwotaGracz2 -=20;
        koniec = 1;
    }
    else if ((czyGracz1 == 2 || czyGracz1 == 3) && czyGracz2 == 1)      //instrukcje dla przypadku, w ktorym gracz drugi wygral, a pierwszy przegral lub nie wylosowal odpowiedniej liczby
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ GRACZ 2. wygral te runde. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        kwotaGracz2 += 20;
        kwotaGracz1 -= 20;
        koniec = 1;
    }
    else if (czyGracz1 == 2 && czyGracz2 == 3)                          //instrukcje dla przypadku, w ktorym gracz pierwszy przegral, a gracz drugi nie wylosowal zadnej funkcjyjnej liczby
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ GRACZ 2. wygral te runde. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        kwotaGracz2 += 20;
        kwotaGracz1 -= 20;
        koniec = 1;
    }
    else if (czyGracz1 == 3 && czyGracz2 == 2)                          //instrukcje dla przypadku, w ktorym gracz drugi przegral, a gracz pierwszy nie wylosowal zadnej funkcjyjnej liczby
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ GRACZ 1. wygral te runde. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        kwotaGracz1 += 20;
        kwotaGracz2 -= 20;
        koniec = 1;
    }
    else if ((czyGracz1 == 1 && czyGracz2 == 1) || (czyGracz1 == 2 && czyGracz2 == 2))          //instrukcje dla przypadku, w ktorym przy tym samym rzucie kostka zarowno jeden, jak i drugi gracz przegrali lub wygrali
    {
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << setw(40) << "~ Remis, nikt nie wygral tej rundy. ~" << endl;
        cout << setw(40) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        koniec = 1;
    }
    else                                                                //instrukcje dla pozostalych przypadkow, czyli ten, w ktorym zaden z graczy nie wyrzucil funkcyjnej liczby
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~                    Na razie brak wygranych.                       ~" << endl;
        cout << "~ GRACZ 1. musi wyrzucic " << punktyGracz1 << ", a GRACZ 2. musi wyrzucic " << punktyGracz2 << ", aby wygrac. ~" << endl;
        cout << "~                Gracz, ktory wyrzuci 7 przegrywa.                  ~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        koniec = 0;
    }
}

int graczPierwszy()                                                             //liczby zwracane przez te funkcje pozwola mi okreslic jaki mamy przypadek, ktory gracz wygral/przegral/remis/musza rzucac kolejny raz
{
    cout << "Rzut koscmi dla GRACZA 1." << endl;
    rzutKoscmi();
    if ((suma == 7)||(suma == 11))                                              //warunek wygranej przy pierwszym rzucie
    {
        return 1;
    }
    else if ((suma == 2) || (suma == 3) || (suma == 12))                        //warunek przegranej przy pierwszym rzucie
    {
        return 2;
    }
    else                                                                        //dla kazdego innego przypadku – czyli suma równa 4, 5, 6, 8, 9, 10 – wykonaja sie ponizsze instrukcje
    {
        punktyGracz1 = suma;                                                    //przypisanie wartosci sumy do zmiennej punktyGracz1 pozwoli sprawdzic czy przy kolejnym rzucie udalo sie wyrzucic te sama liczbe
        return 3;
    }
}

int graczDrugi()                                                                //liczby zwracane przez te funkcje pozwola mi okreslic jaki mamy przypadek, ktory gracz wygral/przegral/remis/musza rzucac kolejny raz
{
    cout << "Rzut koscmi dla GRACZA 2." << endl;
    rzutKoscmi();
    if ((suma == 7)||(suma==11))                                                //warunek wygranej przy pierwszym rzucie
    {
        return 1;
    }
    else if ((suma == 2) || (suma == 3) || (suma == 12))                        //warunek przegranej przy pierwszym rzucie
    {
        return 2;
    }
    else                                                                        //dla kazdego innego przypadku – czyli suma równa 4, 5, 6, 8, 9, 10 – wykonaja sie ponizsze instrukcje
    {
        punktyGracz2 = suma;                                                    //przypisanie wartosci sumy do zmiennej punktyGracz2 pozwoli sprawdzic czy przy kolejnym rzucie udalo sie wyrzucic te sama liczbe
        return 3;
    }
}

int kolejnyRzut(int ktoryGracz)                                                  //liczby zwracane przez te funkcje pozwola mi okreslic jaki mamy przypadek, ktory gracz wygral/przegral/remis/musza rzucac kolejny raz
{
    switch(ktoryGracz)
    {
    case 1:                                                                      //przypadek, gdy sprawdzamy kolejna sume z wylosowanych kostek dla gracza 1.
        rzutKoscmi();
        if (suma == 7)
        {
            return 2;
        }
        else if (punktyGracz1 == suma)
        {
            return 1;
        }
        else
        {
            return 3;
        }
        break;
    case 2:                                                                       //przypadek, gdy sprawdzamy kolejna sume z wylosowanych kostek dla gracza 2.
        rzutKoscmi();
        if (suma == 7)
        {
            return 2;
        }
        else if (punktyGracz2 == suma)
        {
            return 1;
        }
        else
        {
            return 3;
        }
        break;
    default:
        break;
    }
}

void rzutKoscmi()                                                                       //funkcja losuje 2 liczby
{
    cout << endl;
    cout << "************************************************************************************************" << endl;
    wylosowanaLiczba1 = rand()%6+1;                                                     //losowanie liczby od 1 od 6, rand() daje losowa liczbe, instrukcja % sprawia, ze losuja sie liczby od 0 do 5, a +1 daje nam zakres od 1 do 6
    cout << "Pierwsza wylosowana kostka to: " << endl;
    wyswietlanieKostki(wylosowanaLiczba1);                                              //wyswietlanie kostki w zaleznosci od wylosowanej liczby
    wylosowanaLiczba2 = rand()%6+1;
    cout << "Druga wylosowana kostka to: " << endl;
    wyswietlanieKostki(wylosowanaLiczba2);
    suma = wylosowanaLiczba1 + wylosowanaLiczba2;                                       //dodanie wylosowanych wartosci i przypisanie ich do zmiennej suma
    cout << "Suma wylosowanych liczb wynosi: " << suma << endl;
    cout << "************************************************************************************************" << endl;
    cout << endl;
}

void wyswietlanieKostki(int liczbaOczek)                                                //funkcja wyswietla kostki w zaleznosci od wylosowanej liczby
{
    switch(liczbaOczek)
    {
    case 1:
        cout << "-----" << endl;
        cout << "|   |" << endl;
        cout << "| o |" << endl;
        cout << "|   |" << endl;
        cout << "-----" << endl;
        break;
    case 2:
        cout << "-----" << endl;
        cout << "|o  |" << endl;
        cout << "|   |" << endl;
        cout << "|  o|" << endl;
        cout << "-----" << endl;
        break;
    case 3:
        cout << "-----" << endl;
        cout << "|o  |" << endl;
        cout << "| o |" << endl;
        cout << "|  o|" << endl;
        cout << "-----" << endl;
        break;
    case 4:
        cout << "-----" << endl;
        cout << "|o o|" << endl;
        cout << "|   |" << endl;
        cout << "|o o|" << endl;
        cout << "-----" << endl;
        break;
    case 5:
        cout << "-----" << endl;
        cout << "|o o|" << endl;
        cout << "| o |" << endl;
        cout << "|o o|" << endl;
        cout << "-----" << endl;
        break;
    case 6:
        cout << "-----" << endl;
        cout << "|o o|" << endl;
        cout << "|o o|" << endl;
        cout << "|o o|" << endl;
        cout << "-----" << endl;
        break;
    default:
        cout << "W jaki sposob udalo Ci sie wylosowac inna liczbe?" << endl;            //switch musi miec przypadek default, czyli taki, który wykona sie dla kazdego innego przypadku niz te, które zostaly zadeklarowane
        break;
    }
}


//Staralem sie, zeby program konsolowy wygladal tez jak najlepiej, dlatego pojawia sie duzo zbednych (z punktu poprawnosci programu) linijek. Ulatwilo to jednak testowanie, no i jest to przyjazniejsze dla uzytkownikow, ktorzy nie rozumieja kodu czy konsoli i ich wczesniej nie widzieli.
//Program za kazdym razem, gdy gracze musza rzucac kolejny raz wyswietla komunikat ile musza wyrzucic. To rowniez ulatwilo mi testowanie, a ewentualnym graczom przypomina i pokazuje dlaczego nikt nie wygral.
