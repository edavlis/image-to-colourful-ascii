#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION



int main(int argc, char *argv[]) {
  
int imageHeight,imageWidth,numChannels;

unsigned char *data = stbi_load(argv[1], &imageWidth, &imageHeight, &numChannels, 4); 
if (!data) {
  perror("Failed to open file");
}

printf("%s\n", data);
  return 0;
}
