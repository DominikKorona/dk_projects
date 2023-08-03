import pandas as pd
import copy
import random

from operator import itemgetter
from tkinter import Tk, LEFT, RIGHT, BOTH, TOP, Label, RAISED, Entry, DISABLED, Button, Y, NO
from tkinter import messagebox, filedialog, Checkbutton, Scrollbar, LabelFrame, StringVar, IntVar
from tkinter.ttk import Notebook, Frame, Treeview
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt

posilki = pd.read_csv('data/kglod_2600kcal.csv', sep=';')

mega_list = list()


def rozwiazanie_losowe(n):  # funkcja generująca rozwiązanie skladajace sie z n dni
    global mega_list
    X = list()
    for i in range(0, n):
        sniadanie = posilki[posilki.rodzaj == 0].sample(1).to_numpy()
        obiad = posilki[posilki.rodzaj == 1].sample(1).to_numpy()
        kolacja = posilki[posilki.rodzaj == 2].sample(1).to_numpy()
        dzien = [sniadanie, obiad, kolacja]
        X.append(dzien)
        mega_list.append(sniadanie[0][1])
        mega_list.append(obiad[0][1])
        mega_list.append(kolacja[0][1])
    return X


def pokaz_rozwiazanie(x):  # funkcja wypisująca rozwiązanie
    n = len(x)
    for i in range(0, n):
        print('Dzień {}'.format(i + 1))
        for j in range(0, 3):
            if j == 0:
                print('Sniadanie: {}'.format(x[i][j]))
            elif j == 1:
                print('Obiad: {}'.format(x[i][j]))
            else:
                print('Kolacja: {}'.format(x[i][j]))
        print("\n")


def pokaz_rozwiazanie_2(x):  # funkcja wypisująca rozwiązanie (same potrawy)
    n = len(x)
    for i in range(0, n):
        print('Dzień {}'.format(i + 1))
        for j in range(0, 3):
            if j == 0:
                print('Sniadanie: {}'.format(x[i][j][0][1]))
            elif j == 1:
                print('Obiad: {}'.format(x[i][j][0][1]))
            else:
                print('Kolacja: {}'.format(x[i][j][0][1]))
        print("\n")


def wartosc_funkcji_celu(x):  # funkcja obliczająca wartość funkcji celu dla rozwiązania
    n = len(x)
    suma = 0
    for i in range(0, n):
        for j in range(0, 3):
            suma += float(x[i][j][0][6].replace(',', '.'))
    return suma


def ograniczenia_dnia(dzien, ograniczenia):  # funkcja sprawdzająca ograniczenia dla dnia

    czy_ogr_spelnione = 1  # 1-spełnione 0-nie spełnione

    kcal = ograniczenia[0]  # zapotrzebowanie na wartości odżywcze
    bialko = ograniczenia[1]
    tluszcz = ograniczenia[2]
    wegle = ograniczenia[3]

    kcal_tol = ograniczenia[4]  # tolaerancja na wartości odżywcze 0.1 = 10%
    bialko_tol = ograniczenia[5]
    tluszcz_tol = ograniczenia[6]
    wegle_tol = ograniczenia[7]

    owoce = ograniczenia[8]  # zapotrzebowanie  typów produktów
    warzywa = ograniczenia[9]
    zbozowe = ograniczenia[10]
    nabial = ograniczenia[11]
    mieso = ograniczenia[12]
    inne = ograniczenia[13]

    kcal_dnia = 0
    bialko_dnia = 0
    tluszcz_dnia = 0
    wegle_dnia = 0
    owoce_dnia = 0
    warzywa_dnia = 0
    zbozowe_dnia = 0
    nabial_dnia = 0
    mieso_dnia = 0
    inne_dnia = 0

    for i in range(0, 3):  # podliczenie sumy kcal,tłuszczy,białka,węgli,owocy,zbożowych,nabialu i mięsa
        kcal_dnia += float(dzien[i][0][2].replace(',', '.'))
        bialko_dnia += float(dzien[i][0][3].replace(',', '.'))
        tluszcz_dnia += float(dzien[i][0][4].replace(',', '.'))
        wegle_dnia += float(dzien[i][0][5].replace(',', '.'))
        owoce_dnia += int(dzien[i][0][7])
        warzywa_dnia += int(dzien[i][0][8])
        zbozowe_dnia += int(dzien[i][0][9])
        nabial_dnia += int(dzien[i][0][10])
        mieso_dnia += int(dzien[i][0][11])
        inne_dnia += int(dzien[i][0][12])

    # sprawdzenie ogaraniczeń na kalorie, białka, tłuszcze i welowodany
    kcal_down = kcal - (kcal * kcal_tol)
    kcal_up = kcal + (kcal * kcal_tol)
    bialko_down = bialko - (bialko * bialko_tol)
    bialko_up = bialko + (bialko * bialko_tol)
    tluszcz_down = tluszcz - (tluszcz * tluszcz_tol)
    tluszcz_up = tluszcz + (tluszcz * tluszcz_tol)
    wegle_down = wegle - (wegle * wegle_tol)
    wegle_up = wegle + (wegle * wegle_tol)

    if (kcal_dnia < kcal_down) or (kcal_dnia > kcal_up):
        czy_ogr_spelnione = 0
    if (bialko_dnia < bialko_down) or (bialko_dnia > bialko_up):
        czy_ogr_spelnione = 0
    if (tluszcz_dnia < tluszcz_down) or (tluszcz_dnia > tluszcz_up):
        czy_ogr_spelnione = 0
    if (wegle_dnia < wegle_down) or (wegle_dnia > wegle_up):
        czy_ogr_spelnione = 0

    # sprawdzenie ograniczeń na występowanie produktów określonego typu
    if owoce_dnia < owoce:
        czy_ogr_spelnione = 0
    if warzywa_dnia < warzywa:
        czy_ogr_spelnione = 0
    if zbozowe_dnia < zbozowe:
        czy_ogr_spelnione = 0
    if nabial_dnia < nabial:
        czy_ogr_spelnione = 0
    if mieso_dnia < mieso:
        czy_ogr_spelnione = 0
    if inne_dnia < inne:
        czy_ogr_spelnione = 0

    return czy_ogr_spelnione


def ograniczenia_dnia_dla_n_dni(x, ograniczenia):  # funkcja sprawdzająca ograniczenia dniowe dla rozwiązania

    czy_ogr_spelnione = 1  # 1-spełnione 0-nie spełnione

    n = len(x)

    ograniczenia_n_dni = list()
    for i in range(0, n):
        ograniczenia_n_dni.append(ograniczenia_dnia(x[i], ograniczenia))

    if len(set(ograniczenia_n_dni)) != 1:
        czy_ogr_spelnione = 0
    if (len(set(ograniczenia_n_dni)) == 1) and (ograniczenia_n_dni[0] == 0):
        czy_ogr_spelnione = 0

    return czy_ogr_spelnione


def kryterium_roznorodnosci(x):
    n = len(x)

    indeksy_sniadan = list()
    indeksy_obiadow = list()
    indeksy_kolacji = list()

    for i in range(0, n):
        indeksy_sniadan.append(x[i][0][0][0])
        indeksy_obiadow.append(x[i][1][0][0])
        indeksy_kolacji.append(x[i][2][0][0])

    roznorodnosc_sniadan = len(set(indeksy_sniadan))
    roznorodnosc_obiadow = len(set(indeksy_obiadow))
    roznorodnosc_kolacji = len(set(indeksy_kolacji))
    suma_roznorodnosci = sum([roznorodnosc_sniadan, roznorodnosc_obiadow, roznorodnosc_kolacji])
    result = suma_roznorodnosci / (3 * n)
    return result


def podwyzszenie_ceny(a):  # wartość procentowa o jaką sztucznie podbijamy cene
    return (1 - a) * 100


def sasiad_hamming(rozwiazanie_bierzace, h):
    x = copy.deepcopy(rozwiazanie_bierzace)
    n = len(x)
    m = 3
    i = 0
    powtorki = list()
    while i < h:
        dzien = random.randint(0, n - 1)
        posilek = random.randint(0, 2)
        if (dzien, posilek) not in powtorki:
            powtorki.append((dzien, posilek))
            x[dzien][posilek][0] = posilki[posilki.rodzaj == posilek].sample(1).to_numpy()
            i = i + 1
    return x


def BA(kcal_, bialko_, tluszcz_, wegle_, kcal_tol_, bialko_tol_, tluszcz_tol_, wegle_tol_,
       owoce_, warzywa_, zbozowe_, nabial_, mieso_, inne_,
       liczba_dni_,
       liczebnosc_populacji_poczatkowej_, czas_zycia_, max_iteracji_, wspolczynnik_kary_, liczebnosc_sasiedztwa_e_,
       roznorodnosc_sasiedztwa_e_, liczebnosc_sasiedztwa_d_, roznorodnosc_sasiedztwa_d_, liczba_rozwiazan_elitarnych_,
       liczba_rozwiazan_dobrych_, populacja_poczatkowa_=None):
    i_konc = 0  # numer iteracji rozwiazania najlepszego
    kcal = kcal_  # zapotrzebowanie na wartości odżywcze
    bialko = bialko_
    tluszcz = tluszcz_
    wegle = wegle_

    kcal_tol = kcal_tol_  # tolaerancja na wartości odżywcze 0.2 = 20%
    bialko_tol = bialko_tol_
    tluszcz_tol = tluszcz_tol_
    wegle_tol = wegle_tol_

    owoce = owoce_
    warzywa = warzywa_
    zbozowe = zbozowe_
    nabial = nabial_
    mieso = mieso_
    inne = inne_

    ograniczenia = [kcal, bialko, tluszcz, wegle, kcal_tol, bialko_tol, tluszcz_tol, wegle_tol,
                    owoce, warzywa, zbozowe, nabial, mieso, inne]

    liczba_dni = liczba_dni_

    liczebnosc_populacji_poczatkowej = liczebnosc_populacji_poczatkowej_
    czas_zycia = czas_zycia_
    max_iteracji = max_iteracji_

    wspolczynnik_kary = wspolczynnik_kary_
    liczebnosc_sasiedztwa_e = liczebnosc_sasiedztwa_e_
    roznorodnosc_sasiedztwa_e = roznorodnosc_sasiedztwa_e_

    liczebnosc_sasiedztwa_d = liczebnosc_sasiedztwa_d_
    roznorodnosc_sasiedztwa_d = roznorodnosc_sasiedztwa_d_

    liczba_rozwiazan_elitarnych = liczba_rozwiazan_elitarnych_
    liczba_rozwiazan_dobrych = liczba_rozwiazan_dobrych_

    # tworzenie losowej populacji początkowej
    populacja_poczatkowa = list()
    if populacja_poczatkowa_ is None:
        i = 0
        while i < liczebnosc_populacji_poczatkowej:
            x = rozwiazanie_losowe(liczba_dni)  # losowe rozwiązanie
            if ograniczenia_dnia_dla_n_dni(x, ograniczenia):  # sprawdzenie ograniczeń
                populacja_poczatkowa.append(x)
                i = i + 1
    else:
        populacja_poczatkowa = copy.deepcopy(populacja_poczatkowa_)

    # ocena populacji początkowej
    for i in range(0, liczebnosc_populacji_poczatkowej):
        koszt_prawdziwy = wartosc_funkcji_celu(populacja_poczatkowa[i])  # funkcja celu
        roznorodnosc = kryterium_roznorodnosci(populacja_poczatkowa[i])  # roznorodnosc rozwiazania
        kara = podwyzszenie_ceny(roznorodnosc)  # kara
        koszt_sztuczny = koszt_prawdziwy + kara * wspolczynnik_kary
        lst = (populacja_poczatkowa[i], koszt_sztuczny, czas_zycia - 1)  # czas życia
        populacja_poczatkowa[i] = list(lst)  # czas życia

    # posortowanie populacji poczotkowej
    populacja_poczatkowa_sorted = sorted(populacja_poczatkowa, key=itemgetter(1))

    # wybranie rozwiazan do poszukiwan
    populacja_poczatkowa_wybrane = list()
    for i in range(0, liczba_rozwiazan_elitarnych + liczba_rozwiazan_dobrych):
        populacja_poczatkowa_wybrane.append(populacja_poczatkowa_sorted[i])

    najlepsze = populacja_poczatkowa_wybrane[0]

    # pętla główna
    i = 0
    rozwiazania_najlepsze = copy.deepcopy(populacja_poczatkowa_wybrane)

    rozwiazania_elitarne = populacja_poczatkowa_wybrane[0:liczba_rozwiazan_elitarnych]
    rozwiazania_dobre = populacja_poczatkowa_wybrane[liczba_rozwiazan_elitarnych:
                                                     liczba_rozwiazan_elitarnych + liczba_rozwiazan_dobrych]

    do_wykresu = list()
    do_wykresu.append(najlepsze[1])

    while i < max_iteracji:
        # rozwiazania_najlepsze = copy.deepcopy(populacja_poczatkowa_wybrane)
        # dlugosc = len(rozwiazania_najlepsze)
        populacja = copy.deepcopy(rozwiazania_najlepsze)
        rozwiazania_elitarne = populacja[0:liczba_rozwiazan_elitarnych]
        rozwiazania_dobre = populacja[
                            liczba_rozwiazan_elitarnych:liczba_rozwiazan_elitarnych + liczba_rozwiazan_dobrych]

        # dla rozwiazan elitarnych
        for j in range(0, liczba_rozwiazan_elitarnych):
            # utworzenie sąsiedztwa
            sasiedztwo = list()
            k1 = 0
            while liczebnosc_sasiedztwa_e > k1:
                x = sasiad_hamming(rozwiazania_elitarne[j][0], roznorodnosc_sasiedztwa_e)
                if ograniczenia_dnia_dla_n_dni(x, ograniczenia):  # sprawdzenie ograniczeń
                    sasiedztwo.append(x)
                    k1 = k1 + 1
            # wybór najlepszego sąsiada
            # ocena sąsiedztwa
            for k in range(0, liczebnosc_sasiedztwa_e):  # liczebność sąsiadów
                koszt_prawdziwy = wartosc_funkcji_celu(sasiedztwo[k])  # funkcja celu
                roznorodnosc = kryterium_roznorodnosci(sasiedztwo[k])  # roznorodnosc rozwiazania
                kara = podwyzszenie_ceny(roznorodnosc)  # kara
                koszt_sztuczny = koszt_prawdziwy + kara * wspolczynnik_kary
                lst2 = (sasiedztwo[k], koszt_sztuczny, czas_zycia)
                sasiedztwo[k] = list(lst2)  # czas życia
            # posortowanie sąsiedztwa
            sasiedztwo_sorted = sorted(sasiedztwo, key=itemgetter(1))
            # wybór najlepszego i dodanie do populacji
            najlepszy_z_sasiadow = sasiedztwo_sorted[0]
            populacja.append(najlepszy_z_sasiadow)

        # dla rozwiazan dobrych
        for j in range(0, liczba_rozwiazan_dobrych):
            # utworzenie sąsiedztwa
            sasiedztwo = list()
            k1 = 0
            while liczebnosc_sasiedztwa_d > k1:
                x = sasiad_hamming(rozwiazania_dobre[j][0], roznorodnosc_sasiedztwa_d)
                if ograniczenia_dnia_dla_n_dni(x, ograniczenia):  # sprawdzenie ograniczeń
                    sasiedztwo.append(x)
                    k1 = k1 + 1
            # wybór najlepszego sąsiada
            # ocena sąsiedztwa
            for k in range(0, liczebnosc_sasiedztwa_d):  # liczebność sąsiadów
                koszt_prawdziwy = wartosc_funkcji_celu(sasiedztwo[k])  # funkcja celu
                roznorodnosc = kryterium_roznorodnosci(sasiedztwo[k])  # roznorodnosc rozwiazania
                kara = podwyzszenie_ceny(roznorodnosc)  # kara
                koszt_sztuczny = koszt_prawdziwy + kara * wspolczynnik_kary
                lst2 = (sasiedztwo[k], koszt_sztuczny, czas_zycia)
                sasiedztwo[k] = list(lst2)  # czas życia
            # posortowanie sąsiedztwa
            sasiedztwo_sorted = sorted(sasiedztwo, key=itemgetter(1))
            # wybór najlepszego i dodanie do populacji
            najlepszy_z_sasiadow = sasiedztwo_sorted[0]
            populacja.append(najlepszy_z_sasiadow)

        # generowanie nowych osobników
        ilosc_brakujaca = liczebnosc_populacji_poczatkowej - len(populacja)
        nowe = list()
        l = 0
        while l < ilosc_brakujaca:
            x = rozwiazanie_losowe(liczba_dni)  # losowe rozwiązanie
            if ograniczenia_dnia_dla_n_dni(x, ograniczenia):  # sprawdzenie ograniczeń
                nowe.append(x)
                l = l + 1
        for k in range(0, len(nowe)):
            koszt_prawdziwy = wartosc_funkcji_celu(nowe[k])  # funkcja celu
            roznorodnosc = kryterium_roznorodnosci(nowe[k])  # roznorodnosc rozwiazania
            kara = podwyzszenie_ceny(roznorodnosc)  # kara
            koszt_sztuczny = koszt_prawdziwy + kara * wspolczynnik_kary
            lst3 = (nowe[k], koszt_sztuczny, czas_zycia)
            nowe[k] = list(lst3)  # czas życia

        populacja = populacja + nowe

        # zastąpienie osobników starych
        for k in range(0, len(populacja)):
            if populacja[k][2] == 0:
                war = 1
                while war:
                    x = rozwiazanie_losowe(liczba_dni)
                    if ograniczenia_dnia_dla_n_dni(x, ograniczenia):  # sprawdzenie ograniczeń
                        koszt_prawdziwy = wartosc_funkcji_celu(x)  # funkcja celu
                        roznorodnosc = kryterium_roznorodnosci(x)  # roznorodnosc rozwiazania
                        kara = podwyzszenie_ceny(roznorodnosc)  # kara
                        koszt_sztuczny = koszt_prawdziwy + kara * wspolczynnik_kary
                        lst4 = (x, koszt_sztuczny, czas_zycia)
                        populacja[k] = list(lst4)
                        war = 0

        # posortowanie populacji poczotkowej
        populacja_sorted = sorted(populacja, key=itemgetter(1))
        naj_seri = populacja_sorted[0]
        if naj_seri[1] <= najlepsze[1]:
            najlepsze = naj_seri
            i_konc = i + 1  # numer iteracji rozwiazania najlepszego
        do_wykresu.append(naj_seri[1])

        rozwiazania_najlepsze = list()
        for k in range(0, liczba_rozwiazan_elitarnych + liczba_rozwiazan_dobrych):
            rozwiazania_najlepsze.append(populacja_sorted[k])

        for k in range(0, liczba_rozwiazan_elitarnych + liczba_rozwiazan_dobrych):
            old = rozwiazania_najlepsze[k][2]
            rozwiazania_najlepsze[k][2] = old - 1

        i = i + 1
    return najlepsze, do_wykresu, i_konc


#########################################################################################
#################################### INTERFEJS GRAFICZNY ################################
#########################################################################################

win = Tk()
win.title(" Find_Your_Diet ")
win.geometry('1200x900')

tabGeneral = Notebook(win)

"""-------------------------------Pierwsze Okno-----------------------------------------------"""
tab1 = Frame(win)
tabGeneral.add(tab1, text='Menu')


def save_data():
    global owoce, warzywa, zbozowe, nabial, mieso, inne, kcal, bialko, tluszcz, wegle, liczba_dni, kcal_tol, bialko_tol, tluszcz_tol, wegle_tol
    global liczebnosc_populacji_poczatkowej, czas_zycia, max_iteracji, wspolczynnik_kary, liczebnosc_sasiedztwa_e
    global roznorodnosc_sasiedztwa_e, liczebnosc_sasiedztwa_d, roznorodnosc_sasiedztwa_d, liczba_rozwiazan_elitarnych, liczba_rozwiazan_dobrych
    liczba_dni = int(wlist["0"].get())
    kcal = int(wlist["1"].get())
    bialko = int(wlist["2"].get())
    tluszcz = int(wlist["3"].get())
    wegle = int(wlist["4"].get())
    kcal_tol = int(wlist["5"].get()) / 100
    bialko_tol = int(wlist["6"].get()) / 100
    tluszcz_tol = int(wlist["7"].get()) / 100
    wegle_tol = int(wlist["8"].get()) / 100
    owoce = var1.get()
    warzywa = var2.get()
    zbozowe = var3.get()
    nabial = var4.get()
    mieso = var5.get()
    inne = var6.get()
    liczebnosc_populacji_poczatkowej = int(other1.get())
    czas_zycia = int(other2.get())
    max_iteracji = int(other3.get())
    wspolczynnik_kary = int(other4.get())
    liczebnosc_sasiedztwa_e = int(other5.get())
    roznorodnosc_sasiedztwa_e = int(other6.get())
    liczebnosc_sasiedztwa_d = int(other7.get())
    roznorodnosc_sasiedztwa_d = int(other8.get())
    liczba_rozwiazan_elitarnych = int(other9.get())
    liczba_rozwiazan_dobrych = int(other10.get())
    mystr.set('{}'.format(bialko*4 + tluszcz*9 + wegle*4))


def delate():
    treeview.delete(*treeview.get_children())

def update_window1(rows):
    global mydata_meals

    mydata_meals = rows
    treeview.delete(*treeview.get_children())
    for i in range(len(rows[0])):
        sum_kcal = 0
        sum_b = 0
        sum_t = 0
        sum_w = 0
        sum_c = 0
        for j in range(5):

            if j == 0:
                rows[0][i][j][0][0] = "".format(i + 1)
            elif j == 1:
                rows[0][i][j][0][0] = "Dzien{}:".format(i + 1)
            elif j == 2:
                rows[0][i][j][0][0] = "".format(i + 1).replace(" ", ",")
            elif j == 3:
                treeview.insert('', 'end',
                                values=['PODSUMOWANIE DNIA:', '', round(sum_kcal), round(sum_b), round(sum_t),
                                        round(sum_w), round(sum_c, 2)])
            elif j == 4:
                treeview.insert('', 'end', values=['', '', '', '', '', '', ''])
            if j < 3:
                treeview.insert('', 'end', values=list(rows[0][i][j][0]))
                sum_kcal += float(rows[0][i][j][0][2].replace(",", "."))
                sum_b += float(rows[0][i][j][0][3].replace(",", "."))
                sum_t += float(rows[0][i][j][0][4].replace(",", "."))
                sum_w += float(rows[0][i][j][0][5].replace(",", "."))
                sum_c += float(rows[0][i][j][0][6].replace(",", "."))


def srodkowa_obwoluta(min_cost=0, first_cost=0, min_it=0, wspl_rozn=0, przeszukane_posilki=0, max_posilkow=0):
    xlbl11 = Label(wrapper02, text=min_cost, relief=RAISED, width=10)
    xlbl11.grid(row=0, column=1, padx=15, pady=3)
    xlbl21 = Label(wrapper02, text=first_cost, relief=RAISED, width=10)
    xlbl21.grid(row=1, column=1, padx=15, pady=3)
    xlbl31 = Label(wrapper02, text=round(first_cost - min_cost, 2), relief=RAISED, width=10)
    xlbl31.grid(row=0, column=3, padx=15, pady=3)
    xlbl41 = Label(wrapper02, text="{}/{}".format(przeszukane_posilki, max_posilkow), relief=RAISED, width=10)
    xlbl41.grid(row=1, column=3, padx=15, pady=3)
    xlbl51 = Label(wrapper02, text=min_it, relief=RAISED, width=10)
    xlbl51.grid(row=0, column=5, padx=15, pady=3)
    xlbl61 = Label(wrapper02, text="{}%".format(wspl_rozn), relief=RAISED, width=10)
    xlbl61.grid(row=1, column=5, padx=15, pady=3)


def run_ba():
    global najlepsze, do_wykresu
    najlepsze, do_wykresu, i_konc = BA(kcal, bialko, tluszcz, wegle, kcal_tol, bialko_tol, tluszcz_tol, wegle_tol,
                                       owoce, warzywa, zbozowe, nabial, mieso, inne,
                                       liczba_dni,
                                       liczebnosc_populacji_poczatkowej, czas_zycia, max_iteracji, wspolczynnik_kary,
                                       liczebnosc_sasiedztwa_e,
                                       roznorodnosc_sasiedztwa_e, liczebnosc_sasiedztwa_d, roznorodnosc_sasiedztwa_d,
                                       liczba_rozwiazan_elitarnych,
                                       liczba_rozwiazan_dobrych)

    srodkowa_obwoluta(min_cost=round(min(do_wykresu), 2), first_cost=round(do_wykresu[0], 2), min_it=i_konc,
                      wspl_rozn=int(kryterium_roznorodnosci(najlepsze[0]) * 100), przeszukane_posilki=len(set(mega_list)),
                      max_posilkow=len(posilki))
    update_window1(najlepsze)
    mega_list.clear()

def plot_chart():
    root = Tk()
    root.geometry("600x600")
    root.title("Wykres")
    fig = plt.figure(figsize=(10, 6), dpi=100)
    fig.add_subplot(111).plot(do_wykresu)
    plt.xlabel("Iteracje")
    plt.ylabel("Koszt diety")
    plt.title("Wykres kosztu calej diety od iteracji")

    canvas = FigureCanvasTkAgg(fig, master=root)  # A tk.DrawingArea.
    canvas.draw()
    canvas.get_tk_widget().pack(side=TOP, fill=BOTH, expand=1)
    # w tym jest opcja zapisania wykresu i przyblizania, ale to w razie W
    # toolbar = NavigationToolbar2Tk(canvas, root)
    # toolbar.update()
    # canvas.get_tk_widget().pack(side=TOP, fill=tkinter.BOTH, expand=1)


# WARTOSCI DOMYSLNE

kcal = 2607
bialko = 98
tluszcz = 87
wegle = 359
liczba_dni = 7

owoce = 0
warzywa = 1
zbozowe = 0
nabial = 0
mieso = 0
inne = 0

kcal_tol = 0.5
bialko_tol = 0.5
tluszcz_tol = 0.5
wegle_tol = 0.5

liczebnosc_populacji_poczatkowej = 20
czas_zycia = 1
max_iteracji = 9

wspolczynnik_kary = 1
liczebnosc_sasiedztwa_e = 2
roznorodnosc_sasiedztwa_e = 1

liczebnosc_sasiedztwa_d = 2
roznorodnosc_sasiedztwa_d = 2

liczba_rozwiazan_elitarnych = 3
liczba_rozwiazan_dobrych = 3


wlist = {var: StringVar() for var in ["0", "1", "2", "3", "4", "5", "6", "7", "8"]}

var1 = IntVar()  # owoce
var2 = IntVar()  # warzywa
var3 = IntVar()  # zboze
var4 = IntVar()  # nabial
var5 = IntVar()  # mieso
var6 = IntVar()  # inne
other1 = StringVar()
other2 = StringVar()
other3 = StringVar()
other4 = StringVar()
other5 = StringVar()
other6 = StringVar()
other7 = StringVar()
other8 = StringVar()
other9 = StringVar()
other10 = StringVar()

# Mini okna
wrapper01 = LabelFrame(tab1, text="Ograniczenia")
wrapper02 = LabelFrame(tab1, height=40)
wrapper03 = LabelFrame(tab1, text="Dieta")

xlbl10 = Label(wrapper02, text="Calkowity koszt diety:")
xlbl20 = Label(wrapper02, text="Koszt diety po pierwszym losowaniu:")
xlbl30 = Label(wrapper02, text="Roznica miedzy kosztami diet:")
xlbl40 = Label(wrapper02, text="Ilosc przeszukanych posilkow:")
xlbl50 = Label(wrapper02, text="Ilosc iteracji po zwroceniu rozwiazania:")
xlbl60 = Label(wrapper02, text="Wspl. roznorodnosci:")
xlbl10.grid(row=0, column=0, padx=15, pady=3)
xlbl20.grid(row=1, column=0, padx=15, pady=3)
xlbl30.grid(row=0, column=2, padx=15, pady=3)
xlbl40.grid(row=1, column=2, padx=15, pady=3)
xlbl50.grid(row=0, column=4, padx=15, pady=3)
xlbl60.grid(row=1, column=4, padx=15, pady=3)

# Uzupelnienie srodkowych wartosci na opis i wartosc 0
srodkowa_obwoluta()

wrapper01.pack(fill="both", expand="yes", padx=20, pady=5)
wrapper02.pack(fill="both", expand="yes", padx=20, pady=5)

wrapper03.pack(fill="both", expand="yes", padx=20, pady=5)

lbls_1 = [Label(wrapper01, text="Ilosc dni"), Label(wrapper01, text="Sugerowana wartosc kcal:"), Label(wrapper01, text="Kcal"),
          Label(wrapper01, text="Bialko"), Label(wrapper01, text="Tluszcze"), Label(wrapper01, text="Weglowodany"),
          Label(wrapper01, text="Tolerancja makroskladnikow [%]:"), Label(wrapper01, text="Tol. kcal"),
          Label(wrapper01, text="Tol. bialko"),
          Label(wrapper01, text="Tol. tluszcze"), Label(wrapper01, text="Tol. weglowodany")]

# ents_1 = [Entry(wrapper01, textvariable=w0), "zapychacz", Entry(wrapper01, textvariable=w1),
#           Entry(wrapper01, textvariable=w2), Entry(wrapper01, textvariable=w3), Entry(wrapper01, textvariable=w4),
#           "zapychacz", Entry(wrapper01, textvariable=w5), Entry(wrapper01, textvariable=w6),
#           Entry(wrapper01, textvariable=w7), Entry(wrapper01, textvariable=w8)]

# elblag = Label(wrapper01, text="Sugerowana ilosc kcal:2137")
# elblag.grid(row=1, column=2, padx=15, pady=3)

mystr = StringVar()
mystr.set('{}'.format(bialko*4 + tluszcz*9 + wegle*4))

entrblag = Entry(wrapper01, textvariable=mystr, state=DISABLED)
entrblag.grid(row=1, column=2, padx=15, pady=3)

ents_1 = [Entry(wrapper01, textvariable=wlist["0"]), "zapychacz", Entry(wrapper01, textvariable=wlist["1"]),
          Entry(wrapper01, textvariable=wlist["2"]), Entry(wrapper01, textvariable=wlist["3"]), Entry(wrapper01, textvariable=wlist["4"]),
          "zapychacz", Entry(wrapper01, textvariable=wlist["5"]), Entry(wrapper01, textvariable=wlist["6"]),
          Entry(wrapper01, textvariable=wlist["7"]), Entry(wrapper01, textvariable=wlist["8"])]
# Wpisanie wartosci domyslnych
ents_1[0].insert(0, liczba_dni)  # dni
ents_1[2].insert(0, kcal)  # kcal
ents_1[3].insert(0, bialko)  # bialko
ents_1[4].insert(0, tluszcz)  # tluszcze
ents_1[5].insert(0, wegle)  # wegle
ents_1[7].insert(0, int(kcal_tol * 100))  # tolerancja kcal w %
ents_1[8].insert(0, int(bialko_tol * 100))  # tolerancja kcal w %
ents_1[9].insert(0, int(tluszcz_tol * 100))  # tolerancja kcal w %
ents_1[10].insert(0, int(wegle_tol * 100))  # tolerancja kcal w %

for i in range(2):
    for j in range(len(ents_1)):
        if i == 0:
            lbls_1[j].grid(row=j, column=i, padx=15, pady=3)
        if i == 1:
            if ents_1[j] == "zapychacz":
                j += 1
                ents_1[j].grid(row=j, column=i + 1, padx=15, pady=3)
            else:
                ents_1[j].grid(row=j, column=i + 1, padx=15, pady=3)
# ograniczenia z ptaszkami, czyli checkbuttonami
lbl03 = Label(wrapper01, text="Dodatkowe ograniczenia:")
lbl03.grid(row=0, column=3, padx=15, pady=3)

check_btns = [Checkbutton(wrapper01, text='Owoce', variable=var1),
              Checkbutton(wrapper01, text='Warzywa', variable=var2),
              Checkbutton(wrapper01, text='Produkty zbozowe', variable=var3),
              Checkbutton(wrapper01, text='nabial', variable=var4),
              Checkbutton(wrapper01, text='mieso', variable=var5),
              Checkbutton(wrapper01, text='inne', variable=var6)]
for ckb in range(1, len(check_btns) + 1):
    check_btns[ckb - 1].grid(row=ckb, column=3, padx=15, pady=3)
check_btns[1].select()  # domyslnie jest warzywo

# pozostale ustawienia
lbl04 = Label(wrapper01, text="Ustawienia zaawansowane:")
lbl04.grid(row=0, column=4, padx=15, pady=3)

lbls_4 = [Label(wrapper01, text="Max iteracji"), Label(wrapper01, text="Liczebnosc populacji poczatkowej"),
          Label(wrapper01, text="Czas zycia populacji"),
          Label(wrapper01, text="Wspolczynnik kary"), Label(wrapper01, text="Liczebnosc sasiedztwa 'elitarnego'"),
          Label(wrapper01, text="Roznorodnosc sasiedztwa 'elitarnego'"),
          Label(wrapper01, text="Liczebnosc sasiedztwa 'dobrego'"),
          Label(wrapper01, text="Roznorodnosc sasiedztwa 'dobrego'"),
          Label(wrapper01, text="Liczba rozwiazan elitarnych"),
          Label(wrapper01, text="Liczba rozwiazan dobrych")]
ents_4 = [Entry(wrapper01, textvariable=other3), Entry(wrapper01, textvariable=other1),
          Entry(wrapper01, textvariable=other2), Entry(wrapper01, textvariable=other4),
          Entry(wrapper01, textvariable=other5), Entry(wrapper01, textvariable=other6),
          Entry(wrapper01, textvariable=other7), Entry(wrapper01, textvariable=other8),
          Entry(wrapper01, textvariable=other9), Entry(wrapper01, textvariable=other10)]
ents_4[0].insert(0, max_iteracji)
ents_4[1].insert(0, liczebnosc_populacji_poczatkowej)
ents_4[2].insert(0, czas_zycia)
ents_4[3].insert(0, wspolczynnik_kary)
ents_4[4].insert(0, liczebnosc_sasiedztwa_e)
ents_4[5].insert(0, roznorodnosc_sasiedztwa_e)
ents_4[6].insert(0, liczebnosc_sasiedztwa_d)
ents_4[7].insert(0, roznorodnosc_sasiedztwa_d)
ents_4[8].insert(0, liczba_rozwiazan_elitarnych)
ents_4[9].insert(0, liczba_rozwiazan_dobrych)

for i in range(2):
    for j in range(1, len(ents_4) + 1):
        row = j
        if i == 0:
            lbls_4[j - 1].grid(row=row, column=i + 4, padx=15, pady=3)

        if i == 1:
            ents_4[j - 1].grid(row=row, column=i + 5, padx=15, pady=3)

data_plt = Button(wrapper01, text="Zapisz dane", command=save_data, width=25)
data_plt.grid(row=2, column=7, padx=10, pady=3)

runba = Button(wrapper01, text="Dobierz diete", command=run_ba, width=25)
runba.grid(row=4, column=7, padx=10, pady=6)

plotchart = Button(wrapper01, text="Pokaz wykres", command=plot_chart, width=25)
plotchart.grid(row=6, column=7, padx=10, pady=6)

delete_btn = Button(wrapper01, text="Wyczysc tabele", command=delate, width=25)
delete_btn.grid(row=8, column=7, padx=10, pady=6)
# 1 Tabela
frm_wrp = Frame(wrapper03)
frm_wrp.pack(padx=20)
# scrollbar
scrollbar = Scrollbar(frm_wrp)
scrollbar.pack(side=RIGHT, fill=Y)
# tree view
treeview = Treeview(frm_wrp, yscrollcommand=scrollbar.set, columns=(1, 2, 3, 4, 5, 6, 7), show="headings",
                        height="15")
for i in range(1, 8):
    if i == 1:
        treeview.column(i, width=150)
    elif i == 2:
        treeview.column(i, width=350)
    else:
        treeview.column(i, width=100)

scrollbar.config(command=treeview.yview)
treeview.pack()

# kolumny
dict = {1: "", 2: "Nazwa posilku", 3: "kcal", 4: "bialko", 5: "tluszcze", 6: "weglowodany", 7: "cena"}
for i in dict:
    treeview.heading(i, text=dict[i])

"""-------------------------------------------------------------------------------------------"""

"""-------------------------------Drugie Okno-------------------------------------------------"""
tab3 = Frame(win)
tabGeneral.add(tab3, text='Dane')


def update(rows):
    # Tutaj jest na wstepie tworzona lista posilkow
    global mydata
    mydata = rows
    trv.delete(*trv.get_children())
    for i in rows:
        trv.insert('', 'end', values=i)


def search():
    q2 = q.get()
    temporary_list = list()
    # do stworzonej listy dodaje wektory, ktore wsadzam na zasadzie:
    # poczatek ma sie zgadzac, czyli: slowo sniadanie99 wyszuka sniadanie99, sniadanie991 itd.
    for i in posilki['posilek']:
        if i[:len(q2)] == q2:
            temporary_list.append(posilki[posilki.posilek == i].to_numpy())
    update(temporary_list)


def clear():
    update(posilki.to_numpy())


def call_variables(id):
    meal_id = id
    meal_name = t1.get().replace("'", "")
    meal_kcal = t2.get().replace("'", "").replace(".", ",")  # Ze stringa '444.4' robilo stringa "'444.4'" kij wie czego
    meal_b = t3.get().replace("'", "").replace(".", ",")  # I oczywiscie zamieniam "." na ","
    meal_t = t4.get().replace("'", "").replace(".", ",")
    meal_w = t5.get().replace("'", "").replace(".", ",")
    meal_c = t6.get().replace("'", "").replace(".", ",")
    meal_r = int(t7.get())
    m_owoc = int(t8.get())
    m_warz = int(t9.get())
    m_pz = int(t10.get())
    m_nab = int(t11.get())
    m_mieso = int(t12.get())
    m_inny = int(t13.get())
    array = [meal_id, meal_name, meal_kcal, meal_b, meal_t, meal_w, meal_c, m_owoc, m_warz, m_pz, m_nab, m_mieso,
             m_inny, meal_r]
    return array


def getrow(event):
    rowid = trv.identify_row(event.y)
    item = trv.item(trv.focus())
    t0.set(item['values'][0][1:])  # wycinam nawias [
    t1.set(item['values'][1])
    t2.set(item['values'][2])
    t3.set(item['values'][3])
    t4.set(item['values'][4])
    t5.set(item['values'][5])
    t6.set(item['values'][6])  # Cena
    t7.set(item['values'][13][:-1])  # Rodzaj i wycinam nawias ]
    t8.set(item['values'][7])  # owoce
    t9.set(item['values'][8])  # itd
    t10.set(item['values'][9])
    t11.set(item['values'][10])
    t12.set(item['values'][11])
    t13.set(item['values'][12])


def update_meal():
    meal_id = int(t0.get())
    array_ = call_variables(meal_id)
    if messagebox.askyesno("Potwierdzenie", "Czy na pewno chcesz dodac posilek?"):
        posilki.loc[meal_id] = array_
        clear()


def add_new():
    meal_id = posilki['nr'].to_numpy()[-1] + 1
    array_ = call_variables(meal_id)  # pobranie danych
    posilki.loc[meal_id] = array_
    clear()


def delete_meal():
    meal_id = int(t0.get())
    posilki.drop(posilki[posilki["nr"] == meal_id].index, inplace=True)
    clear()
    # for i in posilki['nr']:
    # if i == meal_id-1:
    #     if messagebox.askyesno("Potwierdzenie", "Czy na pewno chcesz usunac?"):
    #         posilki.drop(i, axis=0, inplace=True)


def exportcsv():
    return 1
    # if len(mydata) < 1:
    #     messagebox.showerror("Brak danych", "Export danych nie mozliwy")
    #     return False
    # fln = filedialog.asksaveasfilename(initialdir=os.getcwd(), title="Save CSV",
    #                                    fletypes=(("CSV File", "*.csv"), ("All Files", "*.*")))
    # with open(fln, mode='w') as myfile:
    #     exp_writer = csv.writer(myfile, delimeter=',')
    #     for i in mydata:
    #         exp_writer.writerow(i)
    # messagebox.showinfo("Eksport danych", "Export danych " + os.path.basename(fln) + " pomyslny.")


def importcsv():
    global posilki
    fln = filedialog.askopenfilename(title="Open CSV", filetypes=(("CSV files", "*.csv"), ("All Files", "*.*")))
    posilki = pd.read_csv(fln, sep=";")
    clear()


def savedb():
    return 1


# ZMIENNE OD ZBIERANIA DANYCH
q = StringVar()
t0 = StringVar()
t1 = StringVar()
t2 = StringVar()
t3 = StringVar()
t4 = StringVar()
t5 = StringVar()
t6 = StringVar()
t7 = StringVar()
t8 = StringVar()
t9 = StringVar()
t10 = StringVar()
t11 = StringVar()
t12 = StringVar()
t13 = StringVar()

# Mini okna
wrapper1 = LabelFrame(tab3, text="Meal list")
wrapper2 = LabelFrame(tab3, text="Search")
wrapper3 = LabelFrame(tab3, text="Meal data")

wrapper1.pack(fill="both", expand="yes", padx=20, pady=10)
wrapper2.pack(fill="both", expand="yes", padx=20, pady=10)
wrapper3.pack(fill="both", expand="yes", padx=20, pady=10)

# 1 Tabela
frm = Frame(wrapper1)
frm.pack(padx=20)
# scrollbar
scrollbar = Scrollbar(frm)
scrollbar.pack(side=RIGHT, fill=Y)
# tree view
trv = Treeview(frm, yscrollcommand=scrollbar.set, columns=(1, 2, 3, 4, 5, 6, 7), show="headings", height="20")
for i in range(1, 8):
    if i == 2:
        trv.column(i, width=400)
    else:
        trv.column(i, width=100)

scrollbar.config(command=trv.yview)
trv.column("#0", minwidth=0, width=10, stretch=NO)
trv.pack()

# kolumny
dict = {1: "Number", 2: "Nazwa posilku", 3: "kcal", 4: "bialko", 5: "tluszcze", 6: "weglowodany", 7: "cena"}
for i in dict:
    trv.heading(i, text=dict[i])
# Wpisanie danych domyslnych
update(posilki.to_numpy())  # potem juz bedzie uzywane clear()

trv.bind('<Double 1>', getrow)

# exporty
exbtn = Button(wrapper1, text="Export CSV", command=exportcsv, width=15)
exbtn.pack(side=LEFT, padx=10, pady=10)

impbtn = Button(wrapper1, text="Import CSV", command=importcsv, width=15)
impbtn.pack(side=LEFT, padx=10, pady=10)

savebtn = Button(wrapper1, text="Save Data", command=savedb, width=15)
savebtn.pack(side=LEFT, padx=10, pady=10)

# 2 Search
lbl = Label(wrapper2, text="Search")
lbl.pack(side=LEFT, padx=10)
ent = Entry(wrapper2, textvariable=q)
ent.pack(side=LEFT, padx=6)
btn = Button(wrapper2, text="Search", command=search, width=5)
btn.pack(side=LEFT, padx=6)
cbtn = Button(wrapper2, text="Clear", command=clear, width=5)
cbtn.pack(side=LEFT, padx=6)

# 3 Data Section
labels = [Label(wrapper3, text="Nazwa"), Label(wrapper3, text="kcal"), Label(wrapper3, text="bialko"),
          Label(wrapper3, text="tluszcze"), Label(wrapper3, text="weglowodany"), Label(wrapper3, text="cena"),
          Label(wrapper3, text="rodzaj"), Label(wrapper3, text="owoce"),
          Label(wrapper3, text="warzywa"), Label(wrapper3, text="produkty zbozowe"), Label(wrapper3, text="nabial"),
          Label(wrapper3, text="mieso"), Label(wrapper3, text="inne")]
entries = [Entry(wrapper3, textvariable=t1, width=60), Entry(wrapper3, textvariable=t2),
           Entry(wrapper3, textvariable=t3),
           Entry(wrapper3, textvariable=t4), Entry(wrapper3, textvariable=t5), Entry(wrapper3, textvariable=t6),
           Entry(wrapper3, textvariable=t7), Entry(wrapper3, textvariable=t8),
           Entry(wrapper3, textvariable=t9), Entry(wrapper3, textvariable=t10), Entry(wrapper3, textvariable=t11),
           Entry(wrapper3, textvariable=t12), Entry(wrapper3, textvariable=t13)]

for i in range(4):
    for j in range(len(entries)):
        if i == 0 and j < 7:
            labels[j].grid(row=j, column=i, padx=15, pady=3)
        if i == 1 and j < 7:
            entries[j].grid(row=j, column=i, padx=15, pady=3)
        if i == 2 and j >= 7:
            # if j == 7:
            #     continue
            labels[j].grid(row=j - 6, column=i, padx=15, pady=3)  # przez to -6 zamiast -7 jest miejsce na nazwe
        if i == 3 and j >= 7:
            # if j == 7:
            #     continue
            entries[j].grid(row=j - 6, column=i, padx=15, pady=3)

up_btn = Button(wrapper3, text="Update", command=update_meal)
add_btn = Button(wrapper3, text="Add New", command=add_new)
del_btn = Button(wrapper3, text="Delete", command=delete_meal)

add_btn.grid(row=14, column=0, padx=5, pady=3)
up_btn.grid(row=14, column=1, padx=5, pady=3)
del_btn.grid(row=14, column=2, padx=5, pady=3)
"""-------------------------------------------------------------------------------------------"""

tabGeneral.pack(expand=1, fill="both")
if __name__ == '__main__':
    win.mainloop()
