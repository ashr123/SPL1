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
	 * Copy Constructor
	 * @param other the other FileSystem
	 */
	FileSystem(const FileSystem &other);

	/**
	 * Move Constructor
	 * @param other the other FileSystem
	 */
	FileSystem(FileSystem &&other);

	/**
	 * Copy Assignment
	 * @param other the other FileSystem
	 * @return this reference (after coping)
	 */
	FileSystem &operator=(const FileSystem &other);

	/**
	 * Move Assignment
	 * @param other the other FileSystem
	 * @return this reference (after assignmenting)
	 */
	FileSystem &operator=(FileSystem &&other);

	/**
	 * Destructor
	 */
	virtual ~FileSystem();

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