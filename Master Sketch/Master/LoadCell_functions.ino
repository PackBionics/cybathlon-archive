
/**
 * Initialization of all loadcells
 */
void Init_LC() {
  loadcell1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  loadcell1.set_scale(LOADCELL_DIVIDER1);
  loadcell1.set_offset(LOADCELL_OFFSET1);
  loadcell1.set_gain();
  delay(1000);
  loadcell2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  loadcell2.set_scale(LOADCELL_DIVIDER2);
  loadcell2.set_offset(LOADCELL_OFFSET2);
  loadcell2.set_gain();
  delay(1000);
  loadcell3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);
  loadcell3.set_scale(LOADCELL_DIVIDER3);
  loadcell3.set_offset(LOADCELL_OFFSET3);
  loadcell3.set_gain();
  delay(1000);
  loadcell4.begin(LOADCELL_DOUT_PIN4, LOADCELL_SCK_PIN4);
  loadcell4.set_scale(LOADCELL_DIVIDER4);
  loadcell4.set_offset(LOADCELL_OFFSET4);
  loadcell4.set_gain(); 
}

/**
 * Used for calibration of the loadcells
 * Uses the computer to adjust the variables for the loadcells
 * 
 * NOTE: This may need to change (particularly the use of separate LOADCELL_DIVIDER variables
 * for each loadcell since each loadcell may be different
 * NOTE: The use of the zero factor may be useful for an offset for each loadcell
 */
void Calibrate_LC(HX711 loadcell)
{
  Serial.println("Make sure Arduino is attached to laptop for calibration");
  Serial.println("Calibrating Loadcell 1: ");

  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  loadcell.set_scale();
  loadcell.tare(); //Reset the scale to 0

  long zero_factor = loadcell.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  float calibration_factor = LOADCELL_DIVIDER1;
  while(1) {
    loadcell.set_scale(calibration_factor); //Adjust to this calibration factor

    Serial.print("Reading: ");
    Serial.print(loadcell.get_units(), 1);
    Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
    Serial.print(" calibration_factor: ");
    Serial.print(calibration_factor);
    Serial.println();
  
    if(Serial.available())
    {
      char temp = Serial.read();
      if(temp == '+' || temp == 'a')
        calibration_factor += 10;
      else if(temp == '-' || temp == 'z')
        calibration_factor -= 10;
      else if(temp == '0')
        break;
    }
  }
  
}

/**
 * Reads loadcell 1 (front) and updates global variable
 */
long Read_LC1() {
//  long result = loadcell1.read();
  // large random spikes in lc readings -- need to filter out spikes?
//  result = result == -1 ? lcFront : result;
//  return abs(result - lcFront) > 300000 ? lcFront : result;
  return loadcell1.is_ready() ? loadcell1.read() : lcFront;
}

/**
 * Reads loadcell 2 (back) and updates global variable
 */
long Read_LC2() {
//  long result = loadcell2.read();
  // large random spikes in lc readings -- need to filter out spikes?
//  result = result == -1 ? lcBack : result;
//  return abs(result - lcBack) > 300000 ? lcBack : result;
  return loadcell2.is_ready() ? loadcell2.read() : lcBack;
}

/**
 * Reads loadcell 3 (left) and updates global variable
 */
long Read_LC3() {
//  long result = loadcell3.read();
  // large random spikes in lc readings -- need to filter out spikes?
//  result = result == -1 ? lcLeft : result;
//  return abs(result - lcLeft) > 300000 ? lcLeft : result;
  return loadcell3.is_ready() ? loadcell3.read() : lcLeft;
}

/**
 * Reads loadcell 4 (right) and updates global variable
 */
long Read_LC4() {
//  long result = loadcell4.read();
  // large random spikes in lc readings -- need to filter out spikes?
//  result = result == -1 ? lcRight : result;
//  return abs(result - lcRight) > 300000 ? lcRight : result;
  return loadcell4.is_ready() ? loadcell4.read() : lcRight;
}
