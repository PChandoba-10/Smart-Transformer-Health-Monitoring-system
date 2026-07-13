#define BLYNK_TEMPLATE_ID "TMPL3YllQqwJj"
#define BLYNK_TEMPLATE_NAME "Transformer health monitoring"
#define BLYNK_AUTH_TOKEN "MHzYkmw3H1HMFbleahWo6A10J19_oRjI"

#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp32.h>
#include <UniversalTelegramBot.h>
#include <HardwareSerial.h>

#define BOT_TOKEN "8756555940:AAE482FL7BmwgVpU3S_PMdgndqcr4hcP5k4"
#define CHAT_ID "6345809189"

HardwareSerial gsm(2); // RX=16 TX=17
String phoneNumber = "+918010757295"; 

void setupWifi();
void sendData();
void sendBlynkData();
void sendthingSpeakData();
void sendTelegram(String msg);
void sendSMS(String msg);


const char *SSID = "Payal";
const char *passward = "88888888";
const char *API_key = "X62U4QTOTW7GVXGK";


float tankheight = 20.0;
float temperature;
float current;
float oillevel;

#define CURR_sensor 35
#define TEMP_sensor 34
// ultrasonic sensor
#define TRIG_PIN 5
#define ECHO_PIN 18

#define RELAY 23
#define BUZZER 19

BlynkTimer timer;
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

void setup()
{
  Serial.begin(115200);
  // setupWifi();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RELAY, LOW);  // Relay ON
  digitalWrite(BUZZER, LOW); // Buzzer OFF

  Blynk.begin(BLYNK_AUTH_TOKEN, SSID, passward);

  timer.setInterval(1000L, sendData);
  timer.setInterval(1000L, sendBlynkData);
  timer.setInterval(15000L, sendthingSpeakData);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    setupWifi();
  }

  Blynk.run();
  timer.run();
}

void setupWifi()
{

  WiFi.begin(SSID, passward);
  Serial.print("Connecting..");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected.");
}

// Send data
void sendData()
{

  // CALCULATION FOR TEMPERATURE SENSOR
  int adcVal = analogRead(TEMP_sensor);
  float voltage = adcVal * (3.3 / 4095.0); // in mV
  temperature = voltage * 100 ;                 // LM35 10mV per degree celsius


  // CALCULATION OF CURRENT SENSOR
  int adcVal1 = analogRead(CURR_sensor);
  float Vout = adcVal1 * (3.3 / 4095.0);
  current = abs((Vout - 2.5) / 0.100); // current sensor of 20A and sensitivity 100mV/A


  // CALCULATION OF OIL LEVEL SENSOR
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0)
  {
    Serial.println("Ultrasonic timeout");
    return;
  }
  float distance = duration * (0.034 / 2);
  oillevel = tankheight - distance;


  // print on serial monitor
  Serial.print("Temp: ");
  Serial.println(temperature);

  Serial.print("Current: ");
  Serial.println(current);

  Serial.print("Level: ");
  Serial.println(oillevel);


  if (current > 0.8 || temperature > 60 || oillevel < 10)
  {
    digitalWrite(RELAY, HIGH);
    digitalWrite(BUZZER, HIGH);

    String msg =
        "Transformer Fault Detected!\n"
        "Temp: " + String(temperature) +
        " C\nCurrent: " + String(current) +
        " A\nOil Level: " + String(oillevel) + " cm";
  }
  else
  {
    digitalWrite(RELAY, LOW);
    digitalWrite(BUZZER, LOW);
  }

 
}

void sendthingSpeakData()
{
  // data transfer
  // create object
 
  client.setInsecure();

  HTTPClient http;
  // SEND DATA ON CHANNEL
  String url =
      "https://api.thingspeak.com/update?api_key=" +
      String(API_key) +
      "&field1=" +
      String(temperature) +
      "&field2=" +
      String(current) +
      "&field3=" +
      String(oillevel);

  http.begin(client, url);


  // only for debugging
  int httpCode = http.GET();

  if (httpCode > 0)
  {
    Serial.println("ThingSpeak Updated");
  }
  else
  {
    Serial.println("ThingSpeak Error");
  }

  http.end();
}

void sendBlynkData()
{
  // send to blynk server
  Blynk.virtualWrite(V0, current);
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, oillevel);
}
//GSM 
void sendSMS(String msg)
{
  Serial.println("Sending SMS...");

  gsm.println("AT");
  delay(1000);

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");

  delay(1000);

  gsm.print(msg);

  delay(500);

  gsm.write(26);

  delay(5000);

  Serial.println("SMS Sent");
}
//TELEGRAM
void sendTelegram(String msg)
{
  bot.sendMessage(CHAT_ID, msg, "");
}
