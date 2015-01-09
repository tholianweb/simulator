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
#include "Simulator.h"
using namespace std;

//-----------------------------------------------------------------------------
//Method:		Simulator(istream &readFrom)
//
//Description:	Constructor for the Simulator class.
//
//Parameters:	istream &readFrom
// ----------------------------------------------------------------------------
Simulator::Simulator(istream &readFrom)
{
   char firstLine[FIRSTLINE];
   char current[MAXLINE];
   Program::Statement nextState;
   int programsRead = 0;
   queue<Program::Statement> newProg;

   readFrom.getline(firstLine, FIRSTLINE);
   setValues(firstLine);

   while (programsRead < numPrograms)
   {
      readFrom.getline(current, MAXLINE);
      nextState = parse(current);

      if (nextState.m_type != INVALID)
         newProg.push(nextState);
      if (nextState.m_type == END)
      {
         Program temp((programsRead + 1), newProg);
         readyQueue.push(temp);
         while (!newProg.empty())
         {
            newProg.pop();
         }
         programsRead++;
      }
   }
   locked = false; //locked is initialized to false
   for (int i = 0; i < ALPHABET; i++) //variables all initialized to 0
      varArray[i] = NOVAL;
}
//-----------------------------------------------------------------------------
//Method:		void run(void)
//
//Description:	Main method of the Simulator class. Runs the simulator until
//             the number of programs specified by the user have finished.
//             Assumes the simulator has been properly constructed. Any invalid
//             values should default to constant NOVAL, or 0.
//
//Parameters:	void
// ----------------------------------------------------------------------------
void Simulator::run(void)
{
   StatementType currentType = ASSIGN;
   int programsExecuted = 0;
   bool blocked = false;
   while (programsExecuted < numPrograms)
   {
      int timeLeft = timeQuantum;
      Program current = readyQueue.front();
      while (timeLeft > 0)
      {
         blocked = current.execute(varArray, locked, currentType);
         if(blocked)
         {
            blockedQueue.push(current);
            readyQueue.pop();
            timeLeft = 0;
         }
         else
         {
            timeLeft -= statementTimes[currentType];
            if (currentType == UNLOCK)
            {
               if (!blockedQueue.empty())
               {
                  readyQueue.push(blockedQueue.front());
                  blockedQueue.pop();
               }
            }
            else if (currentType == END)
            {
               readyQueue.pop();
               programsExecuted++;
               timeLeft = 0;
               break;
            }
         }
      }
      if (!blocked && currentType != END)
      {
      readyQueue.push(current);
      readyQueue.pop();
      }

   }

}
//-----------------------------------------------------------------------------
//Method:		Statement parse(char current[])
//
//Description:	Takes one line from an istream any converts it into one of the
//             five specified statement types, then returns the statement.
//             Assumes the line is properly formatted. Possible line formats,
//             where a is any upper or lowercase letter and # is any number
//             0-9: a = ##, a = #, print a, lock, unlock, end
//
//Parameters:	char current[] -- the line being converted to a statement
// ----------------------------------------------------------------------------
Program::Statement Simulator::parse(char current[])
{
   Program::Statement parsed; //statement to be returned
   string line(current); //string version of the current line
   string equals = "="; //assignment character

   if (line.find(equals) != string::npos) //if string contains an equals
   {
      parsed.m_type = ASSIGN;
      parsed.m_var = tolower(current[0]);
      //strtol will safely return 0 if unable to convert string
      int checkVal = strtol(current + 4, NULL, 10);
      //if negative number greater than  negative upper limit is passed in,
      //it is converted to a positive number and assigned
      if (abs(checkVal) < UPPERLIM)
         parsed.m_value = abs(checkVal);
   }
   else
   {
      switch (tolower(current[0]))
      {
         case 'e':
            parsed.m_type = END;
            break;
         case 'l':
            parsed.m_type = LOCK;
            break;
         case 'p':
            parsed.m_type = OUTPUT;
            parsed.m_var = tolower(current[6]);
            break;
         case 'u':
            parsed.m_type = UNLOCK;
            break;
         default:
            parsed.m_type = INVALID;
            break;
      }
   }
   return parsed;
}
//-----------------------------------------------------------------------------
//Method:		void setValues(char firstLine[])
//
//Description:	Sets the various simulator member values using the first line
//             taken from the file/stream.
//
//Parameters:	char firstLine[] -- first line of input, contains simulator
//                                 program and timing values
// ----------------------------------------------------------------------------
void Simulator::setValues(char firstLine[])
{
   char* pNext;
   numPrograms = strtol(firstLine, &pNext, 10);
   statementTimes[ASSIGN] = strtol(pNext, &pNext, 10);
   statementTimes[OUTPUT] = strtol(pNext, &pNext, 10);
   statementTimes[LOCK] = strtol(pNext, &pNext, 10);
   statementTimes[UNLOCK] = strtol(pNext, &pNext, 10);
   statementTimes[END] = strtol(pNext, &pNext, 10);
   timeQuantum = strtol(pNext, NULL, 10);

   statementTimes[INVALID] = 0;
}

