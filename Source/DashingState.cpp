#include "DashingState.hpp"
#include "Player.hpp"

void DashingState::update(Player& player) {

	if (--m_dashTimer == 0)
		return;
		//player.setState(PlayerState::standing);

}
