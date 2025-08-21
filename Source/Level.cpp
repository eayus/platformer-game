#include "Level.hpp"
#include "Utils/Logging.hpp"
#include "FireBall.hpp"
#include "ResourceManager.hpp"

#include <algorithm>
#include <pugixml.hpp>
#include <iostream>

Level::Level(const char* tmxFilepath, TileSet* tileSet):
    m_tileSet(tileSet),
    m_player(sf::Vector2i(100, 100), this),
    m_camera(40 * 32, 20 * 32, &m_player) { //Un hardcode the resolution, get it from config file.

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(tmxFilepath);

    Utils::log(result.description());

    m_tilesWide = std::stoi(doc.child("map").attribute("width").value());  
    m_tilesHigh = std::stoi(doc.child("map").attribute("height").value());
    
    for (pugi::xml_node property = doc.child("map").child("properties").child("property"); property; property = property.next_sibling("property")) {

        if (std::string(property.attribute("name").value()) == "background_img")
        m_bg = std::make_unique<sf::Sprite>(*ResourceManager::getTexture(property.attribute("value").value()));

    }


    pugi::xml_node data = doc.child("map").child("layer").child("data");

    for (int i = 0; i < m_tilesHigh; i++)
        m_map.push_back(std::vector<Tile*>{});

    int x = 0;
    int y = 0;

    for (pugi::xml_node tile = data.child("tile"); tile; tile = tile.next_sibling("tile")) {
       
        std::string tileStr(tile.attribute("gid").value());

        if (tileStr == "") {
            
            m_map.at(y).push_back(nullptr);

        } else {

        	m_map.at(y).push_back(&m_tileSet->tiles.at(std::stoi(tileStr) - 1));

        }

        x++;
        if (x >= m_tilesWide) {
            y += 1;
            x = 0;
        }


    }

    auto fireball = std::make_unique<FireBall>(sf::Vector2i(200, 400), sf::Vector2i(5, 0), this);
    m_objects.push_back(std::move(fireball));

    //Unhardcode this:
    m_bg->setScale(sf::Vector2f(2.0f, 2.0f));

}

void Level::update() {
    
    m_player.update();

    for (auto& ob : m_objects)
        ob->update();

	for (auto& ob : m_objects) {
	
		if (ob->getBoundingBox().intersects(m_player.getBoundingBox())) {
			ob->collided(&m_player);
			m_player.collided(ob.get());
		}

		for (auto& ob2 : m_objects) {
			
			if (ob == ob2) continue;

			if (ob->getBoundingBox().intersects(ob2->getBoundingBox())) {
				ob->collided(ob2.get());
				ob2->collided(ob.get());
			}

		}

	}

    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
            [](auto& ob) { return ob->shouldDelete(); }
        ), m_objects.end());

}

void Level::render(sf::RenderWindow& window) {

    m_camera.update();

    //This only needs to be called once in the constructor, but need to pass window to the consutrctor.
    window.setView(*m_camera.getView());
     
    sf::Vector2f camPos = m_camera.getView()->getCenter();
    m_bg->setPosition({0.5f * (camPos.x - 480.0f), 0});
    window.draw(*m_bg);

    for (int i = 0; i < m_tilesHigh; i++) {

        for (int j = 0; j < m_tilesWide; j++) {

            if (m_map.at(i).at(j) == nullptr) continue;
            m_tileSet->sprite->setTextureRect(m_map.at(i).at(j)->textureRect);
            m_tileSet->sprite->setPosition({(float)j * m_tileSet->tileSize, (float)i * m_tileSet->tileSize});
            window.draw(*m_tileSet->sprite); 

        }

    }

    for (auto& ob : m_objects)
        ob->draw(window);

    if (!m_player.shouldDelete()) m_player.draw(window);

}

TileType Level::getTileType(int x, int y) {

    Tile* t = m_map.at(y).at(x);
    
    if (t == nullptr)
        return TileType::Empty;

    else
        return t->type;

}

TileType Level::getTileTypeAtCoord(int x, int y) {

    return this->getTileType(x / 32, y / 32);

}

int Level::roundDownToTileSize(int num) {

    return (num / 32) * 32;

}

void Level::createObject(std::unique_ptr<GameObject> object) {

	m_objects.push_back(std::move(object));

}

std::vector<std::unique_ptr<GameObject>>& Level::getObjects() {

	return m_objects;

}
