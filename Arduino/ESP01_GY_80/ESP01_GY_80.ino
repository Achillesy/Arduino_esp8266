#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// GY-80地址
#define GY80_ADDR 0x68

// WiFi设置
const char* ssid = "Metronet1150";
const char* password = "1318995CX";

ESP8266WebServer server(6447); // 监听6447端口

// 初始化GY80传感器
void initGY80() {
  Wire.begin(4, 5); // 将SDA连接到GPIO4, SCL连接到GPIO5
  Wire.beginTransmission(GY80_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1寄存器
  Wire.write(0); // 设置为正常工作模式
  Wire.endTransmission(true);
}

// 读取GY80数据
void readGY80(float* gy_f) {
  Wire.beginTransmission(GY80_ADDR);
  Wire.write(0x3B); // 从加速度数据寄存器开始
  Wire.endTransmission(false);
  Wire.requestFrom(GY80_ADDR, 14, true); // 请求14个字节的数据

  // 合并高位和低位字节
  int16_t ax, ay, az, gx, gy, gz;
  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  int temp = Wire.read() << 8 | Wire.read(); // 温度数据
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();

  // 打印原始数据
  Serial.print("AcX="); Serial.print(ax); gy_f[0] = ax;
  Serial.print(" AcY="); Serial.print(ay); gy_f[1] = ay;
  Serial.print(" AcZ="); Serial.print(az); gy_f[2] = az;
  Serial.print(" Tmp="); Serial.print(temp / 340.00 + 36.53); gy_f[3] = temp; // 温度计算
  Serial.print(" GyX="); Serial.print(gx); gy_f[4] = gx;
  Serial.print(" GyY="); Serial.print(gy); gy_f[5] = gy;
  Serial.print(" GyZ="); Serial.println(gz); gy_f[6] = gz;
}

void setup() {
  Wire.begin(4, 5); // 将SDA连接到GPIO4, SCL连接到GPIO5
  Serial.begin(9600);
  initGY80();

  // 连接到WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // 设置路由
  server.on("/req", HTTP_GET, handleGet);

  // 启动服务器
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // 处理客户端请求
  server.handleClient();
}

void handleGet() {
  // 模拟采集的浮点数数据
  float binary_gy[7];
  readGY80(binary_gy);

  // 将浮点数转换为二进制数组
  int binary_data_length = sizeof(float) * sizeof(binary_gy); // sizeof(float);

  // 在这里你可以对二进制数据进行处理，比如解析和使用
  // float binary_data[2];
  // binary_data[0] = t1;
  // binary_data[1] = t2;

  // 返回响应，将二进制数组作为响应内容
  server.setContentLength(binary_data_length);
  server.send(200, "application/octet-stream", reinterpret_cast<const char*>(binary_gy), binary_data_length);
  //Serial.print(t1);Serial.print(t2);
}
