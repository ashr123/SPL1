//
// Created by roy on 09/11/17.
//

#include <algorithm>
#include "../include/Files.h"

using namespace std;

BaseFile::BaseFile(string name) : name(move(name))
{
}

string BaseFile::getName() const
{
	return name;
}

void BaseFile::setName(string newName)
{
	name=move(newName);
}

BaseFile::~BaseFile()
{
}


File::File(string name, int size) : BaseFile(move(name)), size(size)
{
}

int File::getSize() const
{
	return size;
}

bool File::isDir() const
{
	return false;
}

Directory::Directory(string name, Directory *parent) : BaseFile(move(name)), children(), parent(parent)
{
}

void Directory::copy(const Directory &other)
{
	for (auto &child : other.children)
		if (dynamic_cast<Directory *>(child))
		{
			children.push_back(new Directory(*(Directory *)child));
			((Directory *)children[children.size()-1])->setParent(this);
		}
		else
			children.push_back(new File(*(File *)child));
}

void Directory::clear()
{
	for (auto &child : children)
		delete child;
//	for (unsigned int i=0; i<children.size(); i++)
//	{
//		delete children[i];
//		children.erase(children.begin());
//	}
	children.erase(children.begin(), children.end());
}

Directory::Directory(const Directory &other) : BaseFile(other), children(), parent(other.parent)
{
	copy(other);
}

Directory::Directory(Directory &&other) : BaseFile(other), children(), parent(other.parent)
{
	copy(other);
	other.parent=nullptr;
}

Directory &Directory::operator=(const Directory &other)
{
	if (this!=&other)
	{
		clear();
		copy(other);
		parent=other.parent;
		setName(other.getName());
	}
	
	return *this;
}

Directory &Directory::operator=(Directory &&other)
{
	if (this!=&other)
	{
		clear();
		copy(other);
		parent=other.parent;
		setName(other.getName());
		other.parent=nullptr;
	}
	
	return *this;
}

Directory::~Directory()
{
	clear();
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
	for (unsigned int i=0; i<children.size(); i++)
		if (children[i]->getName()==name)
		{
			delete children[i];
			children.erase(children.begin()+i);
			return;
		}
}

void Directory::removeFile(BaseFile *file)
{
	for (unsigned int i=0; i<children.size(); i++)
		if (children[i]==file)
		{
			delete children[i];
			children.erase(children.begin()+i);
			return;
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

vector<BaseFile *> Directory::getChildren() const
{
	return children;
}

int Directory::getSize() const
{
	int sum(0);
	for (auto &baseFile : children)
		sum+=baseFile->getSize();
	return sum;
}

string Directory::getAbsolutePath() const
{
	if (parent==nullptr)
		return '/'+getName();
	return parent->getAbsolutePath()+'/'+getName();
}

bool Directory::isDir() const
{
	return true;
}