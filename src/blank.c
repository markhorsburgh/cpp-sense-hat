#include <sense-hat.h>
#include <stdio.h>

int main() 
{
	int rc = sense_hat_blank();
	if(rc != 0) {
		fprintf(stderr, "error in sense_hat_blank(): %s", strerror(rc));
	}
	return 0;
}

