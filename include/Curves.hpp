#ifndef Curves_H
#define Curves_H

#include <stdexcept>
#include <sstream>

#include "../constants.hpp"
#include "EditorObject.hpp"
#include "ConstrueFunction.hpp"
#include "GraphView.hpp"


/// for the moment, Curves can be represented by the multi shaping method
class Curves : public EditorObject
{
    public:
        Curves(std::string function = "0", float _begin = 0.0f, float _end = 0.1f, float step = Step);
        virtual ~Curves();
        Curves(const Curves& other);
        virtual EditorObject* clone() const ;
        virtual std::string save(float scale = GraphScale) const ;
        virtual void draw(sf::RenderTarget& app);
        void build(int _begin = - MaxSizeGraph, int _end = MaxSizeGraph, float step = Step);
        std::string getFunction() const;
        const ConstrueFunction* getModel();
        void move(float step = Step);
        void setFunction(std::string str);
        void reset();
        void represent(float step);
        virtual void setColor (const sf::Color& graphColor);
        void drawInterval(sf::RenderTarget& app);

        private:
    	virtual void setPosition(sf::Vector2f& position);
        virtual void setPosition(float x, float y);
        virtual sf::FloatRect get_GlobalBounds() const ;
        virtual sf::Vector2f get_Position() const;
        virtual EditorObject* loadView(const Element& elmt, float scale);


        ConstrueFunction m_model;
        GraphView m_view;
};

inline EditorObject* Curves::loadView(const Element& elmt, float scale)
{
#ifdef DEBUG
std::cerr << "nothing to do for the moment";
#endif
return nullptr;
}

inline void Curves::setPosition(sf::Vector2f& position)
{
	std::runtime_error("In the class Curves::setPosition -> nothing to do");
}


inline void Curves::setPosition(float x, float y)
{
	std::runtime_error("In the class Curves::setPosition -> nothing to do");
}


inline sf::FloatRect Curves::get_GlobalBounds() const
{
	std::runtime_error("In the class Curves::get_GlobalBounds -> nothing to do");
	return sf::FloatRect();
}

inline sf::Vector2f Curves::get_Position() const
{
	std::runtime_error("In the class Curves::get_Position -> nothing to do");
	return sf::Vector2f();
}

inline std::string Curves::getFunction() const
{
    return m_model.getFunction();
}

inline void Curves::setFunction(std::string str)
{
    m_model.setFunction(str);
}

inline void Curves::setColor(const sf::Color& graphColor)
{
    m_view.setGraphColor(graphColor);
}

#endif // Curves_H
