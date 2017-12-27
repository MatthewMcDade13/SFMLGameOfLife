#include "stdafx.h"
#include "State.h"


State::State(StateManager* manager): m_stateManager(manager)
{
}


State::~State()
{
}

bool State::isTransparent() const
{
	return m_bTransparent;
}

bool State::isTranscendant() const
{
	return m_bTranscendant;
}

bool State::isActive() const
{
	return m_bActive;
}
