#include <LiquidCrystal_I2C.h>
#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h> 
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial nodemcu(5,4);//Tx, Rx
LiquidCrystal_I2C lcd(0x27,16,2);

const int PulseWire = 0; // Chân tín hiệu cảm biến là A0
const int LED13 = 13;

PulseSensorPlayground pulseSensor; // 

void setup() {

Serial.begin(9600); // tốc độ truyền của cổng arduino 9600 b/s
nodemcu.begin(115200);// tốc độ truyền của cổng nodemcu 115200 b/s
lcd.init(); //khởi động LCD
lcd.backlight(); // bậtđèn của LCD
lcd.clear(); // xoá màn hình LCD

pulseSensor.analogInput(PulseWire);//kết nối chân cảm biến
pulseSensor.blinkOnPulse(LED13); //tín hiệu nhấp nháy cho cảm biến

// Kiểm tra cảm biến và hiển thị LCD
if (pulseSensor.begin()) {
lcd.setCursor(4,0);//Định vị vị trí mà tại đó văn bản tiếp theo được ghi vào màn hình LCD sẽ được hiển thị.
lcd.print("Nhip tim: ");
}
}

void loop() {

int data = pulseSensor.getBeatsPerMinute(); // Lấy giá trị nhịp tim từ cảm biến thông qua hàm
if (pulseSensor.sawStartOfBeat()) { 
Serial.println("Bat dau"); 
Serial.print("Nhip tim = "); 
Serial.println(data); 

lcd.setCursor(4,1);
lcd.print(data);
lcd.print(" Bpm");
nodemcu.write(data);//

}
delay(1000); 
}
