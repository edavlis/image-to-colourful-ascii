#include <stdio.h>
#include <strings.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"



int main(int argc, char *argv[]) {
	char oldchars[] = " `^\",:;Il!i~+_-?][}(1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao#MW&8%B@S";
	char chars[] = "             +_-?][}(1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao#MW&8%B@S";
	int charsLen = strlen(chars);

	int imageHeight,imageWidth,numChannels;

	unsigned char *data = stbi_load(argv[1], &imageWidth, &imageHeight, &numChannels, 4); 

	if (!data) {
	  perror("Failed to open file");
	  return 1;
	}

	unsigned char *pixelData = data;
	int columnIndex;
	int rowIndex;
	int pixel = 0;

	for (rowIndex =0; rowIndex < imageHeight; rowIndex++) {
		for (columnIndex = 0 ; columnIndex < imageWidth; columnIndex++) {
			unsigned char r = *pixelData++;
			unsigned char g = *pixelData++;
			unsigned char b = *pixelData++;
			unsigned char a = *pixelData++;
//			printf("\npixel %d:\tr:%c g:%c b:%c a:%c", pixel, r,g,b,a );
			pixel++;

			float brightnessAverage =  (r + g + b) / 3;
			int characterIndex = (int) (( brightnessAverage / 256) * charsLen);
		printf("\033[48;2;%d;%d;%dm%c\033[0m",r,g,b, chars[characterIndex]);
		// erresc: unknown csi ESC[48;2;0z



		}
		printf("\n");


		

	}
	stbi_image_free(data);

	  return 0;
}
