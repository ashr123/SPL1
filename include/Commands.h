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
	string getArgs();
	virtual void execute(FileSystem &fs) = 0;
	virtual string toString() = 0;
};

class PwdCommand : public BaseCommand
{
public:
	PwdCommand(string args);
	void execute(FileSystem &fs); // Every derived class should implement this function according to the document (pdf)
	virtual string toString();
};

class CdCommand : public BaseCommand
{
public:
	CdCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class LsCommand : public BaseCommand
{
public:
	LsCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class MkdirCommand : public BaseCommand
{
public:
	MkdirCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class MkfileCommand : public BaseCommand
{
public:
	MkfileCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class CpCommand : public BaseCommand
{
public:
	CpCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class MvCommand : public BaseCommand
{
public:
	MvCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class RenameCommand : public BaseCommand
{
public:
	RenameCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class RmCommand : public BaseCommand
{
public:
	RmCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class HistoryCommand : public BaseCommand
{
private:
	const vector<BaseCommand *> &history;

public:
	HistoryCommand(string args, const vector<BaseCommand *> &history);
	void execute(FileSystem &fs);
	string toString();
};


class VerboseCommand : public BaseCommand
{
public:
	VerboseCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class ErrorCommand : public BaseCommand
{
public:
	ErrorCommand(string args);
	void execute(FileSystem &fs);
	string toString();
};

class ExecCommand : public BaseCommand
{
private:
	const vector<BaseCommand *> &history;

public:
	ExecCommand(string args, const vector<BaseCommand *> &history);
	void execute(FileSystem &fs);
	string toString();
};

#endif