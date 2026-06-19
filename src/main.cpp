#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
// put function declarations here:
void setupServer();
HardwareSerial printer(2);

WebServer server(80);

void setup() {
  setupServer();    

  // put your setup code here, to run once:
  delay(2000);   // critical
  printer.begin(
    9600,
    0x800001c,
    16,
    17
  );
  printer.println("");
  printer.println("");
  delay(50);
  printer.println("******************************");
  delay(50);
  printer.println("********* HELLO GOAT *********");
  delay(50);
  printer.println("******************************");
  delay(50);
  printer.println("");
  printer.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void setupServer() {
    const char* ssid = "glinet";
    const char* password = "aJpxasPX13haHeYwam";
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    server.on("/test", HTTP_GET, []() {
        server.send(200, "text/plain", "ok");
    });
    server.on(
    "/print/raw",
    HTTP_POST,
    []()
    {
      String body = server.arg("plain");

      printer.write(
          (const uint8_t*)body.c_str(),
          body.length()
      );

      server.send(
          200,
          "application/json",
          "{\"ok\":true}"
      );
    }
  );
    server.begin();
}