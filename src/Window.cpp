#include "Window.h"

Window::Window(const std::string &title, sf::Vector2u size)
        : window_(sf::VideoMode(size.x, size.y), title),
          view_(sf::FloatRect(0, 0, size.x, size.y)) {
    window_.setView(view_);
    framerate_ = 150;
    window_.setFramerateLimit(framerate_);

    uiView_.setSize(window_.getSize().x, window_.getSize().y);
    uiView_.setCenter(window_.getSize().x / 2, window_.getSize().y / 2);
}

void Window::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)    window_.close();
    }
}

void Window::updateView(const sf::Vector2f &position) {
    view_.setCenter(position);
    window_.setView(view_);
}

void Window::clear() { window_.clear(); }

// Draw a drawable object (like a sprite or shape) to the window
void Window::draw(const sf::Drawable& drawable) { window_.draw(drawable); }

// Display the drawn objects
void Window::display() { window_.display(); }

// Check if the window is open
bool Window::isOpen() const { return window_.isOpen(); }

sf::Vector2u Window::getSize() const { return window_.getSize(); }

sf::RenderWindow &Window::getRenderWindow() { return window_; }

void Window::setUiView() { window_.setView(uiView_); }