#include <Wire.h>

int ADXLAddress = 0x53; 

#define X_Axis_Register_DATAX0 0x32 
#define X_Axis_Register_DATAX1 0x33 
#define Y_Axis_Register_DATAY0 0x34 
#define Y_Axis_Register_DATAY1 0x35
#define Z_Axis_Register_DATAZ0 0x36
#define Z_Axis_Register_DATAZ1 0x37

#define Power_Register 0x2D 

int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z0,Z1,Z_out;

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  delay(10);
  // Enable measurement
  Wire.beginTransmission(ADXLAddress);
  Wire.write(Power_Register);

  Wire.write(8);  
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(ADXLAddress);
  
  //Ask the particular registers for data
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);
  
 // Wire.write(Y_Axis_Register_DATAY0);
//  Wire.write(Y_Axis_Register_DATAY1);
  
  Wire.write(Z_Axis_Register_DATAZ0);
  Wire.write(Z_Axis_Register_DATAZ1);
  
  
  Wire.endTransmission(); 
  
  Wire.requestFrom(ADXLAddress,4); // Request the transmitted bytes from the two registers
  
  if(Wire.available()<=4) {
    delay(1000); 
    X0 = Wire.read(); // Reads the data from the register
    X1 = Wire.read(); 
    
    //Y0 = Wire.read(); 
    //Y1 = Wire.read();
    
   
    Z0 = Wire.read(); 
    Z1 = Wire.read();
  }
  
  Serial.print("X0= ");
  Serial.print(X0);
  Serial.print("   X1= ");
  Serial.println(X1);
  
  Serial.print("Y0= ");
  Serial.print(Y0);
  Serial.print("   Y1= ");
  Serial.println(Y1);
  
  Serial.print("Z0= ");
  Serial.print(Z0);
  Serial.print("   Z1= ");
  Serial.println(Z1);
}
