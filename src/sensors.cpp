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
	return 0;
}

