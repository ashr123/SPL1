#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include "FileSystem.h"

using namespace std;

class BaseCommand
{
private:
	string args;

public:
	BaseCommand(string args);
	
	string getArgs() const;
	
	virtual void execute(FileSystem &fs) = 0;
	
	virtual string toString() const = 0;

};

class PwdCommand : public BaseCommand
{
public:
	PwdCommand(string args);
	
	void execute(FileSystem &fs); // Every derived class should implement this function according to the document (pdf)
	virtual string toString() const;
};

class CdCommand : public BaseCommand
{
public:
	CdCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class LsCommand : public BaseCommand
{
public:
	LsCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class MkdirCommand : public BaseCommand
{
public:
	MkdirCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class MkfileCommand : public BaseCommand
{
public:
	MkfileCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class CpCommand : public BaseCommand
{
public:
	CpCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class MvCommand : public BaseCommand
{
public:
	MvCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class RenameCommand : public BaseCommand
{
public:
	RenameCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class RmCommand : public BaseCommand
{
public:
	RmCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class HistoryCommand : public BaseCommand
{
private:
	const vector<BaseCommand *> &history;

public:
	HistoryCommand(string args, const vector<BaseCommand *> &history);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};


class VerboseCommand : public BaseCommand
{
public:
	VerboseCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class ErrorCommand : public BaseCommand
{
public:
	ErrorCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

class ExecCommand : public BaseCommand
{
private:
	const vector<BaseCommand *> &history;

public:
	ExecCommand(string args, const vector<BaseCommand *> &history);
	
	void execute(FileSystem &fs);
	
	string toString() const;
};

#endif