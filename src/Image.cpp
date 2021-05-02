#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"			// These are necessary headers
#include "stb_image_write.h"    // for the image processing functions
#include "Image.h"

bool Image::read(const char* filename)
{
	// stbi_load() reads the header data of an image
	// returns an unsigned char* at the beggining of the image data
	data = stbi_load(filename, &width, &height, &channels, 0);
	return data; // data = NULL if reading fails
}
bool Image::write(const char* filename)
{
	bool success; // success of writing image to file
	switch (getFileType(filename))
	{
	case PNG:
		success = stbi_write_png(filename, width, height, channels, data, width * channels);
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
	default :
		success = false;
	}

	if (success) printf("Image %s was saved to file.\n", filename);
	else printf("Image %s could not be saved to file.\n", filename);

	return success;
}
ImageType Image::getFileType(const char* filename)
{
	const char* ext = strrchr(filename, '.'); // returns extension of filename
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
	if (channels < 3) printf("The image has less than 3 channels.\n");
	else
	{
		// Computes the average of (R, G, B) for each pixel and makes all 3 values equal to the average
		// => grayscale effect
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
		// Each pixel = 0.2126 * R + 0.7152 * G + 0.0722 * B of that pixel
		for (int i = 0; i < size; i += channels)
		{
			int gray = 0.2126 * data[i] + 0.7152 * data[i + 1] + 0.0722 * data[i + 2];
			memset(data + i, gray, 3);
		}
	}
}

double to_subunit(double x)
{
	// Makes sure the number is between 0 and 1
	if (x > 0.99) x = 1.0;
	else if (x < 0.0) x = 0.0;
	return x;
}
void Image::colorMask(double r, double g, double b)
{
	// (R, G, B) values must be between 0 and 1
	to_subunit(r);
	to_subunit(g);
	to_subunit(b);

	if (channels < 3) printf("The image has less than 3 channels.\n");
	else
	{
		// Multiplies all pixels by the given multiplier (r, g, b)
		for (int i = 0; i < size; i += channels)
		{
			data[i] *= r;
			data[i + 1] *= g;
			data[i + 2] *= b;
		}
	}
}
void Image::flipX()
{
	uint8_t tmp[4]; // There may be 4 channels (R, G, B, A)
	uint8_t* px1;
	uint8_t* px2;

	for (int y = 0; y < height; y++)
		for (int x = 0; x <= width / 2; x++)
		{
			px1 = &data[(x + y * width) * channels];
			px2 = &data[((width - 1 - x) + y * width) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
}
void Image::flipY()
{
	uint8_t tmp[4]; // There may be 4 channels (R, G, B, A)
	uint8_t* px1;
	uint8_t* px2;

	for (int x = 0; x < width; x++)
		for (int y = 0; y <= height / 2; y++)
		{
			px1 = &data[(x + y * width) * channels];
			px2 = &data[(x + (height - 1 - y) * width) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
}
void Image::crop(int cx, int cy, int cropped_width, int cropped_height)
{
	size = cropped_width * cropped_height * channels;
	uint8_t* new_data = new uint8_t[size];

	// Limits the crop area to the image
	if (cx + cropped_width > width) cropped_width = width - cx;
	if (cy + cropped_height > height) cropped_height = height - cy;

	//copy cropped data to new_data
	for (int y = 0; y < cropped_height; y++)
		for (int x = 0; x < cropped_width; x++)
			memcpy(&new_data[(x + y * cropped_width) * channels],
				   &data[((x + cx) + (y + cy) * width) * channels],
				   channels);

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
