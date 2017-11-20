#include <iostream>
#include "../include/Environment.h"
// ... You may not change this file

unsigned int verbose=0;

int main(int, char **)
{
//	Environment env;
//	env.start();
//	File a("ababa", 3), b("qqqqq", 5),
//			c(a);
//	a=b;
//	a=File("sss", 7);
//	Directory *directory=new Directory("first", nullptr);
//	directory->addFile(new Directory("second", directory));
//	directory->addFile(new Directory("third", directory));
//	cout<<directory->getName()<<endl;
//	//directory->removeFile(directory->getChildren()[0]);
//	delete directory;
	
	FileSystem fileSystem;
	MkdirCommand mkdirCommand("/first/second/third");
	mkdirCommand.execute(fileSystem);
	MkfileCommand mkfileCommand("/first/second/third/NewFile 20");
	mkfileCommand.execute(fileSystem);
	CdCommand cdCommand("/first/second");
	cdCommand.execute(fileSystem);
	cout<<fileSystem.getWorkingDirectory().getAbsolutePath()<<endl;
	CdCommand cdCommand1("/..");
	cdCommand1.execute(fileSystem);
	cout<<fileSystem.getWorkingDirectory().getAbsolutePath()<<endl;
	return 0;
}