#include <Arduino.h>
#include "Button.h"

/**
 * Initializes button for Locked state
 */
void Init_Button() {
  pinMode(LOCKED_BUTTON, INPUT);
}
