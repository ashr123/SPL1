//
// Created by roy on 09/11/17.
//

#include "../include/Files.h"
using namespace std;

File::File(string name, int size) : size(size), setName(name)
{
};

int File::getSize()
{
    return size;
};

BaseFile::BaseFile(string name)
{

}

string BaseFile::getName() const
{
	return std::__cxx11::string();
}

void BaseFile::setName(string newName)
{

}

Directory::Directory(string name, Directory *parent)
{

}

Directory *Directory::getParent() const
{
	return nullptr;
}

void Directory::setParent(Directory *newParent)
{

}

void Directory::addFile(BaseFile *file)
{

}

void Directory::removeFile(string name)
{

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
	return vector<BaseFile *>();
}

int Directory::getSize()
{
	return 0;
}

string Directory::getAbsolutePath()
{
	return std::__cxx11::string();
}