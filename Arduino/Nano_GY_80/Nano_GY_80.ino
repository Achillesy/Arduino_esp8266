#include <Wire.h>

// GY-80地址
#define ACCEL_ADDR 0x53  // 加速度计地址
#define GYRO_ADDR 0xiB   // 陀螺仪地址
#define MAG_ADDR 0x1E    // 磁力计地址
#define BARO_ADDR 0x77   // 气压计地址

void setup() {
  Wire.begin();
  Serial.begin(9600);
  initAccel();
  initGyro();
  initMag();
  initBaro();
}

void loop() {
  readAccel();
  readGyro();
  readMag();
  readBaro();
  delay(2000);
}

// 初始化气压计
void initBaro() {
  Wire.beginTransmission(BARO_ADDR);
  Wire.write(0xD0); // 重置码
  Wire.write(0x54); // 写入重置码
  Wire.endTransmission();
}

// 读取气压计数据
void readBaro() {
  Wire.beginTransmission(BARO_ADDR);
  Wire.write(0x1D); // 从压力数据寄存器开始读取
  Wire.endTransmission(false);
  Wire.requestFrom(BARO_ADDR, 3, true); // 请求3个字节的数据

  int32_t pressure;
  pressure = Wire.read() << 16 | Wire.read() << 8 | Wire.read();
  pressure >>= 8; // 去除小数部分

  Serial.print("Pressure: ");
  Serial.print(pressure); // 打印原始压力数据
  Serial.println(" Pa");
}

// 其他代码部分与之前相同...