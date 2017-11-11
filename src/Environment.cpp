//
// Created by roy on 11/11/17.
//

#include "../include/FileSystem.h"
#include "../include/Commands.h"
#include "../include/Environment.h"

void Environment::start()
{

}

FileSystem &Environment::getFileSystem() const
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