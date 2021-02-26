#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class RGB
{
public:
	RGB() :r(0), g(0), b(0) {}

	RGB(const uint8_t& r_, const uint8_t& g_, const uint8_t& b_)
		: r(r_), g(g_), b(b_)
	{}

public:
	uint8_t r, g, b;
};

class PixelBuffer
{
public:
	PixelBuffer(const int& width_, const int& height_)
		: width(width_), height(height_), buffer(width* height)
	{}

	void clear(const RGB& rgb)
	{
		fill(buffer.begin(), buffer.end(), rgb);
	}
	// i is x-pos, width * j is y-pos.
	void drawPixel(const int& i, const int& j, const RGB& rgb)
	{
		buffer[i + width * j] = rgb;
	}

	// Easy to understand but unoptimized implementation
	void drawLineTest2(int x0, int y0, int x1, int y1, const RGB& rgb)
	{
		int step = 0;
		int* inc = nullptr;
		// Compare which axis is bigger.
		// If x-axis is bigger than y-axis
		if (abs(x1 - x0) > abs(y1 - y0))
		{
			if (x0 > x1)
			{
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			step = x1 - x0;
		}
		// If y-axis is bigger than x-axis
		else
		{
			if (y0 > y1)
			{
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			step = y1 - y0;
		}
		// For avoid code duplication, make two increasement variable. but I don't know whether it is efficient.
		float x = x0;
		float y = y0;
		const float x_inc = float(x1 - x0) / step;
		const float y_inc = float(y1 - y0) / step;

		for (int i = 0; i <= step; i++)
		{
			drawPixel(round(x), round(y), rgb);
			x += x_inc;
			y += y_inc;
		}
	}

	void writePPM(const string& filename)
	{
		ofstream ofile(filename);

		ofile << "P3\n" << width << ' ' << height << "\n" << "255\n";

		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				const int offset = i + width * j;
				ofile << (int)buffer[offset].r << " " << (int)buffer[offset].g << " " << (int)buffer[offset].b;
				if (i < width - 1)
					ofile << " ";
			}
			ofile << "\n";
		}

		ofile << flush;
	}

public:
	int width, height;
	vector<RGB> buffer;
};

int main()
{
	PixelBuffer pixel_buffer(5, 5);
	pixel_buffer.clear(RGB(255, 255, 255));

	// Case 1: 4 - 0 > 2 - 1
	//pixel_buffer.drawLineTest2(0, 1, 4, 2, RGB(0,0,0)); 

	// Case 2: 9 - 7 < 3 - 0
	// It works!
	pixel_buffer.drawLineTest2(2, 0, 4, 3, RGB(0, 0, 0));

	pixel_buffer.writePPM("/Users/IMYONGSIK/Desktop/ex3_DDA2.ppm");

	return 0;
}
