#include <iostream>
#include <fstream>

#define RED 0
#define GREEN 1
#define BLUE 2

#define DEBUG

using namespace std;

void write_header(ofstream&, const int, const int);
void write_RGB(ofstream&, const int, const int);

int main() {
	string filename;
	ofstream ofs;

	const int height_size = 128;
	const int width_size = 128;

	cout << "input filename : ";
	cin >> filename;

	try {
		ofs.open(filename);
		if (!ofs.is_open())
			throw new exception();
	}
	catch (exception e) {
		cout << "file oppen error";
		return -1;
	}

	write_header(ofs, height_size, width_size);
	write_RGB(ofs, height_size, width_size);

	ofs.close();

	return 0;
}

void write_header(ofstream& ofs, const int height_size, const int width_size) {
	const char* format = "P3\n";
	int type = 255;
	ofs << format;
	ofs << width_size << " " << height_size << '\n';
	ofs << type << '\n';
	ofs << flush;
}

void write_RGB(ofstream& ofs, const int height_size, const int width_size) {
	for (int i = 0; i < height_size; i++) {
		for (int j = 0; j < width_size; j++) {
			unsigned char value[] = { 255,0,255 };
			float alpha = 0.0f;


			if (i > j) {
				alpha = 0.5f / i * (j + 1);
			}
			else {
				alpha = 0.5f * (1 + 1.0f / (height_size - 1 - i) * (j - i));
			}
			float real_value[] = { (float)value[RED] * (alpha), (float)value[GREEN], (float)value[BLUE] * (1.0f - alpha) };

			for (int k = 0; k < sizeof(value) / sizeof(unsigned char); k++)
				value[k] = (unsigned char)real_value[k];

			for (int c = 0; c < sizeof(value) / sizeof(unsigned char); c++) {
				ofs << (int)value[c];
				if (2 > c || width_size - 1 > c)
					ofs << " ";
			}
		}
		ofs << endl;
	}
}