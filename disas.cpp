#include <iostream>
#include <fstream>
#include <iomanip>
#include "opcodes.h"

std::string decode(unsigned char *opcode) {
	char index = (opcode[0] & 0xF0) >> 4; // Primeros 4 bits del primer byte
	if (index < 0 || index > 0xF) {
		return OPCODE_NOT_VALID;
	}
	return decode_functions[index](opcode); // Array de funciones dependiendo de los primeros 4 bits de la instruccion
}
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
		cout << "Usage:\n\t" << argv[0] << " <file> [<offset>]" << endl;
		return 1;
	}
	int initial_offset = 0;
	if (argc > 2) {
		initial_offset = std::atoi(argv[2]);
		if (initial_offset < 0 || (initial_offset % 2) != 0) {
			cout << "El offset inicial tiene que ser mayor que 0 y multiplo de 2" << endl;
			return 1;
		}
	}

	ifstream file;
	file.open(argv[1], ios::binary | ios::in);

	if (!file.is_open()) {
		cout << "Error opening the file" << endl;
		return 1;
	}

	int fsize = fileSize(file);
	cout << "File: " << argv[1] << " (" << fsize << " bytes)" << endl;

	unsigned char* opcode = new unsigned char[2];
	for (int offset = initial_offset; offset < (fsize); offset += 2) {
		file.seekg(offset, ios::beg);
		file.read(reinterpret_cast<char*>(opcode), 2);
		cout << hex << setfill('0') << setw(3) << offset << "\t";
		cout << hex << setfill('0') << setw(2) << +opcode[0] << setw(2)  << +opcode[1] << "\t";
		cout << decode(opcode) << endl;
	}

	delete[] opcode;
	file.close();

	return 0;
}
