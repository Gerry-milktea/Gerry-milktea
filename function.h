#ifndef fuction_H_
#define fuction_H_
#include <Arduino.h>
#include <myfont.h>
#include <TFT_eSPI.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_MPU6050.h>
#include "Adafruit_APDS9960.h"


extern TFT_eSPI tft;
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
extern int mark2;
void showMyFont(int32_t x, int32_t y, const char c[3], uint32_t color)
{
    for (int k = 0; k < 11; k++)
    {
        if (hanzi[k].Index[0] == c[0] && hanzi[k].Index[1] == c[1] && hanzi[k].Index[2] == c[2])

            tft.drawBitmap(x, y, hanzi[k].hz_Id, hanzi[k].hz_width, 32, color);
    }
}

void showMyFonts(int32_t x, int32_t y, char str[], uint32_t color)
{
    //显示整句汉字，字库比较简单，上下、左右输出是在函数内实现
    int x0 = x;
    for (int i = 0; i < strlen(str); i += (strlen(str) < 3 ? 1 : 3))
    {
        showMyFont(x0, y, str + i, color);
        x0 += 31;
    }
}
void WiFi_Connect()
{
    WiFi.begin("HUAWEI Mate 40", "a25418f73bd0");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        Serial.print(".");
    }
}

void judgeWeek(int weekDay)
{
    switch (weekDay)
    {
    case 1 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周一", TFT_SKYBLUE);
        break;
    case 2 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周二", TFT_SKYBLUE);
        break;
    case 3 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周三", TFT_SKYBLUE);
        break;
    case 4 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周四", TFT_SKYBLUE);
        break;
    case 5 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周五", TFT_SKYBLUE);
        break;
    case 6 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周六", TFT_SKYBLUE);
        break;
    case 0 /* constant-expression */:
        /* code */
        showMyFonts(100, 80 + 80, (char *)"周日", TFT_SKYBLUE);
        break;
    default:
        break;
    }
}
String UID = "1353470342";
String followerUrl = "http://api.bilibili.com/x/relation/stat?vmid=" + UID;
long follower = 0;
DynamicJsonDocument doc(1024);
int getBiliBiliFollower()
{
    HTTPClient http;
    http.begin(followerUrl);
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        // Serial.printf("HTTP Get Code: %d\r\n", httpCode);
        if (httpCode == HTTP_CODE_OK)
        {
            String resBuff = http.getString();
            // Serial.println(resBuff);
            deserializeJson(doc, resBuff);
            follower = doc["data"]["follower"];
            // Serial.printf("Follows: %ld \r\n", follower);
        }
    }
    else
    {
        Serial.printf("HTTP Get Error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    return (int)follower;
}
String weatherUrl = "https://api.seniverse.com/v3/weather/now.json?key=SD3HmAZWdFwcl1_Er&location=nanjing&language=zh-Hans&unit=c";
DynamicJsonDocument doc2(1024);
String now_address = "", now_weather = "", now_temperature = "";
void getWeather()
{

    HTTPClient http;
    http.begin(weatherUrl);
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        Serial.printf("HTTP Get Code: %d\r\n", httpCode);
        if (httpCode == HTTP_CODE_OK)
        {
            String resBuff = http.getString();
            // Serial.println(resBuff);
            deserializeJson(doc2, resBuff);
            JsonObject results_0 = doc2["results"][0];

            JsonObject results_0_location = results_0["location"];

            const char *results_0_location_name = results_0_location["name"]; // "上海"

            JsonObject results_0_now = results_0["now"];
            const char *results_0_now_text = results_0_now["text"]; // "阴"
            // const char* results_0_now_code = results_0_now["code"]; // "9"
            const char *results_0_now_temperature = results_0_now["temperature"]; // "28"
            now_address = results_0_location_name;
            now_weather = results_0_now_text;
            now_temperature = results_0_now_temperature;
            Serial.print("Now address:");
            Serial.println(now_address);
            Serial.print("Now weather:");
            Serial.println(now_weather);
            Serial.print("Now temperature:");
            Serial.println(now_temperature);
        }
    }
    else
    {
        Serial.printf("HTTP Get Error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}

void xTaskOne(void *xTask1)
{
    while (1)
    {

        // getBiliBiliFollower();
        // getWeather();
       // Serial.println(mark2);
        delay(500);
        //uint8_t gesture = apds.readGesture();

        
    }
}

void xTaskTwo(void *xTask2)
{

    while (1)
    {

        mpu.getEvent(&a, &g, &temp); //获取加速度、角速度、温度
        // Serial.print("");
        // Serial.print(g.acceleration.x);
        // Serial.print(",");
        // Serial.print(g.acceleration.y);
        // Serial.print(",");
        // Serial.println(g.acceleration.z);
        if (g.acceleration.x < -2)
        {
            mark2--;
            if (mark2 < -1)
                mark2 = -1;
            delay(600);
        }
        if (g.acceleration.x > 2)
        {
            mark2++;
            if (mark2 > 1)
                mark2 = -1;
            delay(600);
        }
    }
}
#endif
