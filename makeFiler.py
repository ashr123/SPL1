import os

pName=raw_input('What is the name of the Program? ')
file=open('makefile', 'w')
l={}
names=''
for fil in os.listdir(os.getcwd()+'/src'):
	root, ext=os.path.splitext(fil)
	if ext=='.cpp':
		l[root+'.cpp']=root+'.o'
		names+='bin/'+root+'.o '

file.write("GREEN=\\e[103m\\033[1;34m\n")
file.write("NC=\\033[0m\n")
file.write('CC= g++\n')
file.write('CFLAGS=-g -Wall -Weffc++ -std=c++11\n')
file.write('LFLAGS=-L/usr/lib\n\n')
file.write('all: '+pName+'\n'+pName+": "+names)
file.write('\n\t'+"@echo 'Building target: "+pName+"'\n")
file.write("\t@echo 'Invoking: C++ Linker'\n")
file.write("\t$(CC) -o bin/"+pName+' '+names+"$(LFLAGS)\n")
file.write("\t@echo 'Finished building target: "+pName+"'\n\n")

for key in l.keys():
	file.write('bin/'+l[key]+': src/'+key+'\n')
	file.write("\t@echo -e '${GREEN}Compiling target: "+key+"${NC}'\n")
	file.write('\t$(CC) $(CFLAGS) -c -Iinclude -o bin/'+l[key]+' src/'+key+'\n')
	file.write("\t@echo ''\n\n")
file.write('clean:\n\trm -f bin/*')
file.close()
print "Finished"
