#include <WiFi.h>
#include <ESP32Ping.h>

#define RELAY_PIN 26 // define the pin used to control the relay 
#define RELAY_NO    true // Set to true to define Relay as Normally Open (NO)
#define DEBUG true // enable print messages

const char* ssid     = "ssid";
const char* password = "passphrase";

const char* remote_host = "1.1.1.1";

// relay let the current flow: the router is switched on
void on() {
	if(RELAY_NO) {
		digitalWrite(RELAY_PIN, LOW);
	} else {
		digitalWrite(RELAY_PIN, HIGH);
	}
}

// relay let the current flow: the router is switched off
void off() {
	if(RELAY_NO) {
		digitalWrite(RELAY_PIN, HIGH);
	} else {
		digitalWrite(RELAY_PIN, LOW);
	}
}


void setup() {
  Serial.begin(115200);
  delay(10);

	pinMode(RELAY_PIN, OUTPUT);
	
  // Connecting to a WiFi network
	#if DEBUG
  Serial.println();
  Serial.println("Connecting to WiFi");
	#endif
	
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  #if DEBUG
  Serial.println();
  Serial.print("WiFi connected with ip ");  
  Serial.println(WiFi.localIP());
	#endif
}

void loop() {

	#if DEBUG
	Serial.print("Pinging host ");
  Serial.println(remote_host);
	#endif
	
  if(Ping.ping(remote_host, 10)) {
    // Do nothing, everything going well... For now
  } else {
		#if DEBUG
		Serial.println("Rebooting...");
		#endif
		
		off();
		delay(5000);
		on();
  }

}
