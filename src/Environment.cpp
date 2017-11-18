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
	{
		if (dynamic_cast<PwdCommand *>(command))
		{
			commandsHistory.push_back(new PwdCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<CdCommand *>(command))
		{
			commandsHistory.push_back(new CdCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<LsCommand *>(command))
		{
			commandsHistory.push_back(new LsCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<MkdirCommand *>(command))
		{
			commandsHistory.push_back(new MkdirCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<MkfileCommand *>(command))
		{
			commandsHistory.push_back(new MkfileCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<CpCommand *>(command))
		{
			commandsHistory.push_back(new CpCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<MvCommand *>(command))
		{
			commandsHistory.push_back(new MvCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<RenameCommand *>(command))
		{
			commandsHistory.push_back(new RenameCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<RmCommand *>(command))
		{
			commandsHistory.push_back(new RmCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<HistoryCommand *>(command))
		{
			commandsHistory.push_back(new HistoryCommand(*(HistoryCommand *)command));
			return;
		}
		if (dynamic_cast<VerboseCommand *>(command))
		{
			commandsHistory.push_back(new VerboseCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<ErrorCommand *>(command))
		{
			commandsHistory.push_back(new ErrorCommand(command->getArgs()));
			return;
		}
		if (dynamic_cast<ExecCommand *>(command))
		{
			commandsHistory.push_back(new ExecCommand(*(ExecCommand *)command));
			return;
		}
	}
}

void Environment::clear()
{
	for (auto &commnad : commandsHistory)
		delete commnad;
}

Environment::Environment() : commandsHistory(), fs()
{

}

Environment::Environment(const Environment &other) : commandsHistory(), fs()
{

}

Environment::Environment(Environment &&other) : commandsHistory(), fs()
{

}

Environment &Environment::operator=(const Environment &other)
{
	
	
	return *this;
}

Environment &Environment::operator=(Environment &&other)
{
	
	
	return *this;
}

Environment::~Environment()
{

}
