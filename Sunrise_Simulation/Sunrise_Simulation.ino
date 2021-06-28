#define FASTLED_INTERNAL

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    1

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

char Time[]     = "Time:  :  :  ";
char Calendar[] = "Date:  /  /20  ";
char Alarm[] = "Alarm:  :  ";
byte i, second, minute, hour, date, month, year, alarm_hour, alarm_minute;

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(8, INPUT_PULLUP);                      // button1 is connected to pin 8
  pinMode(9, INPUT_PULLUP);                      // button2 is connected to pin 9
  pinMode(10, INPUT_PULLUP);                     // button3 is connected to pin 10
  pinMode(11, INPUT_PULLUP);                     // button3 is connected to pin 11
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  // set up the LCD's number of columns and rows
  lcd.begin();
  lcd.setCursor(3, 3);
  lcd.print(Alarm);                              // Display alarm set time
  Wire.begin();                                  // Join i2c bus
}

void DS1307_display(){
  // Convert BCD to decimal
  second = (second >> 4) * 10 + (second & 0x0F);
  minute = (minute >> 4) * 10 + (minute & 0x0F);
  hour   = (hour >> 4)   * 10 + (hour & 0x0F);
  date   = (date >> 4)   * 10 + (date & 0x0F);
  month  = (month >> 4)  * 10 + (month & 0x0F);
  year   = (year >> 4)   * 10 + (year & 0x0F);
  // End conversion
  Time[12]     = second % 10 + 48;
  Time[11]     = second / 10 + 48;
  Time[9]      = minute % 10 + 48;
  Time[8]      = minute / 10 + 48;
  Time[6]      = hour   % 10 + 48;
  Time[5]      = hour   / 10 + 48;
  Calendar[14] = year   % 10 + 48;
  Calendar[13] = year   / 10 + 48;
  Calendar[9]  = month  % 10 + 48;
  Calendar[8]  = month  / 10 + 48;
  Calendar[6]  = date   % 10 + 48;
  Calendar[5]  = date   / 10 + 48;
  lcd.setCursor(3, 0);
  lcd.print(Time);                               // Display time
  lcd.setCursor(3, 1);
  lcd.print(Calendar);                           // Display calendar
}

void blink_parameter(){
  byte j = 0;
  while (j < 10 && digitalRead(8) && digitalRead(9)) {
    j++;
    delay(25);
  }
}

byte edit_time(byte x, byte y, byte parameter) {
  char text[3];
  while (!digitalRead(8));                       // Wait until button (pin #8) released
  while (true) {
    while (!digitalRead(9)) {                    // If button (pin #9) is pressed
      parameter++;
      if (i == 0 && parameter > 23)              // If hours > 23 ==> hours = 0
        parameter = 0;
      if (i == 1 && parameter > 59)              // If minutes > 59 ==> minutes = 0
        parameter = 0;
      if (i == 2 && parameter > 31)              // If date > 31 ==> date = 1
        parameter = 1;
      if (i == 3 && parameter > 12)              // If month > 12 ==> month = 1
        parameter = 1;
      if (i == 4 && parameter > 99)              // If year > 99 ==> year = 0
        parameter = 0;
      sprintf(text,"%02u", parameter);
      lcd.setCursor(x, y);
      lcd.print(text);
      delay(200);                                // Wait 200ms
    }
    while (!digitalRead(10)) {                   // If button (pin #10) is pressed
      parameter--;
      if (i == 0 && parameter == 255)            // If hours < 0 ==> hours = 23
        parameter = 23;
      if (i == 1 && parameter == 255)            // If minutes < 0 ==> minutes = 59
        parameter = 59;
      if (i == 2 && parameter < 1)               // If date < 1 ==> date = 31
        parameter = 31;
      if (i == 3 && parameter < 1)               // If month < 1 ==> month = 12
        parameter = 12;
      if (i == 4 && parameter == 255)            // If year < 0 ==> year = 99
        parameter = 99;
      sprintf(text,"%02u", parameter);
      lcd.setCursor(x, y);
      lcd.print(text);
      delay(200);                                // Wait 200ms
    }
    lcd.setCursor(x, y);
    lcd.print("  ");                             // Display two spaces
    blink_parameter();
    sprintf(text,"%02u", parameter);
    lcd.setCursor(x, y);
    lcd.print(text);
    blink_parameter();
    if (!digitalRead(8)){                        // If button (pin #8) is pressed
      i++;                                       // Increment 'i' for the next parameter
      return parameter;                          // Return parameter value and exit
    }
  }
}

byte edit_alarm(byte x, byte y, byte parameter) {
  char text[3];
  while (!digitalRead(11));                      // Wait until button (pin #11) released
  while (true) {
    while (!digitalRead(9)) {                    // If button (pin #9) is pressed
      parameter++;
      if (i == 0 && parameter > 23)              // If hours > 23 ==> hours = 0
        parameter = 0;
      if (i == 1 && parameter > 59)              // If minutes > 59 ==> minutes = 0
        parameter = 0;
      sprintf(text,"%02u", parameter);
      lcd.setCursor(x, y);
      lcd.print(text);
      delay(200);                                // Wait 200ms
    }
    while (!digitalRead(10)) {                   // If button (pin #10) is pressed
      parameter--;
      if (i == 0 && parameter == 255)            // If hours < 0 ==> hours = 23
        parameter = 23;
      if (i == 1 && parameter == 255)            // If minutes < 0 ==> minutes = 59
        parameter = 59;
      sprintf(text,"%02u", parameter);
      lcd.setCursor(x, y);
      lcd.print(text);
      delay(200);                                // Wait 200ms
    }
    lcd.setCursor(x, y);
    lcd.print("  ");                             // Display two spaces
    blink_parameter();
    sprintf(text,"%02u", parameter);
    lcd.setCursor(x, y);
    lcd.print(text);
    blink_parameter();
    if (!digitalRead(11)){                       // If button (pin #11) is pressed
      i++;                                       // Increment 'i' for the next parameter
      return parameter;                          // Return parameter value and exit
    }
  }
}

void sunrise() {
  // total sunrise length, in minutes
  static const uint8_t sunriseLength = 30;
  
  // how often (in seconds) should the heat color increase?
  // for the default of 30 minutes, this should be about every 7 seconds
  // 7 seconds x 256 gradient steps = 1,792 seconds = ~30 minutes
  static const uint8_t interval = (sunriseLength * 60) / 256;
  
  // current gradient palette color index
  static uint8_t heatIndex = 0; // start out at 0
  
  // HeatColors_p is a gradient palette built in to FastLED
  // that fades from black to red, orange, yellow, white
  // feel free to use another palette or define your own custom one
  CRGB color = ColorFromPalette(HeatColors_p, heatIndex);
  
  // fill the entire strip with the current color
  fill_solid(leds, NUM_LEDS, color);
  
  // slowly increase the heat
  EVERY_N_SECONDS(interval) {
  // stop incrementing at 255, we don't want to overflow back to 0
  if(heatIndex < 255) {
      heatIndex++;
    }
  }
}

void check_alarm() {
  if (hour == alarm_hour) {
    sunrise();
    FastLED.show();
  } else {
    FastLED.clear();
    FastLED.show();
  }
}

void loop() {
  if (!digitalRead(8)) {                          // If button (pin #8) is pressed
      i = 0;
      hour   = edit_time(8, 0, hour);
      minute = edit_time(11, 0, minute);
      date   = edit_time(8, 1, date);
      month  = edit_time(11, 1, month);
      year   = edit_time(16, 1, year);
      // Convert decimal to BCD
      minute = ((minute / 10) << 4) + (minute % 10);
      hour = ((hour / 10) << 4) + (hour % 10);
      date = ((date / 10) << 4) + (date % 10);
      month = ((month / 10) << 4) + (month % 10);
      year = ((year / 10) << 4) + (year % 10);
      // End conversion
      // Write data to DS1307 RTC
      Wire.beginTransmission(0x68);               // Start I2C protocol with DS1307 address
      Wire.write(0);                              // Send register address
      Wire.write(0);                              // Reset sesonds and start oscillator
      Wire.write(minute);                         // Write minute
      Wire.write(hour);                           // Write hour
      Wire.write(1);                              // Write day (not used)
      Wire.write(date);                           // Write date
      Wire.write(month);                          // Write month
      Wire.write(year);                           // Write year
      Wire.endTransmission();                     // Stop transmission and release the I2C bus
      delay(200);                                 // Wait 200ms
    }
    if (!digitalRead(11)) {                       // If button (pin #11) is pressed
      i = 0;
      alarm_hour = edit_alarm(9, 3, alarm_hour);
      alarm_minute = edit_alarm(12, 3, alarm_minute);
    }
    Wire.beginTransmission(0x68);                 // Start I2C protocol with DS1307 address
    Wire.write(0);                                // Send register address
    Wire.endTransmission(false);                  // I2C restart
    Wire.requestFrom(0x68, 7);                    // Request 7 bytes from DS1307 and release I2C bus at end of reading
    second = Wire.read();                         // Read seconds from register 0
    minute = Wire.read();                         // Read minutes from register 1
    hour   = Wire.read();                         // Read hour from register 2
    Wire.read();                                  // Read day from register 3 (not used)
    date   = Wire.read();                         // Read date from register 4
    month  = Wire.read();                         // Read month from register 5
    year   = Wire.read();                         // Read year from register 6
    DS1307_display();                             // Display time & calendar
    check_alarm();                                // Check the current time for alarm
    delay(50);                                    // Wait 50ms
}
