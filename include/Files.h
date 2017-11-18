#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>

using namespace std;

/**
 * This is an abstract class for File and Directory
 */
class BaseFile
{
private:
	string name;

public:
	/**
	 * Constructor
	 * @param name the name of the file or directory
	 */
	BaseFile(string name);
	
	/**
	 * @return the name of the file or directory
	 */
	string getName() const;
	
	/**
	 * changes the name of the file or directory
	 * @param newName the new name to be changed into
	 */
	void setName(string newName);
	
	virtual int getSize() const =0;
	
	virtual bool isDir() const =0;
	
	virtual ~BaseFile();
};

/**
 * Represents a single file in the system
 */
class File : public BaseFile
{
private:
	int size;

public:
	/**
	 * Constructor
	 * @param name the name of the file
	 * @param size the size of the file
	 */
	File(string name, int size);
	
	/**
	 * @return the size of the file
	 */
	int getSize() const;
	
	virtual bool isDir() const;
};

/**
 * Represents a single folder in the system
 */
class Directory : public BaseFile
{
private:
	vector<BaseFile *> children;
	Directory *parent;
	
	/**
	 * Coping children
	 * @param other the other Directory
	 */
	void copy(const Directory &other);
	
	void clear();

public:
	/**
	 * Constructor
	 * @param name the name of the directory
	 * @param parent the parent directory
	 */
	Directory(string name, Directory *parent);
	
	/**
	 * Copy Constructor
	 * @param other the other directory
	 */
	Directory(const Directory &other);
	
	/**
	 * Move Constructor
	 * @param other the other directory
	 */
	Directory(Directory &&other);
	
	/**
	 * Copy Assignment
	 * @param other the other directory
	 * @return this reference (after coping)
	 */
	Directory &operator=(const Directory &other);
	
	/**
	 * Move Assignment
	 * @param other the other directory
	 * @return this reference (after assignmenting)
	 */
	Directory &operator=(Directory &&other);
	
	/**
	 * Destructor
	 */
	virtual ~Directory();
	
	/**
	 * @return a pointer to the parent of this directory
	 */
	Directory *getParent() const;
	
	/**
	 * Change the parent of this directory
	 * @param newParent the new parent directory
	 */
	void setParent(Directory *newParent);
	
	/**
	 * Add the file to children
	 * @param file the new file to add
	 */
	void addFile(BaseFile *file);
	
	/**
	 * Remove the file with the specified name from children
	 * @param name the name of the file to be removed
	 */
	void removeFile(string name);
	
	/**
	 * Remove the file from children
	 * @param file the file to be removed
	 */
	void removeFile(BaseFile *file);
	
	/**
	 * Sort children by name alphabetically (not recursively)
	 */
	void sortByName();
	
	/**
	 * Sort children by size (not recursively)
	 */
	void sortBySize();
	
	/**
	 * @return children
	 */
	vector<BaseFile *> getChildren() const;
	
	/**
	 * @return the size of the directory (recursively)
	 */
	int getSize() const;
	
	/**
	 * @return the path from the root to this
	 */
	string getAbsolutePath() const;
	
	virtual bool isDir() const;
};

#endif