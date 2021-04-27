#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"			// These are necessary headers
#include "stb_image_write.h"    // for the image processing functions
#include "Image.h"

bool Image::read(const char* filename)
{
	data = stbi_load(filename, &width, &height, &channels, 0);
	return data;
}
bool Image::write(const char* filename)
{
	int success = 0;
	switch (getFileType(filename))
	{
	case PNG:
		success = stbi_write_png(filename, width, height, channels, data, width*channels);
		break;
	case JPG:
		success = stbi_write_jpg(filename, width, height, channels, data, 100);
		break;
	case BMP:
		success = stbi_write_bmp(filename, width, height, channels, data);
		break;
	case TGA:
		success = stbi_write_tga(filename, width, height, channels, data);
		break;
	}

	if (success)printf("Image %s was saved to file.\n", filename);
	else printf("Image %s could not be saved to file.\n", filename);

	return success;
}
ImageType Image::getFileType(const char* filename)
{
	const char* ext = strrchr(filename, '.');
	if (ext)
	{
		if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0)
			return JPG;
		else if (strcmp(ext, ".png") == 0)
			return PNG;
		else if (strcmp(ext, ".bmp") == 0)
			return BMP;
		else if (strcmp(ext, ".tga") == 0)
			return TGA;
	}
	return JPG;
}
	 
void Image::grayscale_avg()
{
	if (channels < 3)printf("The image has less than 3 channels.\n");
	else
	{
		for (int i = 0; i < size; i += channels)
		{
			int gray = (data[i] + data[i + 1] + data[i + 2]) / 3; // (r+g+b)/3
			memset(data + i, gray, 3);
		}
	}
}
void Image::grayscale_lum()
{
	if (channels < 3)printf("The image has less than 3 channels.\n");
	else
	{
		for (int i = 0; i < size; i += channels)
		{
			int gray = 0.2126 * data[i] + 0.7152 * data[i + 1] + 0.0722 * data[i + 2];
			memset(data + i, gray, 3);
		}
	}
}
void Image::colorMask(double r, double g, double b)
{
	if (channels < 3)printf("The image has less than 3 channels.\n");
	else
	{
		for (int i = 0; i < size; i += channels)
		{
			data[i] *= r;
			data[i+1] *= g;
			data[i+2] *= b;
		}
	}
}

Image::Image(const char* filename)
{
	if (read(filename))
	{
		printf("File %s has been successfully open.\n", filename);
		size = width * height * channels;
	}
	else
	{
		printf("ERROR ! File %s could not be opened.\n", filename);
		exit(1);
	}
}
Image::Image(Image& img) : width(img.width), height(img.height), channels(img.channels)
{
	size = width * height * channels;
	data = new uint8_t[size];
	memcpy(data, img.data, size);
}
Image::~Image()
{
	stbi_image_free(data);
}