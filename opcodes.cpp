#include <iostream>
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
