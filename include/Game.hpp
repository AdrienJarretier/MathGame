#ifndef GAME_H
#define GAME_H

#include <fstream>

#include "SFML/Graphics.hpp"

#include "Axis.hpp"
#include "ButtonAnim.hpp"
#include "../constants.hpp"
#include "CharacterModel.hpp"
#include "CharacterView.hpp"
#include "ConstrueFunction.hpp"
#include "../files.hpp"
#include "GraphView.hpp"
#include "GravityCircle.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "ManageLevel.hpp"
#include "ScreenLink.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


using namespace sf;

class Game
{
    public:
         RenderWindow &m_app;
        Game( RenderWindow& _app, Difficulty _diff = Normal );
        virtual ~Game();
        bool handleInput();
        void draw();
        void move();
        void zoom();
        void resetWindow();
        int levelOperation(ScreenLink& stat);
        void selectLevel(ScreenLink& stat);
        void show();
        void reset();
        void manageSound();
        inline bool isBacked()const { return m_isBack;};
        inline void setBack( bool _b){ m_isBack = _b;};
        inline void setZoom(bool _b){ m_isZoom = _b;};
        void setCenterCamera();
        void loadConfigFile();

    private:
        Axis m_axis;
        ButtonPerso m_buttonReset;
        ButtonAnim m_buttonSound;
        ButtonPerso m_buttonBack;
        bool m_gameStarted;
        bool m_isZoom;
        bool m_isSound;
        bool m_isBack;
        Event m_event;
        ConstrueFunction m_graphModel;
        GraphView m_graphView;
        ManageLevel m_level;
        sf::Clock m_timer;
    #ifdef DEBUG
        int m_frameCount;
        sf::Clock m_frameCountClock;
        sf::Text m_frameCountText;
    #endif
        CharacterModel m_player1Model;
        CharacterView m_player1View;
        Sprite m_spriteBG;
        TextAreaSFML2_0 m_textAreaFunction;
        View m_viewPerso;
        GravityCircle test;
};
#endif // GAME_H
