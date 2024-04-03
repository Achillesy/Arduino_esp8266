#include <Wire.h>

// GY-80地址
#define GY80_ADDR 0x68

void setup() {
  Wire.begin(D1, D2); // 将SDA连接到D1引脚,SCL连接到D2引脚
  Serial.begin(115200);
  initGY80();
}

void loop() {
  readGY80();
  delay(100); // 延时100毫秒
}

// 初始化GY80传感器
void initGY80() {
  Wire.beginTransmission(GY80_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1寄存器
  Wire.write(0);    // 设置为正常工作模式
  Wire.endTransmission(true);
}

// 读取GY80数据
void readGY80() {
  Wire.beginTransmission(GY80_ADDR);
  Wire.write(0x3B); // 从加速度数据寄存器开始
  Wire.endTransmission(false);
  Wire.requestFrom(GY80_ADDR, 14, true); // 请求14个字节的数据

  // 合并高位和低位字节
  int16_t ax, ay, az, temp, gx, gy, gz;
  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  temp = Wire.read() << 8 | Wire.read(); // 温度数据
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();

  // 打印原始数据
  Serial.print("AcX="); Serial.print(ax);
  Serial.print(" AcY="); Serial.print(ay);
  Serial.print(" AcZ="); Serial.print(az);
  Serial.print(" Tmp="); Serial.print(temp);
  Serial.print(" GyX="); Serial.print(gx);
  Serial.print(" GyY="); Serial.print(gy);
  Serial.print(" GyZ="); Serial.println(gz);
}
