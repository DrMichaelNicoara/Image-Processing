# Image Processing
This program takes an image from a file and it manipulates its data in different ways, then it saves a new image in the same folder.


# Features

## Grayscale
There are 2 styles of grayscale : Basic and Luma.
Basic Grayscale just takes the average of the RGB pixels.
Luma Grayscale has a specific formula for a more enhanced gray.

## Color Mask
This feature just multiplies all RGB pixels with a specific (R, G, B) value from the user. This looks like a filter of some color the user gave over the image.
This feature will not work as expected if any of the values from (R, G, B) is not in the (0, 1) range.
