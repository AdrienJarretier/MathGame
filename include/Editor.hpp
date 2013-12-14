#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "Axis.hpp"
#include "ButtonPerso.hpp"
#include "ConstrueFunction.hpp"
#include "GraphView.hpp"
#include "GravityCircle.hpp"
#include "ManageText.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "PanelEditor.hpp"
#include "Point.hpp"
#include "ScreenLink.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


class Editor
{
    enum class CreatingType {POINT, CIRCLE, ENNEMY};

    public:
        sf::RenderWindow &m_app;
        Editor(sf::RenderWindow& App);
        bool handleInput();
        void draw();
        void zoom();
        void show();
        void reset();
        void resetWindow();
        void move( );
        inline bool isBacked()const { return m_isBack;};
        inline void setBack( bool _b){ m_isBack = _b;};
        inline void setSaving(bool _b){m_saving = _b;};
        void setCenterCamera();
        void managePanel(  int coordMouseX);
        void movePanel ();
        int save(ScreenLink * link);
        void addPoint( int x , int y);
        void addCirle(int x, int y);
        void popPoint();
        void deleteGravityCircle(int x, int y);
        void deletePoint(int x , int y);
        ~Editor();

    private:
        sf::View m_viewPerso;
        sf::Event m_event;
        Axis m_axis;
        ButtonPerso m_buttonReset;
        ButtonPerso m_buttonSave;
        ButtonPerso m_buttonBack;
        ButtonPerso m_buttonCursor;
        ButtonPerso m_buttonGoalButton;
        ButtonPerso m_buttonCircle;
        ButtonPerso m_buttonNormalButton;
        sf::Texture m_Buttonpoint;
        sf::Texture m_Buttongoal;
        CreatingType m_creatingType;
        ConstrueFonction m_graphModel;
        GraphView   m_graphView;
        bool m_isBack;
        bool m_isNormalPoint;
        bool m_isZoom;
        PanelEditor m_panel;
        bool m_saving;
        sf::Sprite m_spriteBG;
        std::vector<EditorObject*> m_spriteList;
        TextAreaSFML2_0 m_textAreaFunction;
        sf::Clock m_timer;
        ManageText m_textVerifSave;

        // HAVE TO IMPROVE IT
        sf::Vector2f m_radiusBuilder;
};
#endif // EDITOR_H
