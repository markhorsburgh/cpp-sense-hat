#include <pthread.h>
#include <errno.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "sense-hat.h"

static pthread_mutex_t sense_hat_mutex = PTHREAD_MUTEX_INITIALIZER;
static int sense_hat_fbfd = -1;
const char SENSE_HAT_FB_NAME[] = "RPi-Sense FB";

static uint16_t pack_pixel(uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t r16 = (r >> 3) & 0x1F;
	uint16_t g16 = (g >> 2) & 0x3F;
	uint16_t b16 = (b >> 3) & 0x1F;
	return (r16 << 11) + (g16 << 5) + b16;
}

static void sense_hat_rstrip(char* s)
{
	size_t l = strlen(s);
	if(l == 0) return;
	char* end = s + l - 1;
	while(end >= s && isspace(*end)) {
		end--;
	}
	end[1] = '\0';
}

static int sense_hat_init_fb()
{
	if(sense_hat_fbfd != -1) {
		return 0;
	}
	DIR* d = opendir("/sys/class/graphics");
	if(d == NULL) {
		return errno;
	}
	struct dirent* dent = (struct dirent*)malloc(offsetof(struct dirent, d_name) + NAME_MAX + 1);
	struct dirent* dentp;
	while(1) {
		int rc = readdir_r(d, dent, &dentp);
		if(rc == 0 && dentp == NULL) {
			rc = ENOENT;
		}
		if(rc != 0) {
			free(dent);
			closedir(d);
			return rc;
		}
		if(strncmp("fb", dent->d_name, 2) == 0) {
			char path[PATH_MAX];
			snprintf(path, PATH_MAX, "/sys/class/graphics/%s/name", dent->d_name);
			FILE* f = fopen(path, "r");
			if(f == NULL) continue;
			char name[1024];
			fgets(name, sizeof(name), f);
			sense_hat_rstrip(name);
			if(strcmp(name, SENSE_HAT_FB_NAME) == 0) {
				snprintf(path, PATH_MAX, "/dev/%s", dent->d_name);
				sense_hat_fbfd = open(path, O_RDWR);
				free(dent);
				closedir(d);
				if(sense_hat_fbfd == -1) {
					return errno;
				}
				break;
			}
		}
	}
	return 0;
}

int sense_hat_set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	int rc = sense_hat_init_fb();
	if(rc != 0) {
		return rc;
	}
	uint16_t p = pack_pixel(r, g, b);
	pwrite(sense_hat_fbfd, &p, 2, (x + y*8)*2);
	return 0;
}

/*
int main() 
{
	int x, y;
	for(x = 0; x < 8; x++) {
		for(y = 0; y < 8; y++) {
			int rc = sense_hat_set_pixel(x, y, 255, 255, 255);
			if(rc != 0) {
				fprintf(stderr, "error in sense_hat_set_pixel(): %s", strerror(rc));
			}
			usleep(100000);
			rc = sense_hat_set_pixel(x, y, 0, 0, 0);
			if(rc != 0) {
				fprintf(stderr, "error in sense_hat_set_pixel(): %s", strerror(rc));
			}
		}
	}
}
*/

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

