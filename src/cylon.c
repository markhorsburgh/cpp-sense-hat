#include <sense-hat.h>
#include <stdio.h>

int put_dot(int x, uint8_t r, uint8_t g, uint8_t b)
{
	int rc;
	rc = sense_hat_set_pixel(3, x, r, g, b);
	if(rc != 0) return rc;
	rc = sense_hat_set_pixel(4, x, r, g, b);
	if(rc != 0) return rc;
	rc = sense_hat_set_pixel(3, x+1, r, g, b);
	if(rc != 0) return rc;
	rc = sense_hat_set_pixel(4, x+1, r, g, b);
	if(rc != 0) return rc;
}

int main() 
{
	int rc = sense_hat_blank();
	if(rc != 0) {
		fprintf(stderr, "error in sense_hat_blank(): %s", strerror(rc));
	}
	int x = 0;
	int i = 1;
	while(1) {
			rc = put_dot(x, 255, 0, 0);
			if(rc != 0) {
				fprintf(stderr, "error in sense_hat_set_pixel(): %s", strerror(rc));
				return 1;
			}
			usleep(150000);
			rc = put_dot(x, 0, 0, 0);
			if(rc != 0) {
				fprintf(stderr, "error in sense_hat_set_pixel(): %s", strerror(rc));
				return 1;
			}
			x += i;
			if(x < 0) {
				i = 1;
				x = 1;
			}
			if(x > 6) {
				i = -1;
				x = 5;
			}
	}
	return 0;
}

