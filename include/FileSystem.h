#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"

using namespace std;

class FileSystem//TODO Rule of 5
{
private:
	Directory *rootDirectory;
	Directory *workingDirectory;
public:
	FileSystem();
	
	/**
	 * @return reference to the root directory
	 */
	Directory &getRootDirectory() const;
	
	/**
	 * @return reference to the working directory
	 */
	Directory &getWorkingDirectory() const;
	
	/**
	 * Change the working directory of the file system
	 * @param newWorkingDirectory the new working directory
	 */
	void setWorkingDirectory(Directory *newWorkingDirectory);
};

#endif