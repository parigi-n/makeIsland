#include <cmath>
#include <iostream>
#include "ppm.h"
#include "PerlinNoise.h"

int main() {
	// Define the size of the image
	unsigned int width = 1000, height = 1000;

	// Create an empty PPM image
	ppm image(width, height);

	// Create a PerlinNoise object with a random permutation vector generated with seed
	unsigned int seed = 258;
	PerlinNoise pn(seed);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for(unsigned int i = 0; i < height; ++i) {     // y
		for(unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j/(double)width - 0.5;
			double y = (double)i/(double)height - 0.5;

			// Typical Perlin noise
			double n = pn.noise(6 * x, 6 * y, 0);
			double d = 3.5 * sqrt(x*x + y*y);

			//double e = e + 0.05 - 1.00*pow(d, 2.00);
			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			//if (255.0 * -(d / 2) > 255.0
			/*image.r[kk] = floor(255 * ((d / 2)));
			image.g[kk] = floor(255 * ((d / 2)));
			image.b[kk] = floor(255 * ((d / 2)));*/
			double r = (n - (d / 2.0));
			r = (r - 0) / (1 - 0);
			  if (r > 1)
			    r = 1;
			  else if (r < 0)
			    r = r + 0.1;
		       
			image.r[kk] = 255.0 * r;
			image.g[kk] = 255.0 * r;
			image.b[kk] = 255.0 * r;
			kk++;
			//std::cout << n << std::endl;
			//std::cout << " %[" << (d / 2) << "]|[" << n << "]% "; 
		}
		//std::cout << std::endl;
	}

	// Save the image in a binary PPM file
	image.write("figure_7_P.ppm");

	return 0;
}
