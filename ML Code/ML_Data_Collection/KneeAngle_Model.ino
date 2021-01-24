void Model_Init() {
  // Wait for Serial to connect
  #if DEBUG
    while(!Serial);
  #endif

  // Set up logging (will report to Serial, even within TFLite functions)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure
  model = tflite::GetModel(lstm_knee_angle);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report("Model version does not match Schema");
    while(1);
  }

  // Pull in only needed operations (should match NN layers)
  // Available ops:
  //  https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/micro/kernels/micro_ops.h
//  static tflite::MicroMutableOpResolver micro_mutable_op_resolver;
//  micro_mutable_op_resolver.AddBuiltin(
//    tflite::BuiltinOperator_FULLY_CONNECTED,
//    tflite::ops::micro::Register_FULLY_CONNECTED(),
//    1, 3);
//  micro_mutable_op_resolver.AddBuiltin(
//    tflite::BuiltinOperator_ADD,
//    tflite::ops::micro::Register_ADD(),
//    1, 3);
//  micro_mutable_op_resolver.AddBuiltin(
//    tflite::BuiltinOperator_MUL,
//    tflite::ops::micro::Register_MUL(),
//    1, 3);
//  micro_mutable_op_resolver.AddBuiltin(
//    tflite::BuiltinOperator_RESHAPE,
//    tflite::ops::micro::Register_RESHAPE(),
//    1, 3);
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model
  static tflite::MicroInterpreter static_interpreter(
    model, resolver, tensor_arena, kTensorArenaSize,
    error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    while(1);
  }

  // Assign model input and output buffers (tensors) to pointers
  model_input = interpreter->input(0);
  model_output = interpreter->output(0);

  // Get information about the memory area to use for the model's input
  // Supported data types:
  // https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/c/common.h#L226
  #if DEBUG
    Serial.print("Input Number of dimensions: ");
    Serial.println(model_input->dims->size);
    Serial.print("Dim 1 size: ");
    Serial.println(model_input->dims->data[0]);
    Serial.print("Dim 2 size: ");
    Serial.println(model_input->dims->data[1]);
//    Serial.print("Dim 3 size: ");
//    Serial.println(model_input->dims->data[2]);
    Serial.print("Input type: ");
    Serial.println(model_input->type);
    Serial.print("Output Number of dimensions: ");
    Serial.println(model_output->dims->size);
    Serial.print("Dim 1 size: ");
    Serial.println(model_output->dims->data[0]);
    Serial.print("Dim 2 size: ");
    Serial.println(model_output->dims->data[1]);
//    Serial.print("Dim 3 size: ");
//    Serial.println(model_output->dims->data[2]);
    Serial.print("Output type: ");
    Serial.println(model_output->type);
  #endif

}

void Predict_Knee_Angle(float input_arr[]) {
  #if DEBUG
    unsigned long start_timestamp = micros();
  #endif

  // Copy value to input buffer (tensor)
  for (int i = 0; i < INPUT_SIZE; i++) {
    Serial.println(input_arr[i]);
//    model_input->data.f[i] = input_arr[i];
    model_input->data.f[i] = (float) 0.00;
  }
  Serial.println("Invoking...");
  // Run inference
  TfLiteStatus invoke_status = interpreter->Invoke();
  Serial.println("Done Invoking");
  if (invoke_status != kTfLiteOk) {
    String err_input = "";
    for (int i = 0; i < INPUT_SIZE; i++) {
      char str_buffer[5];
      snprintf(str_buffer, 5, "%f", input_arr[i]);
      err_input += str_buffer;
    }
    error_reporter->Report("Invoke failed on input: %s\n", err_input);
  }

  // Read predicted y value from output buffer (tensor)
  for (int i = 0; i < NUM_PREDICT; i++) {
    output_arr[i] = model_output->data.f[i];
  }

  // Print value
  Serial.print("Predicted Angle: "); 
  for (int i = 0; i < NUM_PREDICT; i++) {
    Serial.print(output_arr[i]); Serial.print("\t");
  }
  Serial.println();

  #if DEBUG
    Serial.print("Time for inference (us): ");
    Serial.println(micros() - start_timestamp);
  #endif
}
