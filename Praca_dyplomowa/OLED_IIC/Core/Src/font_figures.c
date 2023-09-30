
#include "fonts.h"

/*
**  Font data for MS Shell Dlg 2 8pt
*/

/* Character bitmaps for MS Shell Dlg 2 8pt */

const uint8_t figures_8pt[] = {
    
    //∙∙∙∙∙∙
    //∙∙∙∙∙∙
    //∙∙∙∙∙∙
    //∙∙∙∙∙∙
    //∙∙∙∙∙∙
    //∙∙∙∙∙∙
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,

    //∙∙∙∙∙∙
    //∙∙██∙∙
    //∙∙██∙∙
    //∙████∙
    //∙∙██∙∙
    //∙████∙
    0x00, 
    0x30, 
    0x30, 
    0x78, 
    0x30, 
    0x78,

    //∙█∙∙█∙
    //∙████∙
    //∙∙██∙∙
    //∙∙██∙∙
    //∙∙██∙∙
    //∙████∙
    0x48, 
    0x78, 
    0x30, 
    0x30, 
    0x30, 
    0x78,

    //∙∙█∙∙█
    //∙∙∙██∙
    //∙██∙█∙
    //∙██∙█∙
    //∙∙∙██∙
    //∙∙███∙
    0x24, 
    0x18, 
    0x68, 
    0x68, 
    0x18, 
    0x38,

    //∙∙██∙∙
    //∙█∙∙█∙
    //█∙∙∙∙█
    //∙█∙∙█∙
    //∙∙██∙∙
    //██████
    0x30, 
    0x48, 
    0x84, 
    0x48, 
    0x30, 
    0xfc,

    //∙∙██∙∙
    //█∙██∙█
    //██████
    //██████
    //∙████∙
    //∙████∙
    0x30, 
    0xb4, 
    0xfc, 
    0xfc, 
    0x78, 
    0x78,

    //∙∙██∙∙
    //██████
    //██∙∙██
    //∙████∙
    //∙████∙
    //∙∙██∙∙
    0x30, 
    0xfc, 
    0xcc, 
    0x78, 
    0x78, 
    0x30

};
/* Font information for figures */
FontDef_t figures_6x6 =
{
    6, /*  Width, in pixels, of space character */
    6, /*  Character height */
    figures_8pt, /*  Character bitmap array */
};
