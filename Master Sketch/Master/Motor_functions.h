// Pins used for motordriver and motor
#define PWM         11                  //Pin for Power of motor.
#define DIR         12                  //Pin for Direction of the motor.
#define MTR_ENABLE  8                  //A0 Pin which enables power to the motor driver

//#define STOP_DIST   5                 // error for stopping motor
#define MAX_MPWR      255               // max motor power = MOTOR_PWR + MIN_MPWR <= 255
#define MIN_MPWR      0                 // initial minimum motor power
#define RANGE_STOP    1                 // error for stopping
#define RANGE_STOP_CAM    5                 // error for stopping
#define RANGE_SLOW    20                // error for slowing down
#define MAX_RET_ANG   80               // angle of fully retracted leg
#define MAX_EXT_ANG   0                 // angle of fully extended leg
#define MAX_CAM_ANG   66               // maximum angle for CAM for fully retracted leg
#define MIN_CAM_ANG   0                 // minimum angle for CAM for fully extended leg
#define MTR_FORWARD   HIGH              // motor direction for forwards (extension)
#define MTR_BACKWARD  LOW               // motor direction for backwards (retraction)
#define MIN_SSPEED    130                // minimum starting/end speed
#define ACC_CONST     1                 // default for acc_const [0] which is used for regular rotate
#define ACC_CONST_FIX 1                 // default for acc_const_fix [1] which is used for rotating the CAM to its correct position
#define RMP_DWN_CONST 0.2               // default ramp_down_const [0] which is used for regular rotate, lower means faster ramp down
#define RMP_DWN_CONST_FIX 0.2           // default ramp_down_const [1] which is used for rotating the CAM to its correct position, lower means faster ramp down

int curr_speed[2] = {MIN_MPWR, MIN_MPWR};              // global variable for the current speed of the motor (pwm)
int curr_dir[2] = {MTR_FORWARD, MTR_FORWARD};             // global variable for the current direction the motor is spinning
bool init_movement[2] = {false, false};             // global variable dictating whether this is the initial movement (true if movement in progress)
int dest_ang[2] = {0, 0};                       // global variable for destination angle for rotation (only changed when init_movement is set to true)
int init_ang[2] = {0, 0};                       // global variable for initial angle at start of movement (only set when init_movement is set to true)
float a[2] = {0, 0};                    // part of quadratic used for determining speed of motor (initialized at beginning of movement)
float b[2] = {0, 0};                    // part of quadratic used for determining speed of motor (initialized at beginning of movement)
float c[2] = {0, 0};                    // part of quadratic used for determining speed of motor (initialized at beginning of movement)
volatile bool updated_sensors_motor = false;  // boolean for determining whether the sensors have been updated since last call of motor function
double acc_const[2] = {ACC_CONST, ACC_CONST_FIX}; // constant used for determining 3rd point in quadratic equation used for determining speed
double ramp_down_const[2] = {RMP_DWN_CONST, RMP_DWN_CONST_FIX}; // constant used for determining how fast the motor ramps down when reversing from previous movement

// Constant Array for converting given cam angle to the corresponding knee angle
int enc_conversion[141] = {-2,
0,
1,
2,
2,
3,
4,
5,
5,
6,
7,
8,
8,
9,
10,
10,
11,
12,
13,
13,
14,
15,
16,
17,
17,
18,
18,
20,
20,
21,
21,
23,
23,
24,
25,
25,
26,
27,
28,
28,
29,
29,
31,
31,
32,
33,
34,
34,
36,
36,
37,
38,
39,
39,
41,
41,
42,
43,
44,
44,
46,
46,
47,
48,
49,
50,
51,
52,
53,
54,
55,
56,
57,
58,
59,
60,
61,
62,
63,
65,
66,
67,
68,
70,
71,
72,
74,
75,
77,
78,
80,
81,
83,
85,
87,
88,
90,
91,
94,
96,
97,
100,
102,
104,
107,
109,
112,
115,
117,
120,
123,
126,
129,
132,
135,
140
};

// functions
void Init_Motors(void);                     // initializes the motors
void calcParabConsts(int index);            // function to calculate constants used in the speed calculation
void rotate(int angle);                     // wrapper function for rotation logic (to rotate normally or fix cam position)
void rotate_helper(int angle, int index);   // helper function to rotate the knee
void Free_Swing(void);                      // Function that tries to mimic "free swing" by finding the "angle" of gravity
void cableTension(void);                    // Function to keep the cables in tension
int enc_convert(void);                      // gets the corresponding knee angle given the current CAM angle
void auto_cal_enc(void);                    // easy method to recalibrate CAM to Knee angles
