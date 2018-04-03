#include <SFML/Graphics.hpp>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(1300, 900), "Teeko");
    while (window.isOpen())
    {
        // Draw the game board border
        sf::RectangleShape border(sf::Vector2f(1200,800));
        border.setPosition(50,50);
        border.setFillColor(sf::Color(0,0,0,0));
        border.setOutlineThickness(10);
        border.setOutlineColor(sf::Color(0,0,0));

        // Draw the circles
        sf::CircleShape circle[5][5];
        int x,y;
        for(int i = 0; i<5; i++) {
            for(int j = 0; j<5; j++) {
                circle[i][j].setRadius(50);
                circle[i][j].setFillColor(sf::Color::Transparent);
                circle[i][j].setOutlineThickness(3);
                circle[i][j].setOutlineColor(sf::Color(25,25,25));
                circle[i][j].setPosition(70+150*i,70+150*j);
            }
        }

        // Event management
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close button
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(238,192,106)); // Set the background color
        for(int i = 0; i<5; i++) {
            for(int j = 0; j<5; j++)
            window.draw(circle[i][j]);
        }
        window.draw(border);
        window.display();
    }

    return 0;
}