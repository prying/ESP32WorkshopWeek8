#include <WiFi.h>
#include <string.h>
#include <ArduinoJson.h>

// The size of the buffer to store the response
#define BUFF_SIZE 1000 

#define KELVIN_CELSIUS 273.15

#define SERVER "api.openweathermap.org"
#define API "/data/2.5/weather?q=Melbourne,AUS&appid="
#define API_KEY YOUR_KEY

char ssid[] = MY_SSID;
char pass[] = MY_PASSWORD;


// Create WiFiClient object
WiFiClient client;

// Prototypes
void WiFi_setup();
void print_weather(char *weather_json)
//void print_weather(char *weather_json);

void setup()
{
	// Condensed wifi startup into a function 
  WiFi_setup();

  // Connect to server for http request (hand shake)
  if (client.connect(SERVER, 80)) 
  {
    Serial.println("connected to server");
    // Make a HTTP request
    client.println("GET "API""API_KEY" HTTP/1.1");
    client.println("Host: " SERVER "");
    client.println("Connection: close");
    client.println();
  }
	Serial.println("sent headder");
}

void loop()
{
	char response_buffer[BUFF_SIZE];
	char *response_ptr;
	
  // Print available bytes from response
  for (int i = 0; client.available(); i++) 
  {
    response_buffer[i] = client.read();
  }
	
  // When server is not connected stop the client
  if (!client.connected()) 
  {
    client.stop();
    Serial.println("\nDisconnected from server\n");
		
		// Remove the header from the response
		response_ptr = strstr(response_buffer, "\r\n\r\n");

		// Shift the pointer accross by 4 
		// as that is the lenght of \r\n\r\n
		response_ptr += 4;

		// Print the weather in a meaningfull way
		print_weather(response_ptr);

    // Wait forever
    while (true);
  }
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

/* prints the weather from json input */
void print_weather(char *weather_json)
{
	DynamicJsonDocument doc(BUFF_SIZE);
	deserializeJson(doc, weather_json);

	JsonArray weather = doc["weather"];
	JsonObject weather_0 = weather[0];
	const char* weather_description = weather_0["description"];

	JsonObject main = doc["main"];
	float temp = main["temp"];
	temp -= KELVIN_CELSIUS;

	Serial.println("\nthe current weather is:");
	Serial.print(weather_description);
	Serial.print(" at a temperature of ");
	Serial.print(temp);
	Serial.println(" C");
}