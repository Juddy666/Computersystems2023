#include "CompilerParser.h"
#include <iostream>
using namespace std;

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens){
    this->tokens =  tokens;
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree */
ParseTree* CompilerParser::compileProgram() {
    
    ParseTree* myTree = new ParseTree("class","class");
    myTree->addChild(mustBe("keyword","class"));
    Token* currToken = current();
    
    if(currToken->getType() == "identifier"){
        myTree->addChild(currToken);
        next();
    }
    else{
        throw new ParseException();
    }
    myTree->addChild(mustBe("symbol", "{"));
    myTree->addChild(mustBe("symbol", "}"));
    
    return myTree;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    if(mustBe("keyword", "class")!=NULL){
    ParseTree* myTree = new ParseTree("keyword","class");
    myTree->addChild(mustBe("identifier", "MyClass"));
    myTree->addChild(mustBe("symbol", "{"));
    while(have("keyword", "static") || have("keyword", "field")) {
        ParseTree* varDec = compileClassVarDec();
        myTree->addChild(varDec);
    }

    while(have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
        ParseTree* subDec = compileSubroutine();
        myTree->addChild(subDec);
    }
    
    myTree->addChild(mustBe("symbol", "}"));
    
    
    
    
   return myTree;
   };
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for andvanced to the next token in the list of tokens.
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/*
 Advance to the next token
 */
void CompilerParser::next(){
    if(tokens.empty()!=true){
        tokens.pop_front();
    }   
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if(tokens.empty()!=true){
        return tokens.front();
    }
    
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    
    Token* currentToken = current();
    
    if(currentToken==NULL){
        return false;
    }

    if(currentToken->getType() == expectedType){
        if(currentToken->getValue() == expectedValue){
            return true;
        }
    }    
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if(have(expectedType,expectedValue)){
       Token* currentToken = current();
       next();
       return currentToken;
    } else {
        throw new ParseException();
    }
    
    
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}

