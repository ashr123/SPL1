//
// Created by roy on 11/11/17.
//

#include "../include/Commands.h"

BaseCommand::BaseCommand(string args)
{

}

string BaseCommand::getArgs()
{
	return std::__cxx11::string();
}

PwdCommand::PwdCommand(string args) : BaseCommand(args)
{
    
}

void PwdCommand::execute(FileSystem &fs)
{

}

string PwdCommand::toString()
{
	return std::__cxx11::string();
}

CdCommand::CdCommand(string args) : BaseCommand(args)
{
}

void CdCommand::execute(FileSystem &fs)
{

}

string CdCommand::toString()
{
	return std::__cxx11::string();
}

LsCommand::LsCommand(string args) : BaseCommand(args)
{
}

void LsCommand::execute(FileSystem &fs)
{

}

string LsCommand::toString()
{
	return std::__cxx11::string();
}

MkdirCommand::MkdirCommand(string args) : BaseCommand(args)
{
}

void MkdirCommand::execute(FileSystem &fs)
{

}

string MkdirCommand::toString()
{
	return std::__cxx11::string();
}

MkfileCommand::MkfileCommand(string args) : BaseCommand(args)
{
}

void MkfileCommand::execute(FileSystem &fs)
{

}

string MkfileCommand::toString()
{
	return std::__cxx11::string();
}

CpCommand::CpCommand(string args) : BaseCommand(args)
{
}

void CpCommand::execute(FileSystem &fs)
{

}

string CpCommand::toString()
{
	return std::__cxx11::string();
}

MvCommand::MvCommand(string args) : BaseCommand(args)
{
}

void MvCommand::execute(FileSystem &fs)
{

}

string MvCommand::toString()
{
	return std::__cxx11::string();
}

RenameCommand::RenameCommand(string args) : BaseCommand(args)
{
}

void RenameCommand::execute(FileSystem &fs)
{

}

string RenameCommand::toString()
{
	return std::__cxx11::string();
}

RmCommand::RmCommand(string args) : BaseCommand(args)
{
}

void RmCommand::execute(FileSystem &fs)
{

}

string RmCommand::toString()
{
	return std::__cxx11::string();
}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args), history(history)
{
}

void HistoryCommand::execute(FileSystem &fs)
{

}

string HistoryCommand::toString()
{
	return std::__cxx11::string();
}

VerboseCommand::VerboseCommand(string args) : BaseCommand(args)
{

}

void VerboseCommand::execute(FileSystem &fs)
{

}

string VerboseCommand::toString()
{
	return std::__cxx11::string();
}

ErrorCommand::ErrorCommand(string args) : BaseCommand(args)
{

}

void ErrorCommand::execute(FileSystem &fs)
{

}

string ErrorCommand::toString()
{
	return std::__cxx11::string();
}

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(args), history(history)
{
}

void ExecCommand::execute(FileSystem &fs)
{

}

string ExecCommand::toString()
{
	return std::__cxx11::string();
}