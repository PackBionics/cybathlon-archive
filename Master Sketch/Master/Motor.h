
// constants 
#define MOTOR_SPEED  180                   //Change speed of the motor.

// Pins used for motordriver and motor
#define PWM         9                     //Pin for Power of motor.
#define DIR         10                    //Pin for Direction of the motor.

#define STOP_DIST   5                     // error for stopping motor
#define MAX_DIST    16384                 // 2^14 is the max distance
#define MOTOR_PWR   200                   // max motor power = MOTOR_PWR + MIN_MPWR <= 255
#define MIN_MPWR    55                    // minimum motor power

// functions
void Init_Motors(void);
uint16_t rotate(uint16_t halt, uint8_t pwm, uint8_t dir);
uint16_t stall(uint8_t pwm, uint8_t dir);
