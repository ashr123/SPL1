#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment
{
private:
	vector<BaseCommand *> commandsHistory;
	FileSystem fs;

public:
	//Environment();
	void start();
	
	/**
	 * @return a reference to the file system
	 */
	FileSystem &getFileSystem();
	
	/**
	 * Add a new command to the history
	 * @param command the command that to be added
	 */
	void addToHistory(BaseCommand *command);
	
	/**
	 * @return a reference to the history of commands
	 */
	const vector<BaseCommand *> &getHistory() const;
};

#endif