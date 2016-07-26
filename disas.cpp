#include <iostream>
#include <fstream>
#include <iomanip>

std::streampos fileSize(std::ifstream& file) {
	std::streampos fsize;
	
	fsize = file.tellg();
	file.seekg(0, std::ios::end);
	
	fsize = file.tellg() - fsize;
	
	file.seekg(0, std::ios::beg);
	return fsize;
}

int main(int argc, char *argv[]) {
	using namespace std;

	if (argc < 2) {
		cout << "Usage:\n\t" << argv[0] << " <file>" << endl;
		return 1;
	}

	ifstream file;
	file.open(argv[1], ios::binary | ios::in);

	if (!file.is_open()) {
		cout << "Error opening the file" << endl;
		return 1;
	}

	int fsize = fileSize(file);
	cout << "Reading " << argv[1] << " (" << fsize << " bytes)" << endl;

	int offset;
	char* opcode = new char[2];
	for (offset = 0; offset < (fsize); offset += 2) {
		file.seekg(offset, ios::beg);
		file.read(opcode, 2);
		cout << hex << setfill('0') << setw(3) << offset << "\t";
		cout << setw(6) << hex << setfill('0') << setw(2) << +static_cast<unsigned char>(opcode[0]) << setw(2)  << +static_cast<unsigned char>(opcode[1]) << "\t" << endl;
	}

	delete[] opcode;
	file.close();
}
