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
	return "pwd "+getArgs();
}

BaseCommand *PwdCommand::clone() const
{
	return new PwdCommand(getArgs());
}


CdCommand::CdCommand(string args) : BaseCommand(move(args))
{
}

void CdCommand::execute(FileSystem &fs)
{
	istringstream str(getArgs());
	string s(getArgs());
	bool find;
	if (s[0]=='/')
	{
		getline(str, s, '/');
		fs.setWorkingDirectory(&fs.getRootDirectory());
	}
	getline(str, s, '/');
	do
	{
		find=false;
		if (s=="..")
		{
			if (&fs.getWorkingDirectory()!=&fs.getRootDirectory())
				fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
			else
				cout<<"The system cannot find the path specified"<<endl;
		}
		else
		{//for name
			for (unsigned int i=0; i<fs.getWorkingDirectory().getChildren().size(); i++)
				if (fs.getWorkingDirectory().getChildren().at(i)->getName()==s)
					if (fs.getWorkingDirectory().getChildren().at(i)->isDir())
					{
						fs.setWorkingDirectory(
								(Directory *)(fs.getWorkingDirectory().getChildren().at(i)));
						find=true;
					}
			if (!find)
			{
				cout<<"The system cannot find the path specified"<<endl;
				break;
			}
		}
		
	} while (getline(str, s, '/'));
}


string CdCommand::toString() const
{
	return "cd "+getArgs();
}

BaseCommand *CdCommand::clone() const
{
	return new CdCommand(getArgs());
}

LsCommand::LsCommand(string args) : BaseCommand(move(args))
{
}

void LsCommand::execute(FileSystem &fs)//TODO
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
	return "ls "+getArgs();
}

BaseCommand *LsCommand::clone() const
{
	return new LsCommand(getArgs());
}

MkdirCommand::MkdirCommand(string args) : BaseCommand(move(args))
{
}

void MkdirCommand::execute(FileSystem &fs)
{
	vector<string> c;
	istringstream str(getArgs());
	string s(getArgs());
	Directory *curr;
	if (s[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	while (getline(str, s, '/'))
		c.push_back(s);
	bool find=false;
	for (unsigned int i=0; i<c.size(); i++)
	{
		if (c[i]=="..")
		{
			if (curr->getParent()==NULL)
			{
				cout<<"The system cannot find the path specified"<<endl;
				break;
			}
			curr=curr->getParent();
			i++;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==c[i])
				if (curr->getChildren()[j]->isDir())
				{
					curr=(Directory *)curr->getChildren()[j];
					find=true;
					if (i==c.size())
						cout<<"The directory already exists"<<endl;
				}
		if (!find)
		{
			curr->addFile(new Directory(c[i], curr));
			curr=(Directory *)curr->getChildren()[curr->getChildren().size()-1];
		}
	}
}

string MkdirCommand::toString() const
{
	return "mkdir "+getArgs();
}

BaseCommand *MkdirCommand::clone() const
{
	return new MkdirCommand(getArgs());
}

MkfileCommand::MkfileCommand(string args) : BaseCommand(move(args))
{
}

void MkfileCommand::execute(FileSystem &fs)
{
	vector<string> v;
	istringstream str(getArgs());
	string s(getArgs());
	Directory *curr;
	if (s[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	while (getline(str, s, '/'))
		v.push_back(s);
	string newFile=v[v.size()-1].substr(0, v[v.size()-1].find(' '));
	string fileSize=v[v.size()-1].substr(v[v.size()-1].find(' ')+1);
	for (unsigned int i=0; i<v.size()-1; i++)
	{
		bool find=false;
		if (v[i]=="..")
		{
			if (curr->getParent()==NULL)
			{
				cout<<"The system cannot find the path specified"<<endl;
				return;
			}
			curr=curr->getParent();
			i++;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==v[i])
				if (curr->getChildren()[j]->isDir())
				{
					curr=(Directory *)curr->getChildren()[j];
					find=true;
				}
		if (!find)
		{
			cout<<"The system cannot find the path specified"<<endl;
			return;
		}
	}
	for (unsigned int j=0; j<curr->getChildren().size(); j++)
		if (curr->getChildren()[j]->getName()==newFile)
		{
			cout<<"File already exists"<<endl;
			return;
		}
	curr->addFile(new File(newFile, atoi(fileSize.c_str())));
}

string MkfileCommand::toString() const
{
	return "mkfile "+getArgs();
}

BaseCommand *MkfileCommand::clone() const
{
	return new MkfileCommand(getArgs());
}

CpCommand::CpCommand(string args) : BaseCommand(move(args))
{
}

void CpCommand::execute(FileSystem &fs)
{

}

string CpCommand::toString() const
{
	return "cp "+getArgs();
}

BaseCommand *CpCommand::clone() const
{
	return new CpCommand(getArgs());
}

MvCommand::MvCommand(string args) : BaseCommand(move(args))
{
}

void MvCommand::execute(FileSystem &fs)
{

}

string MvCommand::toString() const
{
	return "mv "+getArgs();
}

BaseCommand *MvCommand::clone() const
{
	return new MvCommand(getArgs());
}

RenameCommand::RenameCommand(string args) : BaseCommand(move(args))
{
}

void RenameCommand::execute(FileSystem &fs)
{
	vector<string> v;
	istringstream str(getArgs());
	string s(getArgs());
	Directory *curr;
	if (s[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	while (getline(str, s, '/'))
		v.push_back(s);
	string oldName = v[v.size()-1].substr(0, v[v.size()-1].find(' '));
	string newName = v[v.size()-1].substr(v[v.size()-1].find(' '));
	if (curr->getName()== oldName)
	{
		cout<<"“Can’t rename the working directory"<<endl;
		return;
	}
	for(int i=0;i<v.size()-1;i++)
	{
		bool find=false;
		if (v[i]=="..")
		{
			if (curr->getParent()==NULL)
			{
				cout<<"The system cannot find the path specified"<<endl;
				return;
			}
			curr=curr->getParent();
			i++;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==v[i])
				if (curr->getChildren()[j]->isDir())
				{
					curr=(Directory *)curr->getChildren()[j];
					find=true;
				}
		if (!find)
		{
			cout<<"No such file or directory"<<endl;
			return;
		}
	}
	bool change=false;
	for (unsigned int j=0; j<curr->getChildren().size(); j++)
		if (curr->getChildren()[j]->getName()==oldName)
		{
			curr->getChildren()[j]->setName(newName);
			change=true;
		}
	if(!change)
		cout<<"No such file or directory"<<endl;
}

string RenameCommand::toString() const
{
	return "rename "+getArgs();
}

BaseCommand *RenameCommand::clone() const
{
	return new RenameCommand(getArgs());
}

RmCommand::RmCommand(string args) : BaseCommand(move(args))
{
}

void RmCommand::execute(FileSystem &fs)
{
	vector<string> v;
	istringstream str(getArgs());
	string s(getArgs());
	Directory *curr;
	if (s[0]=='/')
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	while (getline(str, s, '/'))
		v.push_back(s);
	string toRemove = v[v.size()-1];
	if(toRemove==curr->getName()|toRemove==fs.getRootDirectory().getName())
	{
		cout<<"Can’t remove directory"<<endl;
		return;;
	}
	for(int i=0;i<v.size()-1;i++)
	{
		bool find = false;
		if (v[i] == "..") {
			if (curr->getParent() == NULL) {
				cout << "The system cannot find the path specified" << endl;
				return;
			}
			curr = curr->getParent();
			i++;
		}
		for (unsigned int j = 0; j < curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName() == v[i])
				if (curr->getChildren()[j]->isDir()) {
					curr = (Directory *) curr->getChildren()[j];
					find = true;
				}
		if (!find) {
			cout << "No such file or directory" << endl;
			return;
		}
	}
	bool deleted=false;
	for (unsigned int j = 0; j < curr->getChildren().size(); j++)
		if (curr->getChildren()[j]->getName() == toRemove)
		{
			deleted=true;
			if (curr->getChildren()[j]->isDir())
				removeDirectory((Directory&)curr->getChildren()[j]);///roy check this line pls
			else
				delete curr->getChildren()[j];
		}
	if(!deleted)
		cout << "No such file or directory" << endl;
}


string RmCommand::toString() const
{
	return "rm "+getArgs();
}

BaseCommand *RmCommand::clone() const
{
	return new RmCommand(getArgs());
}

void RmCommand::removeDirectory(Directory d)
{
	for(int i=0;i<d.getChildren().size();i++){
		if(d.getChildren()[i]->isDir())
			removeDirectory((Directory&)d.getChildren()[i]);
		else
			delete d.getChildren()[i];
	}
	delete &d;
}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) :
		BaseCommand(move(args)), history(history)
{
}

void HistoryCommand::execute(FileSystem &fs)
{
	for (unsigned int i=0; i<history.size(); i++)
		cout<<i<<'\t'<<history[i]->toString()<<endl;
}

string HistoryCommand::toString() const
{
	return "history";
}

BaseCommand *HistoryCommand::clone() const
{
	return new HistoryCommand(getArgs(), history);
}

VerboseCommand::VerboseCommand(string args) : BaseCommand(move(args))
{
}

void VerboseCommand::execute(FileSystem &fs)
{
	int temp=stoi(getArgs(), nullptr, 10);
	if (temp<0 || temp>3)
		cout<<"Wrong verbose input"<<endl;
	else
		verbose=static_cast<unsigned int>(temp);
}

string VerboseCommand::toString() const
{
	return "verbose "+getArgs();
}

BaseCommand *VerboseCommand::clone() const
{
	return new VerboseCommand(getArgs());
}

ErrorCommand::ErrorCommand(string args) : BaseCommand(move(args))
{
}

void ErrorCommand::execute(FileSystem &fs)
{
	cout<<getArgs()<<": Unknown command"<<endl;
}

string ErrorCommand::toString() const
{
	return getArgs();
}

BaseCommand *ErrorCommand::clone() const
{
	return new ErrorCommand(getArgs());
}

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(move(args)), history(history)
{
}

void ExecCommand::execute(FileSystem &fs)
{
	int temp=stoi(getArgs(), nullptr, 10);
	if (temp<0 || temp>=(int)history.size())
		cout<<"Command not found"<<endl;
	else
		history[temp]->execute(fs);
}

string ExecCommand::toString() const
{
	return "exex "+getArgs();
}

BaseCommand *ExecCommand::clone() const
{
	return new ExecCommand(getArgs(), history);
}
