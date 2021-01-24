// Figure out what's going on in our model
#define DEBUG 1
#define NUM_PREDICT 1
#define INPUT_SIZE 72

// Import TensorFlow stuff
#include "TensorFlowLite.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/version.h"

#include <string.h>  

// Our model
#include "lstm_knee_angle.h"

// TFLite globals, used for compatibility with Arduino-style sketches
namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* model_input = nullptr;
  TfLiteTensor* model_output = nullptr;

  // Create an area of memory to use for input, output, and other TensorFlow
  // arrays. You'll need to adjust this by combiling, running, and looking
  // for errors.
  constexpr int kTensorArenaSize = 60 * 1024;
  alignas(16) uint8_t tensor_arena[kTensorArenaSize];
} // namespace


// Array to store the next x=NUM_PREDICT predicted knee angles [t+1, t+2, t+3...]
float output_arr[NUM_PREDICT] = {0};


void Model_Init(void);
void Predict_Knee_Angle(float input_arr[]);

// constant vars
float subj_height = 1803.4; // mm
float floor_to_imu1 = 441.0; // mm
float floor_to_knee = 453.0; // mm
float floor_to_hip = 983.0; // mm
float knee_to_imu2 = 50.0; // mm
float subj_weight = 74.8427; // kg
float female = 0.0;
float male = 1.0;

// test_vars
float input_arr_test[INPUT_SIZE] = {
  female,
  male,
  subj_weight,
  subj_height,
  floor_to_imu1,
  floor_to_knee,
  floor_to_hip,
  knee_to_imu2,
  9.03,
  3.74,
  0.67,
  -13.56,
  -12.44,
  -86.25,
  1.14,
  -0.84,
  2.22,
  -0.000391,
  -0.000438,
  -0.000871,
  3.921499,
  67.180176,
  22.442563,
  9.48,
  2.41,
  0.57,
  -72.44,
  -7.75,
  -115.87,
  1.0,
  -2.86,
  -0.69,
  -0.000265,
  -0.000089,
  0.00019,
  3.335028,
  75.359628,
  14.238884,
  1.4015,
  9.3,
  3.01,
  0.66,
  -34.19,
  5.06,
  -81.12,
  1.34,
  -2.24,
  -1.73,
  0.001074,
  0.00036,
  0.000976,
  3.862712,
  71.667638,
  17.89236,
  0.196279,
  9.2,
  3.29,
  0.7,
  0.44,
  3.25,
  -55.06,
  0.13,
  0.83,
  -0.49,
  0.001012,
  -0.000053,
  0.000761,
  4.09788,
  69.916907,
  19.625118,
  2.003998,
  1.866442
};
