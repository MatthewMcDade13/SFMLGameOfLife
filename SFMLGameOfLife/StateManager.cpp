#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
#include "Context.h"

using namespace std;

StateManager::StateManager(Context* context)
	: m_states(vector<pair<int, unique_ptr<State>>>()), 
	m_stateFactory(unordered_map<int, function<unique_ptr<State>(StateManager*)>>()),
	m_context(context)
{
}

StateManager::~StateManager()
{
}

Context* StateManager::getContext()
{
	return m_context;
}

State* StateManager::getCurrentState()
{
	if (m_states.empty()) return nullptr;

	return m_states.back().second.get();
}

int StateManager::getCurrentStateId() const
{
	if (m_states.empty()) return -1;
	return m_states.back().first;
}

void StateManager::registerState(int typeId, function<unique_ptr<State>(StateManager*)> stateFactory)
{
	m_stateFactory.emplace(typeId, stateFactory);
}

void StateManager::popState()
{
	State* back = m_states.back().second.get();
	back->onDestroy();
	m_states.pop_back();
	m_states.back().second->activate();
}

void StateManager::pushState(int typeId)
{
	// if state being pushed is already at the top of the stack just return.
	if (!m_states.empty() && m_states.back().first == typeId) return;

	// find if given state is already in stack so we can move 
	// it to top of stack.
	for (auto it = m_states.begin(); it != m_states.end(); it++)
	{
		if (it->first == typeId)
		{
			unique_ptr<State> state = move(it->second);
			state->deactivate();

			m_states.erase(it);

			// If we aren't empty, there is probably a state at top of stack that needs
			// to be deactivated to make way for new state.
			if (!m_states.empty())
				m_states.back().second->deactivate();

			state->activate();
			m_states.emplace_back(typeId, move(state));
			return;
		}
	}

	// If we havent found given state in stack, we need to create a new one
	createState(typeId);
	m_states.back().second->activate();
}

bool StateManager::removeState(int typeId)
{
	for (auto it = m_states.begin(); it != m_states.end(); it++)
	{
		if (it->first == typeId)
		{
			it->second->onDestroy();
			m_states.erase(it);
			return true;
		}
	}

	return false;
}

bool StateManager::hasState(int typeId)
{
	for (auto& pair : m_states)
	{
		if (pair.first == typeId) return true;
	}
	return false;
}

void StateManager::draw()
{
	if (m_states.empty()) return;

	State* backState = m_states.back().second.get();

	if (backState->isTransparent() && m_states.size() > 1)
	{
		auto it = m_states.end() - 1;
		// Iterate backwards until we find most recent state that is
		// not transparent.
		for (; it != m_states.begin(); it--)
		{
			if (!it->second->isTransparent()) break;
		}

		// Draw all states that we found up to top of stack.
		for (; it != m_states.end(); it++)
		{
			it->second->draw(*m_context->window);
		}
	}
	else
	{
		// otherwise just draw state at top of stack.
		m_states.back().second->draw(*m_context->window);
	}
}

void StateManager::update(float deltaTime)
{
	if (m_states.empty()) return;
	State* backState = m_states.back().second.get();

	if (backState->isTranscendant() && m_states.size() > 1)
	{
		auto it = m_states.end() - 1;
		// Iterate backwards until we find most recent state that is
		// not transcendant.
		for (; it != m_states.begin(); it--)
		{
			if (!it->second->isTranscendant()) break;
		}

		// update all states that we found up to top of stack.
		for (; it != m_states.end(); it++)
		{
			it->second->update(deltaTime);
		}
	}
	else
	{
		// otherwise just update state at top of stack.
		m_states.back().second->update(deltaTime);
	}
}

void StateManager::handleInput(const sf::Event & event)
{
	if (m_states.empty()) return;

	State* currentState = m_states.back().second.get();

	currentState->handleInput(event);
}

bool StateManager::createState(int typeId)
{
	auto it = m_stateFactory.find(typeId);
	// if we cant find a factory function for given state, it wasn't registered,
	// so just return.
	if (it == m_stateFactory.end()) return false;

	unique_ptr<State> newState = it->second(this);
	newState->onCreate();

	m_states.emplace_back(typeId, move(newState));
	return true;
}
