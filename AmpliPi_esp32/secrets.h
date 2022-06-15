#ifndef _SECRETS_H    // Put these two lines at the top of your file.
#define _SECRETS_H    // (Use a suitable name, usually based on the file name.)

char* ssid = "Bristol"; //replace this with your WiFi network name
char* ssid2 = "Daytona"; //replace this with your WiFi network name
const char* password = "password"; //replace this with your WiFi network password
bool connected = 0;

String ampliPiHost = "amplipi.local";

const char* mqttServer = "192.168.176.9";
const int mqttPort = 1883;
const char* mqttUser = "yourInstanceUsername";
const char* mqttPassword = "yourInstancePassword";
const char* TOPIC = "weather/subtopic";  //  this also will be tracable in InfluxDB


#endif //  _SECRETS_H    // Put this line at the end of your file.
