#include "HX711.h"

#define     BAUDRATE_LC         9600  // May not be needed if BAUDRATE used for SPI
                                      // is good enough for universal use
// 1. HX711 circuit wiring
#define     LOADCELL_DOUT_PIN1  6
#define     LOADCELL_DOUT_PIN2  5
#define     LOADCELL_DOUT_PIN3  4
#define     LOADCELL_DOUT_PIN4  7
#define     LOADCELL_SCK_PIN1   19
#define     LOADCELL_SCK_PIN2   20
#define     LOADCELL_SCK_PIN3   21
#define     LOADCELL_SCK_PIN4   22



// 2. Adjustment settings
#define     LOADCELL_OFFSET1   1.631336256 - 261
//#define     LOADCELL_DIVIDER1  7952.9  // 1.834 mV/V  1.469 mV/V  62
#define     LOADCELL_DIVIDER1  7692.35
#define     LOADCELL_OFFSET2   8.066430817 - 30.5
//#define     LOADCELL_DIVIDER2  8441.8  // 1.874 mV/V  1.484 mV/V  61
#define     LOADCELL_DIVIDER2  7860.96
#define     LOADCELL_OFFSET3   5.344611733 + 146
//#define     LOADCELL_DIVIDER3  7986    // 1.826 mV/V  1.482 mV/V  72
#define     LOADCELL_DIVIDER3  7793.44
#define     LOADCELL_OFFSET4   4.810347797 + 222
//#define     LOADCELL_DIVIDER4  8219.8  // 1.858 mV/V  1.478 mV/V  65
#define     LOADCELL_DIVIDER4  7657.12
//#define     LOADCELL_OFFSET1   0
//#define     LOADCELL_DIVIDER1  1
//#define     LOADCELL_OFFSET2   0
//#define     LOADCELL_DIVIDER2  1
//#define     LOADCELL_OFFSET3   0
//#define     LOADCELL_DIVIDER3  1
//#define     LOADCELL_OFFSET4   0
//#define     LOADCELL_DIVIDER4  1


// Declarations for loadcells
HX711 loadcell1; // front
HX711 loadcell2; // back
HX711 loadcell3; // left
HX711 loadcell4; // right
long lcFront;
long lcBack;
long lcLeft;
long lcRight;

// Functions
void Init_LC(void);
void Calibrate_LC(HX711 loadcell);
long Read_LC1(void);
long Read_LC2(void);
long Read_LC3(void);
long Read_LC4(void);
