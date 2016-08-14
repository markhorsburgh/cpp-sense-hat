/*
 *
 */

#include <stdint.h>

class RTHumidity;

class SenseHAT {
public:
	SenseHAT();

	// Methods for manipulating LED matrix
	int blank();
	int set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

	// Sensor methods
	double get_humidity();

private:
	int fbfd;

	int init_fb();

	RTHumidity* humidity;
};
