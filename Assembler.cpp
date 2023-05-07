#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include "Assembler.h"
#include "SymbolTable.h"

#include <string>

using namespace std;

/**
 * Assembler constructor
 */
Assembler::Assembler() {
    //
    SymbolTable* symbolTable = new SymbolTable();
}

/**
 * Assembler destructor
 */
Assembler::~Assembler() {
    // Your code here

}

/**
 * Assembler first pass; populates symbol table with label locations.
 * @param instructions An array of the assembly language instructions.
 * @param symbolTable The symbol table to populate.
 */
void Assembler::buildSymbolTable(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    // Your code here
   int currAddr = 0;

    for (int i = 0; i < numOfInst; i++) {
        string currInst = instructions[i];
    
    if(currInst[0] == '(') {
            string symbol = currInst.substr(1, currInst.length() - 2);
            symbolTable->addSymbol(symbol, currAddr);
        } else {
            currAddr++;
        }
    }
}
/**
 * Assembler second pass; Translates a set of instructions to machine code.
 * @param instructions An array of the assembly language instructions to be converted to machine code.
 * @param symbolTable The symbol table to reference/update.
 * @return A string containing the generated machine code as lines of 16-bit binary instructions.
 */
string Assembler::generateMachineCode(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    // Your code here
        int ramAddr = 16;
    stringstream machineCode;
    // Second pass: translate instructions to machine code
    for (int i = 0; i < numOfInst; i++) {
        string instruction = instructions[i];
        if (instruction[0] == '@') {
            // A-instruction
            string symbol = instruction.substr(1);
            int address;
            if (isdigit(symbol[0])) {
                address = stoi(symbol);
            } else {
                if (!symbolTable->contains(symbol)) {
                    symbolTable->addSymbol(symbol, ramAddr);
                    ramAddr++;
                }
                address = symbolTable->getAddress(symbol);
            }
            machineCode << bitset<16>(address) << endl;
        } else if (instruction[0] == '(') {
            // Label instruction, do nothing
        } else {
            // C-instruction
            InstructionType type = parseInstructionType(instruction);
            if (type == C_INSTRUCTION) {
                InstructionComp comp = parseInstructionComp(instruction);
                InstructionDest dest = parseInstructionDest(instruction);
                InstructionJump jump = parseInstructionJump(instruction);
                machineCode << "111" << translateComp(comp) << translateDest(dest) << translateJump(jump) << endl;
            }
        }
    }
    return machineCode.str();
  };

/**
 * Parses the type of the provided instruction
 * @param instruction The assembly language representation of an instruction.
 * @return The type of the instruction (A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NULL)
 */
Assembler::InstructionType Assembler::parseInstructionType(string instruction) {
    // Your code here:
       if (instruction[0] == '@') {
        return A_INSTRUCTION;
    } else if (instruction[0] == '(') {
        return L_INSTRUCTION;
    } else if (instruction[0] == '/' && instruction[1] == '/') {
        return NULL_INSTRUCTION;
    } else {
        return C_INSTRUCTION;
    }
}



/**
 * Parses the jump condition of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The jump condition for the instruction (JLT, JGT, JEQ, JLE, JGE, JNE, JMP, NULL)
 */
Assembler::InstructionJump Assembler::parseInstructionJump(string instruction) {
    if (instruction.find("JLT") != string::npos) {
        return JLT;
    } else if (instruction.find("JGT") != string::npos) {
        return JGT;
    } else if (instruction.find("JEQ") != string::npos) {
        return JEQ;
    } else if (instruction.find("JLE") != string::npos) {
        return JLE;
    } else if (instruction.find("JGE") != string::npos) {
        return JGE;
    } else if (instruction.find("JNE") != string::npos) {
        return JNE;
    } else if (instruction.find("JMP") != string::npos) {
        return JMP;
    } else {
        return NULL_JUMP;
    }
}

Assembler::InstructionDest Assembler::parseInstructionDest(string instruction) {
    // Your code here:
    size_t equalsPos = instruction.find('=');
    if (equalsPos == string::npos) {
        return NULL_DEST;
    }
    string destString = instruction.substr(0, equalsPos);
    if (destString == "M") {
        return M;
    } else if (destString == "D") {
        return D;
    } else if (destString == "MD") {
        return MD;
    } else if (destString == "A") {
        return A;
    } else if (destString == "AM") {
        return AM;
    } else if (destString == "AD") {
        return AD;
    } else if (destString == "AMD") {
        return AMD;
    } else {
        return NULL_DEST;
    }
}



Assembler::InstructionComp Assembler::parseInstructionComp(string instruction) {
    // Your code here:
    // for example if "0" appear at the comp field return CONST_0
    if (instruction.find("0") != string::npos) {
        return CONST_0;
    } else if (instruction.find("1") != string::npos) {
        return CONST_1;
    } else if (instruction.find("-1") != string::npos) {
        return CONST_NEG_1;
    } else if (instruction.find("A") != string::npos) {
        return VAL_A;
    } else if (instruction.find("M") != string::npos) {
        return VAL_M;
    } else if (instruction.find("D") != string::npos) {
        return VAL_D;
    } else if (instruction.find("!A") != string::npos) {
        return NOT_A;
    } else if (instruction.find("!M") != string::npos) {
        return NOT_M;
    } else if (instruction.find("!D") != string::npos) {
        return NOT_D;
    } else if (instruction.find("-A") != string::npos) {
        return NEG_A;
    } else if (instruction.find("-M") != string::npos) {
        return NEG_M;
    } else if (instruction.find("-D") != string::npos) {
        return NEG_D;
    } else if (instruction.find("A+1") != string::npos) {
        return A_ADD_1;
    } else if (instruction.find("M+1") != string::npos) {
        return M_ADD_1;
    } else if (instruction.find("D+1") != string::npos) {
        return D_ADD_1;
    } else if (instruction.find("A-1") != string::npos) {
        return A_SUB_1;
    } else if (instruction.find("M-1") != string::npos) {
        return M_SUB_1;
    } else if (instruction.find("D+A") != string::npos || instruction.find("A+D") != string::npos) {
        return D_ADD_A;
    } else if (instruction.find("D+M") != string::npos || instruction.find("M+D") != string::npos) {
        return D_ADD_M;
    } else if (instruction.find("D-A") != string::npos) {
        return D_SUB_A;
    } else if (instruction.find("D-M") != string::npos) {
        return D_SUB_M;
    } else if (instruction.find("A-D") != string::npos) {
        return A_SUB_D;
    } else if (instruction.find("M-D") != string::npos) {
        return M_SUB_D;
    } else if (instruction.find("D&A") != string::npos || instruction.find("A&D") != string::npos) {
        return D_AND_A;
    } else if (instruction.find("D&M") != string::npos || instruction.find("M&D") != string::npos) {
        return D_AND_M;
    } else if (instruction.find("D|A") != string::npos || instruction.find("A|D") != string::npos) {
        return D_OR_A;
    } else if (instruction.find("D|M") != string::npos || instruction.find("M|D") != string::npos) {
        return D_OR_M;
    }
    return NULL_COMP;
}





/**
 * Parses the symbol of the provided A/L-instruction
 * @param instruction The assembly language representation of a A/L-instruction.
 * @return A string containing either a label name (L-instruction),
 *         a variable name (A-instruction), or a constant integer value (A-instruction)
 */


string Assembler::parseSymbol(string instruction) {
        // check if the instruction is an A or L instruction (starts with '@' or '(' respectively)
    if (instruction[0] == '@') {
        // for A instructions, symbol is everything after the '@'
        return instruction.substr(1);
    } else if (instruction[0] == '(') {
        // for L instructions, symbol is everything inside the parentheses
        return instruction.substr(1, instruction.length() - 2);
    } else {
        // not an A or L instruction, so no symbol to return
        return "";
    }
}



/**
 * Generates the binary bits of the dest part of a C-instruction
 * @param dest The destination of the instruction
 * @return A string containing the 3 binary dest bits that correspond to the given dest value.
 */
string Assembler::translateDest(InstructionDest dest) {
    switch (dest) {
        case NULL_DEST:
            return "000";
        case M:
            return "001";
        case D:
            return "010";
        case MD:
            return "011";
        case A:
            return "100";
        case AM:
            return "101";
        case AD:
            return "110";
        case AMD:
            return "111";
    }
    return "";
}

/**
 * Generates the binary bits of the jump part of a C-instruction
 * @param jump The jump condition for the instruction
 * @return A string containing the 3 binary jump bits that correspond to the given jump value.
 */
string Assembler::translateJump(InstructionJump jump) {
        switch (jump) {
        case JLT:
            return "001";
        case JGT:
            return "010";
        case JEQ:
            return "011";
        case JLE:
            return "100";
        case JGE:
            return "101";
        case JNE:
            return "110";
        case JMP:
            return "111";
        case NULL_JUMP:
        default:
            return "000";
    }
}
/**
 * Generates the binary bits of the computation/op-code part of a C-instruction
 * @param comp The computation/op-code for the instruction
 * @return A string containing the 7 binary computation/op-code bits that correspond to the given comp value.
 */
string Assembler::translateComp(InstructionComp comp) {
    // Your code here:
     switch (comp) {
        case CONST_0:
            return "0101010";
        case CONST_1:
            return "0111111";
        case CONST_NEG_1:
            return "0111010";
        case VAL_D:
            return "0001100";
        case VAL_A:
            return "0110000";
        case NOT_D:
            return "0001101";
        case NOT_A:
            return "0110001";
        case NEG_D:
            return "0001111";
        case NEG_A:
            return "0110011";
        case A_ADD_1:
            return "0110111";
        case D_ADD_1:
            return "0011111";
        case M_ADD_1:
            return "1110111";
        case A_SUB_1:
            return "0110010";
        case D_SUB_1:
            return "0001110";
        case M_SUB_1:
            return "1110010";
        case D_ADD_A:
            return "0000010";
        case D_ADD_M:
            return "1000010";
        case D_SUB_A:
            return "0010011";
        case D_SUB_M:
            return "1010011";
        case A_SUB_D:
            return "0000111";
        case M_SUB_D:
            return "1000111";
        case D_AND_A:
            return "0000000";
        case D_AND_M:
            return "1000000";
        case D_OR_A:
            return "0010101";
        case D_OR_M:
            return "1010101";
        default:
            return "0000000";
    }
}

/**
 * Generates the binary bits for an A-instruction, parsing the value, or looking up the symbol name.
 * @param symbol A string containing either a label name, a variable name, or a constant integer value
 * @param symbolTable The symbol table for looking up label/variable names
 * @return A string containing the 15 binary bits that correspond to the given sybmol.
 */
string Assembler::translateSymbol(string symbol, SymbolTable* symbolTable) {
    // Your code here:
      // Look up the symbol in the symbol table
    int address = symbolTable->getAddress(symbol);

    // If the symbol is not found in the table, it might be a variable
    if (address == -1) {
        // Assign a new address to the variable
        address = symbolTable->getNextVariableAddress();
        symbolTable->addSymbol(symbol, address);
    }

    // Convert the address to binary and return it
    string binary = bitset<16>(address).to_string();
    return binary;
}
