//
// Created by roy on 11/11/17.
//

#include <iostream>
#include <sstream>
#include "../include/Commands.h"

BaseCommand::BaseCommand(string args) : args(move(args))
{
}

string BaseCommand::getArgs() const
{
	return args;
}

BaseCommand::~BaseCommand()
{}

PwdCommand::PwdCommand(string args) : BaseCommand(move(args))
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


CdCommand::CdCommand(string args) : BaseCommand(move(args))
{
}

void CdCommand::execute(FileSystem &fs)
{
	istringstream str(getArgs());
	string s;
	bool find;
	getline(str, s, '/');
	if (s==".." || s==".")
		do
		{//Relative path
			find=false;
			if (s=="..")
			{
				fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
			}
			else
				if (s==".")
				{
					getline(str, s, '/');
					for (unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++)
					{
						if (fs.getWorkingDirectory().getChildren().at(i)->getName()==s)
							if (fs.getWorkingDirectory().getChildren().at(i)->isDir())
							{
								fs.setWorkingDirectory(
										(Directory *)(fs.getWorkingDirectory().getChildren().at(i)));
								find=true;
							}
					}
					if (!find)
						break;
				}
				else
				{//for name
					for (unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++)
					{
						if (fs.getWorkingDirectory().getChildren().at(i)->getName()==s)
							if (fs.getWorkingDirectory().getChildren().at(i)->isDir())
							{
								fs.setWorkingDirectory(
										(Directory *)(fs.getWorkingDirectory().getChildren().at(i)));
								find=true;
							}
					}
					if (!find)
						break;
				}
			
		} while (getline(str, s, '/'));
	else
	{//Absolute path
		fs.setWorkingDirectory(&fs.getRootDirectory());
		do
		{
			find=false;
			for (unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++)
			{
				if (fs.getWorkingDirectory().getChildren().at(i)->getName()==s)
				{
					if (fs.getWorkingDirectory().getChildren().at(i)->isDir())
						fs.setWorkingDirectory((Directory *)(fs.getWorkingDirectory().getChildren().at(i)));
					find=true;
				}
			}
			if (!find)
				break;
		} while (getline(str, s, '/'));
	}
	if (!find)
		cout<<"The system cannot find the path specified"<<endl;
}


string CdCommand::toString() const
{
	return std::__cxx11::string();
}

LsCommand::LsCommand(string args) : BaseCommand(move(args))
{
}

void LsCommand::execute(FileSystem &fs)
{
	vector<BaseFile *> vec=fs.getWorkingDirectory().getChildren();
	for (auto &i : vec)
	{
		if (i->isDir())
			cout<<"DIR"<<"\t"<<i->getName()<<"\t"<<i->getSize()<<endl;
		cout<<"FILE"<<"\t"<<i->getName()<<"\t"<<i->getSize()<<endl;
	}
}

string LsCommand::toString() const
{
	return std::__cxx11::string();
}

MkdirCommand::MkdirCommand(string args) : BaseCommand(move(args))
{
}

void MkdirCommand::execute(FileSystem &fs)
{
	string s(getArgs());
	istringstream str(getArgs());
	if (s.at(0)=='/')
	{
		fs.setWorkingDirectory(&fs.getRootDirectory());
		bool isCreated=false;
		do
		{
			bool find=false;
			for (unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++)
			{
				if (fs.getWorkingDirectory().getChildren().at(i)->getName()==s)
					if (fs.getWorkingDirectory().getChildren().at(i)->isDir())
					{
						fs.setWorkingDirectory((Directory *)(fs.getWorkingDirectory().getChildren().at(i)));
						find=true;
					}
			}
			if (!find)
			{
				fs.getWorkingDirectory().addFile(new Directory(s, &fs.getWorkingDirectory()));
				isCreated=true;
			}
			
		} while (getline(str, s, '/'));
		if (!isCreated)
			cout<<"The directory already exists"<<endl;
	}
	else
	{
		bool find=false;
		for (unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++)
		{
			if (fs.getWorkingDirectory().getChildren().at(i)->getName()==s)
				if (fs.getWorkingDirectory().getChildren().at(i)->isDir())
					find=true;
		}
		if (!find)
			fs.getWorkingDirectory().addFile(new Directory(s, &fs.getWorkingDirectory()));
		else
			cout<<"The directory already exists"<<endl;
	}
}

string MkdirCommand::toString() const
{
	return std::__cxx11::string();
}

MkfileCommand::MkfileCommand(string args) : BaseCommand(move(args))
{
}

void MkfileCommand::execute(FileSystem &fs)
{

}

string MkfileCommand::toString() const
{
	return std::__cxx11::string();
}

CpCommand::CpCommand(string args) : BaseCommand(move(args))
{
}

void CpCommand::execute(FileSystem &fs)
{

}

string CpCommand::toString() const
{
	return std::__cxx11::string();
}

MvCommand::MvCommand(string args) : BaseCommand(move(args))
{
}

void MvCommand::execute(FileSystem &fs)
{

}

string MvCommand::toString() const
{
	return std::__cxx11::string();
}

RenameCommand::RenameCommand(string args) : BaseCommand(move(args))
{
}

void RenameCommand::execute(FileSystem &fs)
{

}

string RenameCommand::toString() const
{
	return std::__cxx11::string();
}

RmCommand::RmCommand(string args) : BaseCommand(move(args))
{
}

void RmCommand::execute(FileSystem &fs)
{

}

string RmCommand::toString() const
{
	return std::__cxx11::string();
}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) :
		BaseCommand(move(args)), history(history)
{
}

void HistoryCommand::execute(FileSystem &fs)
{

}

string HistoryCommand::toString() const
{
	return std::__cxx11::string();
}

VerboseCommand::VerboseCommand(string args) : BaseCommand(move(args))
{

}

void VerboseCommand::execute(FileSystem &fs)
{

}

string VerboseCommand::toString() const
{
	return std::__cxx11::string();
}

ErrorCommand::ErrorCommand(string args) : BaseCommand(move(args))
{

}

void ErrorCommand::execute(FileSystem &fs)
{

}

string ErrorCommand::toString() const
{
	return std::__cxx11::string();
}

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(move(args)), history(history)
{
}

void ExecCommand::execute(FileSystem &fs)
{

}

string ExecCommand::toString() const
{
	return std::__cxx11::string();
}