#include <Bridge.h>
#include <BridgeClient.h>
#include <MQTT.h>

BridgeClient net;
MQTTClient client;

unsigned long lastMillis = 0;
float theInterrupt = 0;
int prevCount = 0;
int counter = 0;

void connect() {
  while (!client.connect("arduino-yun-vizinviz", "ecf929fe", "f65bde19d8e46d67")) {

  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Bridge.begin();

  client.begin("broker.shiftr.io", net);
  connect();

  attachInterrupt(digitalPinToInterrupt(2), interrupt, RISING);//set interrupt 0,digital port 3
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (prevCount!=counter) {
    prevCount = counter;
    //client.publish("/hello", "world");
    //client.publish("/velo", "moto");
    String topic = "/interrupt";
    String payload = "";
    payload += counter;
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish(topic, payload);

    delay(100);
    digitalWrite(LED_BUILTIN, LOW);

  }


}

/*Function: Interrupt service routine.Get the sigal from the external interrupt*/
void interrupt()
{

  theInterrupt = millis();
  counter++;

}
