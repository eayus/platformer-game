#pragma once

#include "Tile.hpp"
#include "TileSet.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include <SFML/Graphics.hpp>

class Level
{
public:
    Level(const char* tmxFilepath, TileSet* tileSet);
    void render(sf::RenderWindow& window);
    void update();
    TileType getTileType(int x, int y);
    TileType getTileTypeAtCoord(int x, int y);
    int roundDownToTileSize(int num);
    void createObject(std::unique_ptr<GameObject> object);


private:
    TileSet* m_tileSet;
    int m_tilesWide;
    int m_tilesHigh;
    std::vector< std::vector<Tile*> > m_map;

    std::vector<std::unique_ptr<GameObject>> m_objects;
    Player m_player;

    sf::Sprite m_bg;
    Camera m_camera;

};
