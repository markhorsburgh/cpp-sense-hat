#include <sense-hat.h>
#include <stdio.h>
#include <string.h>

int main() 
{
	SenseHAT senseHAT;
	int rc = senseHAT.blank();
	if(rc != 0) {
		fprintf(stderr, "error in sense_hat_blank(): %s", strerror(rc));
	}
	return 0;
}

