#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#include <time.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);
unsigned long ch_no = 124555;//Replace with ThingSpeak Channel number
const char * write_api = "cvxxx";//Replace with ThingSpeak write API

char ssid[] = "admin";
char pass[] = "12345678";
int count = 0;
int vis_count = 0;

char input[12];
int a = 0, b = 0, c = 0, d = 0, e = 0;

WiFiClient client;
const char *str;

void setup() {
  Serial.begin(9600);
  configTime(11 * 1800, 0, "pool.ntp.org", "time.nist.gov");
  Wire.begin(D2, D1);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME TO ");
  lcd.setCursor(0, 1);
  lcd.print(" CIRCUIT DIGEST ");
  delay(2000);
  lcd.clear();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 1);
  lcd.print("WiFi connected ");
  delay(2000);
  lcd.clear();
  ThingSpeak.begin(client);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("No. of Vis:" + String(vis_count));
  time_t now = time(nullptr);
  str = ctime(&now);
  if (Serial.available()) {
    count = 0;
    while (Serial.available() && count < 12) {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12) {
      if ((strncmp(input, "0B00284F9AF6", 12) == 0) && (a == 0)) {
        lcd.setCursor(0, 1);
        lcd.print("Welcome Debasis ");
        vis_count++;
        a = 1;
        delay(2000);
        lcd.clear();
        senddata("Debasis");
      } else if ((strncmp(input, "0B002854EB9C", 12) == 0) && (b == 0)) {
        lcd.setCursor(0, 1);
        lcd.print("Welcome Manas ");
        b = 1;
        vis_count++;
        delay(2000);
        lcd.clear();
        senddata("Manas");
      } else if ((strncmp(input, "0B0029516C1F", 12) == 0) && (c == 0)) {
        lcd.setCursor(0, 1);
        lcd.print("Welcome Aswinth ");
        c = 1;
        vis_count++;
        delay(2000);
        lcd.clear();
        senddata("Aswinth");
      } else if ((strncmp(input, "0B00292F5E53", 12) == 0) && (d == 0)) {
        lcd.setCursor(0, 1);
        lcd.print("Welcome Sourav ");
        d = 1;
        vis_count++;
        delay(2000);
        lcd.clear();
        senddata("Sourav");
      } else if ((strncmp(input, "0B00283E6479", 12) == 0) && (e == 0)) {
        lcd.setCursor(0, 1);
        lcd.print("Welcome Rakesh ");
        e = 1;
        vis_count++;
        delay(2000);
        lcd.clear();
        senddata("Rakesh");
      } else {
        lcd.setCursor(0, 1);
        lcd.print("Welcome Back!!! ");
        delay(2000);
        lcd.clear();
      }
    }
  }
}

void senddata(String input) {
  ThingSpeak.setField(1,input);
  ThingSpeak.setField(2, str);
  ThingSpeak.writeFields(ch_no, write_api);
}