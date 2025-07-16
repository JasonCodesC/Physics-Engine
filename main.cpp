#include "Physics.h"
#include "Ball.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <vector>

// Constants
constexpr unsigned int WINDOW_W = 1200;
constexpr unsigned int WINDOW_H = 800;
constexpr float SCALE = 50.0f;
constexpr float PHYSICS_DT = 1.0f / 60.0f;

int main() {
    // Physics world
    Physics phys(Vector2(0.0f, -9.81f), WINDOW_W / SCALE, WINDOW_H / SCALE);

    // Create balls
    std::vector<Ball> balls;
    balls.emplace_back(0.95f, 1.0f, Vector2(3.0f, 9.0f));
    balls.emplace_back(0.95f, 1.0f, Vector2(18.0f, 9.0f));
    balls.emplace_back(0.75f, 0.7f, Vector2(10.0f, 15.0f)); // Third ball

    for (auto& b : balls) {
        phys.addBall(&b);
    }

    // SFML window
    sf::RenderWindow window(sf::VideoMode({WINDOW_W, WINDOW_H}), "2D Physics Drag & Throw");
    window.setFramerateLimit(60);

    // Font for velocity display
    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        // Handle font loading error if necessary
    }

    // Thread synchronization
    std::mutex physicsMutex;
    std::atomic<bool> running(true);

    // Physics thread
    std::thread physicsThread([&] {
        while (running) {
            {
                std::lock_guard<std::mutex> lock(physicsMutex);
                phys.step(PHYSICS_DT);
            }
            std::this_thread::sleep_for(std::chrono::duration<float>(PHYSICS_DT));
        }
    });

    Ball* dragged = nullptr;
    Vector2 lastMouseWorldPos;

    while (window.isOpen()) {
        // Event handling
        while (auto optEvt = window.pollEvent()) {
            const auto& evt = *optEvt;

            if (evt.is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto mbp = evt.getIf<sf::Event::MouseButtonPressed>()) {
                if (mbp->button == sf::Mouse::Button::Left) {
                    Vector2 clickPos(mbp->position.x / SCALE, (WINDOW_H - mbp->position.y) / SCALE);
                    std::lock_guard<std::mutex> lock(physicsMutex);
                    for (auto& b : balls) {
                        if ((b.getPosition() - clickPos).lengthSquared() < b.getRadius() * b.getRadius()) {
                            dragged = &b;
                            lastMouseWorldPos = clickPos;
                            break;
                        }
                    }
                }
            }

            if (auto mbr = evt.getIf<sf::Event::MouseButtonReleased>()) {
                if (mbr->button == sf::Mouse::Button::Left && dragged) {
                    dragged = nullptr;
                }
            }
        }

        // Dragging logic
        if (dragged) {
            sf::Vector2i mp = sf::Mouse::getPosition(window);
            Vector2 worldPos(mp.x / SCALE, (WINDOW_H - mp.y) / SCALE);
            Vector2 dragVel = (worldPos - lastMouseWorldPos) / PHYSICS_DT;
            std::lock_guard<std::mutex> lock(physicsMutex);
            dragged->setPosition(worldPos);
            dragged->setVelocity(dragVel);
            lastMouseWorldPos = worldPos;
        }

        // Rendering
        window.clear(sf::Color::Black);

        std::vector<sf::CircleShape> shapes;
        {
            std::lock_guard<std::mutex> lock(physicsMutex);
            for (const auto& b : balls) {
                sf::CircleShape shape(b.getRadius() * SCALE);
                shape.setOrigin({b.getRadius() * SCALE, b.getRadius() * SCALE});
                shape.setPosition({b.getPosition().x * SCALE, WINDOW_H - b.getPosition().y * SCALE});
                if (&b == &balls[0]) shape.setFillColor(sf::Color::Blue);
                else if (&b == &balls[1]) shape.setFillColor(sf::Color::Yellow);
                else shape.setFillColor(sf::Color::Green); // Third ball color
                shapes.push_back(shape);
            }
        }

        for (const auto& shape : shapes) {
            window.draw(shape);
        }

        // Display velocities
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        int y_offset = 0;
        for (const auto& b : balls) {
            oss.str("");
            oss << "Velocity => (X: " << b.getVelocity().x << ", Y: " << b.getVelocity().y << ")";
            sf::Text text(font, oss.str(), 14);
            text.setPosition({10.f, 10.f + y_offset});
            if (&b == &balls[0]) text.setFillColor(sf::Color::Blue);
            else if (&b == &balls[1]) text.setFillColor(sf::Color::Yellow);
            else text.setFillColor(sf::Color::Green);
            window.draw(text);
            y_offset += 20;
        }

        window.display();
    }

    running = false;
    physicsThread.join();
    return 0;
}
