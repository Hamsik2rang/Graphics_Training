#include <iostream>
#include <fstream>

#define CORAL 0
#define COST 1

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
	unsigned char value[][3] = { {0xFC,0x76,0x6A},{0x5B,0x74,0xB1} };
	const int cell_side_length = 32;
	
	for (int i = 0; i < height_size; i++) {
		for (int j = 0; j < width_size; j++) {
			int selected;
			if ((i / cell_side_length % 2) ^ (j / cell_side_length % 2))
				selected = COST;
			else
				selected = CORAL;

			for (int k = 0; k < sizeof(value[selected]) / sizeof(unsigned char); k++) {
				ofs << (int)value[selected][k];
				if (2 > k || width_size - 1 > j)
					ofs << " ";
			}
		}
		ofs << endl;
	}
}