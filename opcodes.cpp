#include <iostream>
#include <sstream>
#include <iomanip>
#include "opcodes.h"

std::string decode_0(unsigned const char* opcode) {
	if (opcode[0] != 0x00) {
		return OPCODE_NOT_VALID;
	}
	switch (opcode[1]) {
	case 0xE0:
		return OPCODE_0E0;
	case 0xEE:
		return OPCODE_0EE;	
	default:
		return OPCODE_NOT_VALID;
	}
}

std::string decode_1(unsigned const char* opcode) {
	short addr = ((opcode[0] & 0xF) << 8) + opcode[1]; //Se cojen las ultimas 3 cifras del opcode, p. ej 0x1234 -> 0x234
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_1;
	decoded << std::setw(0) << "0x" << std::hex << std::setfill('0') << std::setw(3) << (addr & 0xFFF);
	return decoded.str();
}

std::string decode_2(unsigned const char* opcode) {
	short addr = ((opcode[0] & 0xF) << 8) + opcode[1];
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_2;
	decoded << std::setw(0) << std::left << "0x" << std::hex << std::setfill('0') << std::setw(3) << (addr & 0xFFF);
	return decoded.str();
}

std::string decode_3(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF; //Ultimos 4 bits del primer byte
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_3;
	decoded << std::setw(0) << "V" << std::hex << +reg << ", 0x" << +opcode[1];
	return decoded.str();
}

std::string decode_4(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF;
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_4;
	decoded << std::setw(0) << "V" << std::hex << +reg << ", 0x" << +opcode[1];
	return decoded.str();
}
