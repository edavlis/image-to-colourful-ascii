#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/stb_image_resize2.h"



int main(int argc, char *argv[]) {

	char *helpMessage = "Usage: ascii-to-image <path to image>\nOptions:\n\t-s: Scale image to terminal size\n\t-h: Print this message: \n";

	if (argc == 1) {
			printf("%s", helpMessage);
			return 1;
	}

	int notScaled = 0;
	int opt;
	while ((opt = getopt(argc, argv, "sh")) != -1)  {
		switch (opt) {
//		case 's':
//			notScaled = 1;		
//			break;
		case 'h':
			printf("%s", helpMessage);
			return 0;
		
		}
			}
	// different levels of ascii-ification
	const char wchars[] = " `^\",:;Il!i~+_-?][}(1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao#MW&8%B@S";
	const char chars[] = "                                        `^\",:;Il!i~+_-?][}(1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao#MW&8%B@S";
	const char xchars[] = "                                   vczXYUJCLQ0OZmwqpdbkhao#MW&8%B@S";
	const char ychars[] = "                                           CLQ0OZmwqpdbkhao#MW&8%B@S";
	const char zchars[] = "                                        UJCLQ0OZmwqpdbkhao#MW&8%B@S";
	int charsLen = strlen(chars);
	//const char *chars[22]= {" ", " ", " ", " "," ", " ","⠁","⠂","⠃","⠅", "⠇","⠋", "⠛", "⠟","⠿","⡟","⡿","⢿","⣟","⣯","⣷","⣿"};
	//int charsLen = sizeof(chars) / sizeof(chars[0]);

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int winHeight = w.ws_row - 1; // promtp at bottom
	int winWidth = w.ws_col;

	int imageHeight,imageWidth,numChannels;
	unsigned char *data = stbi_load(argv[1], &imageWidth, &imageHeight, &numChannels, 4); 

	if (!data) {
	  perror("Failed to open file");
	  return 1;
	}

//	if (notScaled == 1) {
//	} else {
//	// if image is too wide
	if (imageWidth > winWidth) {
		float imageToWindowScaleFactor = (float) imageWidth / winWidth;
		unsigned char *resizedData = malloc(winWidth * ((int)( imageHeight / imageToWindowScaleFactor)) * 4);
		stbir_resize_uint8_srgb(data, imageWidth, imageHeight, 0, resizedData, winWidth, (int) (imageHeight / imageToWindowScaleFactor), 0, 4);
		data = resizedData;
		imageWidth = winWidth;
		imageHeight = (int) imageHeight / imageToWindowScaleFactor; 
	}
	// if image to too tall
	if (imageHeight > winHeight) {
		float imageToWindowScaleFactor = (float) imageHeight / winHeight;
		unsigned char *resizedData = malloc(winHeight* ((int)( imageWidth / imageToWindowScaleFactor)) *4);
		stbir_resize_uint8_srgb(data, imageWidth, imageHeight, 0, resizedData, (int) imageWidth / imageToWindowScaleFactor, winHeight, 0, 4);
		data = resizedData;
		imageHeight = winHeight;
		imageWidth = (int) imageWidth / imageToWindowScaleFactor; 
	}
//	}

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
			pixel++;

			float brightnessAverage =  (r + g + b) / 3;
			int characterIndex = (int) (( brightnessAverage / 256) * charsLen);
		printf("\033[48;2;%d;%d;%dm%c\033[0m",r,g,b, chars[characterIndex]);



		}
		printf("\n");


		

	}
	stbi_image_free(data);
//	stbi_image_free(resizedData);

	  return 0;
}
