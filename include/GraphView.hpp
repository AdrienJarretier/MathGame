#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <list>
#include <vector>
#include <limits>
#include <SFML/Graphics.hpp>
#include "ConstrueFunction.hpp"
#include "../libs/LineSFML2_0.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

class GraphView
{
    public:
        GraphView( ConstrueFonction& model, float thickness=1.0f, float scale=1.0f);
        virtual ~GraphView();
        void represent(float step);
        void draw( sf::RenderWindow& App );
        void setGraphColor(const sf::Color& graphColor);
//        void setChanged(bool _changed) ;
//        bool getChanged()const ;
        //sf::VertexArray m_functionRepresentation;

	private:
	    const ConstrueFonction& m_model;
        std::list<LineSFML2_0> m_lines;
		float m_thickness;
		float m_scale;
		sf::Color m_graphColor;
};

/**
*  accessors
**/

inline void GraphView::setGraphColor(const sf::Color& graphColor)
{
	m_graphColor = graphColor;
}

/**
*  accessors
**/

#endif // GRAPHVIEW_H