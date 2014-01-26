#ifndef TEXTAREASFML2_0_H
#define TEXTAREASFML2_0_H

#ifdef DEBUG
	#include <iostream>
#endif//DEBUG

#include <cctype>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Utf.hpp>
#include <SFML/Window/Event.hpp>

#include "../files.hpp"
#include "../constants.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)
#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)

class TextAreaSFML2_0 : public sf::Drawable
{
	public:
		/** Default constructor */
		TextAreaSFML2_0(unsigned int padding=0U, const sf::Color& textColor=sf::Color::Black);
		/** Default destructor */
		virtual ~TextAreaSFML2_0();

		void handleInput(const sf::Event& event, const sf::RenderTarget& target);

		void setAlphaColor(unsigned char alphaColor);
		unsigned char getAlphaColor() const;

		const sf::FloatRect getLocalBounds() const;
		const sf::FloatRect getGlobalBounds() const;
		sf::String getString();

//		/** Copy constructor
//		 *  \param other Object to copy from
//		 */
//		TextAreaSFML2_0(const TextAreaSFML2_0& other);
//		/** Assignment operator
//		 *  \param other Object to assign from
//		 *  \return A reference to this
//		 */
//		TextAreaSFML2_0& operator=(const TextAreaSFML2_0& other);
//		/** Access m_text
//		 * \return The current value of m_text
//		 */
//		const sf::Text& Gettext() const;
//		/** Access m_background
//		 * \return The current value of m_background
//		 */
//		void Setbackground(sf::Sprite val);

		bool moveCaretForward();
		bool moveCaretBackward();

		void insertCharacter(std::size_t position, sf::Uint32 utf32Char);
		void insertCharacter(sf::Uint32 utf32Char);
		void erase(std::size_t position);
		void erase();
		void eraseNext();

		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f &position);

		void setCharacterSize(unsigned int size);

		void blinkCaret(sf::Int32 millisecondsElapsedTime = 500);

	protected:
	private:
		static sf::Font font;
		static sf::Texture backgroundTexture;
		static bool resourcesLoaded, fontLoaded, backgroundTextureLoaded;
		static bool loadResources(const char* fontFilename = FilenameFont, const char* textureFilename = FilenameTextAreaTex);

		void clearArtificalsEndl();
		void addArtificalsEndl();
		void checkBoundsCharacter(sf::Uint32 code);
		void checkForMaxHeightCharacter();

		std::vector<std::size_t> m_positionArtificialsEndl;
		std::size_t m_caretPosition;
		unsigned int m_paddingLeft, m_paddingRight, m_paddingTop, m_paddingBottom;
		int m_maxHeigtCharacter, m_minXCharacter;
		unsigned int m_lines;
		unsigned char m_alphaColor;
		sf::Color m_caretColor;


		sf::String m_string;
		sf::Text m_text; //!< Member variable "m_text"
		sf::Sprite m_background; //!< Member variable "m_background"
		sf::RectangleShape m_caret;
		sf::Clock m_timer;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

inline void TextAreaSFML2_0::setAlphaColor(unsigned char alphaColor)
{
	m_alphaColor = alphaColor;
	sf::Color tmpTextColor(m_text.getColor());
	tmpTextColor.a = m_alphaColor;
	m_text.setColor(tmpTextColor);
	m_background.setColor(sf::Color(255,255,255,m_alphaColor));
}

inline unsigned char TextAreaSFML2_0::getAlphaColor() const
{
	return m_alphaColor;
}

inline const sf::FloatRect TextAreaSFML2_0::getLocalBounds() const
{
	return m_background.getLocalBounds();
}

inline const sf::FloatRect TextAreaSFML2_0::getGlobalBounds() const
{
	return m_background.getGlobalBounds();
}

inline sf::String TextAreaSFML2_0::getString()
{
	clearArtificalsEndl();
	sf::String tmpString(m_string);
	addArtificalsEndl();
	return tmpString;
}

//inline const sf::Text& TextAreaSFML2_0::Gettext() const
//{
//	return m_text;
//}

#endif // TEXTAREASFML2_0_H
