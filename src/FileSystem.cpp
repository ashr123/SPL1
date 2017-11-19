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

FileSystem::FileSystem() : rootDirectory(new Directory("first", nullptr)), workingDirectory(rootDirectory)
{
}