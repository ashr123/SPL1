//
// Created by roy on 11/11/17.
//

#include "../include/FileSystem.h"

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
	workingDirectory=newWorkingDirectory;
}

FileSystem::FileSystem() : rootDirectory(new Directory("root", nullptr)), workingDirectory(rootDirectory)
{
}


FileSystem::FileSystem(const FileSystem &other) : rootDirectory(new Directory(*other.rootDirectory)), workingDirectory(new Directory(*other.workingDirectory))
{
}

FileSystem::FileSystem(FileSystem &&other) : rootDirectory(other.rootDirectory), workingDirectory(other.workingDirectory)
{
	other.rootDirectory= nullptr;
	other.workingDirectory= nullptr;
}

FileSystem &FileSystem::operator=(const FileSystem &other) {
	if(&other!=this)
	{
		delete rootDirectory;
		rootDirectory=workingDirectory= nullptr;
		rootDirectory=new Directory(*other.rootDirectory);
		workingDirectory=new Directory(*other.workingDirectory);
	}
	return *this;
}

FileSystem &FileSystem::operator=(FileSystem &&other)
{
	if(&other!=this)
	{
		delete rootDirectory;
		rootDirectory=workingDirectory= nullptr;
		rootDirectory=new Directory(*other.rootDirectory);
		workingDirectory=new Directory(*other.workingDirectory);
		other.workingDirectory= nullptr;
		other.rootDirectory= nullptr;
	}
	return *this;
}

FileSystem::~FileSystem() {

}


