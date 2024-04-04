// Program: Gyro Test L3G4200D 
// Adaptations: Arduino and Co. 

#include <Wire.h> 

#define CTRL_REG1 0x20 
#define CTRL_REG2 0x21 
#define CTRL_REG3 0x22 
#define CTRL_REG4 0x23 
#define CTRL_REG5 0x24 

// address I2C L3G4200D 
int L3G4200D_Address = 105;
int x;
int y;
int z;

void writeRegister ( int deviceAddress, byte address, byte val) { 
  Wire.beginTransmission (deviceAddress); // start transmission to device 
  Wire.write (address);        // send address register 
  Wire.write (val);          // send value to write 
  Wire.endTransmission ();      // end transmission 
}

int readRegister ( int deviceAddress, byte address) { int v; 
  Wire.beginTransmission ( deviceAddress); 
  Wire.write (address); // register to read 
  Wire.endTransmission (); 
  Wire.requestFrom (deviceAddress, 1 ); // read a byte while (Wire.available (!)) {
     // waiting 
  } 

void setup () 
{ 
  Wire.begin (); 
  Serial.begin ( 9600 ); 
  Serial.println ( "Starting the L3G4200D" );
   // set the L3G4200 to 200, 500 or 2000 degrees / sec 
  setupL3G4200D ( 2000 ); // Waits for the sensor response 
  delay ( 1500 ); 
}

void loop () 
{ // Update the values of X, Y and Z 
  getGyroValues ();   // display the values in the serial monitor 
  Serial.print ( "x" ); 
  Serial.print (x); 
  Serial.print ( "Y" ); 
  Serial.print (y); 
  Serial.print ( "Z" ); 
  Serial.println (z) ; // Wait 100ms and restarts the process 
  delay ( 100 ); 
}

void getGyroValues () 
{ // routine for reading the values of X, Y and Z 
  byte xMSB = readRegister(L3G4200D_Address, 0x29 ); 
  byte xlsb = readRegister(L3G4200D_Address, 0x28 ); 
  x = ((xMSB << 8 ) | xlsb); 
  byte yMSB = readRegister(L3G4200D_Address, 0x2B ); 
  byte yLSB = readRegister(L3G4200D_Address, 0x2A ); 
  y = ((yMSB << 8 ) | yLSB); 
  byte zMSB = readRegister(L3G4200D_Address, 0x2D ); 
  byte zLSB = readRegister(L3G4200D_Address, 0x2C ); 
  z = ((zMSB << 8 ) | zLSB); 
}

int setupL3G4200D ( int scale) 
{ // From Jim Lindblom of Sparkfun's code // Enable x, y, z and turn off power down: 
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111); // If you'd like to adjust / use the HPF, you can edit the line below to configure CTRL_REG2: 
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000); // set CTRL_REG3 to generate data ready interrupt on INT2 // No interrupts used on INT1, if you'd like to configure INT1 // INT2 or otherwise, consult the datasheet: 
  writeRegister(L3G4200D_Address , CTRL_REG3, 0b00001000); // CTRL_REG4 controls the full-scale range, Among other things: if (scale == 250 ) { 
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000); 
  } elseif (scale == 500 ) { 
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000); 
  }
  else { 
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000); 
  } // CTRL_REG5 controls high-pass filtering of outputs, use it // if you'd like: 
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000); 
}

void writeRegister ( int deviceAddress, byte address, byte val) 
{ 
    Wire.beginTransmission (deviceAddress); // start transmission to device 
    Wire.write (address);        // send address register 
    Wire.write (val);          // send value to write 
    Wire.endTransmission ();      // end transmission 
} int readRegister ( int deviceAddress, byte address) 
{ int v; 
    Wire.beginTransmission (deviceAddress); 
    Wire.write (address); // register to read 
    Wire .endTransmission (); 
    Wire.requestFrom (deviceAddress, 1 ); // read byte while (Wire.available ()!) 
    { // waiting 
    } 
    v = Wire.read (); return v; 
}


