#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "glinet";
const char* password = "aJpxasPX13haHeYwam";
AsyncWebServer server(80);
server.on(
    "/print/raw",
    HTTP_POST,
    [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request,
       uint8_t *data,
       size_t len,
       size_t index,
       size_t total)
    {
        Serial2.write(data, len);

        if(index + len == total)
        {
            request->send(
                200,
                "application/json",
                "{\"ok\":true}"
            );
        }
    }
);