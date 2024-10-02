#ifndef WINDOWMOVER_HPP
#define WINDOWMOVER_HPP

#include <SFML/Graphics.hpp>

class WindowMover {
public:
    WindowMover(float gravity, float restitution, float friction);

    void update(sf::RenderWindow& window, float deltaTime);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, float deltaTime);
    void confineToScreen(sf::RenderWindow& window, float deltaTime);

    float getGravity() const;
    void setGravity(float value);

    float getRestitution() const;
    void setRestitution(float value);

    float getFriction() const;
    void setFriction(float value);

    void draw(sf::RenderWindow& window);

private:
    void updateText();

    float velocityX; // Horizontal velocity of the window
    float velocityY; // Vertical velocity of the window
    float gravity;   // Gravity effect on the window
    float restitution; // Coefficient of restitution for the window
    float friction; // Coefficient of friction for the window
    sf::Font font;
    sf::Text gravityText;
    sf::Text restitutionText;
    sf::Text frictionText;
};

#endif // WINDOWMOVER_HPP