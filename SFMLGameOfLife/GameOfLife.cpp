#include "stdafx.h"
#include "GameOfLife.h"
#include "Grid.h"
#include "Cell.h"
#include "CellState.h"
#include "ResourceManager.h"
#include "parallelFor.h"
#include "GetConsoleInput.h"
#include "SplashScreen.h"
#include "GameState.h"
#include "PlayState.h"
#include "ToUnderlying.h"
#include <memory>

using namespace std;

GameOfLife::GameOfLife()
	: m_stateManager(&m_context), m_settings({0,0,0})
{
}


GameOfLife::~GameOfLife()
{
}

void GameOfLife::onGameStart()
{
	m_stateManager.registerState(GameState::Intro, [this](StateManager* manager) { return make_unique<SplashScreen>(manager, &m_settings); });
	m_stateManager.registerState(GameState::Playing, [this](StateManager* manager) { return make_unique<PlayState>(manager, &m_settings); });

	m_stateManager.pushState(GameState::Intro);
}

void GameOfLife::update(float deltaTime)
{
	m_stateManager.update(deltaTime);
	m_stateManager.draw();
}

void GameOfLife::handleInput(const sf::Event& event)
{
	m_stateManager.handleInput(event);
}

