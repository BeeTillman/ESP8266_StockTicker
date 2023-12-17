
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Math.h>
#include "lcd_functions.h"
#include "keys.h"



#define TEST_HOST "www.finnhub.io"
#define ssid ssidKey // Network SSID (Defined in keys header)
#define password passwordKey  // Network Password (Defined in keys header)
#define TEST_HOST_FINGERPRINT fingerprintKey   // Chrome fingerprint (Defined in keys header)
#define apikey apiKey // Finnhub.io API Key (Defined in keys header)

WiFiClientSecure client;

  // This is almost certainly your display's i2c address, but worth checking if you're having issues


void setup() {
  Serial.begin(112500); //esp8266 default baud rate
  displayInitialStartup();
  client.setInsecure();
}

void loop() {
  //Connect To WiFi
  connectToWiFi(); // I have it connect to WiFi every few calls just in case the connection gets interrupted. 
                    // Connecting and disconnecting more than required isn't going to cause any problems; better safe than sorry
                    
  getData("FIVN");
  delay(25000);
  getData("AMZN");
  delay(25000);
  getData("NVDA");
  delay(25000);
  getData("AAPL");
  delay(25000);
}

void getData(String ticker){
  // Don't ask me how any of this code works. I have no idea
    Serial.println("Making a HTTP Request");
  // Opening connection to server (Use 80 as port if HTTP)
  if (!client.connect(TEST_HOST, 443))
  {
    Serial.println(F("Connection failed"));
  }

  // give the esp a breather
  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  // API KEY GOES HERE
  client.print("/api/v1/quote?symbol="+ticker+"&token="+apikey); // %2C == ,
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
  }
  //delay(100);
  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
  }

  // This is probably not needed for most, but I had issues
  // with the Tindie api where sometimes there were random
  // characters coming back before the body of the response.
  // This will cause no hard to leave it in
  // peek() will look at the character, but not take it off the queue
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
    Serial.println("BAD");
  }

    // While the client is still availble read each
    // byte and print to the serial monitor
    // This is kind of unnecessary but I added the for loop
    // to limit API calls that return huge amounts of data
    String peppapig = ""; // don't make fun of my variable declaration
    for (int i=0; i<600; i++){
      if (client.available()) {
        char c = 0;
        client.readBytes(&c, 1);
        Serial.print(c);
        peppapig+=c;
        }
    }

    // We now have a String called peppapig, which contains the first 
    // 600 characters that were returned from our API call. 
    // We now throw peppapig into a JSON document so we can index it.
    Serial.println(peppapig);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, peppapig);
    JsonObject obj = doc.as<JsonObject>();
  
    String currentPrice = obj["c"].as<String>();
    String pchange = obj["dp"].as<String>();
    float float_pchange = pchange.toFloat();

    displayStockResult(ticker, float_pchange, currentPrice);
}


void connectToWiFi(){
 // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { // Wireless network not connected
    Serial.println("");
    Serial.println("Awaiting WiFi Connection.");
    Serial.println("Update Environment Variables if Necessary");
    displayReconnectingCycle();
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  displayWifiSuccess();
  delay(1000);
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setFingerprint(TEST_HOST_FINGERPRINT);
}
