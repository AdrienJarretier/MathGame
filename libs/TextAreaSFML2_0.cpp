#include "TextAreaSFML2_0.hpp"

sf::Font TextAreaSFML2_0::font;
sf::Texture TextAreaSFML2_0::backgroundTexture;
bool TextAreaSFML2_0::fontLoaded;
bool TextAreaSFML2_0::backgroundTextureLoaded;

bool TextAreaSFML2_0::loadResources(const char* fontFilename, const char* textureFilename)
{
	fontLoaded = font.loadFromFile(fontFilename) ;
	backgroundTextureLoaded = backgroundTexture.loadFromFile(textureFilename);
	return fontLoaded && backgroundTextureLoaded;
}

bool TextAreaSFML2_0::resourcesLoaded = loadResources();


TextAreaSFML2_0::TextAreaSFML2_0(unsigned int padding, const sf::Color& textColor)
:m_caretPosition(0U), m_paddingLeft(padding), m_paddingRight(padding), m_paddingTop(padding), m_paddingBottom(padding), m_lines(1U)
,m_alphaColor(Blur), m_caretColor(206,49,49)
{
	setAlphaColor(m_alphaColor);
	if(resourcesLoaded)
	{
		m_text.setFont(font);
		m_text.setColor(textColor);

		checkForMaxHeightCharacter();

		m_background.setTexture(backgroundTexture, true);
		m_background.setScale(1, (m_maxHeigtCharacter*m_lines+m_paddingTop+m_paddingBottom)/m_background.getLocalBounds().height);

		m_text.setPosition(m_background.getPosition().x-m_minXCharacter+m_paddingLeft,m_background.getPosition().y+m_maxHeigtCharacter/4+m_paddingTop);
		m_caret.setPosition(m_text.findCharacterPos(m_caretPosition).x, m_text.findCharacterPos(m_caretPosition).y-m_maxHeigtCharacter/4);
		m_caret.setSize(sf::Vector2f(2, m_maxHeigtCharacter));
		m_caret.setFillColor(m_caretColor);
	}
}

TextAreaSFML2_0::~TextAreaSFML2_0()
{
	//dtor
}

void TextAreaSFML2_0::handleInput(const sf::Event& event, const sf::RenderTarget& target)
{
	switch(event.type)
	{
	case sf::Event::TextEntered:
		insertCharacter(event.text.unicode);
		break;

	case sf::Event::MouseMoved:
    {
        int x =  event.mouseMove.x;
        int y =  event.mouseMove.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x,y)));

        if(getGlobalBounds().contains(coord.x,coord.y))
		{
            setAlphaColor(Clear);
		}
        else
		{
            setAlphaColor(Blur);
		}
    }
		break;

	case sf::Event::KeyPressed:
		switch(event.key.code)
		{
		case sf::Keyboard::BackSpace:
			erase();
			break;

		case sf::Keyboard::Delete:
			eraseNext();
			break;

		case sf::Keyboard::Left:
			if(m_alphaColor==Clear)
				moveCaretBackward();
			break;

		case sf::Keyboard::Right:
			if(m_alphaColor==Clear)
				moveCaretForward();
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

//TextAreaSFML2_0::TextAreaSFML2_0(const TextAreaSFML2_0& other)
//{
//	//copy ctor
//}
//
//TextAreaSFML2_0& TextAreaSFML2_0::operator=(const TextAreaSFML2_0& rhs)
//{
//	if (this == &rhs) return *this; // handle self assignment
//	//assignment operator
//	return *this;
//}

bool TextAreaSFML2_0::moveCaretForward()
{
	bool caretMoved=false;


//	m_caretPosition++;
//	caretMoved = true;
//	m_caret.setPosition(m_text.findCharacterPos(m_caretPosition).x, m_text.findCharacterPos(m_caretPosition).y-m_maxHeigtCharacter/4);


	if(m_caretPosition<m_string.getSize())
	{
		if(m_string[m_caretPosition+1] == '\n')
			m_caretPosition++;

		m_caretPosition++;

		m_caret.setPosition(m_text.findCharacterPos(m_caretPosition).x, m_text.findCharacterPos(m_caretPosition).y-m_maxHeigtCharacter/4);
		caretMoved = true;
	}
	m_caret.setFillColor(m_caretColor);
	m_timer.restart();
	return caretMoved;
}

bool TextAreaSFML2_0::moveCaretBackward()
{
	bool caretMoved=false;


	if(m_caretPosition>0)
	{
		if(m_string[m_caretPosition-1] == '\n')
			m_caretPosition--;

		m_caretPosition--;
		m_caret.setPosition(m_text.findCharacterPos(m_caretPosition).x, m_text.findCharacterPos(m_caretPosition).y-m_maxHeigtCharacter/4);
		caretMoved = true;
	}
	m_caret.setFillColor(m_caretColor);
	m_timer.restart();
	return caretMoved;
}

void TextAreaSFML2_0::insertCharacter(std::size_t position, sf::Uint32 utf32Char)
{
	clearArtificalsEndl();
	if(!iscntrl(utf32Char) && position<=m_string.getSize())
	{
		m_string.insert(position, sf::String(utf32Char));
		m_text.setString(m_string);
		if(position<=m_caretPosition)
			moveCaretForward();
	}
	addArtificalsEndl();
	m_background.setScale(1, (m_maxHeigtCharacter*m_lines+m_paddingTop+m_paddingBottom)/m_background.getLocalBounds().height);
}

void TextAreaSFML2_0::insertCharacter(sf::Uint32 utf32Char)
{
	clearArtificalsEndl();
	insertCharacter(m_caretPosition, utf32Char);
}

void TextAreaSFML2_0::erase(std::size_t position)
{
	clearArtificalsEndl();
	if(position>=0 && position<m_string.getSize())
	{
		m_text.setString(m_string);
		m_string.erase(position);
		if(position<m_caretPosition)
			moveCaretBackward();
	}
	addArtificalsEndl();

	m_background.setScale(1, (m_maxHeigtCharacter*m_lines+m_paddingTop+m_paddingBottom)/m_background.getLocalBounds().height);
}

void TextAreaSFML2_0::erase()
{
	clearArtificalsEndl();
	if(m_caretPosition>0)
		erase(m_caretPosition-1);
}

void TextAreaSFML2_0::eraseNext()
{
	clearArtificalsEndl();
	erase(m_caretPosition);
}

void TextAreaSFML2_0::setPosition(float x, float y)
{
	m_background.setPosition(x, y);
	m_text.setPosition(m_background.getPosition().x-m_minXCharacter+m_paddingLeft,m_background.getPosition().y+m_maxHeigtCharacter/4+m_paddingTop);
	m_caret.setPosition(m_text.findCharacterPos(m_caretPosition).x, m_text.findCharacterPos(m_caretPosition).y-m_maxHeigtCharacter/4);
}

void TextAreaSFML2_0::setPosition(const sf::Vector2f &position)
{
	setPosition(position.x, position.y);
}

void TextAreaSFML2_0::setCharacterSize(unsigned int size)
{
	m_text.setCharacterSize(size);

	checkForMaxHeightCharacter();

	m_background.setScale(1, (m_maxHeigtCharacter*m_lines+m_paddingTop+m_paddingBottom)/m_background.getLocalBounds().height);

	m_text.setPosition(m_background.getPosition().x-m_minXCharacter+m_paddingLeft,m_background.getPosition().y+m_maxHeigtCharacter/4+m_paddingTop);
	m_caret.setPosition(m_text.findCharacterPos(m_caretPosition).x, m_text.findCharacterPos(m_caretPosition).y-m_maxHeigtCharacter/4);
	m_caret.setSize(sf::Vector2f(2, m_maxHeigtCharacter));
}

void TextAreaSFML2_0::blinkCaret(sf::Int32 millisecondsElapsedTime)
{
	if(m_timer.getElapsedTime().asMilliseconds()<millisecondsElapsedTime)
		m_caret.setFillColor(m_caretColor);
	else if(getAlphaColor()==Blur || m_timer.getElapsedTime().asMilliseconds()<millisecondsElapsedTime*2)
		m_caret.setFillColor(sf::Color::Transparent);
	else
		m_timer.restart();
}

void TextAreaSFML2_0::clearArtificalsEndl()
{
	FOR_STL_REVERSE_ITERATOR(std::vector<std::size_t>, m_positionArtificialsEndl, itr)
	{
		m_string.erase(*itr);
		m_lines--;
		if(*itr<m_caretPosition)
			moveCaretBackward();
	}
	m_positionArtificialsEndl.clear();
}

void TextAreaSFML2_0::addArtificalsEndl()
{
	m_text.setString(m_string);
	for(std::size_t actualPosition=0; actualPosition<=m_string.getSize(); actualPosition++)
	{
		if(m_text.findCharacterPos(actualPosition+1).x+m_paddingLeft+m_paddingRight-m_background.getGlobalBounds().left>m_background.getLocalBounds().width)
		{
			m_string.insert(actualPosition, sf::String('\n'));
			m_positionArtificialsEndl.push_back(actualPosition);
			m_text.setString(m_string);
			m_lines++;
			if(actualPosition<=m_caretPosition)
				moveCaretForward();
		}
	}
}

void TextAreaSFML2_0::checkBoundsCharacter(sf::Uint32 code)
{
	if(font.getGlyph(code, m_text.getCharacterSize(), false).bounds.height>m_maxHeigtCharacter)
		m_maxHeigtCharacter = font.getGlyph(code, m_text.getCharacterSize(), false).bounds.height;

	if(font.getGlyph(code, m_text.getCharacterSize(), false).bounds.left<m_minXCharacter)
		m_minXCharacter = font.getGlyph(code, m_text.getCharacterSize(), false).bounds.left;
}

void TextAreaSFML2_0::checkForMaxHeightCharacter()
{
	m_maxHeigtCharacter=0;
	m_minXCharacter=0;
	std::string specialCodes[] ={"&", "é", "~", "\"", "#" , "'", "{", "(", "[", "-"
								,"|", "è", "`", "_",  "\\", "ç", "^", "à", "@", "°"
								,")", "]", "+", "=",  "}" , "¨", "^", "£", "$", "¤"
								,"%", "ù", "µ", "*",  "?" , ",", ".", ";", "/", ":"
								,"§", "!", ">", "<"};
	sf::Uint32 specialCodesUint32[44];
	sf::Uint32 tmp[10];
	for(size_t i=0; i<44; i++)
	{
		// converti la chaine de caracteres représentant un caractère Ansi en code Utf8
		sf::Uint32* itEnd = sf::Utf32::fromAnsi(specialCodes[i].begin(), specialCodes[i].end(), tmp);
		// convertie le codage utf8 en codage utf32
		sf::Utf8::decode(tmp, itEnd, specialCodesUint32[i]);
	}

	for(sf::Uint32 code='A'; code<='Z'; code++)
		checkBoundsCharacter(code);

	for(sf::Uint32 code='a'; code<='z'; code++)
		checkBoundsCharacter(code);

	for(sf::Uint32 code='0'; code<='9'; code++)
		checkBoundsCharacter(code);

	for(size_t i=0; i<44; i++)
		checkBoundsCharacter(specialCodesUint32[i]);
}

void TextAreaSFML2_0::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_background);
	target.draw(m_text);
	target.draw(m_caret);
}