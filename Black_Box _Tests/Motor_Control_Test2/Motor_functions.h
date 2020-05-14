// Pins used for motordriver and motor
#define PWM         11                  //Pin for Power of motor.
#define DIR         12                  //Pin for Direction of the motor.

//#define STOP_DIST   5                 // error for stopping motor
#define MAX_MPWR      255               // max motor power = MOTOR_PWR + MIN_MPWR <= 255
#define MIN_MPWR      0                 // initial minimum motor power
#define RANGE_STOP    2                 // error for stopping
#define RANGE_SLOW    20                // error for slowing down
#define MAX_RET_ANG   115               // angle of fully retracted leg
#define MAX_EXT_ANG   0                 // angle of fully extended leg
#define MTR_FORWARD   HIGH              // motor direction for forwards (extension)
#define MTR_BACKWARD  LOW               // motor direction for backwards (retraction)
#define MIN_SSPEED    30                // minimum starting/end speed
#define ACC_CONST     1                 // default for acc_const
#define RMP_DWN_CONST 0.2               // default ramp_down_const


int curr_speed = MIN_MPWR;              // global variable for the current speed of the motor (pwm)
int curr_dir = MTR_FORWARD;             // global variable for the current direction the motor is spinning
bool init_movement = false;             // global variable dictating whether this is the initial movement (true if movement in progress)
int dest_ang = 0;                       // global variable for destination angle for rotation (only changed when init_movement is set to true)
int init_ang = 0;                       // global variable for initial angle at start of movement (only set when init_movement is set to true)
float a;                                // part of quadratic used for determining speed of motor (initialized at beginning of movement)
float b;                                // part of quadratic used for determining speed of motor (initialized at beginning of movement)
float c;                                // part of quadratic used for determining speed of motor (initialized at beginning of movement)
bool updated_sensors_motor = false;     // boolean for determining whether the sensors have been updated since last call of motor function
double acc_const = ACC_CONST;           // constant used for determining 3rd point in quadratic equation used for determining speed
double ramp_down_const = RMP_DWN_CONST; // constant used for determining how fast the motor ramps down when reversing from previous movement

// functions
void Init_Motors(void);
void calcParabConsts(void);
void rotate(int angle);
// Function that tries to mimic "free swing" by finding the "angle" of gravity
void Free_Swing(void);
// Function to keep the cables in tension
void cableTension(void);
