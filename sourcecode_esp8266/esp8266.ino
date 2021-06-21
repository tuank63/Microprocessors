#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

WiFiClient client;

String thingSpeakAddress = "http://api.thingspeak.com/update?"; // Địa chỉ web sever
String writeAPIKey = "WISKOIQUA0UHVGFC"; //Key để ghi dữ liệu lên kênh
String request_string;
String data;
HTTPClient http;

void setup()
{
   //Kết nối Wifi 
   WiFi.disconnect();
   WiFi.mode(WIFI_STA); // Thiết lập chế độ Station cho Nodemcu
   Serial.begin(115200);
   Serial.print("Connecting");
   WiFi.begin("Tuan Tuan","tuan20182861");
   while ((!(WiFi.status() == WL_CONNECTED)))
   {
      delay(300);
      Serial.print(".");
   }
   Serial.println("");
   Serial.println("WiFi connected");
}


void loop()
{
    if (Serial.available() > 0 ) 
  {
    data = String(Serial.read()); } // Đọc giá trị cảm biến từ cổng Serial ghi lại từ Arduino
//    data = String(Serial.readString()); } 
    
    // Gửi dữ liệu lên sever
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += writeAPIKey;
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += (data);
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(request_string.length());
      client.print("\n\n");
      client.print(request_string);
      //Thông báo ra cổng Serial Monitor
      Serial.println(data);
      Serial.println("Sending...");
      //Delay
      delay(1000);

    }

}
