//
// Created by roy on 11/11/17.
//

#include <iostream>
#include <sstream>
#include "../include/Commands.h"

BaseCommand::BaseCommand(string args) : args(args)
{
}

string BaseCommand::getArgs() const
{
	return args;
}

Directory *BaseCommand::getPath(istringstream str, FileSystem &fs) {
    string s;
    getline(str, s, '/');
    if(s==".."|s==".")
        do{//Relative path
            if(s=="..")
            {
                fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
            }
            else
            if(s==".") {
                string tmp;
                bool find=false;
                getline(str, tmp, '/');
                for(int i=0;i<fs.getWorkingDirectory().getChildren().size();i++)
                    if(fs.getWorkingDirectory().getChildren().at(i)->getName()==tmp)
                        if(fs.getWorkingDirectory().getChildren().at(i)->isDir()) {
                            fs.setWorkingDirectory(
                                    dynamic_cast<Directory *>(fs.getWorkingDirectory().getChildren().at(i)));
                            find = true;
                        }
                if(!find)
                    return NULL;
            }
            else{

            }

        }while (getline(str, s, '/'));
    else {//Absolute path
        fs.setWorkingDirectory(&fs.getRootDirectory());
        do {
            bool find=false;
            for(int i=0;i<fs.getWorkingDirectory().getChildren().size();i++)
                if(fs.getWorkingDirectory().getChildren().at(i)->getName()==s){
                    if(fs.getWorkingDirectory().getChildren().at(i)->isDir()) {
                        fs.setWorkingDirectory(
                                dynamic_cast<Directory *>(fs.getWorkingDirectory().getChildren().at(i)));
                        find = true;
                    }
                }
            if(!find)
                return NULL;
        }while (getline(str, s, '/'));
    }
    return &fs.getWorkingDirectory();
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
    istringstream str(getArgs());
    if(!getPath(str,fs))
        cout<<"The system cannot find the path specified"<<endl;
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
    vector<BaseFile*> vec=fs.getWorkingDirectory().getChildren();
    for(int i=0;i<vec.size();i++){
        if(vec.at(i)->isDir());
            cout<<"DIR"<<"\t"<<vec.at(i)->getName()<<"\t"<<vec.at(i)->getSize()<<endl;
        cout<<"FILE"<<"\t"<<vec.at(i)->getName()<<"\t"<<vec.at(i)->getSize()<<endl;
    }
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