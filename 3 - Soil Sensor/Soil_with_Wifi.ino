/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6YteNTziR"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "ihfCl3rzOc3JruROwSTukjtYBqzUjPob"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define ldr 33

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);

#define led 5

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Hydra";
char pass[] = "divLX404";

BlynkTimer timer;

BLYNK_WRITE(V1) {
  bool LED = param.asInt();
  if (LED == 1) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

void soilMoisture() {
  int value = analogRead(ldr);
  int newValue = map(value, 0, 4095, 0, 100);
  Blynk.virtualWrite(V2, newValue);
  Serial.println(newValue);

  
    lcd.setCursor(1, 0); 
    lcd.print("Reading...");
    lcd.setCursor(1, 1); 
    lcd.print("Mositure:");
    lcd.print(value);
    delay(100);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  pinMode(ldr,OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  lcd.begin();
    lcd.backlight();
    pinMode(ldr,OUTPUT);
    lcd.setCursor(1, 0); 
    lcd.print("Soil Hydration");
    delay(200);
    lcd.setCursor(1, 1); 
    lcd.print("Monitor System");
    delay(2000);

    lcd.clear();

  
}

void loop()
{
  soilMoisture();
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
