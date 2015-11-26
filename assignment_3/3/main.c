#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char **argv){
	wiringPiSetupGpio(); //wiringPi v2 returns always 0

	int led_pins[] = {2,3,4,7,8,9,10,11}; 


	for (int i = 0; i < 8; i++) {
		pinMode(led_pins[i], OUTPUT);
		digitalWrite(led_pins[i], LOW);
	}

	for (int i = 0; i < 8; i++) {
		delay(1000);
		digitalWrite(led_pins[i], HIGH);
	}

	return 0;
}
