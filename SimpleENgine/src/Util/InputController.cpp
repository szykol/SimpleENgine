#include "InputController.h"


namespace sen {
	Text* InputController::s_text = nullptr;
	Cursor InputController::s_cursor;
	stringValidateFunc InputController::s_validateFunc;
	bool InputController::s_isBound = false;

	void InputController::handleInput(const sf::Event& evnt)
	{
		if(!s_isBound) return;

		sf::String string = s_text->getString();

		auto unicode = evnt.text.unicode;
		if (unicode >= 'A' && unicode <= 'Z'
			|| unicode >= 'a' && unicode <= 'z'
			|| unicode >= '1' && unicode <= '9'
			|| unicode == ' ')

		{
			string += char(evnt.key.code);
			if(validate())
				s_text->setString(string);
		}
		else if (unicode == '\b' && !string.isEmpty())
		{
			string.erase(string.getSize() - 1);
			if(validate())
				s_text->setString(string);
		}
		
	}

	void InputController::bindText(Text& text)
	{
		s_isBound = true;
		s_text = &text;
		s_cursor.setTextRef(&text);
	}

	void InputController::unbindText()
	{
		s_isBound = false;
		s_text = nullptr;
		s_cursor.setTextRef(nullptr);
	}

	//void InputController::update()
	//{
	//}

	void InputController::render(sf::RenderTarget & target)
	{
		if(s_isBound)
			s_cursor.render(target);
	}
	bool InputController::validate()
	{
		if (s_validateFunc)
			return s_validateFunc(s_text->getString());
		else
			return true;
	}
}
