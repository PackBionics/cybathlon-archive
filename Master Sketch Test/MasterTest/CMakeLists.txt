cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME MasterSketch)
project(${PROJECT_NAME})
#set(${PROJECT_NAME}_AFLAGS -v)
set(ARDUINO_SDK_PATH /Applications/Arduino.app/Contents/java)

# Define project sketch file
set(${CMAKE_PROJECT_NAME}_SKETCH MasterSketch.ino)

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD micro)
set(${CMAKE_PROJECT_NAME}_PORT /dev/cu.usbmodem143101)
#set(mega.build.mcu atmega32u4)
#set(mega.upload.protocol wiring)
#set(micro.upload.speed 115200)

# Add library directory to project path
include_directories(${PROJECT_SOURCE_DIR}/libraries/Adafruit_MMA8451)
include_directories(${PROJECT_SOURCE_DIR}/libraries/Adafruit_Sensor)
include_directories(${PROJECT_SOURCE_DIR}/libraries/TimerOne)
#target_include_directories(Adafruit_MMA8451 PRIVATE "libraries/Adafruit_MMA8451")

#generate_arduino_library(HX711
#        SRCS HX711.ino
#        HDRS  HX711.h
#        BOARD micro)

generate_arduino_library(Adafruit_MMA8451
        SRCS  libraries/Adafruit_MMA8451/Adafruit_MMA8451.cpp
        HDRS  libraries/Adafruit_MMA8451/Adafruit_MMA8451.h
        BOARD micro)

generate_arduino_library(Adafruit_Sensor
        SRCS  libraries/Adafruit_Sensor/Adafruit_Sensor.cpp
        HDRS  libraries/Adafruit_Sensor/Adafruit_Sensor.h
        BOARD micro)

generate_arduino_library(TimerOne
        SRCS  libraries/TimerOne/TimerOne.cpp
        HDRS  libraries/TimerOne/TimerOne.h
        BOARD micro)

# Define header files
set(${PROJECT_NAME}_HDRS  Accelerometer_functions.h Button.h Encoder_functions.h FSM.h Inner_FSMs.h
        LoadCell_functions.h Motor_functions.h Sensor_Interrupt.h)
# Define source files
set(${PROJECT_NAME}_SRCS Accelerometer_functions.ino Button.ino Encoder_functions.ino FSM.ino Inner_FSMs.ino
        LoadCell_functions.ino Motor_functions.ino Sensor_Interrupt.ino)

#set(${PROJECT_NAME}_LIBS HX711)
set(${PROJECT_NAME}_LIBS Adafruit_MMA8451)
set(${PROJECT_NAME}_LIBS Adafruit_Sensor)
set(${PROJECT_NAME}_LIBS TimerOne)

# Build project firmware
generate_arduino_firmware(${CMAKE_PROJECT_NAME})