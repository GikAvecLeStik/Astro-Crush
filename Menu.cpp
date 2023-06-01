#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include "Menu.hpp"
#include "Player.hpp"


Player player;
Menu::Menu()
    : m_window(sf::VideoMode(1280, 720), "SFML Menu Example")
    , m_currentState(Option::MainMenu)
{
    m_window.setFramerateLimit(60);

    //fondo del menu
    if (!m_backgroundTexture.loadFromFile("Textures/menu.png"))
    {
        std::cout << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(m_window.getSize().x / static_cast<float>(m_backgroundTexture.getSize().x),m_window.getSize().y / static_cast<float>(m_backgroundTexture.getSize().y));

    //fondo del juego
    if (!m_background2Texture.loadFromFile("Textures/espacio.png"))
    {
        std::cout << "Error al cargar la imagen de fondo." << std::endl;
        return;
    }
    m_background2Sprite.setTexture(m_background2Texture);
    m_background2Sprite.setScale(
        m_window.getSize().x / static_cast<float>(m_background2Texture.getSize().x),
        m_window.getSize().y / static_cast<float>(m_background2Texture.getSize().y));

    //fondo de instrucciones
    if (!m_instructionsTexture.loadFromFile("Textures/menu2.png"))
    {
        std::cout << "Error al cargar la imagen de instrucciones." << std::endl;
        return;
    }
    m_instructionsSprite.setTexture(m_instructionsTexture);

    //fondo de creditos
    if (!m_creditsTexture.loadFromFile("Textures/menu3.png"))
    {
        std::cout << "Error al cargar la imagen de créditos." << std::endl;
        return;
    }
    m_creditsSprite.setTexture(m_creditsTexture);

    if (!m_font.loadFromFile("Fonts/Pixelated Regular.ttf"))
    {
        std::cout << "Error al cargar la fuente." << std::endl;
        return;
    }

    //musica del menu
    if (!m_menuMusic.openFromFile("Sounds/melodyloops-preview-breathe-easy-8bit-1m5s.ogg"))
    {
        std::cout << "Error al cargar el archivo de música del menú." << std::endl;
        return;
    }
    m_menuMusic.setLoop(true);

    //musica del juego
    if (!m_gameMusic.openFromFile("Sounds/melodyloops-preview-8-bit-trance-0m55s.ogg"))
    {
        std::cout << "Error al cargar el archivo de música del juego." << std::endl;
        return;
    }
    m_gameMusic.setLoop(true);
}



void Menu::run()
{
    m_menuMusic.play();

    while (m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }

    m_menuMusic.stop();
}

void Menu::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (m_currentState == Option::MainMenu)
                {
                    m_window.close();
                }
                else
                {
                    m_currentState = Option::MainMenu;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                switch (m_currentState)
                {
                case Option::MainMenu:
                    handleMainMenuClick(x, y);
                    break;
                case Option::Instructions:
                    handleReturnClick(x, y);
                    break;
                case Option::Credits:
                    handleReturnClick(x, y);
                    break;
                }
            }
        }
    }
}

void Menu::update()
{
    // No se requiere lógica de actualización para este ejemplo
}

void Menu::render()
{
    m_window.clear();

    switch (m_currentState)
    {
    case Option::MainMenu:
        m_window.draw(m_backgroundSprite);

        // Dibujar las opciones del menú principal
        {
            sf::Text playText("Jugar", m_font, 30);
            playText.setPosition(100, 200);
            m_window.draw(playText);
        }

        {
            sf::Text instructionsText("Instrucciones", m_font, 30);
            instructionsText.setPosition(100, 300);
            m_window.draw(instructionsText);
        }

        {
            sf::Text creditsText("Creditos", m_font, 30);
            creditsText.setPosition(100, 400);
            m_window.draw(creditsText);
        }

        {
            sf::Text exitText("Salir", m_font, 30);
            exitText.setPosition(100, 500);
            m_window.draw(exitText);
        }
        break;
    case Option::Instructions:
        m_window.draw(m_instructionsSprite);

        // Dibujar el botón de regresar
        {
            sf::Text returnText("Regresar", m_font, 20);
            returnText.setPosition(600, 500);
            m_window.draw(returnText);
        }
        break;

    case Option::Credits:
        m_window.draw(m_creditsSprite);

        // Dibujar el botón de regresar
        {
            sf::Text returnText("Regresar", m_font, 20);
            returnText.setPosition(600, 500);
            m_window.draw(returnText);
        }
        break;
    }

    m_window.display();
}

void Menu::showGame()
{
    m_gameMusic.play();

    runGame(m_window);

    m_gameMusic.stop();

}


void Menu::handleMainMenuClick(int x, int y)
{
    if (x >= 100 && x <= 300 && y >= 200 && y <= 250)
    {
        std::cout << "Iniciar juego" << std::endl;
        // Aquí puedes agregar el código para iniciar el juego

        showGame();
    }
    else if (x >= 100 && x <= 400 && y >= 300 && y <= 350)
    {
        std::cout << "Mostrar instrucciones" << std::endl;
        m_currentState = Option::Instructions;
    }
    else if (x >= 100 && x <= 300 && y >= 400 && y <= 450)
    {
        std::cout << "Mostrar créditos" << std::endl;
        m_currentState = Option::Credits;
    }
    else if (x >= 100 && x <= 300 && y >= 500 && y <= 550)
    {
        std::cout << "Salir del juego" << std::endl;
        m_window.close();
    }
}



void Menu::handleReturnClick(int x, int y)
{
    if (x >= 600 && x <= 700 && y >= 500 && y <= 550)
    {
        std::cout << "Regresar al menú principal" << std::endl;
        m_currentState = Option::MainMenu;
    }
}
