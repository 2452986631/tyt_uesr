#include <Arduino.h>
#include <WiFi.h>
#include "PubSubClient.h"
#include "Ticker.h"
#include <Adafruit_Sensor.h>


void clientReconnect();
void callback(char *topic, byte *payload, unsigned int length);
void Send_Data();


int god=0;

//------------------------------------------------------------------------------
const char *ssid     = "1234555"; //wifi名称
const char *password = "12341234";//wifi密码
WiFiClient espClient;           //创建一个WIFI连接客户端
PubSubClient client(espClient); // 创建一个PubSub客户端, 传入创建的WIFI客户端
//------------------------------------------------------------------------------
const char *mqtt_server = "183.230.40.96"; //onenet 的 IP地址
const int port = 6002;                     //端口号

#define mqtt_devid "1136559503" //设备ID      1162031449
#define mqtt_pubid "614737"        //产品ID
#define mqtt_password "20230910" //鉴权信息   1632108152261tyt
//------------------------------------------------------------------------------
char msg_buf[200];               //发送信息缓冲区
char msgJson[100]; //要发送的json格式的数据
unsigned short json_len = 0;                      //json长度
int Temp=0,Humi=0,CO2=10,TVOC=10,MQ5=0,data=0;
float Light=0;
char dataTemplate[] = "{\"Temp\":%d,\"Humi\":%d,\"Light\":%.2f,\"MQ5\":%d}"; //信息模版  temp humi要与onenet相对应
//char dataTemplate[] = "{\"Temp\":%d,\"Humi\":%d,\"Light\":%.2f,\"MQ5\":%d,\"CO2\":%d,\"TVOC\":%d}"; //信息模版  temp humi要与onenet相对应
int arr[6],i=0;


void UART_Read_Write_Multibyte(void)
{
  if(Serial.available()>0)
  {
    delay(10);
    data=Serial.read();
    arr[i]=data;
    i++;
    if(i==6)
    {
      i=0;
      Temp=arr[0];
      Humi=arr[1];
      MQ5=(arr[2]<<8)+arr[3];
      Light=(( (arr[4]<<8)+arr[5]) * 1152.0)/625.0;
      Send_Data();
      while (Serial.available ())//清除串口缓存，防止内存溢出导致重启
        { Serial.read (); }
    }
    //Serial.write(arr[i]);
  }
}


//WIFI连接
void setupWifi(){
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("正在连接中----\n");
    }

    Serial.print("WIFI已连接\n");
    Serial.print(WiFi.localIP());
}
void setup() {

  Serial.begin(115200);
  Serial.onReceive(UART_Read_Write_Multibyte);//设置串口回调函数
  setupWifi();   //调用函数连接WIFI


  client.setServer(mqtt_server, port);  //设置客户端连接的服务器,连接Onenet服务器, 使用6002端口
  client.connect(mqtt_devid, mqtt_pubid, mqtt_password); //客户端连接到指定的产品的指定设备.同时输入鉴权信息
  if (client.connected())
  {
    Serial.print("连接成功\r\n");//判断以下是不是连好了.
  }
  //client.setCallback(callback);                                //设置好客户端收到信息是的回调
  client.setCallback(callback); //订阅命令下发主题
  //tim1.attach(5, sendTempAndHumi);                      //定时每1秒调用一次发送数据函数sendTempAndHumi
}

void loop() {
  //delay(5000);
  if (!WiFi.isConnected()) //先看WIFI是否还在连接
  {
    setupWifi();
  }
  if (!client.connected()) //如果客户端没连接ONENET, 重新连接
  {
    clientReconnect();
    delay(100);
  }
  client.loop(); //客户端循环检测
}


//向主题发送模拟的温湿度数据
void Send_Data()
{
  if (client.connected())
  {//float Temp=0,Humi=0,CO2=0,TVOC=0,Light=0,MQ5=0
    snprintf(msgJson,100, dataTemplate,Temp,Humi,Light,MQ5); //将模拟温湿度数据套入dataTemplate模板中, 生成的字符串传给msgJson
    json_len = strlen(msgJson);                   //msgJson的长度
    msg_buf[0] = char(0x03);                       //要发送的数据必须按照ONENET的要求发送, 根据要求,数据第一位是3
    msg_buf[1] = char(json_len >> 8);              //数据第二位是要发送的数据长度的高八位
    msg_buf[2] = char(json_len & 0xff);            //数据第三位是要发送数据的长度的低八位

    memcpy(msg_buf + 3, msgJson, strlen(msgJson)); //从msg_buf的第四位开始,放入要传的数据msgJson
    msg_buf[3 + strlen(msgJson)] = 0;              //添加一个0作为最后一位, 这样要发送的msg_buf准备好了

    client.publish("$dp", (uint8_t *)msg_buf, 3 + strlen(msgJson)); //发送数据到主题$dp
  }
}

//收到主题下发的回调, 注意这个回调要实现三个形参 1:topic 主题, 2: payload: 传递过来的信息 3: length: 长度
void callback(char *topic, byte *payload, unsigned int length)
{
  //------------------小车运动-------------------------
  if ((char)payload[0] == '0') {
    god=0; Serial.write(god);
  }
  if ((char)payload[0] == '1') {
    god=1; Serial.write(god);
  }
  if ((char)payload[0] == '2') {
    god=2; Serial.write(god);
  }
  if ((char)payload[0] == '3') {
    god=3; Serial.write(god);

  }
  if ((char)payload[0] == '4') {
    god=4; Serial.write(god);
  }
}

//ONENET重新连接
void clientReconnect()
{
  while (!client.connected()) //再重连客户端
  {
    Serial.print("reconnect MQTT...\r\n");
   if (client.connect(mqtt_devid, mqtt_pubid, mqtt_password))
    {
      Serial.print("connected");
    }
    else
    {
      Serial.print("failed");
      Serial.print(client.state());
      Serial.print("try again in 5 sec");
     delay(5000);
    }
  }
}
