#include <iostream>
#include "image.h"

int main()
{
	//Grayscale feature
	Image photo("Photo.jpg");
	Image copy = photo;
	photo.grayscale_avg(); // Basic grayscale
	copy.grayscale_lum(); // Enhanced grayscale

	photo.write("GrayPhoto.jpg");
	copy.write("EnhancedGrayPhoto.jpg");

	std::cout << std::endl;

	//Color Mask feature
	Image photo2("Photo.jpg");
	Image copy2 = photo2;
	photo2.colorMask(1, 0, 1);
	copy2.colorMask(0, 1, 1);

	photo2.write("PurplePhoto.jpg");
	copy2.write("CyanPhoto.jpg");

	//More features are coming...
	return 0;
}