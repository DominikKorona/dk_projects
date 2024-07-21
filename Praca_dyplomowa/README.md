# Development of an OLED display support library for embedded systems

W tym repozytorium umieszczono pliki, które zostały wykorzystane podczas projektu inżynierskiego. W folderze *LCD_Image_Converter_templates* umieszczono szablony w wykorzystywanym programie do generacji czcionek systemowych, obrazków czy własnych grafik. Przykładowe grafiki stworzone w programie #LCD Image Converter# przedstawiono poniżej.

<img src="https://github.com/user-attachments/assets/238fb10d-7a37-4f48-9831-4c921d9f5f18" width="700" alt="image">

W użytym programie w wygodny sposób dokonuje się konwersji z wczytanej czcionki systemowej czy też ręcznie zmienianej siatki pikseli na mapę bitową, którą wykorzystywyano przy użyciu języka C w projekcie dyplomowym.
<img src="https://github.com/user-attachments/assets/2ec55a22-7708-4b03-8c82-befa90d4d7fc" width="700" alt="image">

Główna część projektu znajduje się w pliku *OLED_Universal*, w którym zawarto wszystkie pliki konfiguracyjne. Projekt wykonano na module STM32f411RE oraz dwóch wyświetlaczach OLED ze sterownikami *SSD1306* oraz *SH1106*. W pierszym wyświetlaczu skupiono się na komunikacji przy pomocy interfejsu I2C, natomiast w drugim SPI. W ramach rozwoju projektu, zaimplementowano na obydwu wyświetlaczach mechanizm DMA.

Głównym celem projektu było zaimplementowanie uniwersalnej biblioteki do wyświetlaczy OLED w taki sposób, aby możliwie łatwo można było podmieniać wyświetlacze z różnymi parametrami, dlatego pliki rozdzielono na kilka modułów, opisanych w strukturze projektu poniżej.
## Struktura projektu
```bash
Core
├── Inc
│ ├── oled_Functions.h
│ ├── oled_Init.h
│ ├── oled_Comm.h
│ ├── oled_fonts.h
│ └── oled_bitmaps.h
└── src
  ├── oled_Functions.c
  ├── oled_Init.c
  ├── oled_Comm.c
  ├── oled_Arial8pt.c
  └── oled_ArialBold13pt.c
```
Celem "tak rozbudowanej" struktury plików było to, aby dokonywanie zmian w projekcie, zdeterminowanych np. zmianą wyświetlacza było jak najprostrze. 
* Pliki *oled_Functions.h/.c* zawierają funkcje tworzące grafikę w postaci pojedynczych pikseli, lini, figur czy też  na mapach bitowych generowanych we wcześniej wymienionym programie.
* Pliki *oled_Init.h/.c* zawierają sekwencje inicjalizacyjne wyświetlaczy, bufor GRAM zawierający informacje do bezpośredniego przekazania do wyświetlacza, funkcje Callback od DMA i funkcje odświerzania ekranu.
* Pliki *oled_Comm.h/.c* zawierają funkcje komunikujące się bezpośrednio ze sterownikiem. Zawarto w tych plikach odpowiednie funkcje do wysyłania pojedynczych komend, np. do wysyłania sekwencji pojedynczych bajtów w celach inicjalizacji sterownika, oraz do wysyłania danych, np. bufora GRAM w celu odświeżenia informacji wyświetlanych na matrycy OLED. Są to pliki na najniższej warstwie, ponieważ pracują bezpośrednio ze sprzętem.
* Pliki *oled_fonts.h/oled_bitmaps.h/oled_Arial...* zawierają zapisane bitmapy. Celem osobnego umieszczania czcionek jest możliwe ograniczenie miejsca w pamięci używanego mikrokontrolera.

Poniżej przedstawiono przykładowe wykorzystanie wyświetlaczy:

<img src="https://github.com/user-attachments/assets/9b18b531-f378-44c7-a8ae-dcb7d77f19b2" width="500" alt="image">

<br>

<img src="https://github.com/user-attachments/assets/5115cfd4-aea8-4a25-a3ce-d5f6f99c4c34" width="500" alt="image">
