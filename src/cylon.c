#include <sense-hat.h>
#include <stdio.h>

int main() 
{
	int x = 0;
	int i = 1;
	while(1) {
			int rc = sense_hat_set_pixel(4, x, 255, 0, 0);
			if(rc != 0) {
				fprintf(stderr, "error in sense_hat_set_pixel(): %s", strerror(rc));
			}
			usleep(150000);
			rc = sense_hat_set_pixel(4, x, 0, 0, 0);
			if(rc != 0) {
				fprintf(stderr, "error in sense_hat_set_pixel(): %s", strerror(rc));
			}
			x += i;
			if(x < 0) {
				i = 1;
				x = 1;
			}
			if(x > 7) {
				i = -1;
				x = 6;
			}
	}
}

