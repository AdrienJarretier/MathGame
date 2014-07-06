#include "ResourcesManagerSFML2_1.hpp"

sf::Texture* TextureManager::getResource(const std::string& fileName, const sf::IntRect &area)
{
	if(m_subrectTextures.find(fileName)==m_subrectTextures.end() || m_subrectTextures[fileName].find(area)==m_subrectTextures[fileName].end())
		loadFromFile(fileName, area);

	if(m_subrectTextures.find(fileName)!=m_subrectTextures.end())
        if(m_subrectTextures[fileName].find(area)!=m_subrectTextures[fileName].end())
            return m_subrectTextures[fileName][area];

    return 0;
}

// static TextureManager* getTextureManager();
// renvoie un pointeur sur une seule instance de TextureManager
TextureManager* TextureManager::getTextureManager()
{
    static TextureManager manager;
    return &manager;
}

void TextureManager::loadFromFile(const std::string& fileName)
{
    sf::Texture* tmpText = new sf::Texture;
    if(tmpText->loadFromFile(fileName))
        m_resources.insert(std::pair<std::string, sf::Texture* >(fileName, tmpText));
    else
    {
        delete tmpText;
        #ifdef DEBUG
            // // std::cout << "CANT LOAD : " << fileName << std::endl;
        #endif
    }
}

void TextureManager::loadFromFile(const std::string &fileName, const sf::IntRect &area)
{
    sf::Texture* tmpText = new sf::Texture;
    tmpText->loadFromFile(fileName);
    map_IntRect_ptrTexture tmpMap;
    tmpMap.insert(std::pair<sf::IntRect, sf::Texture*>(sf::IntRect(), tmpText));
    m_subrectTextures.insert(std::pair<std::string, map_IntRect_ptrTexture >(fileName, tmpMap));
}

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{}

/***********************************************************************************************************/
/*********************************************** FontManager ***********************************************/

FontManager* FontManager::getFontManager()
{
    static FontManager manager;
    return &manager;
}

void FontManager::loadFromFile(const std::string& fileName)
{
    sf::Font* tmpFont = new sf::Font;
    if(tmpFont->loadFromFile(fileName))
        m_resources.insert(std::pair<std::string, sf::Font* >(fileName, tmpFont));
    else
    {
        delete tmpFont;
        #ifdef DEBUG
            // // std::cout << "CANT LOAD : " << fileName << std::endl;
        #endif
    }
}

FontManager::FontManager()
{}

FontManager::~FontManager()
{}
