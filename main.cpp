#include <Arduino.h>
#include <myfont.h>
#include <pic.h>
#include <NTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <function.h>
#include "Adafruit_APDS9960.h"
#define offset 80
Adafruit_APDS9960 apds;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);
TFT_eSprite pic = TFT_eSprite(&tft);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com"); // NTP服务器地址

void setup()
{
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(19, LOW);
  Serial.begin(9600);
  tft.init();                //初始化
  tft.fillScreen(TFT_BLACK); //屏幕颜色
  tft.setSwapBytes(true);
  tft.setRotation(4);
  tft.pushImage(0, offset, 240, 240, begin);

  delay(100);

  Serial.print("Connecting.. ");
  WiFi_Connect();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



  timeClient.begin();
  timeClient.setTimeOffset(28800); //+ 1区 偏移3600， +8区 ：3600×8 = 28800,如果注释掉这行代码会发现通过串口监听器打印出来的时间和电脑中显示的时间并不同步,相差8小时。

  clk.setColorDepth(8);
  clk.createSprite(160, 70);
  clk.fillSprite(TFT_BLACK);
  // clk.setScrollRect(0, 0, 40, 16, TFT_BLACK); // Scroll the "Hello" in the first 40 pixels
  clk.setTextColor(TFT_WHITE);

  pic.setColorDepth(8);
  pic.createSprite(240, 240);
  pic.fillSprite(TFT_BLACK);
  // clk.setScrollRect(0, 0, 40, 16, TFT_BLACK); // Scroll the "Hello" in the first 40 pixels
  pic.setTextColor(TFT_WHITE);

  Wire.begin(12, 13); // SDA->19,SCL->21,可以根据情况自行修改
  while (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G); //加速度量程±2G
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);      //角速度量程±250°/s
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);   //采样频率21Hz

  xTaskCreatePinnedToCore(xTaskOne, "TaskOne", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(xTaskTwo, "TaskTwo", 4096, NULL, 2, NULL, 1);
}

int mark = 1;
int mark2 = 0;
void loop()
{
  // put your main code here, to run repeatedly:
  // getBiliBiliFollower();
  // delay(1000);
  while (mark2 == 0)
  {
    if (mark == 1)
    {
      tft.fillScreen(TFT_BLACK);
    }
    clk.setSwapBytes(true);

    // showMyFonts(100, 80, "周三", TFT_SKYBLUE);

    tft.pushImage(-20, 120 + offset, 120, 120, cat);

    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();

    int weekDay = timeClient.getDay();
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();

    tft.setBitmapColor(TFT_WHITE, TFT_BLACK);
    clk.pushSprite(40, 0 + offset);
    clk.setTextColor(TFT_WHITE); //设置文本颜色为白色 //clk.setTextSize(3);//设置文字的大小 (1~7)按之前步骤进行烧写，结果如下图所示：
    clk.fillScreen(TFT_BLACK);   //屏幕颜色

    clk.setTextSize(4);
    clk.setCursor(10, 0, 2);  //设置起始坐标(10, 10)，2 号字体
    clk.println(currentHour); //显示文字

    clk.setTextSize(4);
    clk.setCursor(80, 0, 2);
    clk.println(":"); //显示文字

    clk.setTextSize(4);
    clk.setCursor(90, 0, 2);
    clk.println(currentMinute); //显示文字

    judgeWeek(weekDay);

    Serial.print("星期");
    Serial.print(weekDay);
    Serial.print(";");
    Serial.print(currentHour);
    Serial.print("点");
    Serial.print(currentMinute);
    Serial.println("分;");

    //将epochTime换算成年月日
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon + 1;
    int currentyear = ptm->tm_year - 100;
    Serial.print(currentyear);
    Serial.print("年");
    Serial.print(currentMonth);
    Serial.print("月");
    Serial.print(monthDay);
    Serial.println("日");
    delay(1000);

    //uint8_t gesture = apds.readGesture();
    mark = 0;
  }
  mark = 1;
  while (mark2 == -1)
  {
    if (mark == 1)
    {
      pic.fillScreen(TFT_BLACK);
    }
    pic.setSwapBytes(true);
    pic.pushSprite(0, 0 + offset);
    pic.pushImage(35, 10, 170, 170, me);
    pic.setCursor(35, 200, 4);

    pic.setTextColor(pic.color565(245, 144, 130));
    pic.println("Fans:");
    pic.setCursor(140, 200, 4);
    pic.setTextColor(pic.color565(154, 193, 232));
    pic.println(getBiliBiliFollower());
    mark = 0;
  }
  mark = 1;
  while (mark2 == 1)
  {
    if (mark == 1)
    {
      pic.fillScreen(TFT_BLACK);
    }
    pic.setSwapBytes(true);
    pic.pushSprite(0, 0 + offset);
    pic.pushImage(35, 10, 170, 170, qing);
    //showMyFonts(100, 200 + 80, (char *)"晴", TFT_SKYBLUE);
    pic.drawBitmap(100, 200, hanzi[10].hz_Id, hanzi[10].hz_width, 32, pic.color565(255, 77, 52));
    mark = 0;
  }
  mark = 1;

}





// /* Sweep
//  by BARRAGAN <http://barraganstudio.com>
//  This example code is in the public domain.

//  modified 8 Nov 2013
//  by Scott Fitzgerald

//  modified for the ESP32 on March 2017
//  by John Bennett

//  see http://www.arduino.cc/en/Tutorial/Sweep for a description of the original code

//  * Different servos require different pulse widths to vary servo angle, but the range is 
//  * an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
//  * sweep 180 degrees, so the lowest number in the published range for a particular servo
//  * represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
//  * of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
//  * 1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
//  * degrees.
//  * 
//  * Circuit: (using an ESP32 Thing from Sparkfun)
//  * Servo motors have three wires: power, ground, and signal. The power wire is typically red,
//  * the ground wire is typically black or brown, and the signal wire is typically yellow,
//  * orange or white. Since the ESP32 can supply limited current at only 3.3V, and servos draw
//  * considerable power, we will connect servo power to the VBat pin of the ESP32 (located
//  * near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS. 
//  * 
//  * We could also connect servo power to a separate external
//  * power source (as long as we connect all of the grounds (ESP32, servo, and external power).
//  * In this example, we just connect ESP32 ground to servo ground. The servo signal pins
//  * connect to any available GPIO pins on the ESP32 (in this example, we use pin 18.
//  * 
//  * In this example, we assume a Tower Pro MG995 large servo connected to an external power source.
//  * The published min and max for this servo is 1000 and 2000, respectively, so the defaults are fine.
//  * These values actually drive the servos a little past 0 and 180, so
//  * if you are particular, adjust the min and max values to match your needs.
//  */

// #include <ESP32Servo.h>

// Servo myservo;  // create servo object to control a servo
// // 16 servo objects can be created on the ESP32

// int pos = 0;    // variable to store the servo position
// // Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// // Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// #if defined(ARDUINO_ESP32S2_DEV)
// int servoPin = 17;
// #else
// int servoPin = 33;
// #endif

// void setup() {
// 	// Allow allocation of all timers
// 	ESP32PWM::allocateTimer(0);
// 	ESP32PWM::allocateTimer(1);
// 	ESP32PWM::allocateTimer(2);
// 	ESP32PWM::allocateTimer(3);
// 	myservo.setPeriodHertz(50);    // standard 50 hz servo
// 	myservo.attach(servoPin, 400, 2000); // attaches the servo on pin 18 to the servo object
// 	// using default min/max of 1000us and 2000us
// 	// different servos may require different min/max settings
// 	// for an accurate 0 to 180 sweep
// }

// void loop() {

// 	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
// 		// in steps of 1 degree
// 		myservo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(10);             // waits 15ms for the servo to reach the position
// 	}
// 	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
// 		myservo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(10);             // waits 15ms for the servo to reach the position
// 	}
 
// }


