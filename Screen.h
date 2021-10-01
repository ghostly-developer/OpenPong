#pragma once

#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Game;


class Screen {
public:
	double xpos, ypos;

	virtual void drawScreen(Game* g){}
	virtual void updateScreen(Game* g){}
	void getCursorPosition(Game* g);
};

class ScreenHandler : public Screen {
public:
	enum SCREENTYPE { GAME, PAUSE, MAIN };
	SCREENTYPE screen;

	void ScreenInit(Game* g);
	void ScreenSwitch(SCREENTYPE screen, Game* g);
};

class PauseMenu : public Screen {
public:
	void drawScreen(Game* g) override;
	void updateScreen(Game* g) override;
	void remove(Game* g);
};

class MainMenu : public Screen {
public:
	void drawScreen(Game* g) override;
	//void updateScreen(Game* g) override;
	void remove(Game* g);
};

class GameScene : public Screen {
public:
	void drawScreen(Game* g) override;
	void updateScreen(Game* g) override;
	void remove(Game* g);
};