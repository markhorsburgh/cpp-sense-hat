/*
 *
 */

#include <stdint.h>

class SenseHAT {
public:
	SenseHAT();

	// Methods for manipulating LED matrix
	int blank();
	int set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

private:
	int fbfd;

	int init_fb();
};
