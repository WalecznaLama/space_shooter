#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
public:
    Game() {
        window.create(sf::VideoMode(800, 600), "Space Shooter");
        player.init(window.getSize());
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            update();
            render();
        }
    }

private:
    void update() {
        player.update(window.getSize());
        // TODO: Update game state
    }

    void render() {
        window.clear();
        player.draw(window);
        window.display();
    }

    sf::RenderWindow window;
    Player player;
};

int main() {
    Game game;
    game.run();
    return 0;
}
