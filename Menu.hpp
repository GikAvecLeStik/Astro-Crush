#pragma once
#include <iostream>


enum class Option { MainMenu, Game , Instructions, Credits };

class Menu
{
public:
    Menu();

    void run();

private:
    void processEvents();
    void update();
    void render();
    void showGame();
    void handleMainMenuClick(int x, int y);
    void handleReturnClick(int x, int y);

    sf::RenderWindow m_window;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Texture m_background2Texture;
    sf::Sprite m_background2Sprite;
    sf::Texture m_instructionsTexture;
    sf::Sprite m_instructionsSprite;
    sf::Texture m_creditsTexture;
    sf::Sprite m_creditsSprite;
    sf::Font m_font;
    sf::Music m_menuMusic;
    sf::Music m_gameMusic;

    Option m_currentState;
};

