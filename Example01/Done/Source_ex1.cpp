#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream ofs("first.ppm");

	const int width_size = 2;
	const int height_size = 2;
	const int type = 255;

	int value[][2][3] = { {{255,0,0} ,{0,255,0}},{{0,0,255},{0,0,0}} };

	ofs << "P3\n" << width_size << " " << height_size << '\n' << type << '\n';

	for (int i = 0; i < height_size; i++) {
		for (int j = 0; j < width_size; j++) {
			for (int k = 0; k < sizeof(value[i][k])/sizeof(int); k++) {
				ofs << value[i][j][k];
				if (k < 2 || j < width_size - 1)
					ofs << " ";
			}
		}
		ofs << '\n';
	}

	ofs.close();
}