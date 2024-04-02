#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define D 2
DHT dht11(D, DHT11);

// WiFi 设置
const char* ssid = "Metronet1150";
const char* password = "1318995CX";

// LED 连接的 GPIO 引脚
const int ledPin = 0; // GPIO2

ESP8266WebServer server(6447); // 监听 6447 端口

void setup() {
  Serial.begin(115200);
  dht11.begin();

  // 初始化 LED 引脚
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // 初始状态关闭 LED

  // 连接到 WiFi
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
  // 打开 LED 表示数据准备中
  digitalWrite(ledPin, HIGH);

  // 模拟采集的浮点数数据
  float t1 = dht11.readHumidity();
  // if(isnan(t1)) {
  //   Serial.print("t1 nan");
  //   t1 = -11.11;
  // }
  float t2 = dht11.readTemperature();//1.2;
  // if(isnan(t2)) {
  //   Serial.print("t2 nan");
  //   t2 = -1;
  // }

  // 将浮点数转换为二进制数组
  int binary_data_length = sizeof(float)*2;
  uint8_t binary_data[binary_data_length];
  memcpy(binary_data, &t1, sizeof(float));
  memcpy(binary_data + sizeof(float), &t2, sizeof(float));

  // 在这里你可以对二进制数据进行处理，比如解析和使用
  // float binary_data[2];
  // binary_data[0] = t1;
  // binary_data[1] = t2;
  // 返回响应，将二进制数组作为响应内容
  server.setContentLength(binary_data_length);
  server.send(200, "application/octet-stream", reinterpret_cast<const char*>(binary_data), binary_data_length);
  //Serial.print(t1);Serial.print(t2);
  // 关闭 LED 表示数据发送完毕
  digitalWrite(ledPin, LOW);
}
