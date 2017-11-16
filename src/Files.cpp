//
// Created by roy on 09/11/17.
//

#include <algorithm>
#include "../include/Files.h"

using namespace std;

BaseFile::BaseFile(string name) : name(new string(move(name)))
{
}

string BaseFile::getName() const
{
	return *name;
}

void BaseFile::setName(string newName)
{
	*name=move(newName);
}

BaseFile::~BaseFile()
{
	clear();
}

//void BaseFile::copy(const BaseFile &other)
//{
//	name=new string(*other.name);
//}

void BaseFile::clear()
{
	delete name;
	name=nullptr;
}

BaseFile::BaseFile(const BaseFile &other) : name(new string(*other.name))
{
	//copy(other);
}

BaseFile::BaseFile(BaseFile &&other) : name(other.name)
{
	other.name=nullptr;
}

BaseFile &BaseFile::operator=(const BaseFile &other)
{
	if (this!=&other)
	{
		clear();
		//copy(other);
		name=new string(*other.name);
	}
	
	return *this;
}

BaseFile &BaseFile::operator=(BaseFile &&other)
{
	if (this!=&other)
	{
		clear();
		name=other.name;
		other.name=nullptr;
	}
	
	return *this;
}


File::File(string name, int size) : BaseFile(move(name)), size(size)
{
}

int File::getSize() const
{
	return size;
}

bool File::isFile() const
{
	return true;
}

bool File::isDir() const
{
	return false;
}

Directory::Directory(string name, Directory *parent) : BaseFile(move(name)), parent(parent), children()
{
}

void Directory::copy(const Directory &other)
{
	setName(other.getName());
	parent=new Directory(*other.parent);
	children=other.children;
}

void Directory::clear()
{
	for (auto &child : children)
		delete child;
}

Directory::Directory(const Directory &other) : BaseFile(other), children(other.children), parent(new Directory(*other.parent))
{
}

Directory::Directory(Directory &&other) : BaseFile(move(other)), parent(other.parent), children(move(other.children))
{
	other.parent=nullptr;
}

Directory &Directory::operator=(const Directory &other)
{
	if (this!=&other)
	{
		clear();
		//copy(other);
		parent=new Directory(*other.parent);
		setName(other.getName());
		children=other.children;
	}
	
	return *this;
}

Directory &Directory::operator=(Directory &&other)
{
	return <#initializer#>;
}

Directory::~Directory()
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

bool Directory::isFile() const
{
	return false;
}

bool Directory::isDir() const
{
	return true;
}