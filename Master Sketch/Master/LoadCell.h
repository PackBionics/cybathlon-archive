#include "HX711.h"

// Declarations for loadcells
HX711 loadcell1;
HX711 loadcell2;
HX711 loadcell3;
HX711 loadcell4;

// 1. HX711 circuit wiring
#define     LOADCELL_DOUT_PIN1  2
#define     LOADCELL_DOUT_PIN2  4
#define     LOADCELL_DOUT_PIN3  2
#define     LOADCELL_DOUT_PIN4  4
#define     LOADCELL_SCK_PIN    3


// 2. Adjustment settings
#define     LOADCELL_OFFSET     50682624
#define     LOADCELL_DIVIDER    5895655

void Init_LC(void);
void Calibrate_LC(uint8_t loadcell);
