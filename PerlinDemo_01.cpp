#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ppm.h"
#include "PerlinNoise.h"

double distance(double x1, double y1, double x2, double y2)
{
  return (sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}

int main() {
	// Define the size of the image
	unsigned int width = 2000, height = 2000;

	// Create an empty PPM image
	ppm image(width, height);
	std::vector<double> r(width * height);
	// Create a PerlinNoise object with a random permutation vector generated with seed
	unsigned int seed = 42;
	PerlinNoise pn(seed);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for(unsigned int y = 0; y < height; ++y)
	{     // y
		for(unsigned int x = 0; x < width; ++x)
		{  // x
		  double dist = distance(x, y, (double)(width * 0.5), (double)(height * 0.5));
		  double edge = (double)width * 0.6;
		  double scale = 3;
		  double sx = scale * (x) / (double)width; //A REMPLACER PAR LA PLUS GRANDE LARGEUR OU LONGUEUR
		  double sy = scale * y / (double)width;
		  unsigned int octaves = 5;
		  double value = 0;
		  double persistence = 0.65;

		  for (unsigned int n = 0; n < octaves; ++n)
		    {
		      double frequency = pow(2, n);
		      double amplitude = pow(persistence, n);
		      value += pn.noise(sx * frequency, sy * frequency, 4) * amplitude;
		      //std::cout << pn.noise(sx * frequency, sy * frequency, 4) * amplitude << std::endl;
		    }
		  double fall = 2 * pow(dist / edge, 1.5);
		  r[kk] = (value - fall);
		  //r[kk] = (1.500 - value);
		  /*image.r[kk] = 255.0 * r[kk];
		  image.g[kk] = 255.0 * r[kk];
		  image.b[kk] = 255.0 * r[kk];*/
		  //std::cout << r[kk] << "|";
		  kk++;
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
		  //double r_normal = (r[kk] - min) / (max - min);
		  double r_normal = r[kk];
		  /*if (r_normal > 1)
		    r_normal = 1;
		  if (r_normal < 0)
		  r_normal = 0;*/
		  if (r_normal > 1.1000) //Haute montagne
		    {
		      image.r[kk] = 0;
		      image.g[kk] = 0;
		      image.b[kk] = 0;
		    }
		  else if (r_normal > 0.9500) //Montagne
		    {
			image.r[kk] = 74;
			image.g[kk] = 74;
			image.b[kk] = 74;
		    }
		  else if (r_normal > 0.8000) //Hautes coline
		    {
		      image.r[kk] = 36;

		     image.g[kk] = 69;
		      image.b[kk] = 21;
		    }
		  else if (r_normal > 0.7000) //colinnes
		    {
		      image.r[kk] = 65;
		      image.g[kk] = 128;
		      image.b[kk] = 36;
		    }
		  else if (r_normal > 0.500) //Terre
		    {
		      image.r[kk] = 72;
		      image.g[kk] = 196;
		      image.b[kk] = 14;
		    }
		  else if (r_normal > 0.4500) // Sable
		    {
		      image.r[kk] = 216;
		      image.g[kk] = 202;
		      image.b[kk] = 149;
		    }
		  else if (r_normal > 0.0000) //Eau
		    {
		      image.r[kk] = 17;
		      image.g[kk] = 157;
		      image.b[kk] = 250;
		    }
		  else
		    {
		      image.r[kk] = 11;
		      image.g[kk] = 75;
		      image.b[kk] = 143;
		    }
					
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
