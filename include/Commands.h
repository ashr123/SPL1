#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "FileSystem.h"
#include <string>

using namespace std;

class BaseCommand
{
private:
	string args;

public:
	BaseCommand(string args);
	
	string getArgs() const;
	
	/**
	 * Every derived class should implement this function according to the document (pdf)
	 * @param fs the current file system
	 */
	virtual void execute(FileSystem &fs) = 0;
	
	virtual string toString() const = 0;
	
	virtual ~BaseCommand();
	
	virtual BaseCommand *clone() const =0;
};

class PwdCommand : public BaseCommand
{
public:
	PwdCommand(string args);
	
	void execute(FileSystem &fs);
	virtual string toString() const;
	
	virtual BaseCommand *clone() const;
};

class CdCommand : public BaseCommand
{
public:
	CdCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class LsCommand : public BaseCommand
{
public:
	LsCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class MkdirCommand : public BaseCommand
{
public:
	MkdirCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class MkfileCommand : public BaseCommand
{
public:
	MkfileCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class CpCommand : public BaseCommand
{
public:
	CpCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class MvCommand : public BaseCommand
{
public:
	MvCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class RenameCommand : public BaseCommand
{
public:
	RenameCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class RmCommand : public BaseCommand
{
public:
	RmCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class HistoryCommand : public BaseCommand//TODO Rule of 5
{
private:
	const vector<BaseCommand *> &history;

public:
	HistoryCommand(string args, const vector<BaseCommand *> &history);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};


class VerboseCommand : public BaseCommand
{
public:
	VerboseCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class ErrorCommand : public BaseCommand
{
public:
	ErrorCommand(string args);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

class ExecCommand : public BaseCommand//TODO Rule of 5
{
private:
	const vector<BaseCommand *> &history;

public:
	ExecCommand(string args, const vector<BaseCommand *> &history);
	
	void execute(FileSystem &fs);
	
	string toString() const;
	
	virtual BaseCommand * clone() const;
};

#endif