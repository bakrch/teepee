#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
// put function declarations here:
void setupServer();
HardwareSerial printer(2);

WebServer server(80);

void setup() {
  Serial.begin(115200);
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
    Serial.println("Connecting to wifi..");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.println("Connection established.");
    server.on("/test", HTTP_GET, []() {
        server.send(200, "text/plain", "ok");
    });
    server.on(
    "/print/text",
    HTTP_POST,
    []()
    {

      Serial.println("Received request at /print/raw");
      String body = server.arg("plain");
      Serial.println("Request body: " + body);
      printer.print(body);
      printer.println("\n\n");

      server.send(
          200,
          "application/json",
          "{\"ok\":true}"
      );
    }
  );
    server.begin();
}