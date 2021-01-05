#include <iostream>
#include <fstream>

using namespace std;

void WriteHeader(ofstream&, const int, const int);
void WriteRGB(ofstream&, const int, const int);

int main() {
	string filename;
	ofstream ofs;

	const int heightSize = 64;
	const int widthSize = 64;

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

	WriteHeader(ofs, heightSize, widthSize);
	WriteRGB(ofs, heightSize, widthSize);

	ofs.close();

	return 0;
}

void WriteHeader(ofstream& ofs, const int height_size, const int width_size) {
	const char* format = "P3\n";
	int type = 255;
	ofs << format;
	ofs << width_size << " " << height_size << '\n';
	ofs << type << '\n';
	ofs << flush;
}

void WriteRGB(ofstream& ofs, const int heightSize, const int widthSize) {
	for (int i = 0; i < heightSize; i++) {
		for (int j = 0; j < widthSize; j++) {
			if (i == 0 || j == 0 || j == widthSize - 1 || i == heightSize - 1 || i == j || widthSize - i == j) {
				ofs << 0 << ' ' << 0 << ' ' << 0;
			}
			else {
				ofs << 255 << ' ' << 255 << ' ' << 255;
			}
			if (j == widthSize - 1) {
				ofs << '\n';
			}
			else {
				ofs << ' ';
			}
		}
	}
}