#include <iostream>
#include <fstream>

#define RED 0
#define BLUE 1

using namespace std;

int main() {
	ofstream ofs("fifth.ppm");

	const int width_size = 128;
	const int height_size = 128;
	const int type = 255;

	int value[][3] = { {255,0,0} ,{0,0,255} };

	ofs << "P3\n" << width_size << " " << height_size << '\n' << type << '\n';

	for (int i = 0; i < height_size; i++) {
		for (int j = 0; j < width_size; j++) {
			int selected;
			if (i > j * 2)
				selected = RED;
			else
				selected = BLUE;
			for (int k = 0; k < sizeof(value[selected]) / sizeof(int); k++) {
				ofs << value[selected][k];
				if (2 > k || width_size - 1 > j)
					ofs << " ";
			}
		}
		ofs << '\n';
	}

	ofs.close();
}