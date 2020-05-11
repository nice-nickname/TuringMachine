#include "TuringMachine.h"

void TuringMachine::forvard()
{
	if (looking_at < tape.size() - 1)
	{
		looking_at++;
	}
	else
	{
		tape.push_back(alph[0]);
		looking_at++;
	}

}

void TuringMachine::back()
{
	if (looking_at > 0)
	{
		looking_at--;
	}
	else
	{
		tape.push_front(alph[0]);
	}
}

void TuringMachine::execute(char& letter, Commands command)
{
	if (command.state != -1)
	{
		letter = command.letter;
		state = command.state;

		if (command.direction == Direction::forward)
		{
			forvard();
		}
		else if (command.direction == Direction::back)
		{
			back();
		}
	}
	else
	{
		std::cout << "\nTM can't reach HEAD~0\n";
		state = command.state;
	}
}

TuringMachine::TuringMachine()
{
	state = 1;
	looking_at = -1;
	alph = "#10+-abc";
	commands_inited = false;
}

void TuringMachine::read_commands(std::string file_name)
{
	commands_inited = false;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			commands[i][j].init(-1, '#', Direction::stay);
		}
	}

	std::ifstream fin;
	fin.open(file_name);

	if (fin.is_open())
	{
		int n;
		fin >> n;

		for (int i = 0; i < n; i++)
		{
			int ostate, nstate;
			char oletter, nletter;
			Direction ndir;
			int tempdir;
			fin >> ostate >> oletter >> nstate >> nletter >> tempdir;

			switch (tempdir)
			{
			case 1:
				ndir = Direction::forward;
				break;

			case 0:
				ndir = Direction::stay;
				break;

			case -1:
				ndir = Direction::back;
				break;

			default:
				std::cout << "Invalid commands, wrong direction\n";
				return;
			}

			if (ostate > 15 || ostate < 0 || nstate > 15 || nstate < 0)
			{
				std::cout << "invalid commands, wrong state\n";
				return;
			}

			if (alph.find(oletter) == std::string::npos || alph.find(nletter) == std::string::npos)
			{
				std::cout << "invalid commands, wrong letter\n";
				return;
			}

			commands[ostate][alph.find(oletter)].init(nstate, nletter, ndir);
		}
		commands_inited = true;
	}
}

void TuringMachine::read_tape(std::string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != alph[0])
		{
			looking_at = i + 1;
			break;
		}
	}

	state = 1;
	tape.clear();

	tape.push_front('#');
	for (auto& i : str)
	{
		tape.push_back(i);
	}
	tape.push_back('#');
}

void TuringMachine::next_iteration()
{
	int count = 0;

	for (auto i = tape.begin(); i != tape.end(); ++i)
	{
		if (count == looking_at)
		{
			execute(*i, commands[state][alph.find(*i)]);
			return;
		}
		count++;
	}
}

void TuringMachine::print()
{
	int count = 0;

	for (auto& i : tape)
	{
		std::cout << i;
	}
	std::cout << "  HEAD~" << state << '\n';
	for (int i = 0; i < looking_at; i++)
	{
		std::cout << ' ';
	}
	std::cout << "^\n";
}

void TuringMachine::start()
{
	if (commands_inited && looking_at != -1 && state == 1)
	{
		std::cout << "---TAPE---\n";
		print();
		int counter = 0;

		for (int i = 0; i < MAX_ITERATIONS; i++)
		{
			counter++;

			next_iteration();
			print();
			if (state == 0 || state == -1)
				return;
		}
		if (counter == MAX_ITERATIONS)
			std::cout << "Run out of iterations. Probably, machine is looped\n";
	}
}

void Commands::init(int state, char letter, Direction dir)
{
	this->direction = dir;
	this->letter = letter;
	this->state = state;
}