# Image Processing
This program takes an image from a file and it manipulates its data in different ways, then it saves a new image in the same folder.


# Features

## Grayscale
There are 2 styles of grayscale : Basic and Luma.
Basic Grayscale just takes the average of the RGB pixels.
Luma Grayscale has a specific formula for a more enhanced gray.

## Color Mask
This feature just multiplies all RGB pixels with a specific (R, G, B) value from the user. This looks like a filter of some color the user gave over the image.

## Flip Image
This feature flips the image on the X or Y axis.

## Crop Image
This feature crops an area of (width, height) from the image from a certain point (x, y). Both (x, y) and (width, height) are given by the user.
If the cropped image is going over the image of the original image, the rest will just be black.
