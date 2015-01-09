//-----------------------------------------------------------------------------
//	File: Simulator.h
//
//	Class: Simulator
//
//	Description:  Simulates the concurrent execution of multiple, simple
//               programs on a uniprocessor system and prints their outputs.
//
// Programmer: Sarah Kazemian
//
// Date completed:	12/3/14
//
// Environment:   Linux Mint 17 for execution,
//					   Compiles under Code::Blocks 13.12 using gnu GCC compiler
//
//	Properties:
//      bool locked; -- keeps track of whether variables are locked
//      int varArray[ALPHABET]; -- holds all variables
//      queue<Program> readyQueue -- holds programs being run
//      queue<Program> blockedQueue -- holds programs that have been blocked
//      int numPrograms -- number of programs in the file/input
//      int statementTimes[5] -- times needed to execute statements
//      int timeQuantum -- time alloted to each program each cycle
//	Methods:
//    public methods:
//      Simulator(istream &readFrom) -- constructor
//      void run(void) -- main method, runs the simulator
//    private methods:
//      Program::Statement parse(char[]) -- parses a line of input
//      void setValues(char[]) -- sets simulator member values
//-----------------------------------------------------------------------------
#ifndef SIM_H
#define SIM_H

#include "Program.h"
using namespace std;

const int MAXLINE = 10; //no statement should be more than 7 characters
const int FIRSTLINE = 20; //maximum characters in the first line
const int ALPHABET = 26; //letters in the alphabet
const int UPPERLIM = 100; //upper limit of values assigned
//-----------------------------------------------------------------------------
// Simulator class
//-----------------------------------------------------------------------------
class Simulator {
   public:
      Simulator(istream &readFrom);
      void run(void);
      bool locked;

   private:
      int varArray[ALPHABET];
      queue<Program> readyQueue;
      queue<Program> blockedQueue;
      int numPrograms;
      int statementTimes[6];
      int timeQuantum;

      Program::Statement parse(char[]);
      void setValues(char[]);
};

#endif // SIM_H
