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
	
	/**
	 * Copy constructor
	 * @param other the other environment
	 */
	Environment(const Environment &other);
	
	/**
	 * Move constructor
	 * @param other the other environment
	 */
	Environment(Environment &&other);
	
	/**
	 * Copy operator
	 * @param other the other environment
	 * @return this reference
	 */
	Environment &operator=(const Environment &other);
	
	/**
	 * Move operator
	 * @param other the other environment
	 * @return this reference
	 */
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