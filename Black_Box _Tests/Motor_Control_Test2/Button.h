// Pin on Arduino Micro for button 
#define LOCKED_BUTTON 13

void Init_Button(void);

volatile int button_state; // 1 is pressed, 0 is not pressed
