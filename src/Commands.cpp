//
// Created by roy on 11/11/17.
//

#include <iostream>
#include <cstring>
#include "../include/Commands.h"

BaseCommand::BaseCommand(string args) : args(args)
{
}

string BaseCommand::getArgs() const
{
	return args;
}

PwdCommand::PwdCommand(string args) : BaseCommand(args)
{
}

void PwdCommand::execute(FileSystem &fs)
{
	cout<<fs.getWorkingDirectory().getAbsolutePath()<<endl;
}

string PwdCommand::toString() const
{
	return std::__cxx11::string();
}

CdCommand::CdCommand(string args) : BaseCommand(args)
{
}

void CdCommand::execute(FileSystem &fs)
{
	string str(getArgs());
	strtok()
}

string CdCommand::toString() const
{
	return std::__cxx11::string();
}

LsCommand::LsCommand(string args) : BaseCommand(args)
{
}

void LsCommand::execute(FileSystem &fs)
{

}

string LsCommand::toString() const
{
	return std::__cxx11::string();
}

MkdirCommand::MkdirCommand(string args) : BaseCommand(args)
{
}

void MkdirCommand::execute(FileSystem &fs)
{

}

string MkdirCommand::toString() const
{
	return std::__cxx11::string();
}

MkfileCommand::MkfileCommand(string args) : BaseCommand(args)
{
}

void MkfileCommand::execute(FileSystem &fs)
{

}

string MkfileCommand::toString() const
{
	return std::__cxx11::string();
}

CpCommand::CpCommand(string args) : BaseCommand(args)
{
}

void CpCommand::execute(FileSystem &fs)
{

}

string CpCommand::toString() const
{
	return std::__cxx11::string();
}

MvCommand::MvCommand(string args) : BaseCommand(args)
{
}

void MvCommand::execute(FileSystem &fs)
{

}

string MvCommand::toString() const
{
	return std::__cxx11::string();
}

RenameCommand::RenameCommand(string args) : BaseCommand(args)
{
}

void RenameCommand::execute(FileSystem &fs)
{

}

string RenameCommand::toString() const
{
	return std::__cxx11::string();
}

RmCommand::RmCommand(string args) : BaseCommand(args)
{
}

void RmCommand::execute(FileSystem &fs)
{

}

string RmCommand::toString() const
{
	return std::__cxx11::string();
}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args), history(history)
{
}

void HistoryCommand::execute(FileSystem &fs)
{

}

string HistoryCommand::toString() const
{
	return std::__cxx11::string();
}

VerboseCommand::VerboseCommand(string args) : BaseCommand(args)
{

}

void VerboseCommand::execute(FileSystem &fs)
{

}

string VerboseCommand::toString() const
{
	return std::__cxx11::string();
}

ErrorCommand::ErrorCommand(string args) : BaseCommand(args)
{

}

void ErrorCommand::execute(FileSystem &fs)
{

}

string ErrorCommand::toString() const
{
	return std::__cxx11::string();
}

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args), history(history)
{
}

void ExecCommand::execute(FileSystem &fs)
{

}

string ExecCommand::toString() const
{
	return std::__cxx11::string();
}