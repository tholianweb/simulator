//-----------------------------------------------------------------------------
//	File: Program.cpp
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
#include "Program.h"
using namespace std;

//-----------------------------------------------------------------------------
//Method:		Program(int progNum, queue<Statement> statements)
//
//Description:	Constructor for the Program class.
//
//Parameters:	int progNum -- program is assigned a number by the simulator
//             queue<Statement> statements -- list of all statements in the
//                                            program
// ----------------------------------------------------------------------------
Program::Program(int progNum, queue<Statement> statements)
{
   m_progNum = progNum;
   m_statements = statements;
   m_done = false;
}
//-----------------------------------------------------------------------------
//Method:		void execute(int varArray[], bool &locked)
//
//Description:	Method to execute the next statement in the statements queue.
//
//Parameters:	int varArray[] -- the array of variables the simulator is using
//             bool &locked -- reference to the boolean keeping track of
//                             whether or not the variables are locked
// ----------------------------------------------------------------------------
bool Program::execute(int varArray[], bool &locked, StatementType &type)
{
   bool blocked = false;
   Statement current = m_statements.front();

   switch (current.m_type)
   {
      case ASSIGN:
         type = ASSIGN;
         varArray[current.m_var - OFFSET] = current.m_value;
         m_statements.pop();
         break;
      case OUTPUT:
         type = OUTPUT;
         cout << m_progNum << ": " << varArray[current.m_var - OFFSET] << endl;
         m_statements.pop();
         break;
      case LOCK:
         type = LOCK;
         if (locked == true)
            blocked = true;
         else
         {
            locked = true;
            m_statements.pop();
         }
         break;
      case UNLOCK:
         type = UNLOCK;
         locked = false;
         m_statements.pop();
         break;
      case END:
         type = END;
         m_done = true;
         m_statements.pop();
         break;
      case INVALID:
      default:
         type = INVALID;
         m_statements.pop();
         break;
   }
   return blocked;
}
//-----------------------------------------------------------------------------
//Method:		bool isDone(void)
//
//Description:	Returns true if the program is done, false otherwise
//
//Parameters:	void
// ----------------------------------------------------------------------------
bool Program::isDone(void)
{
   return m_done;
}
//-----------------------------------------------------------------------------
//Method:		void setProgNum(int number)
//
//Description:	Sets the program number to the value passed in. If passed in
//             value is negative, program number is set to error flag value
//
//Parameters:	int number -- program number to set
// ----------------------------------------------------------------------------
void Program::setProgNum(int number)
{
   if (number > 0)
      m_progNum = number;
   else
      //if out of range number passed in, program number set to error value
      m_progNum = NOVAL;
}

ostream& operator<<(ostream& sout, const Program& progOut)
{
   sout << "Program " << progOut.m_progNum << endl;
   queue<Program::Statement> temp = progOut.m_statements;
   while (!temp.empty())
   {
      Program::Statement cur = temp.front();
      switch (cur.m_type)
      {
         case ASSIGN:
            sout << cur.m_var << " = " << cur.m_value << endl;
            break;
         case OUTPUT:
            sout << "print " << cur.m_var << endl;
            break;
         case LOCK:
            sout << "lock" << endl;
            break;
         case UNLOCK:
            sout << "unlock" << endl;
            break;
         case END:
            sout << "end" << endl;
            break;
         default:
            break;
      }
      temp.pop();
   }
   return sout;
}

