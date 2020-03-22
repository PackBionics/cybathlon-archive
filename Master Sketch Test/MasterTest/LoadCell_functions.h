#ifndef LoadCell_functions
#define LoadCell_functions

#include "HX711.h"

#define     BAUDRATE_LC         9600  // May not be needed if BAUDRATE used for SPI
                                      // is good enough for universal use
// 1. HX711 circuit wiring
#define     LOADCELL_DOUT_PIN1  4
#define     LOADCELL_DOUT_PIN2  5
#define     LOADCELL_DOUT_PIN3  6
#define     LOADCELL_DOUT_PIN4  7
#define     LOADCELL_SCK_PIN    8


// 2. Adjustment settings
#define     LOADCELL_OFFSET     0
#define     LOADCELL_DIVIDER    5895655000

// Declarations for loadcells
HX711 loadcell1; // front
HX711 loadcell2; // back
HX711 loadcell3; // left
HX711 loadcell4; // right
int lcFront;
int lcBack;
int lcLeft;
int lcRight;

// Functions
void Init_LC(void);
void Calibrate_LC(HX711 loadcell);
int Read_LC1(void);
int Read_LC2(void);
int Read_LC3(void);
int Read_LC4(void);

#endif