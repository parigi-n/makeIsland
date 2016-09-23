#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ppm.h"
#include "PerlinNoise.h"

int main() {
	// Define the size of the image
	unsigned int width = 1000, height = 1000;

	// Create an empty PPM image
	ppm image(width, height);
	std::vector<double> r(width * height);
	// Create a PerlinNoise object with a random permutation vector generated with seed
	unsigned int seed = 42;
	PerlinNoise pn(seed);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for(unsigned int i = 0; i < height; ++i)
	{     // y
		for(unsigned int j = 0; j < width; ++j)
		{  // x
			double x = (double)j/(double)width - 0.5;
			double y = (double)i/(double)height - 0.5;

			// Typical Perlin noise
			double n = pn.noise(4 * x, 4 * y, 0);
			double d = 2 * sqrt(x*x + y*y);

			//double e = e + 0.05 - 1.00*pow(d, 2.00);
			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			//if (r_normal > 1)
			  //  r_normal = 1;
			  //else if (r_normal < 0)
			  //  r_normal = r_normal + 0.1;
		       
			r[kk] = n;
			r[kk] = r[kk] + 0.05 - 1.00*pow(d, 0.80);
			kk++;
			//std::cout << n << std::endl;
			//std::cout << " %[" << (d / 2) << "]|[" << n << "]% "; 
		}
		//std::cout << std::endl;
	}
	
	double min = *std::min_element(std::begin(r), std::end(r));
	double max = *std::max_element(std::begin(r), std::end(r));
	kk = 0;
		for(unsigned int i = 0; i < height; ++i)
	{     // y
		for(unsigned int j = 0; j < width; ++j)
		{  // x

			//double e = e + 0.05 - 1.00*pow(d, 2.00);
			// Wood like structure
			//n = 20 * pn.noise(x, y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			//if (255.0 * -(d / 2) > 255.0
		  double r_normal = (r[kk] - min) / (max - min);


		       
			image.r[kk] = 255.0 * r_normal;
			image.g[kk] = 255.0 * r_normal;
			image.b[kk] = 255.0 * r_normal;
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
