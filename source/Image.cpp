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

double to_subunit(double x)
{
	if (x > 1) x = 1;
	else if (x < 0) x = 0;
	return x;
}
void Image::colorMask(double r, double g, double b)
{
	// (R, G, B) values must be between 0 and 1
	to_subunit(r);
	to_subunit(g);
	to_subunit(b);

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
void Image::flipX()
{
	uint8_t tmp[4];
	uint8_t* px1;
	uint8_t* px2;

	for(int y=0; y < height; y++)
		for (int x = 0; x <= width / 2; x++)
		{
			px1 = &data[(x + y * width) * channels];
			px2 = &data[((width - 1 - x) + y*width) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
}
void Image::flipY()
{
	uint8_t tmp[4];
	uint8_t* px1;
	uint8_t* px2;

	for (int x = 0; x < width; x++)
		for (int y = 0; y <= height/ 2; y++)
		{
			px1 = &data[(x + y * width) * channels];
			px2 = &data[(x +(height - 1 - y) * width) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
}
void Image::crop(int cx, int cy, int cropped_width, int cropped_height)
{
	size = cropped_width * cropped_height * channels;
	uint8_t* new_data = new uint8_t[size];
	memset(new_data, 0, size);

	//copy cropped data to new_data
	for (int y = 0; y < cropped_height; y++)
	{
		if (y + cropped_height > height) break;
		for (int x = 0; x < cropped_width; x++)
		{
			if (x + cropped_width > width) break;
			memcpy(&new_data[(x + y * cropped_width) * channels], &data[((x + cx) + (y + cy) * width) * channels], channels);
		}
	}

	width = cropped_width;
	height = cropped_height;

	delete[] data;
	data = new_data;
	new_data = nullptr;
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