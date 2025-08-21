#include <SFML/Graphics.hpp>
#include <random>
#include <functional>
#include <algorithm>

#include "Utils/Logging.hpp"
#include "Level.hpp"
#include <iostream>

#include "TileSet.hpp"
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "FireBall.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"


int main() {

    sf::RenderWindow window(sf::VideoMode({config::window_width, config::window_height}), "My Game!");
    window.setVerticalSyncEnabled(true);

    TileSet tileset("Maps/tileset.tsx");
    Level level("Maps/map.tmx", &tileset);

    std::default_random_engine gen;
    std::uniform_int_distribution<int> distX(0, 1500);
    auto rainX = std::bind(distX, gen);

    sf::Texture* rainTex = ResourceManager::getTexture("Assets/Rain.png");
    sf::Sprite rainSprite(*rainTex);
    std::vector<sf::Vector2f> rains;
    
    while (window.isOpen()) {

        while (const auto ev = window.pollEvent()) {

            if (ev->is<sf::Event::Closed>())
                window.close();

			if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>()) {
			
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();

				else if (keyPressed->scancode == sf::Keyboard::Scancode::U)
					level.createObject(std::make_unique<Enemy>(sf::Vector2i(300, 300), &level));
			}

        }

        window.clear(sf::Color::White);
        

        //window.draw(bg);
        level.update();
        level.render(window);
        
        rains.push_back(sf::Vector2f(rainX(), 0));
        
        rains.erase(std::remove_if(rains.begin(), rains.end(), [](auto& rain) {
            return (rain.x < 0 || rain.y > 640);
        } ), rains.end());

        for (auto& rain : rains) {
            rain += sf::Vector2f(-2, 8);
            rainSprite.setPosition(rain);
            window.draw(rainSprite);
        }

        window.display();

    }

}
