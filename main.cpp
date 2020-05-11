#include <string>
#include "TuringMachine.h"

int main()
{
	TuringMachine TM;
	
	TM.read_commands("input.txt");
	TM.read_tape("1#111#1");
	TM.start();

	return 0;
}