#include "Enemy.hpp"

Enemy::Enemy()
: m_model(true, sf::Vector2f(0.0f, 0.0f), 12),
  m_view(m_model,GraphScale)
{
     m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
     m_type = TypeObject::Enemy;
}

Enemy::Enemy(const Enemy& copy)
:m_model(copy.m_model), m_view(m_model, GraphScale)
{
    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_type = TypeObject::Enemy;

}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
{
    m_model.handle_input(event, textAreaFunction);
}

void Enemy::show()
{
     m_view.setStringAttempt(m_model.getNbAttemptStr());
     m_view.show();
}

void Enemy::draw(sf::RenderTarget& app)
{
    m_view.draw(app);
}

void Enemy::reset()
{
    m_model.setCoords(sf::Vector2f(0.0f, 0.0f));
    m_model.setAngle(0.0f);
}

EditorObject* Enemy::clone() const
{
	return new Enemy(*this);
}

EditorObject* Enemy::loadView(const Element& elmt, float scale)
{
    Enemy* newEnemy = new Enemy();
    newEnemy->set_Position(elmt.getCoord().x /*- widthTex*/ ,  elmt.getCoord().y /* - heightTex*/);
    newEnemy->setNbAttempt(elmt.getAttempt());
    return newEnemy;
}

std::string Enemy::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << m_model.getNbAttemptStr() << std::endl;
    flux << m_model.getDirection() << std::endl;
    flux << m_model.getCoords().x  << " " <<  m_model.getCoords().y  << std::endl;
    return flux.str();
}
