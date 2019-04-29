#include <WiFi.h>
#include <string.h>
#include <ArduinoJson.h>

// The size of the buffer to store the response
#define BUFF_SIZE 1000 

#define KELVIN_CELSIUS 273.15

#define SERVER "iottemperatureapi.azurewebsites.net"
#define API "/update?key="YOUR_KEY"&temp="


char ssid[] = MY_SSID;
char pass[] = MY_PASSWORD;


// Create WiFiClient object
WiFiClient client;

// Prototypes
void WiFi_setup();
//void print_weather(char *weather_json);

void setup()
{
	// Condensed wifi startup into a function 
  WiFi_setup();

}

void loop()
{
	float temp = 19.2;
	// Connect to server for http request (hand shake)
  if (client.connect(SERVER, 80)) 
  {
    Serial.println("connected to server");
    // Make a HTTP request
    client.print("GET "API);
		client.print(temp);
		client.println(" HTTP/1.1");
    client.println("Host: " SERVER "");
    client.println("Connection: close");
    client.println();
  }
	client.stop();

	// Dont stop the loop()
	while(true);
}


void WiFi_setup()
{
	// Start serial comunications
	Serial.begin(115200);
	// Start WiFi
	// Check if it is currently in connected
	if (WiFi.status() != WL_CONNECTED)
	  {
	    Serial.print("Attempting to connect to ");
	    Serial.println(ssid);
	    WiFi.begin(ssid, pass);
	  }
	  // Check if connected
	while (WiFi.status() != WL_CONNECTED)
	{
	  delay(200);
	  Serial.print("* ");
	  if (WiFi.status() == WL_CONNECT_FAILED)
	  {
	    Serial.print("\nFailed to connect to network!");
	    // Wait for restart
	    while(true);
	  }
	}
	// print connection
	if (WiFi.status() == WL_CONNECTED)
	{
	  Serial.print("connected as: ");
	  IPAddress ip = WiFi.localIP();
		Serial.println(ip);
	}
}

