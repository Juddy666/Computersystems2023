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
        throw ParseException();
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
    ParseTree* myTree = new ParseTree("class","class");
    myTree->addChild(mustBe("keyword","class"));
    Token* currToken = current();
    if(currToken->getType() == "identifier"){
        myTree->addChild(currToken);
        next();
    }
    else{
        throw ParseException();
    }

    myTree->addChild(mustBe("symbol", "{"));
    //staic or feild
    while(have("keyword", "static") || have("keyword", "field")) {
        ParseTree* varDec = compileClassVarDec();
        myTree->addChild(varDec);
    }

    //subroutine
    while(have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
        ParseTree* subDec = compileSubroutine();
        myTree->addChild(subDec);
    }
    
    myTree->addChild(mustBe("symbol", "}"));
   return myTree;

}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* myTree = new ParseTree("classVarDec","classVarDec");
    
    //static or feild
    if(have("keyword", "static")|| have("keyword", "field")){
        myTree->addChild(current());
         next();  
    }
    else{throw ParseException();}
    
    //type
    if(have("keyword","int")||have("keyword","boolean")||have("keyword","char")){
        myTree->addChild(current());
        next();
    }
     else{throw ParseException();}
    

    //matchVarname
    Token* currToken = current();
    if(currToken->getType() == "identifier"){
        myTree->addChild(currToken);
        next();
    }
    else{throw ParseException();}

    while(have("symbol", ",")) {
        Token* comma = current();
        next();
        Token* currToken = current();
    if(currToken->getType() == "identifier") {
        myTree->addChild(comma);
        myTree->addChild(currToken);
        next();
    } else {
        throw ParseException();
        }
    }
    myTree->addChild(mustBe("symbol",";"));

    return myTree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* myTree = new ParseTree("subroutine","subroutine");
    //constructor function metthod
    if(have("keyword", "constructor")|| have("keyword", "function")|| have("keyword","method")){
        myTree->addChild(current());
        next();  
    }
    else{throw ParseException();}
    
    
    //void type
    Token* currToken = current();
     if(have("keyword", "void")|| have("keyword", "int")|| have("keyword","boolean")||have("keyword","char")||currToken->getType() == "identifier"){
        myTree->addChild(current());
        next();  
    }
    
    else{throw ParseException();}
   
    //subroute name
    currToken = current();
    if(currToken->getType() == "identifier"){
        myTree->addChild(currToken);
        next();
    }
    else{
        throw ParseException();
        }


      
    //Parameter List
    myTree->addChild(mustBe("symbol","("));
    if(have("keyword","int")||have("keyword","boolean")||have("keyword","char")){
    ParseTree* ParameterList = compileParameterList();
        myTree->addChild(ParameterList);
    }
    myTree->addChild(mustBe("symbol",")"));
    
    //subroutinebody
    if(have("symbol","{")){
    ParseTree* subroutineBody= compileSubroutineBody();
        myTree->addChild(subroutineBody);
        }
    else{
        throw ParseException();
    }
    return myTree;
    
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* myTree = new ParseTree("parameterList","parameterList");

    //type Varname
    if(have("keyword","int")||have("keyword","boolean")||have("keyword","char")){
        myTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }   

    Token* currToken = current();
    if(currToken->getType() == "identifier"){
        myTree->addChild(currToken);
        next();
    }
    else{
        throw ParseException();
        }

    //, type Varname
    while(have("symbol", ",")) {
        Token* comma = current();
        next();
        Token* type = current();
        bool istype = have("keyword", "void")|| have("keyword", "int")|| have("keyword","boolean")||have("keyword","char")||type->getType() == "identifier";
        next();
        Token* name = current();
    if(name->getType() == "identifier"&&istype==true) {
        myTree->addChild(comma);
        myTree->addChild(type);
        myTree->addChild(name);
        next();
    }
    else {
        throw ParseException();
    }
    }

    return myTree;
}
/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* myTree = new ParseTree("subroutineBody","subroutineBody");
    myTree->addChild(mustBe("symbol","{"));
    
    //Var
    while(have("keyword","var")){
        ParseTree* VarDec = compileVarDec();
        myTree->addChild(VarDec);
    }

    //statements
    if(have("keyword","let")||have("keyword","if")||have("keyword","while")||have("keyword","do")||have("keyword","return")){
         ParseTree* statements = compileStatements();
        myTree->addChild(statements);
    }
   
    myTree->addChild(mustBe("symbol","}"));
    
    return myTree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* myTree = new ParseTree("varDec","varDec");
    myTree->addChild(mustBe("keyword","var"));
    
    //type Var
    Token* currentToken = current();
    if(have("keyword","int")||have("keyword","boolean")||have("keyword","char")||currentToken->getType() == "identifier"){
        myTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    Token* currToken = current();
    if(currToken->getType() == "identifier"){
        myTree->addChild(currToken);
        next();
    }
    else{
        throw ParseException();
        }

    //, Varname
    while(have("symbol", ",")) {
        Token* comma = current();
        next();
        Token* currToken = current();
        if(currToken->getType() == "identifier") {
            myTree->addChild(comma);
            myTree->addChild(currToken);
            next();
        } else {
            throw ParseException();
        }
    }
  
    myTree->addChild(mustBe("symbol",";"));
    
    return myTree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* myTree = new ParseTree("statements","statments");
    
    return myTree;
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
        throw ParseException();
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

