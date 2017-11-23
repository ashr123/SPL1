//
// Created by roy on 11/11/17.
//

#include <iostream>
#include <sstream>
#include "../include/Environment.h"

void Environment::start()
{
	string args, firstS, secS, thirdS, garbage;
	while (true)
	{
		cout<<fs.getWorkingDirectory().getAbsolutePath()+'>';
		getline(cin, args);
		if (verbose==2 || verbose==3)
			cout<<args<<endl;
		istringstream str(args);
		if (args=="exit")
			return;
		firstS=secS=thirdS="";
		getline(str, firstS, ' ');
		getline(str, secS, ' ');
		getline(str, thirdS, ' ');
		
		if (firstS=="pwd")
		{
			commandsHistory.push_back(new PwdCommand(""));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="cd")
		{
			commandsHistory.push_back(new CdCommand(secS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="ls")
		{
			commandsHistory.push_back(new LsCommand(secS+' '+thirdS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="mkdir")
		{
			commandsHistory.push_back(new MkdirCommand(secS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			getline(str, garbage);
			continue;
		}
		if (firstS=="mkfile")
		{
			commandsHistory.push_back(new MkfileCommand(secS+' '+thirdS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="cp")
		{
			commandsHistory.push_back(new CpCommand(secS+' '+thirdS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="mv")
		{
			commandsHistory.push_back(new MvCommand(secS+' '+thirdS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="rename")
		{
			commandsHistory.push_back(new RenameCommand(secS+' '+thirdS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="rm")
		{
			commandsHistory.push_back(new CpCommand(secS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="history")
		{
			commandsHistory.push_back(new HistoryCommand("", commandsHistory));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="verbose")
		{
			commandsHistory.push_back(new VerboseCommand(secS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		if (firstS=="exec")
		{
			commandsHistory.push_back(new ExecCommand("", commandsHistory));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
			continue;
		}
		else
		{
			commandsHistory.push_back(new ErrorCommand(firstS));
			commandsHistory[commandsHistory.size()-1]->execute(fs);
		}
	}
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
	//commandsHistory.erase(commandsHistory.begin(), commandsHistory.end());
	commandsHistory.clear();
}

Environment::Environment() : commandsHistory(), fs()
{
}

Environment::Environment(const Environment &other) : commandsHistory(), fs(other.fs)
{
	if (verbose==1 || verbose==3)
		cout<<"Environment::Environment(const Environment &other)"<<endl;
	clear();
	copy(other);
}

Environment::Environment(Environment &&other) : commandsHistory(move(other.commandsHistory)),
                                                fs(move(other.fs))
{
	if (verbose==1 || verbose==3)
		cout<<"Environment::Environment(Environment &&other)"<<endl;
	//clear();
	//copy(other);
}

Environment &Environment::operator=(const Environment &other)
{
	if (verbose==1 || verbose==3)
		cout<<"Environment &Environment::operator=(const Environment &other)"<<endl;
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
	if (verbose==1 || verbose==3)
		cout<<"Environment &Environment::operator=(Environment &&other)"<<endl;
	if (this!=&other)
	{
		clear();
		copy(other);
		fs=FileSystem(other.fs);
	}
	
	return *this;
}

Environment::~Environment()
{
	if (verbose==1 || verbose==3)
		cout<<"Environment::~Environment()"<<endl;
	clear();
}