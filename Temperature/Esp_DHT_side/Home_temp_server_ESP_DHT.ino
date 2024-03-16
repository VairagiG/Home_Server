#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

#define DHTPIN 2        // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

#define location "Add location here"
#define sensor "DHT11"
DHT dht(DHTPIN, DHTTYPE);

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "Password";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.1.26/post-esp-temp-data.php";

String apiKeyValue = "Add API key here";

void setup() {
  dht.begin(); 
  Serial.begin(115200);
  delay(10);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int value = 0;
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Read temperature as Celsius (the default)

    
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
//    String httpRequestData = "api_key=BWwdjMeIUg&sensor=BME280&location=Office&Temperature=24.75&Humidity=49.54";
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + String(sensor)
                          + "&location=" + String(location) + "&Temperature=" + String(t) + "&Humidity=" + String(h) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(900000);  
}
