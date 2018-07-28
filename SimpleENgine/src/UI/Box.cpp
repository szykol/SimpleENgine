#include "Box.h"

namespace sen {
	Box::Box(const sf::Vector2f & size)
	{
		setSize(size);
		setOriginMode(OriginMode::CENTER);
	}
	Box::Box(const sf::Vector2f & size, const sf::Vector2f & pos)
	{
		setSize(size);
		setPosition(pos);
		setOriginMode(OriginMode::CENTER);
	}
	void Box::render(sf::RenderTarget & target)
	{
		target.draw(*this);
	}
	void Box::setOriginMode(OriginMode mode)
	{
		if (m_originMode == mode)
			return;

		m_originMode = mode;
		if (m_originMode == OriginMode::CENTER)
			setOrigin(getSize() / 2.f);
		else
			setOrigin(0.f, 0.f);
	}
	void Box::setSize(const sf::Vector2f & size)
	{
		sf::RectangleShape::setSize(size);
		if (m_originMode == OriginMode::CENTER)
			setOrigin(getSize() / 2.f);
	}
	/*void Box::blurBackground(float ammount, sf::RenderWindow &window)
	{
		texture = new sf::Texture();
		texture->create(window.getSize().x, window.getSize().y);
		texture->update(window);

		setTexture(texture);
		setTextureRect(sf::IntRect((sf::Vector2i)getPosition(), (sf::Vector2i)getSize()));

		shader = new sf::Shader();
		shader->loadFromFile("Shaders/blur.frag", sf::Shader::Fragment);
		shader->setUniform("blur_radius", ammount);
		shader->setUniform("texture", texture);
	}*/
}
