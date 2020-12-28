#include <iostream>
#include <fstream>

#define RED 0
#define GREEN 1
#define BLUE 2

using namespace std;

void write_header(ofstream& ofs, const int, const int);
void write_RGB(ofstream& ofs, const int, const int);

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
		unsigned char value[] = { 255,0,255 };
		float alpha = (float)i / (height_size - 1);
		float real_value[] = { (float)value[RED] * (1.0f - alpha) ,(float)value[GREEN],(float)value[BLUE] * (alpha) };

		for (int j = 0; j < width_size; j++) {
			for (int k = 0; k < sizeof(value) / sizeof(unsigned char); k++)
				value[k] = static_cast<unsigned char>(real_value[k]);

			for (int c = 0; c < sizeof(value) / sizeof(unsigned char); c++) {
				ofs << (int)value[c];
				if (2 > c || width_size - 1 > c)
					ofs << " ";
			}
		}
		ofs << endl;
	}
}
