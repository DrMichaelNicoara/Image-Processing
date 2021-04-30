#pragma once
#include <stdint.h>
#include <cstdio>

enum ImageType
{
	PNG, JPG, BMP, TGA
};

class Image
{
private:
	// Image Header data
	uint8_t* data = NULL;
	size_t size = 0;
	int width, height;
	int channels;

private:
	bool read(const char* filename);
	ImageType getFileType(const char* filename);

public:
	//Features
	void grayscale_avg(); // Each pixel = average of (R, G, B) of that pixel
	void grayscale_lum(); // Does the same thing like grayscale_avg(), but uses special formula based on how humans perceive colors
	void colorMask(double r, double g, double b); // Adds a filter over the image
	void flipX();
	void flipY();
	void crop(int x, int y, int w, int h); // Crops an area of w*h from the (x, y) pixel in the down-right direction

	bool write(const char* filename);
	Image(const char* filename);
	Image(Image& img);
	~Image();
};