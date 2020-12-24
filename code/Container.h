#ifndef _CONTAINER_H_
#define _CONTAINER_H_
#include "character.h"
class Container {
public:
	character* character;
	Container* next;
	Container();                  // constructor
};
#endif // _CONTAINER_H_