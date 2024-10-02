#include "WindowMover.hpp"

WindowMover::WindowMover(float gravity, float restitution, float friction)
    : velocityX(0.f), velocityY(0.f), gravity(gravity), restitution(restitution), friction(friction) {
}

void WindowMover::update(sf::RenderWindow& window, float deltaTime) {
    confineToScreen(window, deltaTime); // Confine the window to the screen boundaries

    sf::Vector2i position = window.getPosition();
    position.y += static_cast<int>(velocityY * deltaTime);
    position.x += static_cast<int>(velocityX * deltaTime);
    window.setPosition(position);
    velocityY += gravity * deltaTime; // Apply gravity effect
}

void WindowMover::handleEvent(const sf::Event& event, sf::RenderWindow& window, float deltaTime) {
    static bool dragging = false;
    static sf::Vector2i dragOffset;
    static sf::Vector2i lastPosition;

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x <= window.getSize().x &&
                mousePos.y >= 0 && mousePos.y <= window.getSize().y) {
                dragging = true;
                dragOffset = window.getPosition() - sf::Mouse::getPosition();
                lastPosition = window.getPosition();
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            dragging = false;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (dragging) {
            window.setPosition(sf::Mouse::getPosition() + dragOffset);
            sf::Vector2i currentPosition = window.getPosition();
            velocityX = (currentPosition.x - lastPosition.x) / deltaTime;
            velocityY = (currentPosition.y - lastPosition.y) / deltaTime;
            lastPosition = window.getPosition();
        }
    }
}

void WindowMover::confineToScreen(sf::RenderWindow& window, float deltaTime) {
    sf::Vector2i position = window.getPosition();
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    if (position.x < 0) {
        position.x = 0;
        velocityX = -velocityX * restitution; // Apply restitution effect
    }

    if (position.x + window.getSize().x > desktop.width) {
        position.x = desktop.width - window.getSize().x;
        velocityX = -velocityX * restitution; // Apply restitution effect
    }

    if (position.y < 0) {
        position.y = 0;
        velocityY = -velocityY * restitution; // Apply restitution effect
        velocityX *= friction; // Apply friction effect
    }

    if (position.y + window.getSize().y > desktop.height) {
        position.y = desktop.height - window.getSize().y;
        velocityY = -velocityY * restitution; // Apply restitution effect
        velocityX *= friction; // Apply friction effect
    }

    window.setPosition(position);
}

float WindowMover::getGravity() const { return gravity; }
void WindowMover::setGravity(float value) { gravity = value; }

float WindowMover::getRestitution() const { return restitution; }
void WindowMover::setRestitution(float value) { restitution = value; }

float WindowMover::getFriction() const { return friction; }
void WindowMover::setFriction(float value) { friction = value; }

void WindowMover::draw(sf::RenderWindow& window) {
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(std::min(window.getSize().x, window.getSize().y) / 2.f);
    circle.setPosition(window.getSize().x / 2.f - circle.getRadius(), window.getSize().y / 2.f - circle.getRadius());
    window.draw(circle);
}
