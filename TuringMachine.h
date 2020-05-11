#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>

#define MAX_ITERATIONS 100

enum class Direction
{
	forward,
	back,
	stay
};

class Commands
{
public:
	int state;
	char letter;
	Direction direction;

	void init(int state, char letter, Direction dir);
};


class TuringMachine
{
private:
	std::list<char> tape;
	int looking_at;
	int state;
	
	bool commands_inited;

	std::string alph;
	Commands commands[16][8];

	void forvard();
	void back();
	void execute(char& letter, Commands command);
	void next_iteration();

public:
	TuringMachine();

	void read_commands(std::string file_name);
	void read_tape(std::string str);

	void print();
	void start();
};