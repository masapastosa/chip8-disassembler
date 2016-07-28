#ifndef OPCODES_H
#define OPCODES_H

//http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
//Opcode SYS no implementado ya que no es usado actualmente
#define   OPCODE_NOT_VALID   "Not an opcode"
#define   OPCODE_0E0         "cls"
#define   OPCODE_0EE         "ret"
#define   OPCODE_1           "jp"
#define   OPCODE_2           "call"
#define   OPCODE_3           "se"
#define   OPCODE_4           "sne"
#define   OPCODE_5           "se"
#define   OPCODE_6           "ld"
#define   OPCODE_7           "add"
#define   OPCODE_80          "ld"
#define   OPCODE_81          "or"
#define   OPCODE_82          "and"
#define   OPCODE_83          "xor"
#define   OPCODE_84          "add"
#define   OPCODE_85          "sub"
#define   OPCODE_86          "shr"
#define   OPCODE_87          "subn"
#define   OPCODE_8E          "shl"
#define   OPCODE_9           "sne"
#define   OPCODE_A           "ld"
#define   OPCODE_B           "jp"
#define   OPCODE_C           "rnd"
#define   OPCODE_D           "drw"
#define   OPCODE_E9E         "skp"
#define   OPCODE_EA1         "sknp"
#define   OPCODE_F07         "ld"
#define   OPCODE_F0A         "ld"
#define   OPCODE_F15         "ld"
#define   OPCODE_F18         "ld"
#define   OPCODE_F1E         "add"
#define   OPCODE_F29         "ld"
#define   OPCODE_F33         "ld"
#define   OPCODE_F55         "ld"
#define   OPCODE_F65         "ld"

std::string decode_0(unsigned const char*);
std::string decode_1(unsigned const char*);
std::string decode_2(unsigned const char*);
std::string decode_3(unsigned const char*);
std::string decode_4(unsigned const char*);
std::string decode_5(unsigned const char*);
std::string decode_6(unsigned const char*);
std::string decode_7(unsigned const char*);
std::string decode_8(unsigned const char*);
std::string decode_9(unsigned const char*);
std::string decode_a(unsigned const char*);/*
std::string decode_b(char*);
std::string decode_c(char*);
std::string decode_d(char*);
std::string decode_e(char*);
std::string decode_f(char*);
*/
static std::string (*decode_functions[0xF])(unsigned const char*) {
	decode_0,
	decode_1,
	decode_2,
	decode_3,
	decode_4,
	decode_5,
	decode_6,
	decode_7,
	decode_8,
	decode_9,
	decode_a/*,
	decode_b,
	decode_c,
	decode_d,
	decode_e,
	decode_f*/
};
#endif
