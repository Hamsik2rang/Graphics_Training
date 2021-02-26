#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

namespace constant
{
	const int WIDTH = 512;
	const int HEIGHT = 512;
	const int LINE_START = 5;
	const int LINE_END = 200;
	const float PI = 3.141592f;
}

class RGB
{
public:
	uint8_t r, g, b;

public:
	RGB() :r(0), g(0), b(0) {}

	RGB(const uint8_t& r_, const uint8_t& g_, const uint8_t& b_)
		: r(r_), g(g_), b(b_)
	{}
};

class PixelBuffer
{
public:
	int width, height;
	vector<RGB> buffer;

public:
	PixelBuffer(const int& width_, const int& height_)
		: width(width_), height(height_), buffer(width* height)
	{}

	void clear(const RGB& rgb)
	{
		fill(buffer.begin(), buffer.end(), rgb);
	}

	void drawPixel(const int& i, const int& j, const RGB& rgb)
	{
		buffer[i + width * j] = rgb;
	}

	// "Computer Graphics with OpenGL" by Hearn et al.
	void drawLineDDA(const int& x0, const int& y0, const int& x1, const int y1, const RGB& rgb)
	{
		const int dx = x1 - x0;
		const int dy = y1 - y0;
		const int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

		float x = (float)x0;
		float y = (float)y0;
		const float x_inc = (float)dx / steps;
		const float y_inc = (float)dy / steps;

		drawPixel(round(x), round(y), rgb);
		for (int k = 0; k < steps; k++)
		{
			x += x_inc;
			y += y_inc;
			drawPixel(round(x), round(y), rgb);
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
};

int main()
{
	PixelBuffer pixel_buffer(constant::WIDTH, constant::HEIGHT);
	pixel_buffer.clear(RGB(255, 255, 255));

	for (int degree = 0; degree < 360; degree += 30)
	{
		const float theta = degree / 360.0f * constant::PI * 2.0f;// degree to radian
		const float c = cos(theta), s = sin(theta);
		pixel_buffer.drawLineDDA(constant::WIDTH / 2 + c * constant::LINE_START, constant::HEIGHT / 2 + s * constant::LINE_START,
								 constant::WIDTH / 2 + c * constant::LINE_END, constant::HEIGHT / 2 + s * constant::LINE_END, RGB(0, 0, 0));
	}

	pixel_buffer.writePPM("/Users/IMYONGSIK/Desktop/ex4_DDA.ppm");

	return 0;
}