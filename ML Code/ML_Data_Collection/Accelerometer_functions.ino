void Init_Accelerometer() {

  /* Initialize Reset Pin  */
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);

  /* Initialise the sensor */
  if(!bno1.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055_1 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  calibration_sequence(true, FULL_CALIBRATION);
  delay(1000);
    
//  bno1.setExtCrystalUse(true);

    /* Initialise the sensor */
  if(!bno2.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055_2 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  calibration_sequence(false, FULL_CALIBRATION);
  delay(1000);
    
//  bno2.setExtCrystalUse(true);
}

void Rst_Acc() {
  digitalWrite(RESET_PIN, LOW);
  digitalWrite(RESET_PIN, HIGH);
  delay(100);
  bno1.begin();
  bno2.begin();
  was_fixed = true;
  delay(20);
}

void calibration_sequence(bool first, bool full_calib) {
    int eeAddress;
//    Serial.println(sizeof(long));
//    Serial.println(sizeof(adafruit_bno055_offsets_t));
    if (first) {
      eeAddress = 0;
    } else {
      eeAddress = sizeof(adafruit_bno055_offsets_t) + sizeof(long);
    }
    long bnoID;
    bool foundCalib = false;

    EEPROM.get(eeAddress, bnoID);

    Serial.print("Address: "); Serial.println(eeAddress);
    Serial.print("EEPROM BNOID: "); Serial.println(bnoID);

    adafruit_bno055_offsets_t calibrationData;
    sensor_t sensor;

    /*
    *  Look for the sensor's unique ID at the beginning oF EEPROM.
    *  This isn't foolproof, but it's better than nothing.
    */
    if (first) {
      bno1.getSensor(&sensor);
    } else {
      bno2.getSensor(&sensor);
    }
    Serial.print("Sensor ID: "); Serial.println(sensor.sensor_id);
    if (bnoID != sensor.sensor_id || full_calib)
    {
        Serial.println("\nNo Calibration Data for this sensor exists in EEPROM");
        delay(500);
    }
    else
    {
        Serial.println("\nFound Calibration for this sensor in EEPROM.");
        eeAddress += sizeof(long);
        EEPROM.get(eeAddress, calibrationData);

        displaySensorOffsets(calibrationData);

        Serial.println("\n\nRestoring Calibration data to the BNO055...");
        if (first) {
          bno1.setSensorOffsets(calibrationData);
        } else {
          bno2.setSensorOffsets(calibrationData);
        }

        Serial.println("\n\nCalibration data loaded into BNO055");
        foundCalib = true;
    }

    delay(1000);

    /* Display some basic information on this sensor */
    displaySensorDetails(first);

    /* Optional: Display current status */
    displaySensorStatus(first);

   /* Crystal must be configured AFTER loading calibration data into BNO055. */
   if (first) {
      bno1.setExtCrystalUse(true);
   } else {
      bno2.setExtCrystalUse(true);
   }

    sensors_event_t event;
    if (first) {
      bno1.getEvent(&event);
    } else {
      bno2.getEvent(&event);
    }
    /* always recal the mag as It goes out of calibration very often */
    if (foundCalib){
        Serial.println("Move sensor slightly to calibrate magnetometers");
        if (first) {
          while (!bno1.isFullyCalibrated())
          {
              bno1.getEvent(&event);
              delay(BNO055_SAMPLERATE_DELAY_MS);
          }
        } else {
          while (!bno2.isFullyCalibrated())
          {
              bno2.getEvent(&event);
              delay(BNO055_SAMPLERATE_DELAY_MS);
          }
        }
    }
    else
    {
        Serial.println("Please Calibrate Sensor: ");
        if (first) {
          while (!bno1.isFullyCalibrated())
          {
              bno1.getEvent(&event);
  
              Serial.print("X: ");
              Serial.print(event.orientation.x, 4);
              Serial.print("\tY: ");
              Serial.print(event.orientation.y, 4);
              Serial.print("\tZ: ");
              Serial.print(event.orientation.z, 4);
  
              /* Optional: Display calibration status */
              displayCalStatus(first);
  
              /* New line for the next sample */
              Serial.println("");
  
              /* Wait the specified delay before requesting new data */
              delay(BNO055_SAMPLERATE_DELAY_MS);
          }
        } else {
          while (!bno2.isFullyCalibrated())
          {
              bno2.getEvent(&event);
  
              Serial.print("X: ");
              Serial.print(event.orientation.x, 4);
              Serial.print("\tY: ");
              Serial.print(event.orientation.y, 4);
              Serial.print("\tZ: ");
              Serial.print(event.orientation.z, 4);
  
              /* Optional: Display calibration status */
              displayCalStatus(first);
  
              /* New line for the next sample */
              Serial.println("");
  
              /* Wait the specified delay before requesting new data */
              delay(BNO055_SAMPLERATE_DELAY_MS);
          }
        }
    }

    Serial.println("\nFully calibrated!");
    Serial.println("--------------------------------");
    Serial.println("Calibration Results: ");
    adafruit_bno055_offsets_t newCalib;
    if (first) {
      bno1.getSensorOffsets(newCalib);
    } else {
      bno2.getSensorOffsets(newCalib);
    }
    displaySensorOffsets(newCalib);

    Serial.println("\n\nStoring calibration data to EEPROM...");

    if (first) {
      eeAddress = 0;
      bno1.getSensor(&sensor);
    } else {
      eeAddress = sizeof(adafruit_bno055_offsets_t) + sizeof(long);
      bno2.getSensor(&sensor);
    }
    bnoID = sensor.sensor_id;

    Serial.print("Address: "); Serial.println(eeAddress);
    Serial.print("EEPROM BNOID: "); Serial.println(bnoID);
    
    EEPROM.put(eeAddress, bnoID);

    eeAddress += sizeof(long);
    
    Serial.print("Address: "); Serial.println(eeAddress);
//    Serial.print("EEPROM New Calibration Data: "); Serial.println(newCalib);
    EEPROM.put(eeAddress, newCalib);
    Serial.println("Data stored to EEPROM.");

    Serial.println("\n--------------------------------\n");
}

void display_all_sensors() {
    Serial.print("Grav1: \t"); Serial.print(gravX1); Serial.print("\t"); Serial.print(gravY1); Serial.print("\t"); Serial.print(gravZ1); Serial.print("\t");
    Serial.print("Gyro1: \t"); Serial.print(gyroX1); Serial.print("\t"); Serial.print(gyroY1); Serial.print("\t"); Serial.print(gyroZ1); Serial.print("\t");
    Serial.print("Magnet1: \t"); Serial.print(magnetX1); Serial.print("\t"); Serial.print(magnetY1); Serial.print("\t"); Serial.print(magnetZ1); Serial.print("\t");
    Serial.print("Euler1: \t"); Serial.print(eulX1); Serial.print("\t"); Serial.print(eulY1); Serial.print("\t"); Serial.print(eulZ1); Serial.print("\t");
    Serial.print("Acc1: \t"); Serial.print(accX1); Serial.print("\t"); Serial.print(accY1); Serial.print("\t"); Serial.print(accZ1); Serial.print("\t");
    Serial.print("LinAcc1: \t"); Serial.print(linaccX1); Serial.print("\t"); Serial.print(linaccY1); Serial.print("\t"); Serial.print(linaccZ1); Serial.print("\t");
    Serial.print("Quat1: \t"); Serial.print(quatW1); Serial.print("\t"); Serial.print(quatX1); Serial.print("\t"); Serial.print(quatY1); Serial.print("\t"); Serial.print(quatZ1); Serial.print("\t");
  
    Serial.print("Grav2: \t"); Serial.print(gravX2); Serial.print("\t"); Serial.print(gravY2); Serial.print("\t"); Serial.print(gravZ2); Serial.print("\t");
    Serial.print("Gyro2: \t"); Serial.print(gyroX2); Serial.print("\t"); Serial.print(gyroY2); Serial.print("\t"); Serial.print(gyroZ2); Serial.print("\t");
    Serial.print("Magnet2: \t"); Serial.print(magnetX2); Serial.print("\t"); Serial.print(magnetY2); Serial.print("\t"); Serial.print(magnetZ2); Serial.print("\t");
    Serial.print("Euler2: \t"); Serial.print(eulX2); Serial.print("\t"); Serial.print(eulY2); Serial.print("\t"); Serial.print(eulZ2); Serial.print("\t");
    Serial.print("Acc2: \t"); Serial.print(accX2); Serial.print("\t"); Serial.print(accY2); Serial.print("\t"); Serial.print(accZ2); Serial.print("\t");
    Serial.print("LinAcc2: \t"); Serial.print(linaccX2); Serial.print("\t"); Serial.print(linaccY2); Serial.print("\t"); Serial.print(linaccZ2); Serial.print("\t");
    Serial.print("Quat2: \t"); Serial.print(quatW2); Serial.print("\t"); Serial.print(quatX2); Serial.print("\t"); Serial.print(quatY2); Serial.print("\t"); Serial.print(quatZ2); Serial.print("\t");
}

void display_quats() {
    Serial.print("Quat1: \t"); Serial.print(quatW1); Serial.print("\t"); Serial.print(quatX1); Serial.print("\t"); Serial.print(quatY1); Serial.print("\t"); Serial.print(quatZ1); Serial.print("\t");
    Serial.print("Quat2: \t"); Serial.print(quatW2); Serial.print("\t"); Serial.print(quatX2); Serial.print("\t"); Serial.print(quatY2); Serial.print("\t"); Serial.print(quatZ2); Serial.print("\t");
}

void display_eul() {
    Serial.print("Euler1: \t"); Serial.print(eulX1); Serial.print("\t"); Serial.print(eulY1); Serial.print("\t"); Serial.print(eulZ1); Serial.print("\t");
    Serial.print("Euler2: \t"); Serial.print(eulX2); Serial.print("\t"); Serial.print(eulY2); Serial.print("\t"); Serial.print(eulZ2); Serial.print("\t");
}


/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
    */
/**************************************************************************/
void displaySensorDetails(bool first)
{
    sensor_t sensor;
    if (first) {
        bno1.getSensor(&sensor);
    } else {
        bno2.getSensor(&sensor);
    }
    Serial.println("------------------------------------");
    Serial.print("Sensor:       "); Serial.println(sensor.name);
    Serial.print("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
    Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
    Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
    */
/**************************************************************************/
void displaySensorStatus(bool first)
{
    /* Get the system status values (mostly for debugging purposes) */
    uint8_t system_status, self_test_results, system_error;
    system_status = self_test_results = system_error = 0;
    if (first) {
      bno1.getSystemStatus(&system_status, &self_test_results, &system_error);
    } else {
      bno2.getSystemStatus(&system_status, &self_test_results, &system_error);
    }
    /* Display the results in the Serial Monitor */
    Serial.println("");
    Serial.print("System Status: 0x");
    Serial.println(system_status, HEX);
    Serial.print("Self Test:     0x");
    Serial.println(self_test_results, HEX);
    Serial.print("System Error:  0x");
    Serial.println(system_error, HEX);
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
    */
/**************************************************************************/
void displayCalStatus(bool first)
{
    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    if (first) {
      bno1.getCalibration(&system, &gyro, &accel, &mag);
    } else {
      bno2.getCalibration(&system, &gyro, &accel, &mag);
    }
    /* The data should be ignored until the system calibration is > 0 */
    Serial.print("\t");
    if (!system)
    {
        Serial.print("! ");
    }

    /* Display the individual values */
    Serial.print("Sys:");
    Serial.print(system, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel, DEC);
    Serial.print(" M:");
    Serial.print(mag, DEC);
}

/**************************************************************************/
/*
    Display the raw calibration offset and radius data
    */
/**************************************************************************/
void displaySensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
    Serial.print("Accelerometer: ");
    Serial.print(calibData.accel_offset_x); Serial.print(" ");
    Serial.print(calibData.accel_offset_y); Serial.print(" ");
    Serial.print(calibData.accel_offset_z); Serial.print(" ");

    Serial.print("\nGyro: ");
    Serial.print(calibData.gyro_offset_x); Serial.print(" ");
    Serial.print(calibData.gyro_offset_y); Serial.print(" ");
    Serial.print(calibData.gyro_offset_z); Serial.print(" ");

    Serial.print("\nMag: ");
    Serial.print(calibData.mag_offset_x); Serial.print(" ");
    Serial.print(calibData.mag_offset_y); Serial.print(" ");
    Serial.print(calibData.mag_offset_z); Serial.print(" ");

    Serial.print("\nAccel Radius: ");
    Serial.print(calibData.accel_radius);

    Serial.print("\nMag Radius: ");
    Serial.print(calibData.mag_radius);
}
