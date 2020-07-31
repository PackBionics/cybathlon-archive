#include "HX711.h"

#define     BAUDRATE_LC         9600  // May not be needed if BAUDRATE used for SPI
                                      // is good enough for universal use
// 1. HX711 circuit wiring
#define     LOADCELL_DOUT_PIN1  4
#define     LOADCELL_DOUT_PIN2  5
#define     LOADCELL_DOUT_PIN3  6
#define     LOADCELL_DOUT_PIN4  7
#define     LOADCELL_SCK_PIN1   22
#define     LOADCELL_SCK_PIN2   21
#define     LOADCELL_SCK_PIN3   8
#define     LOADCELL_SCK_PIN4   20



// 2. Adjustment settings
#define     LOADCELL_OFFSET1   1.631336256
#define     LOADCELL_DIVIDER1  7952.9
#define     LOADCELL_OFFSET2   8.066430817
#define     LOADCELL_DIVIDER2  8441.8
#define     LOADCELL_OFFSET3   5.344611733
#define     LOADCELL_DIVIDER3  7986
#define     LOADCELL_OFFSET4   4.810347797
#define     LOADCELL_DIVIDER4  8219.8

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
