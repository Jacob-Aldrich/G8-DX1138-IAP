#include "Player.h"

//junlong

Player::Player() : Entity("Player", 100, 10, false, 'P')
{

}

Player::~Player()
{

}

Inventory& Player::GetInventory()
{
	return inventory;
}
