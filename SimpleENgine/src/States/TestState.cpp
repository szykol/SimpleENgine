#include "TestState.h"
#include "StateManager.h"
#include "../GUI/Prompt.h"
#include "../GUI/Popup.h"

namespace sen {
	unsigned int TestState::s_pushedStates = 0;

	TestState::TestState(sf::RenderWindow & window)
		: m_info("Amount of states: ")
	{
		std::shared_ptr<Button> popState(new Button("Pop State"));
		std::shared_ptr<Button> pushState(new Button("Push State"));
		std::shared_ptr<Button> spawnPopup(new Button("Spawn Prompt"));
		//std::shared_ptr<Button> box(new InputBox());

		pushState->setOnClickCalback([&window, this] {
				m_prompt = std::make_shared<Prompt>(PromptStyle::BINARY, "Are you sure?");
				m_prompt->setPosition(sf::Vector2f(window.getSize()) / 2.f);
				StateManager::pushPrompt(m_prompt);

				m_prompt->setOnResponseCallback(
					[&](const json& j) {
						if(j["Response"])
						{
							StateManager::pushState<TestState>(window);
							auto popup = new Popup(window, "Pushed State");
							StateManager::pushPopup(popup);
						}
					}
				);
		});
		popState->setOnClickCalback([&window, this] {
				m_prompt = std::make_shared<Prompt>(PromptStyle::BINARY, "Are you sure?");
				m_prompt->setPosition(sf::Vector2f(window.getSize()) / 2.f);
				StateManager::pushPrompt(m_prompt);
				m_prompt->setOnResponseCallback(
					[&](const json& j) {
						if(j["Response"])
						{
							StateManager::popState();
							auto popup = new Popup(window, "Popped State");
							StateManager::pushPopup(popup);
						}
					}
				);
				
		});

		spawnPopup->setOnClickCalback([&window, this] {
				m_prompt = std::make_shared<Prompt>(PromptStyle::INPUT, "Type something..");
				m_prompt->setPosition(sf::Vector2f(window.getSize()) / 2.f);
				StateManager::pushPrompt(m_prompt);
		});

		// Get text object of textbox and set its string
		// and character size
		auto& tObject = m_info.getTextObject();
		tObject.setCharacterSize(26U);
		sf::String ammount = tObject.getString();
		ammount += std::to_string(s_pushedStates);
		tObject.setString(ammount);
		m_info.setPosition(sf::Vector2f(window.getSize().x / 2.f, 50.f));

		s_pushedStates++;

		// setup button controller
		//m_buttonController.setButtonPlacing(ButtonPlacing::HORIZONTAL);
		m_buttonController.pushButtons(popState, pushState, spawnPopup);
		m_buttonController.placeButtons(window);
		m_buttonController.setButtonFixedSize(
			sf::Vector2f(185.f, 50.f)
		);
		
	}
	void TestState::handleEvents(sf::Event &evnt)
	{
		
	}
	void TestState::update(sf::RenderWindow & window)
	{
		m_buttonController.update(window);
		if (m_prompt && m_prompt->hasResponse())
		{
			std::cout<<"Response: "<<m_prompt->getResponse()["Response"]<<std::endl;
			m_prompt = nullptr;
		}
	}
	void TestState::input(sf::RenderWindow & window)
	{
	}
	void TestState::render(sf::RenderTarget & target)
	{
		m_info.render(target);
		m_buttonController.render(target);
	}
	TestState::~TestState()
	{
		// buttons are no longer heap allocated
		//m_buttonController.freeMemory();
		s_pushedStates--;
	}
}