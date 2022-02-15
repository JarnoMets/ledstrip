#include "bluetooth.h"

void Bluetooth::init() {
	Serial.begin(9600);
	Serial.println("Initializing bluetooth...");

	Serial.println("Bluetooth initialized succesfully!");
}

int Bluetooth::dataAvailable() {
	return Serial.available();
}

char* Bluetooth::read(void) {
	while (dataAvailable()) {
		char temp = Serial.read();
		if (temp != '\n' and temp != B1010 and temp != B1101) {
			strncat(string, &temp, 1);
		
		} else if (temp == B1101) {
			return string;
		}
		delay(5);
	}
	for (int i = 0; i < 32; i++) 
        string[i] = B0;
}