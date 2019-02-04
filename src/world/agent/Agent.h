/*
 * Agent.h
 *
 *  Created on: 2019/01/18
 *      Author: yusuke
 */

#ifndef SRC_WORLD_AGENT_H_
#define SRC_WORLD_AGENT_H_

class Environment;

#include <string>
#include <list>
#include <Object.h>

class Agent : public Object {
private:
	std::list<Environment *> envs;
public:
	Agent();
	virtual ~Agent();

	virtual void action() {} // The agent actions that affects the environment as output.

	virtual void env_in( Environment* env ) {
		this->envs.push_back( env );
	}

	virtual void env_out( Environment* env ) {
	}
};

#endif /* SRC_WORLD_AGENT_H_ */
