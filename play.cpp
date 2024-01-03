#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int GRID_SIZE = 10;
const int CELL_SIZE = 50;

enum BoatDirection {
    HORIZONTAL,
    VERTICAL
};

class Boat {
public:
    Boat(int size) : size(size), rotating(false), beingPlaced(true) {
        shape.setSize(sf::Vector2f(size * CELL_SIZE, CELL_SIZE));
        shape.setFillColor(sf::Color::Blue);
        direction = HORIZONTAL;
    }

    void setPosition(const sf::Vector2f& position) {
        shape.setPosition(position);
    }

    void setRotating(bool rotating) {
        this->rotating = rotating;
    }

    bool isRotating() const {
        return rotating;
    }

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape drawableShape = shape;
        if (isRotating()) {
            drawableShape.setSize(sf::Vector2f(CELL_SIZE, size * CELL_SIZE));
        }
        window.draw(drawableShape);
    }

    void setDirection(BoatDirection newDirection) {
        direction = newDirection;
    }

    BoatDirection getDirection() const {
        return direction;
    }

    bool isPlaced() const {
        return !beingPlaced;
    }

    void place() {
        beingPlaced = false;
    }

    void move(int dx, int dy) {
        shape.move(dx, dy);
    }

private:
    sf::RectangleShape shape;
    BoatDirection direction;
    int size;
    bool rotating;
    bool beingPlaced;
};

class Grid {
public:
    Grid() {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                cell.setFillColor(sf::Color::Transparent);
                cell.setOutlineThickness(1.0f);
                cell.setOutlineColor(sf::Color::Black);
                cells.push_back(cell);
            }
        }
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& cell : cells) {
            window.draw(cell);
        }
    }

private:
    std::vector<sf::RectangleShape> cells;
};

void handleKeyPress(const sf::Event& event, std::vector<Boat>& boats, int& selectedBoatIndex);

const int BOAT_SIZES[] = {2, 3, 3, 4, 5};
const int BOAT_COUNT = sizeof(BOAT_SIZES) / sizeof(BOAT_SIZES[0]);

int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * CELL_SIZE * 2, GRID_SIZE * CELL_SIZE), "Boat Puzzle");
    std::vector<Boat> boats;
    for (int i = 0; i < BOAT_COUNT; ++i) {
        boats.emplace_back(BOAT_SIZES[i]);
    }

    Grid grid;

    int selectedBoatIndex = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event, boats, selectedBoatIndex);
            }
        }

        window.clear(sf::Color::White);

        // Draw grid
        grid.draw(window);

        // Draw boats
        for (size_t i = 0; i < boats.size(); ++i) {
            boats[i].draw(window);
        }

        window.display();
    }

    return 0;
}

void handleKeyPress(const sf::Event& event, std::vector<Boat>& boats, int& selectedBoatIndex) {
    switch (event.key.code) {
        case sf::Keyboard::Up:
            boats[selectedBoatIndex].move(0, -CELL_SIZE);
            break;
        case sf::Keyboard::Down:
            boats[selectedBoatIndex].move(0, CELL_SIZE);
            break;
        case sf::Keyboard::Left:
            boats[selectedBoatIndex].move(-CELL_SIZE, 0);
            break;
        case sf::Keyboard::Right:
            boats[selectedBoatIndex].move(CELL_SIZE, 0);
            break;
        case sf::Keyboard::Enter:
            if (boats[selectedBoatIndex].isPlaced()) {
                selectedBoatIndex = (selectedBoatIndex + 1) % boats.size();
            } else {
                boats[selectedBoatIndex].place();
            }
            break;
        case sf::Keyboard::R:
            if (!boats[selectedBoatIndex].isPlaced()) {
                boats[selectedBoatIndex].setRotating(!boats[selectedBoatIndex].isRotating());
            }
            break;
        case sf::Keyboard::D:
            if (!boats[selectedBoatIndex].isPlaced()) {
                boats[selectedBoatIndex].setDirection(BoatDirection::HORIZONTAL);
            }
            break;
        case sf::Keyboard::V:
            if (!boats[selectedBoatIndex].isPlaced()) {
                boats[selectedBoatIndex].setDirection(BoatDirection::VERTICAL);
            }
            break;
        default:
            break;
    }
}
