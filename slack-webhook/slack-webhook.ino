#include <Nefry.h>
#include <WiFiClientSecure.h>

const int httpPort = 443;
const char* host = "hooks.slack.com";

void setup() {
  Nefry.setStoreTitle("WebhookURL", 0);
  Nefry.setStoreTitle("UserName", 1);
  Nefry.setStoreTitle("IconEmoji", 2);
  Nefry.setStoreTitle("Text1", 3);
  Nefry.setStoreTitle("Text2", 4);
  Nefry.setStoreTitle("Text3", 5);
  Nefry.enableSW();
  Nefry.setLed(0, 0, 255);
}

void loop() {
  if(Nefry.readSW()) {
    postIncommingWebHook();
    Nefry.setLed(0, 0, 255);
  }
}

void postIncommingWebHook() {

  String url = Nefry.getStoreStr(0);
  String userName = Nefry.getStoreStr(1);
  String iconEmoji = Nefry.getStoreStr(2);
  String* texts = new String[3];
  texts[0] = Nefry.getStoreStr(3);
  texts[1] = Nefry.getStoreStr(4);
  texts[2] = Nefry.getStoreStr(5);

  WiFiClientSecure client;

  if (client.connect(host, httpPort)) {

    String payload = String("payload={") +
                            "'text': '" + texts[random(3)] + "', " +
                            "'username': '" + userName + "', " +
                            "'icon_emoji': '" + iconEmoji + "', " +
                            "}";

    client.print(
                 String("POST ") + url + " HTTP/1.1\r\n" +
                 "Host: " + String(host) + "\r\n" +
                 "Connection: close\r\n"
                 "Content-Type: application/x-www-form-urlencoded\r\n" +
                 "Content-Length: " + String(payload.length()) + "\r\n" + 
                 "\r\n" +
                 payload + "\r\n"
                 );

    Nefry.setLed(0, 255, 0);
    Nefry.ndelay(1000);

  } else {
    Nefry.setLed(255, 0, 0);
    Nefry.ndelay(1000);
  }
}

