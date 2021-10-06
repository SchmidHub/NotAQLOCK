#include "main.h"
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "../.pio/libdeps/nodemcuv2/ArduinoJson/src/ArduinoJson.h"

String httpGETRequest(const char *serverName)
{
    WiFiClient client;
    HTTPClient http;

    // Your IP address with path or Domain name with URL path
    http.begin(client, serverName);

    // Send HTTP POST request
    api_response_code = http.GET();

    String payload = "{}";

    if (api_response_code > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(api_response_code);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(api_response_code);
    }
    // Free resources
    http.end();

    return payload;
}

void get_time_from_api()
{
    const char *timeApi = "http://worldtimeapi.org/api/timezone/Europe/Berlin";
    String timeString;
    StaticJsonDocument<800> doc;
    unsigned long timerDelay = 1000;
    static unsigned long lastTime = 0;
    if ((millis() - lastTime) > timerDelay)
    {
        //Check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
            timeString = httpGETRequest(timeApi);

            // Deserialize the JSON document
            DeserializationError error = deserializeJson(doc, timeString);

            // Test if parsing succeeds.
            if (error)
            {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return;
            }
            String currentDateTime = doc["datetime"];
            String unixtimeStr = doc["unixtime"];
            String offsetStr = doc["raw_offset"];
            int offset = offsetStr.toInt();
            unixtime = unixtimeStr.toInt() + 2 * offset;
            // Only Update Time if api call was successful
            Serial.println(currentDateTime == "null");
            if (currentDateTime != "null")
            {
                String hoursStr = currentDateTime.substring(11, 13);
                String minutesStr = currentDateTime.substring(14, 16);

                hours = hoursStr.toInt();
                minutes = minutesStr.toInt();
            }
        }

        lastTime = millis();
    }
}