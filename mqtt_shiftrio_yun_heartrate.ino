#include <Bridge.h>
#include <BridgeClient.h>
#include <MQTT.h>

BridgeClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  while (!client.connect("arduino-yun-vizinviz", "ecf929fe", "f65bde19d8e46d67")) {
   
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Bridge.begin();

  client.begin("broker.shiftr.io", net);
  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 2000) {
    lastMillis = millis();
    //client.publish("/hello", "world");
    //client.publish("/velo", "moto");
    String topic = "/temperature";
    String payload = "";
    payload += random(20, 30);
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish(topic, payload);
   
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);

  }


}
