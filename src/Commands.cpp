//
// Created by roy on 11/11/17.
//

#include <iostream>
#include <sstream>
#include "../include/Commands.h"
#include "../include/GlobalVariables.h"

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

BaseCommand * PwdCommand::clone() const
{
	return new PwdCommand(getArgs());
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
	return "cd "+getArgs();
}

BaseCommand *CdCommand::clone() const
{
	return new CdCommand(getArgs());
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
    Directory* curr;
    if(s[0]=='/')//Absolute path
    {
        curr = &fs.getRootDirectory();
        getline(str, s, '/');
    }
    else
        curr = &fs.getWorkingDirectory();
        while(getline(str,s,'/'))
            c.push_back(s);
        bool find= false, exist=false;
        for(int i=0;i<c.size();i++)
        {
            if(c[i]=="..")
            {
                if(curr->getParent()==NULL) {
                    cout << "The system cannot find the path specified" << endl;
                    break;
                }
                curr = curr->getParent();
                i++;
            }
            for(int j=0;j<curr->getChildren().size();j++)
                if(curr->getChildren()[j]->getName()==c[i]) {
                    exist=true;
                    if(curr->getChildren()[j]->isDir()) {
                        curr = (Directory *) curr->getChildren()[j];
                        find = true;
                        if(i==c.size())
                            cout<<"The directory already exists"<<endl;
                    }
                }
            if(!find & !exist)
            {
                curr->addFile(new Directory(c[i],curr));
                curr=(Directory*)curr->getChildren()[curr->getChildren().size()-1];
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
//    string s;
//    istringstream str(getArgs()),t;
//    getline(str,s,' ');
//    if(s[0] != '/')
//        fs.getWorkingDirectory().addFile(new File(s,(int)getline(str,s,' ')));
//    else {
//        fs.setWorkingDirectory(&fs.getRootDirectory());
//        while (getline(str, s, '/')) {
//            for (unsigned int i = 0; i < fs.getWorkingDirectory().getChildren().size(); i++) {
//                if ((fs.getWorkingDirectory().getChildren().at(i)->getName() == s) &
//                    (fs.getWorkingDirectory().getChildren().at(i)->isDir()))
//                    fs.setWorkingDirectory((Directory *) (fs.getWorkingDirectory().getChildren().at(i)));
//                else {
//                    if (s.at(s.size() - 1) >= 0 | s.at(s.size() - 1) <= 9) {
//                        bool find = false;
//                        istringstream k(s);
//                        getline(k, s, ' ');
//                        for (unsigned int i = 0; i < fs.getWorkingDirectory().getChildren().size(); i++)
//                            if ((fs.getWorkingDirectory().getChildren().at(i)->getName() == s) &
//                                (!fs.getWorkingDirectory().getChildren().at(i)->isDir()))
//                                find = true;
//                        if (!find)
//                            fs.getWorkingDirectory().addFile(
//                                    new File(s, (int) getline(k, s, ' ')));//needs to check the casting
//                        else
//                            cout << "File already exists" << endl;
//                    } else
//                        cout << "The system cannot find the path specified" << endl;
//                }
//            }
//        }
//    }
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
    string s;
    istringstream str(getArgs());

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
	if (temp<0 || temp>=history.size())
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
