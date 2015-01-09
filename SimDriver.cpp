//---------------------------------------------------------------------------------
// File:		SimDriver.cpp
//
// Description:
//				Runs a driver using the Simulator and Program classes
//
// Programmer: Sarah Kazemian
//
// Date:		12/3/14
//
// Environment:   Linux Mint 17 for execution,
//					   Compiles under Code::Blocks 13.12 using gnu GCC compiler
//
// Input:		The first line of input consists of seven integers separated by
//             spaces. These integers specify the number of programs, the unit
//             execution times for each of the five statement types, and the time
//             quantum. The remainder of the input is the programs, which consist
//             of series of statements, one on each line.
//
// Output:		The properly formatted (program: value) output of each program in
//             the order that the statements execute.
//
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
//---------------------------------------------------------------------------------
#include "Simulator.h"

int main (void)
{
   Simulator concurrencySim(cin);
   concurrencySim.run();

   return EXIT_SUCCESS;
}
