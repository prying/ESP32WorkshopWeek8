#include <WiFi.h>

// The size of the buffer to store the response
#define BUFF_SIZE 1024 

#define SERVER "api.openweathermap.org"
#define API "/data/2.5/weather?q=Melbourne,AUS&appid="
#define API_KEY YOUR_KEY

char ssid[] = MY_SSID;
char pass[] = MY_PASSWORD;


// Create WiFiClient object
WiFiClient client;

void setup()
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
}

void loop()
{
  // Print available bytes from response
  while (client.available()) 
  {
    char c = client.read();
    Serial.write(c);
  }

  // When server is not connected stop the client
  if (!client.connected()) 
  {
    client.stop();
    Serial.println("\nDisconnected from server");
    // Wait forever
    while (true);
  }
}



