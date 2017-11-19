//
// Created by roy on 11/11/17.
//

//#include "../include/FileSystem.h"
#include "../include/Environment.h"

void Environment::start()
{

}

FileSystem &Environment::getFileSystem()
{
	return fs;
}

void Environment::addToHistory(BaseCommand *command)
{
	commandsHistory.push_back(command);
}

const std::vector<BaseCommand *> &Environment::getHistory() const
{
	return commandsHistory;
}

void Environment::copy(const Environment &other)
{
	for (auto &command : other.commandsHistory)
		commandsHistory.push_back(command->clone());
}

void Environment::clear()
{
//	for (int i=0; i<commandsHistory.size(); ++i)
//	{
//		delete commandsHistory[i];
//		commandsHistory.erase(commandsHistory.begin()+i);
//	}
	for (auto &command : commandsHistory)
		delete command;
	commandsHistory.erase(commandsHistory.begin(), commandsHistory.end());
}

Environment::Environment() : commandsHistory(), fs()
{
}

Environment::Environment(const Environment &other) : commandsHistory(), fs(other.fs)//<-coping fs
{
	//clear();
	copy(other);
}

Environment::Environment(Environment &&other) : commandsHistory(other.commandsHistory), fs(other.fs)
{
}

Environment &Environment::operator=(const Environment &other)
{
	if (this!=&other)
	{
		clear();
		copy(other);
		fs=FileSystem(other.fs);
	}
	
	return *this;
}

Environment &Environment::operator=(Environment &&other)
{
	if (this!=&other)
	{
		clear();
		commandsHistory=other.commandsHistory;
		fs=other.fs;
	}
	
	return *this;
}

Environment::~Environment()
{
	clear();
}
