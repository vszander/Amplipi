#include <HTTPClient.h>

#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include <Button2.h>
//#include "shortjson.h"
#include "WiFi.h"
#include "secrets.h"  //  this avoids publishing confidential wifi credentials


TFT_eSPI tft = TFT_eSPI(135,240);  // screen size 135 x 240
#define BUTTON_1            35
#define BUTTON_2  0
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
int btnCick = false;  // a flag, used by Button2 to determine when a button has been pressed 
int wificonnected = 0;
int multitry =0; //  used to count retrys during failure loops
bool trying = true;   //used to control timeouts during various while loops
int counter = 0;
int myZone = 0;   // this is the zone we are trying to control

//StaticJsonDocument<12000> doc;
DynamicJsonDocument doc(12000);

void setup() {
  Serial.begin(9600);
  tft.init();
  button_init();
  tft.setRotation(3);  //2=180   //3=  preferred - on its side  USB to the left
  tft.fillScreen(TFT_BLACK);

  tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
  tft.setTextSize(1);

  connectWifi(); 
//   it would make sense to interact with the device using MQTT.
//  http://www.steves-internet-guide.com/using-arduino-pubsub-mqtt-client/
  

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2

  
  getAmpliPiStatus();
//  deserialize();

  statusAmplipi();


}

void loop() {
     button_loop();
     delay(100);
}

int makeAnnouncement(int messageId){
  String destination = "http://" + ampliPiHost + "/api/announce";
  // Serialize JSON document
  StaticJsonDocument <1300> doc2;
  String json3;
  doc2["media"] = "file:///home/pi/Music/beds/BackInTimeRingtone.mp3";
  doc2["source_id"] = 0;
  serializeJson(doc2, json3);
  Serial.println(json3);
  
      
  HTTPClient http2;
  http2.begin(destination); //Specify the URL
  http2.useHTTP10(true);
  http2.addHeader("Content-Type", "application/json");
  http2.addHeader("Accept", "application/json");
  http2.addHeader("Connection", "keep-alive");       

  int httpResponseCode = http2.POST(json3);
  Serial.println(httpResponseCode);
  //  https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/#how-to-send-a-json-document-in-an-http-request

    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // https://programmer.ink/think/color-setting-and-text-display-esp32-learning-tour-arduino-version.html
    tft.setTextSize(1);
    //tft.println(json2);
    tft.println(http2.getString());
    Serial.println(http2.getString());
    tft.setTextSize(2);
  http2.end();
  return httpResponseCode;
}
int changeStream(int desiredStream){
  String destination = "http://" + ampliPiHost + "/api/sources/0";
  // Serialize JSON document
  StaticJsonDocument <1300> doc2;
  String json3; 
  String strStream = String(desiredStream);   //https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/
  String Streamer = "stream=" + strStream;
  doc2.clear();
  //JsonObject updatelist = doc2.createNestedObject("update");
  doc2["input"] = Streamer;
  //JsonArray array = zonelist.to<JsonArray>();
  Serial.println(destination);
  serializeJson(doc2, json3);
  Serial.println(json3);
  
      
  HTTPClient http2;
  http2.begin(destination); //Specify the URL
  http2.useHTTP10(true);
  http2.addHeader("Content-Type", "application/json");
  http2.addHeader("Accept", "application/json");
  http2.addHeader("Connection", "keep-alive");       

  int httpResponseCode = http2.PATCH(json3);
  Serial.println(httpResponseCode);
  //  https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/#how-to-send-a-json-document-in-an-http-request

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    //tft.println(json2);
    tft.println(http2.getString());
    Serial.println(http2.getString());
    tft.setTextSize(2);
  http2.end();
  return httpResponseCode;
}

int changeSource(int desiredSource){
  String destination = "http://" + ampliPiHost + "/api/zones";
  // Serialize JSON document
  StaticJsonDocument <1300> doc2;
  String json3;
  doc2.clear();
  JsonArray zonelist = doc2.createNestedArray("zones");  // https://forum.arduino.cc/t/arduinojson-nested-array/679830
  JsonObject updatelist = doc2.createNestedObject("update");
  updatelist["source_id"] = desiredSource;  //  https://github.com/bblanchon/ArduinoJson/issues/201
  zonelist.add(myZone);
  Serial.println(destination);
  serializeJson(doc2, json3);
  Serial.println(json3);
  
      
  HTTPClient http2;
  http2.begin(destination); //Specify the URL
  http2.useHTTP10(true);
  http2.addHeader("Content-Type", "application/json");
  http2.addHeader("Accept", "application/json");
  http2.addHeader("Connection", "keep-alive");       

  int httpResponseCode = http2.PATCH(json3);
  Serial.println(httpResponseCode);
  //  https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/#how-to-send-a-json-document-in-an-http-request

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    //tft.println(json2);
    tft.println(http2.getString());
    Serial.println(http2.getString());
    tft.setTextSize(2);
  http2.end();
  return httpResponseCode;
}

int changeVolume(int vol_level){
 // String destination = "http://" + ampliPiHost + "/api/zones/" + str(myZone);
    String destination = "http://amplipi.local/api/zones/0";
  // Serialize JSON document
  StaticJsonDocument <1300> doc2;
  String json3;
  doc2["vol"] = -25;
//  String json3 = "{\"vol\":-20}";

  serializeJson(doc2, json3);
  Serial.println(json3);
  
      
  HTTPClient http2;
  http2.begin(destination); //Specify the URL
  http2.useHTTP10(true);
  http2.addHeader("Content-Type", "application/json");
  http2.addHeader("Accept", "application/json");
  http2.addHeader("Connection", "keep-alive");       

  int httpResponseCode = http2.PATCH(json3);
  Serial.println(httpResponseCode);
  //  https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/#how-to-send-a-json-document-in-an-http-request
  http2.end();
  return 1;
}
int getAmpliPiStatus(){
    
  HTTPClient http;
  http.useHTTP10(true);
  http.begin("http://amplipi.local/api"); //Specify the URL
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
//  https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/
  DeserializationError error = deserializeJson(doc, http.getString());
  http.end();
  // Test if parsing succeeds.
  if (error) {
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print(F("deserializeJson() failed: "));
    tft.println(error.f_str());
         delay(9000); 
    return -1;
  }
  else{
    return 1;
  }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  tft.fillScreen(TFT_PURPLE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
    tft.setTextSize(2);
    tft.println("HTTPS SUCCESS !");  
     tft.println("httpResponseCode");
     delay(2000);   
  return httpResponseCode;
}


int statusAmplipi() {
  int activeSource = -1;

  //  https://stackoverflow.com/questions/68751980/androidjson-parsing-nested-get-response

  JsonArray sources = doc["sources"];
  for (JsonVariant sourc: sources) {
      const char* sourcName = sourc["name"];
      int sourceid = sourc["id"];
      String sourceInput = sourc["input"];
    //  JsonObject sourcInfo = sourc["info"].value();
      String InfoName = sourc["info"]["name"];
      String InfoState = sourc["info"]["state"];
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
      tft.print("   ");
      tft.print(sourceid );
      tft.print(" ");
      if(InfoState == "playing"){
        tft.setTextColor(TFT_WHITE, TFT_RED);
        activeSource = sourceid;
      }else{
        tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
      }

      tft.println(InfoName);

  }
  
  JsonArray streams = doc["streams"];
  for (JsonVariant stream: streams) {
      const char* streamName = stream["name"];
      int streamid = stream["id"];
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.print(streamid );
      tft.print(" ");
      tft.setTextColor(TFT_DARKGREY, TFT_BLACK);

      tft.println( streamName);
  }
  
  JsonObject info = doc["info"];
    String infoconfig = info["config_file"]; 
    tft.print("name: ");
    tft.println(infoconfig);

  return activeSource;
}

void button_loop()
{
    btn1.loop();
    btn2.loop();
}

void button_init()
{
    btn1.setLongClickHandler([](Button2 & b) {
        btnCick = false;
        int r = digitalRead(TFT_BL);
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
        tft.drawString("Press again to wake up",  tft.width() / 2, tft.height() / 2 );
       // espDelay(2000);
        digitalWrite(TFT_BL, !r);

        tft.writecommand(TFT_DISPOFF);
        tft.writecommand(TFT_SLPIN);
        //After using light sleep, you need to disable timer wake, because here use external IO port to wake up
        esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
        // esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);
        delay(200);
        esp_deep_sleep_start();
      });
  btn1.setPressedHandler([](Button2 & b) {
    btnCick = true;
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
    tft.setTextSize(2);
    tft.println("btn 1"); 
    btnCick = false;
    changeSource(0);
    changeStream(1002);
//    makeAnnouncement(1);      
    });

  btn2.setPressedHandler([](Button2 & b) {
    btnCick = true;
    tft.fillScreen(TFT_BLUE);
    tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
    tft.setTextSize(2);
    tft.println("btn 2");
    btnCick = false;   
    });
}

//! Long time delay, it is recommended to use shallow sleep, which can effectively reduce the current consumption
void espDelay(int ms)
{
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
    esp_light_sleep_start();
}

int connectWifi() {
    while (trying) {
      tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
      tft.print("Connecting to: "); 
      tft.println(ssid);  // stored in secrets.h
      char* currentssid = ssid;
      Serial.print("Connecting");
      wificonnected = 0;
      counter = 0;
      WiFi.begin(currentssid, password);

      
      
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(300);
        counter +=1;
        Serial.print(".");
        tft.print(".");
    
        if (counter > 20){
            if (currentssid == ssid2) {
               currentssid = ssid;
            } else {
              currentssid = ssid2;
            }
          tft.setCursor(0, 0, 2);
          tft.print("switching to");
          tft.println(currentssid);
          counter = 0;
          delay(2000);
          WiFi.begin(currentssid, password);
          tft.fillScreen(TFT_BLACK);
          multitry += 1;
          if ( multitry > 4){
            wificonnected = 0;
            trying = false;
          }
        }
        
      }
      break; //Wifi Status
      trying = false;
      wificonnected = 1;
    
  } 
  if( wificonnected == 1 ) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
  tft.print("Connected, IP address: ");
  tft.println(WiFi.localIP());
  
 // delay1 = 1000;
  Serial.println(WiFi.localIP());
    
  } else {
      tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2); ///    // Set "cursor" at top left corner of display (0,0) and select font 2
  tft.print("WiFi Failed: ");
  tft.println(WiFi.localIP());
  }
  return wificonnected;
}
