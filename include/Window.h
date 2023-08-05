//
// Created by rav on 05.08.23.
//

#ifndef SPACE_SHOOTER_WINDOW_H
#define SPACE_SHOOTER_WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    // Construct the game window with the given title and size
    Window(const std::string& title, sf::Vector2u size);

    // Process window events (like close button, resizing, etc.)
    void processEvents();

    // Update the view to follow the given position
    void updateView(const sf::Vector2f& position);

    // Clear the window
    void clear();

    // Draw a drawable object (like a sprite or shape) to the window
    void draw(const sf::Drawable& drawable);
    // Display the drawn objects
    void display();
    // Check if the window is open
    bool isOpen() const;

    sf::Vector2u getSize() const;

    sf::RenderWindow& getRenderWindow();

private:
    sf::RenderWindow window_;
    sf::View view_;
    int framerate_;
};


#endif //SPACE_SHOOTER_WINDOW_H
