/*
 * Object.h
 *
 *  Created on: 2019/01/24
 *      Author: yusuke
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

class Object {
private:
	unsigned int id; // unique id in world.
	static unsigned int cnt;
	std::string name; // name of object.
public:
	Object() : name("") {
		this->id = Object::cnt++;
	}
	Object( const std::string& name )
		: name( name ) {
		this->id = Object::cnt++;
	}
	virtual ~Object();

	virtual void see() {
	}

	virtual void next() {
	}

	// getter
	unsigned int getID() {
		return this->id;
	}
	static unsigned int getCnt() {
		return Object::cnt;
	}
	std::string getName() {
		return this->name;
	}
	// setter
	void setName( const std::string& name ) {
		this->name = name;
	}
};

#endif /* OBJECT_H_ */
