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

void PwdCommand::execute(FileSystem &fs) const
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

void CdCommand::execute(FileSystem &fs) const
{
	istringstream str(getArgs());
	string s;
	bool find;
	if (getArgs()[0]=='/')
	{
		getline(str, s, '/');
		fs.setWorkingDirectory(&fs.getRootDirectory());
		if (getArgs()=="/")
			return;
	}
	;
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
						fs.setWorkingDirectory((Directory *)(fs.getWorkingDirectory().getChildren().at(i)));
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

void LsCommand::execute(FileSystem &fs) const
{
	vector<string> v;
	istringstream str(getArgs());
	string s(getArgs()), order;
	Directory *curr;
	if (s[0]=='-')
	{
		getline(str, order, ' ');
		s=s.size()<3 ? "" : s.substr(3);
	}
	if (!s.empty() && s[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	while (getline(str, s, '/'))
		v.push_back(s);
	for (unsigned int i=0; i<v.size(); i++)
	{
		bool find=false;
		if (v[i]=="..")
		{
			if (curr->getParent()==nullptr)
			{
				cout<<"The system cannot find the path specified"<<endl;
				return;
			}
			curr=curr->getParent();
			continue;
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
	if (order=="-s")
		((Directory *)curr)->sortBySize();
	else
		((Directory *)curr)->sortByName();
	for (unsigned int j=0; j<curr->getChildren().size(); j++)
	{
		if (curr->getChildren()[j]->isDir())
			cout<<"DIR\t"<<curr->getChildren()[j]->getName()<<"\t"<<curr->getChildren()[j]->getSize()<<endl;
		else
			cout<<"FILE\t"<<curr->getChildren()[j]->getName()<<"\t"<<curr->getChildren()[j]->getSize()<<endl;
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

void MkdirCommand::execute(FileSystem &fs) const
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
	
	for (unsigned int i=0; i<c.size(); i++)
	{
		bool find=false;
		if (c[i]=="..")
		{
			if (curr->getParent()==nullptr)
			{
				cout<<"The system cannot find the path specified"<<endl;
				break;
			}
			curr=curr->getParent();
			i++;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==c[i])
			{
				if (i==c.size()-1)
				{
					cout<<"The directory already exists"<<endl;
					return;
				}
				if (curr->getChildren()[j]->isDir())
				{
					curr=(Directory *)curr->getChildren()[j];
					find=true;
				}
				else
				{
					cout<<"The directory already exists"<<endl;
					return;
				}
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

void MkfileCommand::execute(FileSystem &fs) const
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
			if (curr->getParent()==nullptr)
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

void CpCommand::execute(FileSystem &fs) const
{
	vector<string> firstPath, secPath;
	istringstream str(getArgs());
	string firstS, secS, s;
	Directory *curr;
	
	getline(str, firstS, ' ');
	getline(str, secS, ' ');
	
	str=istringstream(firstS);
	//getline(str, s, '/');//for nothing to push
	while (getline(str, s, '/'))
		firstPath.push_back(s);
	
	str=istringstream(secS);
	//getline(str, s, '/');//for nothing to push
	while (getline(str, s, '/'))
		secPath.push_back(s);
	
	//Finding source
	if (firstS[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	
	for (unsigned int i=0; i<firstPath.size()-1; i++)
	{
		bool find=false;
		if (firstPath[i]=="..")
		{
			if (curr->getParent()==nullptr)
			{
				cout<<"No such file or directory"<<endl;
				return;
			}
			curr=curr->getParent();
			continue;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==firstPath[i] && curr->getChildren()[j]->isDir())
			{
				curr=(Directory *)curr->getChildren()[j];
				find=true;
				break;
			}
		if (!find)
		{
			cout<<"No such file or directory"<<endl;
			return;
		}
	}
	BaseFile *source=nullptr;
	for (unsigned int j=0; j<curr->getChildren().size(); j++)
		if (curr->getChildren()[j]->getName()==firstPath[firstPath.size()-1])
		{
			source=curr->getChildren()[j];
			break;
		}
	if (!source)
	{
		cout<<"No such file or directory"<<endl;
		return;
	}
	
	//Finding destination
	if (secS[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	
	for (unsigned int i=0; i<secPath.size(); i++)
	{
		bool find=false;
		if (secPath[i]=="..")
		{
			if (curr->getParent()==nullptr)
			{
				cout<<"No such file or directory"<<endl;
				return;
			}
			curr=curr->getParent();
			continue;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==secPath[i] && curr->getChildren()[j]->isDir())
			{
				curr=(Directory *)curr->getChildren()[j];
				find=true;
				break;
			}
		if (!find)
		{
			cout<<"No such file or directory"<<endl;
			return;
		}
	}
	for (unsigned int i=0; i<curr->getChildren().size(); i++)
		if (curr->getChildren()[i]->getName()==source->getName())
			return;
	if (dynamic_cast<Directory *>(source))
		curr->addFile(new Directory(*(Directory *)source));
	else
		curr->addFile(new File(*(File *)source));
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

void MvCommand::execute(FileSystem &fs) const
{
	vector<string> firstPath, secPath;
	istringstream str(getArgs());
	string firstS, secS, s;
	Directory *curr=nullptr, *sourceParent=nullptr;
	unsigned int sourceLocationAtfirstS=0;
	
	getline(str, firstS, ' ');
	getline(str, secS, ' ');
	
	if (firstS!="/")
	{
		str=istringstream(firstS);
		//getline(str, s, '/');//for nothing to push
		while (getline(str, s, '/'))
			firstPath.push_back(s);
	}
	else
	{
		cout<<"Can’t move directory"<<endl;
		return;
	}
	
	if (secS!="/")
	{
		str=istringstream(secS);
		//getline(str, s, '/');//for nothing to push
		while (getline(str, s, '/'))
			secPath.push_back(s);
	}
	
	if (firstS[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	
	if (fs.getWorkingDirectory().getAbsolutePath().find(firstS)!=string::npos)
	{
		cout<<"Can’t move directory"<<endl;
		return;
	}
	
	for (unsigned int i=0; i<firstPath.size()-1; i++)
	{
		bool find=false;
		if (firstPath[i]=="..")
		{
			if (curr->getParent()==nullptr)
			{
				cout<<"No such file or directory"<<endl;
				return;
			}
			curr=curr->getParent();
			continue;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==firstPath[i] && curr->getChildren()[j]->isDir())
			{
				curr=(Directory *)curr->getChildren()[j];
				find=true;
				break;
			}
		if (!find)
		{
			cout<<"No such file or directory"<<endl;
			return;
		}
	}
	BaseFile *source=nullptr;
	for (unsigned int j=0; j<curr->getChildren().size(); j++)
		if (curr->getChildren()[j]->getName()==firstPath[firstPath.size()-1])
		{
			source=curr->getChildren()[j];
			sourceParent=curr;
			sourceLocationAtfirstS=j;
			break;
		}
	if (!source)
	{
		cout<<"No such file or directory"<<endl;
		return;
	}
	
	//Finding destination
	if (secS[0]=='/')//Absolute path
	{
		curr=&fs.getRootDirectory();
		getline(str, s, '/');
		if (secS=="/")
		{
			curr->addFile(source);
			sourceParent->dropChildAt(sourceLocationAtfirstS);
		}
	}
	else
		curr=&fs.getWorkingDirectory();
	for (unsigned int i=0; i<secPath.size(); i++)
	{
		bool find=false;
		if (secPath[i]=="..")
		{
			if (curr->getParent()==nullptr)
			{
				cout<<"No such file or directory"<<endl;
				return;
			}
			curr=curr->getParent();
			continue;
		}
		for (unsigned int j=0; j<curr->getChildren().size(); j++)
			if (curr->getChildren()[j]->getName()==secPath[i] && curr->getChildren()[j]->isDir())
			{
				curr=(Directory *)curr->getChildren()[j];
				find=true;
				curr->addFile(source);
				sourceParent->dropChildAt(sourceLocationAtfirstS);
				break;
			}
		if (!find)
		{
			cout<<"No such file or directory"<<endl;
			return;
		}
	}
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

void RenameCommand::execute(FileSystem &fs) const
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
	string oldName=v[v.size()-1].substr(0, v[v.size()-1].find(' '));
	string newName=v[v.size()-1].substr(v[v.size()-1].find(' '));
	if (curr->getName()==oldName)
	{
		cout<<"“Can’t rename the working directory"<<endl;
		return;
	}
	for (unsigned int i=0; i<v.size()-1; i++)
	{
		bool find=false;
		if (v[i]=="..")
		{
			if (curr->getParent()==nullptr)
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
	if (!change)
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

void RmCommand::execute(FileSystem &fs) const
{
	vector<string> v;
	istringstream str(getArgs());
	string s(getArgs());
	Directory *curr;
	if (s[0]=='/')
	{
		curr=&fs.getRootDirectory();
		if (s=="/")
		{
			cout<<"Can’t remove directory"<<endl;
			return;
		}
		getline(str, s, '/');
	}
	else
		curr=&fs.getWorkingDirectory();
	while (getline(str, s, '/'))
		v.push_back(s);
	if (fs.getWorkingDirectory().getAbsolutePath().find(v[v.size()-1])!=string::npos)
	{
		cout<<"Can’t remove directory"<<endl;
		return;
	}
	for (unsigned int i=0; i<v.size()-1; i++)
	{
		bool find=false;
		if (v[i]=="..")
		{
			if (curr->getParent()==nullptr)
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
	unsigned long deleted=curr->getChildren().size();
	curr->removeFile(v[v.size()-1]);
	if (curr->getChildren().size()==deleted)
		cout<<"No such file or directory"<<endl;
}


string RmCommand::toString() const
{
	return "rm "+getArgs();
}

BaseCommand *RmCommand::clone() const
{
	return new RmCommand(getArgs());
}

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history) :
		BaseCommand(move(args)), history(history)
{
}

void HistoryCommand::execute(FileSystem &fs) const
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

void VerboseCommand::execute(FileSystem &fs) const
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

void ErrorCommand::execute(FileSystem &fs) const
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

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history) : BaseCommand(move(args)),
                                                                              history(history)
{
}

void ExecCommand::execute(FileSystem &fs) const
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