//
// Created by roy on 09/11/17.
//

#include <algorithm>
#include "../include/Files.h"

using namespace std;

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

File::File(string name, int size) : BaseFile(name), size(size)
{
}

int File::getSize()
{
	return size;
}

Directory::Directory(string name, Directory *parent) : BaseFile(name), parent(parent)
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
	for (int i=0; i<children.size(); i++)
	{
		if (children[i]->getName()==name)
		{
			delete children[i];
			children.erase(children.begin()+i);
			return;
		}
	}
}

void Directory::removeFile(BaseFile *file)
{
	for (int i=0; i<children.size(); i++)
	{
		if (children[i]==file)
		{
			delete children[i];
			children.erase(children.begin()+i);
			return;
		}
	}
}

void Directory::sortByName()
{
	sort(children.begin(), children.end(), [](BaseFile *&baseFile, BaseFile *&baseFile1) -> bool
	{
		return baseFile->getName()>baseFile1->getName();
	});
}

void Directory::sortBySize()
{
	sort(children.begin(), children.end(), [](BaseFile *&baseFile, BaseFile *&baseFile1) -> bool
	{
		return baseFile->getSize()>baseFile1->getSize();
	});
}

vector<BaseFile *> Directory::getChildren()
{
	return children;
}

int Directory::getSize()
{
	int sum(0);
	for (auto &baseFile : children)
		sum+=baseFile->getSize();
	return sum;
}

string Directory::getAbsolutePath()
{
	if (parent==nullptr)
		return '/'+getName();
	return parent->getAbsolutePath()+'/'+getName();
}