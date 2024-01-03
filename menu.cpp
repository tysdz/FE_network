#include <SFML/Graphics.hpp>
#include <iostream>

const int MENU_COUNT = 5;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int MENU_WIDTH = 600;
const int MENU_HEIGHT = 400;
const int MENU_ITEM_HEIGHT = MENU_HEIGHT / MENU_COUNT;

const std::string menuItems[MENU_COUNT] = {
    "PLAY ONLINE",
    "PLAY WITH FRIEND",
    "SHOW HISTORY",
    "SHOW RANK",
    "EXIT"
};

enum MenuItem {
    PLAY_ONLINE,
    PLAY_WITH_FRIEND,
    VIEW_HISTORY,
    VIEW_RANK,
    EXIT
};

void drawMenuItem(sf::RenderWindow& window, const std::string& text, int index, int selected) {
    sf::Font font;
    if (!font.loadFromFile("SEA.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    sf::Text menuItem(text, font, 40);
    menuItem.setPosition((WINDOW_WIDTH - MENU_WIDTH) / 2 + 10, (WINDOW_HEIGHT - MENU_HEIGHT) / 2 + index * MENU_ITEM_HEIGHT);

    if (index == selected) {
        menuItem.setFillColor(sf::Color::Red);
    } else {
        menuItem.setFillColor(sf::Color::Black);
    }

    window.draw(menuItem);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BattleShip");

    int selectedMenuItem = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedMenuItem = (selectedMenuItem - 1 + MENU_COUNT) % MENU_COUNT;
                } else if (event.key.code == sf::Keyboard::Down) {
                    selectedMenuItem = (selectedMenuItem + 1) % MENU_COUNT;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    switch (selectedMenuItem) {
                        case PLAY_ONLINE:
                            std::cout << "Selected: PLAY ONLINE" << std::endl;
                            break;
                        case PLAY_WITH_FRIEND:
                            std::cout << "Selected: PLAY_WITH_FRIEND" << std::endl;
                            break;
                        case VIEW_HISTORY:
                            std::cout << "Selected: VIEW_HISTORY" << std::endl;
                            break;
                        case VIEW_RANK:
                            std::cout << "Selected: VIEW_RANK" << std::endl;
                            break;
                        case EXIT:
                            window.close();
                            break;
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw the game title
        sf::Font font;
        if (font.loadFromFile("SEA.ttf")) {
            sf::Text title("BattleShip", font, 50);
            title.setPosition((WINDOW_WIDTH - title.getLocalBounds().width) / 2, 50);
            window.draw(title);
        }

        // Draw menu frame
        sf::RectangleShape menuFrame(sf::Vector2f(MENU_WIDTH, MENU_HEIGHT));
        menuFrame.setFillColor(sf::Color::Transparent);
        menuFrame.setOutlineColor(sf::Color::Black);
        menuFrame.setOutlineThickness(2.0f);
        menuFrame.setPosition((WINDOW_WIDTH - MENU_WIDTH) / 2, (WINDOW_HEIGHT - MENU_HEIGHT) / 2);
        window.draw(menuFrame);

        // Draw menu items
        for (int i = 0; i < MENU_COUNT; ++i) {
            drawMenuItem(window, std::to_string(i + 1) + ". " + menuItems[i], i, selectedMenuItem);
        }

        window.display();
    }

    return 0;
}
