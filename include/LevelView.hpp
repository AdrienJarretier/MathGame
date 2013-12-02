#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <string>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../files.hpp"
#include "LevelModel.hpp"


class LevelView
{
    public:
        LevelView(const LevelModel& model,  float _scale);
        virtual ~LevelView();
        void draw( sf::RenderTarget& target );
        std::vector<sf::Sprite> getSpriteList () const;
        void loadCoord();
    private:
        LevelView();

        std::vector<sf::Sprite> m_listSprite;
        const LevelModel& m_model;
        static sf::Texture m_texNormal;
        static sf::Texture m_texGoal;
        float m_scale;
        static bool TexturesLoaded;
        static bool loadTex(const char* _filenameNormalText = FilenameNormalPointTex, const char* _filenameGoalText = FilenamePointGoalTex);

};

/****************************************************
**
******************************************************/

inline std::vector<sf::Sprite> LevelView::getSpriteList () const { return m_listSprite;};


/****************************************************
**
******************************************************/

#endif // LEVELVIEW_H
