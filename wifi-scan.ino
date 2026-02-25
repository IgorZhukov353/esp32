#include <WiFi.h>
#include <WiFiClientSecure.h>


WiFiClientSecure client;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  Serial.println("\nStarting connection to server...");
  client.setInsecure();

  const char*  server = "uploader919klg.disk.yandex.net"; //cloud-api.yandex.net";

  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println("PUT /upload-target/20260225T161604.075.utd.6ewngjt5jgotf5ni8ippjmuff-k919klg.1557354 HTTP/1.1");
    //GET /v1/disk/resources/upload?path=fortest%2Fdir1%2Ffile2.txt&fields=custom_properties HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Content-Length: 12");
    client.println("Connection: close");
    client.println();
    client.println("fortest890");

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
      else
        Serial.println(line);
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    client.stop();
  }
  Serial.println(" Connected2!");
}

void loop() {

  delay(100); // TODO: Build something amazing!

}