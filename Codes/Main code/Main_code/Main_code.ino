#include <Wire.h>
#include <UnoWiFiDevEd.h>

void setup() {
  pinMode(9, OUTPUT);
  Wifi.begin();
  Wifi.println("Web Server is f up");
}
void loop() {

  while (Wifi.available()) {
    process(Wifi);
  }
  delay(50);
}

void process(WifiData client) {
  // 4itajet komandu
  String command = client.readStringUntil('/');

  // uzhe zaputalsa
  if (command == "webserver") {
    WebServer(client);
  }

  if (command == "digital") {
    digitalCommand(client);
  }
}

void WebServer(WifiData client) {

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html>");

  client.println("<head> </head>");
  client.print("<body>");

  client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/9/1','_parent');w.close();\"value='ON'>pin9 ON<br>");
  client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/9/0','_parent');w.close();\"value='OFF'>pin9 OFF<br>");

  client.print("</body>");
  client.println("</html>");
  client.print(DELIMITER); // ochen vazhno zakan4ivat tak !!!11one

}

void digitalCommand(WifiData client) {
  int pin, value = 0;

  // Read pin number
  pin = client.parseInt();

  // jesli sledushij simbol eot '/' to eto zna4it u nas jest URL
  // vmeste s value liek: "/digital/9/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  }

  // Send feedback to client
  client.println("Status: 200 OK\n");
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.print(value);
  client.print(EOL);

}
