/*
 * Environments.h
 *
 *  Created on: 2019/01/21
 *      Author: yusuke
 */

#ifndef ENVIRONMENTS_H_
#define ENVIRONMENTS_H_

#include <iostream>
#include <list>
#include <Object.h>

class World : Object {
private:
	std::list<Object *> objs;
public:
	World();
	virtual ~World();

	/* registration of objct */
	void regist(Object* obj) {
		this->objs.push_back( obj );
	}

	void output_name() {
		std::list<Object *>::iterator itr;
		for (itr = this->objs.begin(); itr != this->objs.end(); itr++) {
			Object* pobj = *itr;
			std::cout << pobj->getName() << std::endl;
		}
	}

	void see() {
		std::list<Object *>::iterator itr;
		for (itr = objs.begin(); itr != objs.end(); itr++) {
			Object *obj = *itr;
			obj->see();
		}
	}

	void next() {
		std::list<Object *>::iterator itr;
		for (itr = objs.begin(); itr != objs.end(); itr++) {
			Object *obj = *itr;
			obj->next();
		}
	}
};

#endif /* ENVIRONMENTS_H_ */
