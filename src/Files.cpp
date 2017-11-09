//
// Created by roy on 09/11/17.
//

#include "../include/Files.h"

using namespace std;

File::File(string name, int size) : size(size), setName(name)
{
}

int File::getSize()
{
	return size;
}

BaseFile::BaseFile(string name) : name(&name)
{

}

string BaseFile::getName() const
{
	return *name;
}

void BaseFile::setName(string newName)
{
	*name=newName;
}

Directory::Directory(string name, Directory *parent) : setName(name), parent(parent)
{
}

Directory *Directory::getParent() const
{
	return parent;
}

void Directory::setParent(Directory *newParent)
{
	parent=newParent;
}

void Directory::addFile(BaseFile *file)
{
	children.push_back(file);
}

void Directory::removeFile(string name)
{
	children.
}

void Directory::removeFile(BaseFile *file)
{

}

void Directory::sortByName()
{

}

void Directory::sortBySize()
{

}

vector<BaseFile *> Directory::getChildren()
{
	return children;
}

int Directory::getSize()
{
	return 0;
}

string Directory::getAbsolutePath()
{
	return std::__cxx11::string();
}