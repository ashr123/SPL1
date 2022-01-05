//
// Created by roy on 11/11/17.
//

#include <iostream>
#include "../include/FileSystem.h"
#include "../include/Commands.h"

Directory &FileSystem::getRootDirectory() const
{
	return *rootDirectory;
}

Directory &FileSystem::getWorkingDirectory() const
{
	return *workingDirectory;
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory)
{
	workingDirectory = newWorkingDirectory;
}

FileSystem::FileSystem() : rootDirectory(new Directory("/", nullptr)), workingDirectory(rootDirectory)
{
}

FileSystem::FileSystem(const FileSystem &other) : rootDirectory(new Directory(*other.rootDirectory)),
												  workingDirectory(rootDirectory)
{
	if (verbose == 1 || verbose == 3)
		cout << "FileSystem::FileSystem(const FileSystem &other)" << endl;
	CdCommand(other.workingDirectory->getAbsolutePath()).execute(*this);
}

FileSystem::FileSystem(FileSystem &&other) : rootDirectory(other.rootDirectory),
											 workingDirectory(other.workingDirectory)
{
	if (verbose == 1 || verbose == 3)
		cout << "FileSystem::FileSystem(FileSystem &&other)" << endl;
	other.rootDirectory = nullptr;
	other.workingDirectory = nullptr;
}

FileSystem &FileSystem::operator=(const FileSystem &other)
{
	if (verbose == 1 || verbose == 3)
		cout << "FileSystem &FileSystem::operator=(const FileSystem &other)" << endl;
	if (&other != this)
	{
		delete rootDirectory;
		rootDirectory = workingDirectory = nullptr;
		rootDirectory = new Directory(*other.rootDirectory);
		workingDirectory = rootDirectory;
		CdCommand(other.workingDirectory->getAbsolutePath()).execute(*this);
	}
	return *this;
}

FileSystem &FileSystem::operator=(FileSystem &&other)
{
	if (verbose == 1 || verbose == 3)
		cout << "FileSystem &FileSystem::operator=(FileSystem &&other)" << endl;
	if (&other != this)
	{
		delete rootDirectory;
		rootDirectory = workingDirectory = nullptr;
		rootDirectory = new Directory(*other.rootDirectory);
		workingDirectory = new Directory(*other.workingDirectory);
		other.workingDirectory = nullptr;
		other.rootDirectory = nullptr;
	}
	return *this;
}

FileSystem::~FileSystem()
{
	if (verbose == 1 || verbose == 3)
		cout << "FileSystem::~FileSystem()" << endl;
	delete rootDirectory;
}