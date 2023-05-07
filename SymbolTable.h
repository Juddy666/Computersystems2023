#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <cstdint>  // this contains uint16_t
#include <map>      // indexable dictionary
#include <string>   // process c++ string

using namespace std;

class SymbolTable {
   public:
    SymbolTable();
    ~SymbolTable();

    void addSymbol(string symbol, uint16_t value);
    int getSymbol(string symbol);
    uint16_t getAddress(string symbol);
    bool contains(string symbol); 
    uint16_t getNextVariableAddress();
    private:
    std::map<std::string, uint16_t> table_;
};

#endif /* SYMBOL_TABLE_H */