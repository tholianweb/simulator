//-----------------------------------------------------------------------------
//	File: Program.h
//
//	Class: Program
//
//	Description: Each program has a number and a series of statements contained
//              in a queue. Statements execute one at a time using the
//              execute() method. Designed to be used by the Simulator class.
//
// Programmer: Sarah Kazemian
//
// Date completed:	12/3/14
//
// Environment:   Linux Mint 17 for execution,
//					   Compiles under Code::Blocks 13.12 using gnu GCC compiler
//
//	Properties:
//      queue<Statement> m_statements -- ordered list of all statements
//      bool m_done  -- true if end statement is reached
//      int m_progNum -- program's number, assigned by simulator
//	Methods:
//    public methods:
//      Program(int, queue<Statement>) -- constructor
//      void execute (int[], bool &) -- executes next statement
//      bool isDone(void) -- true if end statement is reached
//-----------------------------------------------------------------------------
#ifndef PROG_H
#define PROG_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <list>
#include <math.h>
#include <queue>

using namespace std;
const char NOCHAR = '0';
const int NOVAL = 0;
const int OFFSET = 97; //convert letter's ascii value to array value

enum StatementType {
   ASSIGN,  //0
   OUTPUT,  //1
   LOCK,    //2
   UNLOCK,  //3
   END,     //4
   INVALID,  //5
};
//-----------------------------------------------------------------------------
// Program class
//-----------------------------------------------------------------------------
class Program {
friend ostream& operator<<(ostream& sout, const Program& progOut);
   public:
      struct Statement; //forward declaration of statement struct
      Program() {};
      Program(int, queue<Statement>); //constructor
      bool execute (int[], bool &, StatementType &); //executes next statment
      bool isDone(void); //returns true if the program is done
      void setProgNum(int); //allows simulator to assign program a number

   private:
      queue<Statement> m_statements; //all statements in the program
      bool m_done; //set to true if end statement is executed
      int m_progNum; //keeps track of which program it is in the simulator

   public:
      struct Statement {
         StatementType m_type;
         char m_var;
         int m_value;
         //Statement constructor:
         Statement(StatementType type = ASSIGN, char var = NOCHAR,
         int newVal = NOVAL): m_type(type), m_var(var), m_value(newVal) {}
      };
};

#endif
