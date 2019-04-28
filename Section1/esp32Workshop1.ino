/* Title
 * Flynn Harrison
 * 26/04/2019
 */
#include "secret.h"
#include <WiFi.h>

char ssid[] = MY_SSID;
char pass[] = MY_PASSWORD;

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

void loop()
{
  delay(1000);
  Serial.println(WiFi.status());
}