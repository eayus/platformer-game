#pragma once

#include "DashingState.hpp"

class Player;

class PlayerState
{
public:
	virtual void update(Player& player) = 0;

};
