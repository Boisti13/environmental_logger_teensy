#include <Wire.h>
#include <strings.h>

int bootTime = 1000;
unsigned long logSpeed = 5000;  //Log speed in [ms]
unsigned long tempSpeed = 50;  //Log speed in [ms]

/******
OLED
****/
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//#include <Fonts/Custom_B.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/************
Dallas DS18B20
************/
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

//uint8_t sensorOutdoor[8] = { 0x28, 0xFF, 0x0A, 0xBB, 0x14, 0x14, 0x00, 0xF3 };
//uint8_t sensorIndoor[8] = { 0x28, 0xFF, 0xD5, 0xAB, 0x50, 0x14, 0x00, 0x55 };

DeviceAddress sensorOutdoor = { 0x28, 0xFF, 0x0A, 0xBB, 0x14, 0x14, 0x00, 0xF3 };
DeviceAddress sensorIndoor = { 0x28, 0xFF, 0x47, 0x4F, 0x51, 0x14, 0x00, 0x8D };

int deviceCount = 0;  // Number of temperature devices found
float tempOutdoor1, tempOutdoor1new;
float tempIndoor1, tempIndoor1new;

char tempIndoor1Str[7];
char tempOutdoor1Str[7];

char outTemp[17];
char inTemp[16];

char oneWireDevices[33];

/*********************
BMP180
********************/
/*
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

float tempBmp;
float airPressure;
float Altitude;
float sealevelPressure;
float realAltitude;

char tempBmpStr[10];

char bmpPresStr[6];

char bmpTemp[20];
char bmpPres[20];
*/

/*********************
BME280
********************/
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // I2C

float tempBme;
float pressureBme;
float humidityBme;

char tempBmeStr[10];
char presBmeStr[6];
char humBmeStr[6];

char bmeTemp[20];
char bmePres[20];
char bmeHum[20];

/**********
Rain Sensor
*******/
const int rainDigitalPin = 14;
const int rainAnalogPin = A1;
int rainStatus;  // 0 = Rain / 1 = No Rain
int rainAnalog;

/************
SD Logger
*****/
#include <SD.h>
const int chipSelect = BUILTIN_SDCARD;
File dataFile;
char logFileName[14];
char logString[45];

unsigned long previousMillis = 0;

/****************
RTC Time GPS
********/
#include <DS3232RTC.h>  // https://github.com/JChristensen/DS3232RTC

DS3232RTC myRTC;

char rtcTimeandDateString[20];
char gpsTimeandDateString[20];

#include <TinyGPSPlus.h>

TinyGPSPlus gps;

byte gps_hour;
byte gps_minute;
byte gps_second;
byte gps_month;
byte gps_day;
int gps_year;

const int UTC_offset = 1;