#include "PhysicsComponent.hpp"

#include "Tile.hpp" 
#include "Enemy.hpp"

void PhysicsComponent::update(Enemy& e, Level* l) {

	//if (e.m_velocity.x == 0) return;
	e.m_velocity.x = 4;

    if (e.m_velocity.x > 6)
        e.m_velocity.x = 6;
    else if (e.m_velocity.x < -6)
        e.m_velocity.x = -6;

    AABB box = e.getBoundingBox();

    int lowerBound = box.y;
    int upperBound = box.y + box.h - 1;

    int distance = 0;

    for (; lowerBound <= upperBound; lowerBound += box.h - 1) {

        TileType type;

        if (e.m_velocity.x > 0) {

            int tileLeft = l->roundDownToTileSize(box.x + box.w + e.m_velocity.x);
            type = l->getTileTypeAtCoord(box.x + box.w + e.m_velocity.x, lowerBound);
            distance = tileLeft - (box.x + box.w);

            if (type == TileType::Solid) {
                e.m_velocity.x = 0;
                e.m_position.x += distance;
            }


        } else if (e.m_velocity.x < 0) {

            int tileRight = l->roundDownToTileSize(box.x + e.m_velocity.x) + 32;
            type = l->getTileTypeAtCoord(box.x + e.m_velocity.x, lowerBound);
            distance = tileRight - box.x;

            if (type == TileType::Solid) {
                e.m_velocity.x = 0;
                e.m_position.x += distance;
            }

        } 

    }

    e.m_position.x += e.m_velocity.x;
    //e.m_velocity.x += e.m_velocity.x > 0 ? -1 : 1;
    e.m_velocity.x = 0;



	// Step Y
	//Gravity;
    e.m_velocity.y += 1;

    if (e.m_velocity.y > 12)
        e.m_velocity.y = 12;

    box = e.getBoundingBox();

    lowerBound = box.x;
    upperBound = box.x + box.w - 1;

    distance = 0;
    e.m_onGround = false;

    for (; lowerBound <= upperBound; lowerBound += box.w - 1) {

        TileType type;

        if (e.m_velocity.y > 0) {

            int tileTop = l->roundDownToTileSize(box.y + box.h + e.m_velocity.y);
            type = l->getTileTypeAtCoord(lowerBound, box.y + box.h + e.m_velocity.y);
            distance = tileTop - (box.y + box.h);

            if (type == TileType::Solid) {
                e.m_velocity.y = 0;
                e.m_position.y += distance;
                e.m_onGround = true;
            }

        } else if (e.m_velocity.y < 0) {
            
            int tileBottom = l->roundDownToTileSize(box.y + e.m_velocity.y) + 32;
            type = l->getTileTypeAtCoord(lowerBound, box.y + e.m_velocity.y);
            distance = tileBottom - box.y;

            if (type == TileType::Solid) {
                e.m_velocity.y = 0;
                e.m_position.y += distance;
            }

        } 

    }

    e.m_position.y += e.m_velocity.y;

	// Step Slope

	box = e.getBoundingBox();
    
    //Left Slope
    if (l->getTileTypeAtCoord(box.x, box.y + box.h - 1) == TileType::LeftSlope) {

        int tileLeft = l->roundDownToTileSize(box.x);
        int tileTop = l->roundDownToTileSize(box.y + box.h - 1);

        //distnace from top right
        if ((tileLeft + 32 - box.x) + (box.y + box.h - tileTop) < 32)
            return;

        e.m_position.y = tileTop - box.h + (box.x - tileLeft);
        e.m_onGround = true;
        e.m_velocity.y = 0;

    }

    //Right Slope
    if (l->getTileTypeAtCoord(box.x + box.w - 1, box.y + box.h - 1) == TileType::RightSlope) {

        int tileLeft = l->roundDownToTileSize(box.x + box.w - 1);
        int tileTop = l->roundDownToTileSize(box.y + box.h - 1);

        if ((box.x + box.w - tileLeft) + (box.y + box.h - tileTop) < 32)
            return;

        e.m_position.y = tileTop - box.h + 32 - ( box.x + box.w - tileLeft);
        e.m_onGround = true;
        e.m_velocity.y = 0;

    }

}


