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
	uint8_t* data = NULL;
	size_t size = 0;
	int width, height;
	int channels;

private:
	bool read(const char* filename);
	ImageType getFileType(const char* filename);

public:
	void grayscale_avg();
	void grayscale_lum();
	void colorMask(double r, double g, double b);

	bool write(const char* filename);
	Image(const char* filename);
	Image(Image& img);
	~Image();
};