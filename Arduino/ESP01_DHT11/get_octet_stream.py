import requests
import struct

# ESP-01 的 IP 地址和端口号
esp01_ip = "192.168.1.14"
port = 6447

for i in range(1, 1000):
    print(i)
    # 发起 GET 请求到 ESP-01
    url = f"http://{esp01_ip}:{port}/req"
    response = requests.get(url)

    # 打印收到的二进制数据的字节长度
    print("Received binary data length:", len(response.content))

    # 打印 response.content 的十六进制表示
    print("Content in hex:")
    print(response.content.hex())

    # 打印 response.content 的字节表示
    # print("\nContent in bytes:")
    # for byte in response.content:
    #     print(byte)

    # 解析收到的二进制数据为浮点数数组
    binary_data = response.content
    float_array = struct.unpack('f' * (len(binary_data) // 4), binary_data)

    # 打印浮点数数组
    print(float_array)
