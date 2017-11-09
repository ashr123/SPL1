//
// Created by roy on 09/11/17.
//

#include "../include/Files.h"
using namespace std;

File::File(string name, int size): this.size(size), setName(name){

}

int File::getSize() {
    return size;
};
