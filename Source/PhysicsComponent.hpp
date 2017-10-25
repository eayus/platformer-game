#pragma once

#include "Level.hpp"

class Enemy;

class PhysicsComponent
{
public:
	void update(Enemy& e, Level* l);

};
