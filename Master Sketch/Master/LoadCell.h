#include "HX711.h"

// Declarations for loadcells
HX711 loadcell1;
HX711 loadcell2;
HX711 loadcell3;
HX711 loadcell4;

#define     BAUDRATE_LC         9600

// 1. HX711 circuit wiring
#define     LOADCELL_DOUT_PIN1  4
#define     LOADCELL_DOUT_PIN2  5
#define     LOADCELL_DOUT_PIN3  6
#define     LOADCELL_DOUT_PIN4  7
#define     LOADCELL_SCK_PIN    9


// 2. Adjustment settings
#define     LOADCELL_OFFSET     0
#define     LOADCELL_DIVIDER    5895655000

void Init_LC(void);
void Calibrate_LC(HX711 loadcell);
