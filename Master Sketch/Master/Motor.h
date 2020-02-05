// Pins used for motordriver and motor
#define PWM         9                   //Pin for Power of motor.
#define DIR         10                  //Pin for Direction of the motor.

//#define STOP_DIST   5                 // error for stopping motor
#define MAX_MPWR    255                 // max motor power = MOTOR_PWR + MIN_MPWR <= 255
#define MIN_MPWR    0                   // initial minimum motor power
#define RANGE_STOP  3                   // error for stopping
#define RANGE_SLOW  5                  // error for slowing down
#define RET_ANG     120               // angle of fully retracted leg
#define EXT_ANG     0                 // angle of fully extended leg

int curr_ang = 0;                       // global variable for the current angle of the knee
int curr_speed = MIN_MPWR;              // global variable for the current speed of the motor (pwm)

// functions
void Init_Motors(void);
int rotate(int dir, int angle);






//uint16_t rotate(uint16_t halt, uint8_t pwm, uint8_t dir);
//uint16_t stall(uint8_t pwm, uint8_t dir);
