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

std::string decode_5(unsigned const char* opcode) {
	if ((opcode[1] & 0xF) != 0) {
		return OPCODE_NOT_VALID;
	}
	char reg1, reg2;
	reg1 = opcode[0] & 0xF;
	reg2 = (opcode[1] & 0xF0) >> 4;

	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_5;
	decoded << std::setw(0) << "V" << std::hex << +reg1 << ", V" << +reg2;
	return decoded.str();
}

std::string decode_6(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF;
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_6;
	decoded << std::setw(0) << "V" << std::hex << +reg << ", 0x" << +opcode[1];
	return decoded.str();
}

std::string decode_7(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF;
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_7;
	decoded << std::setw(0) << "V" << std::hex << +reg << ", 0x" << +opcode[1];
	return decoded.str();
}

std::string decode_8(unsigned const char* opcode) {
	char reg1, reg2;
	reg1 = opcode[0] & 0xF;
	reg2 = (opcode[1] & 0xF0) >> 4;

	std::ostringstream decoded;
	decoded << std::setw(7) << std::left;
	switch(opcode[1] & 0xF) {
	case 0:
		decoded << OPCODE_80;
		break;
	case 1:
		decoded << OPCODE_81;
		break;
	case 2:
		decoded << OPCODE_82;
		break;
	case 3:
		decoded << OPCODE_83;
		break;
	case 4:
		decoded << OPCODE_84;
		break;
	case 5:
		decoded << OPCODE_85;
		break;
	case 7:
		decoded << OPCODE_87;
		break;
	//Casos donde solo se tiene que printear un registro
	case 6:
		decoded << OPCODE_86 << std::setw(0) << "V" << std::hex << +reg1;
		return decoded.str();
	case 0xE:
		decoded << OPCODE_8E << std::setw(0) << "V" << std::hex << +reg1;
		return decoded.str();
	default:
		return OPCODE_NOT_VALID;
	}
	decoded << std::setw(0) << std::hex << "V" << +reg1 << ", V" << +reg2;
	return decoded.str();
}

std::string decode_9(unsigned const char* opcode) {
	if ((opcode[1] & 0xF) != 0) {
		return OPCODE_NOT_VALID;
	}
	char reg1, reg2;
	reg1 = opcode[0] & 0xF;
	reg2 = (opcode[1] & 0xF0) >> 4;

	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_9 << std::setw(0) << "V" << std::hex << +reg1 << ", V" << +reg2;
	return decoded.str();
}

std::string decode_a(unsigned const char* opcode) {
	short addr = ((opcode[0] & 0xF) << 8) + opcode[1];
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_A;
	decoded << std::setw(0) << "I, 0x" << std::hex << addr;
	return decoded.str();
}

std::string decode_b(unsigned const char* opcode) {
	short addr = ((opcode[0] & 0xF) << 8) + opcode[1];
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_B;
	decoded << std::setw(0) << "V0, 0x" << std::hex << addr;
	return decoded.str();
}

std::string decode_c(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF;
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_C;
	decoded << std::setw(0) << "V" << std::hex << +reg << ", 0x" << +opcode[1];
	return decoded.str();
}

std::string decode_d(unsigned const char* opcode) {
	char reg1, reg2, nibble;
	reg1 = opcode[0] & 0xF;
	reg2 = (opcode[1] & 0xF0) >> 4;
	nibble = opcode[1] & 0xF;

	std::ostringstream decoded;
	decoded << std::setw(7) << std::left << OPCODE_D;
	decoded << std::setw(0) << std::hex << "V" << +reg1 << ", V" << +reg2 << ", 0x" << +nibble;
	return decoded.str();
}

std::string decode_e(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF;
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left;
	switch(opcode[1]) {
	case 0x9E:
		decoded << OPCODE_E9E;
		break;
	case 0xA1:
		decoded << OPCODE_EA1;
		break;
	}
	decoded << std::setw(0) << "V" << std::hex << +reg;
	return decoded.str();
}

std::string decode_f(unsigned const char* opcode) {
	char reg = opcode[0] & 0xF;
	std::ostringstream decoded;
	decoded << std::setw(7) << std::left;
	switch(+opcode[1]) {
	case 0x7:
		decoded << OPCODE_F07 << std::setw(0) << std::hex << "V" << +reg << ", DT";
		break;
	case 0xA:
		decoded << OPCODE_F0A << std::setw(0) << std::hex << "V" << +reg << ", K";
		break;
	case 0x15:
		decoded << OPCODE_F15 << std::setw(0) << std::hex << "DT, V" << +reg;
		break;
	case 0x18:
		decoded << OPCODE_F18 << std::setw(0) << std::hex << "ST, V" << +reg;
		break;
	case 0x1E:
		decoded << OPCODE_F1E << std::setw(0) << std::hex << "I, V" << +reg;
		break;
	case 0x29:
		decoded << OPCODE_F29 << std::setw(0) << std::hex << "F, V" << +reg;
		break;
	case 0x33:
		decoded << OPCODE_F33 << std::setw(0) << std::hex << "B, V" << +reg;
		break;
	case 0x55:
		decoded << OPCODE_F55 << std::setw(0) << std::hex << "[I], V" << +reg;
		break;
	case 0x65:
		decoded << OPCODE_F65 << std::setw(0) << std::hex << "V" << +reg << ", [I]";
		break;
	default:
		return OPCODE_NOT_VALID;
	}
	return decoded.str();
}

