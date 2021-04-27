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

	std::cout << std::endl;
	
	Image photo3("Photo.jpg");
	Image copy3 = photo3;
	photo3.flipX();
	copy3.flipY();

	photo3.write("flippedX.jpg");
	copy3.write("flippedY.jpg");

	std::cout << std::endl;

	//Crop feature
	Image photo4("Photo.jpg");
	photo4.crop(1500, 700, 1000, 700);
	photo4.write("cropped.jpg");


	return 0;
}