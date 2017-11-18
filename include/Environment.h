#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

//#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment//TODO Rule of 5
{
private:
	vector<BaseCommand *> commandsHistory;
	FileSystem fs;
	
	void copy(const Environment &other);
	void clear();

public:
	/**
	 * Constuctor
	 */
	Environment();
	
	Environment(const Environment &other);
	
	Environment(Environment &&other);
	
	Environment &operator=(const Environment &other);
	
	Environment &operator=(Environment &&other);
	
	virtual ~Environment();
	
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