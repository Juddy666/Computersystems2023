#include "SymbolTable.h"

#include <string>

/**
 * Symbol Table constructor
 */
SymbolTable::SymbolTable() {
      // Initialize symbol table with predefined symbols
    addSymbol("SP", 0x0000);
    addSymbol("LCL", 0x0001);
    addSymbol("ARG", 0x0002);
    addSymbol("THIS", 0x0003);
    addSymbol("THAT", 0x0004);
    for (int i = 0; i <= 15; i++) {
        string r = "R" + to_string(i);
        addSymbol(r, i);
    }
    addSymbol("SCREEN", 0x4000);
    addSymbol("KBD", 0x6000);
};
/**
 * Symbol Table destructor
 */
SymbolTable::~SymbolTable() {
    // Your code here
}

/**
 * Adds a symbol to the symbol table
 * @param symbol The name of the symbol
 * @param value The address for the symbol
 */
void SymbolTable::addSymbol(std::string symbol, uint16_t value) {
    table_[symbol] = value;
}

/**
 * Gets a symbol from the symbol table
 * @param symbol The name of the symbol
 * @return The address for the symbol or -1 if the symbol isn't in the table
 */
int SymbolTable::getSymbol(std::string symbol) {
    if (table_.count(symbol) > 0) {
        return table_[symbol];
    }
    return -1;
}

uint16_t SymbolTable::getAddress(string symbol) {
    return table_[symbol];
}

bool SymbolTable::contains(string symbol) {
    return table_.count(symbol) == 1;
}

uint16_t SymbolTable::getNextVariableAddress() {
    // Start at 16 because the first 16 addresses are reserved for special purposes
    uint16_t nextAddress = 16;

    // Find the highest address in the table
    for (auto const& pair : table_) {
        uint16_t address = pair.second;
        if (address >= nextAddress) {
            nextAddress = address + 1;
        }
    }

    return nextAddress;
}