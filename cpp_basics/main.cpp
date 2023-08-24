#include <iostream>
#include <cmath>
#include <iomanip>

#include <string>
#include <fstream>


#include "course.hpp"
#include <cstring>
#include <algorithm>

#include <cstdlib>
#include <cstdlib>

typedef struct {
    uint8_t FontWidth;    /*!< Font width in pixels */
    uint8_t FontHeight;   /*!< Font height in pixels */
    const uint16_t *data; /*!< Pointer to data font data array */
} FontDef_t;

const uint16_t Font7x10 [] = {
        0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00,
        /* @10 '"' (8 pixels wide) */
        0x00, 0x28, 0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        /* @20 '#' (8 pixels wide) */
        0x00, 0x14, 0x14, 0x7E, 0x14, 0x28, 0x7E, 0x28, 0x28, 0x00,
        /* @30 '$' (8 pixels wide) */
        0x10, 0x38, 0x54, 0x50, 0x30, 0x18, 0x14, 0x54, 0x38, 0x10,
        /* @40 '%' (8 pixels wide) */
        0x00, 0x42, 0xA4, 0xA4, 0x48, 0x12, 0x25, 0x25, 0x42, 0x00,
};

FontDef_t Font_7x10 = {
        8,
        10,
        Font7x10
};

void showtab(uint16_t* tab,FontDef_t* font){

    std::cout<<(int)font->FontHeight<<std::endl;
    std::cout<<(int)font->FontWidth<<std::endl;


};
int main(){
    showtab(const_cast<uint16_t *>(Font7x10), &Font_7x10);


//
//        std::vector<unsigned char> hexValues = {
//                0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
//                0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
//                0x00, 0x00, 0x10, 0x00, 0x00, 0x00
//        };
//    for (const unsigned char hexValue : hexValues) {
//        for (int i = 7; i >= 0; --i) {
//            // Używamy operacji bitowych do uzyskania wartości binarnej.
//            // Przesuwamy 1 w lewo o 'i' miejsc i porównujemy z wartością hexValue.
//            // Jeśli jest ustawiony odpowiedni bit, wypisujemy 1, w przeciwnym razie 0.
//            std::cout << ((hexValue >> i) & 1);
//        }
//        std::cout << " "<<std::endl;
//    }
    return 0;
}