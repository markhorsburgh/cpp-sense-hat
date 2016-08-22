#include <sense-hat.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

int main() 
{
	SenseHAT senseHAT;
	cout << "Humidity: " << senseHAT.get_humidity() << endl;
	cout << "Temperature from humidity: " << senseHAT.get_temperature_from_humidity() << endl;
	cout << "Temperature: " << senseHAT.get_temperature() << endl;
	return 0;
}

