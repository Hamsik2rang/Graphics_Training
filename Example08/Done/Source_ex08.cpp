#include <iostream>
#include <fstream>

#define OUTER 0
#define INNER 1

using namespace std;

void write_header(ofstream&, const int, const int);
void write_RGB(ofstream&, const int, const int);
bool is_inner(const int, const int);

struct point {
	int xpos;
	int ypos;
};

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
	unsigned char value[][3] = { {0x2B,0xAE,0x66}, {0xFC,0xF6,0xF5} };

	for (int i = 0; i < height_size; i++) {
		for (int j = 0; j < width_size; j++) {
			int selected = OUTER;
			if (is_inner(j, i))
				selected = INNER;

			for (int k = 0; k < sizeof(value[selected]) / sizeof(unsigned char); k++) {
				ofs << (int)value[selected][k];
				if (2 > k || width_size - 1 > j)
					ofs << " ";
			}
		}
		ofs << '\n';
	}
}

bool is_inner(const int xpos, const int ypos) {
	point up_left = { 20,30 };
	point down_right = { 70,80 };

	return ((xpos > up_left.xpos && xpos < down_right.xpos) && (ypos > up_left.ypos) && ypos < down_right.ypos);
}