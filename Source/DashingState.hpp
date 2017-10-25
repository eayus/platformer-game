#pragma once

#include "PlayerState.hpp"

class DashingState : public PlayerState
{
public:
	void update(Player& player) override;

private:
	unsigned int m_dashTimer;

};
