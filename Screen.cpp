#include "Screen.h"

#define VEC3_ZERO glm::vec3(0.0f)

void Screen::getCursorPosition(Game* g) {
	glfwGetCursorPos(g->gameWindow, &xpos, &ypos);
}

void Screen::screenToWorldCord() {
	float x = ((2.0f * xpos) / 1920 - 1.0f) * 100.0;
	float y = (1.0f - (2.0f * ypos) / 1080) * 100.0;
	
	xpos = x;
	ypos = y;
}

bool Screen::collisionBB(Game* g, GameObject* GO) {
	if (xpos <= GO->boundingBox.x && xpos >= GO->boundingBox.y && ypos <= GO->boundingBox.z && ypos >= GO->boundingBox.w) {
		return true;
	}
	else {
		return false;
	}
}
void ScreenHandler::ScreenInit(Game* g) {
	if (screen == PAUSE) {
		Screen* crntMenu = new PauseMenu();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == MAIN) {
		Screen* crntMenu = new MainMenu();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == GAME) {
		Screen* crntMenu = new GameScreen();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == SETTINGS) {
		Screen* crntMenu = new SettingScreen();

		g->ScreenObject.push_back(crntMenu);
	}
}

void ScreenHandler::ScreenSwitch(SCREENTYPE screen, Game* g) {
	this->screen = screen;
}

void PauseMenu::drawScreen(Game* g) {
	g->dtUpdate();
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->fonts[1]->drawString(750.0f, 150.0f, "PAUSED", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 350.0f, "CONTINUE", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 500.0f, "OPTIONS", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 1000.0f, "EXIT", g->shaders[2]);
}

void PauseMenu::updateScreen(Game* g) {	
	int state = glfwGetMouseButton(g->gameWindow, GLFW_MOUSE_BUTTON_LEFT);

	if (glfwGetKey(g->gameWindow, GLFW_KEY_P) == GLFW_PRESS) {
		remove(g);
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME, g);
		g->ScreenHandler[0]->ScreenInit(g);
	}

	if (state == GLFW_PRESS)
	{
		g->ScreenObject[0]->getCursorPosition(g);
		cout << g->ScreenObject[0]->ypos << endl;

		if (g->ScreenObject[0]->xpos <= 650.0 && g->ScreenObject[0]->xpos >= 96.0 && g->ScreenObject[0]->ypos >= 272.0 && g->ScreenObject[0]->ypos <= 357.0) {
			remove(g);
			g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME, g);
			g->ScreenHandler[0]->ScreenInit(g);
		}

		if (g->ScreenObject[0]->xpos <= 550.0 && g->ScreenObject[0]->xpos >= 96.0 && g->ScreenObject[0]->ypos >= 412.0 && g->ScreenObject[0]->ypos <= 510.0) {
			remove(g);
			g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::SETTINGS, g);
			g->ScreenHandler[0]->ScreenInit(g);
		}

		if (g->ScreenObject[0]->xpos <= 379.0 && g->ScreenObject[0]->xpos >= 96.0 && g->ScreenObject[0]->ypos >= 960.0 && g->ScreenObject[0]->ypos <= 1030.0) {
			remove(g);
			g->gameReset(g);
			g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::MAIN, g);
			g->ScreenHandler[0]->ScreenInit(g);

		}
	}
		
	
}

void PauseMenu::remove(Game* g) {
	g->removeScreen(this);
}


void SettingScreen::drawScreen(Game* g) {
	g->dtUpdate();
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	if (g->setting == g->VIDEOSET) {
		g->fonts[1]->drawString(670.0f, 150.0f, g->settingType, g->shaders[2]);
		g->fonts[1]->drawString(100.0f, 350.0f, "RESOLUTION:", g->shaders[2]);
		g->fonts[1]->drawString(900.0f, 350.0f, g->resSetting, g->shaders[2]);
		g->fonts[1]->drawString(100.0f, 500.0f, "DEBUG:", g->shaders[2]);
		g->fonts[1]->drawString(550.0f, 500.0f, g->debugSetting, g->shaders[2]);
		g->fonts[1]->drawString(100.0f, 1000.0f, "[ESC]", g->shaders[2]);
	}

	else if (g->setting == g->AUDIOSET) {
		g->fonts[1]->drawString(670.0f, 150.0f, g->settingType, g->shaders[2]);
		g->fonts[1]->drawString(100.0f, 350.0f, "MUSIC:", g->shaders[2]);
		g->fonts[1]->drawString(500.0f, 350.0f, g->musicSetting, g->shaders[2]);
		g->fonts[1]->drawString(100.0f, 500.0f, "SFX:", g->shaders[2]);
		g->fonts[1]->drawString(400.0f, 500.0f, g->sfxSetting, g->shaders[2]);
		g->fonts[1]->drawString(100.0f, 1000.0f, "[ESC]", g->shaders[2]);
	}
}

void SettingScreen::updateScreen(Game* g) {
	int state = glfwGetMouseButton(g->gameWindow, GLFW_MOUSE_BUTTON_LEFT);


	if (glfwGetKey(g->gameWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		remove(g);
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::PAUSE, g);
		g->ScreenHandler[0]->ScreenInit(g);
	}

	if (state == GLFW_PRESS)
	{
		g->ScreenObject[0]->getCursorPosition(g);
		cout << "Y POS: " << g->ScreenObject[0]->ypos << endl;
		cout << "X POS: " << g->ScreenObject[0]->xpos << endl;


		if (g->setting == g->VIDEOSET) {
			g->ScreenObject[0]->getCursorPosition(g);
			if (g->ScreenObject[0]->xpos <= 1708.0 && g->ScreenObject[0]->xpos >= 1653.0 && g->ScreenObject[0]->ypos >= 284.0 && g->ScreenObject[0]->ypos <= 351.0) {
				if (g->resID == g->FHD) {
					g->resSetting = "< 2560 X 1440 >";
					g->resID = g->TWOK;
					g->screenWidth = 2560;
					g->screenHeight = 1440;
					glfwWaitEvents();
				}

				if (g->resID == g->HD) {
					g->resSetting = "< 1920 X 1080 >";
					g->resID = g->FHD;
					g->screenWidth = 1920;
					g->screenHeight = 1080;
					glfwWaitEvents();
				}
			}

			if (g->ScreenObject[0]->xpos <= 948.0 && g->ScreenObject[0]->xpos >= 893.0 && g->ScreenObject[0]->ypos >= 284.0 && g->ScreenObject[0]->ypos <= 351.0) {
				if (g->resID == g->FHD) {
					g->resSetting = "< 1280 X 720 >";
					g->resID = g->HD;
					g->screenWidth = 1280;
					g->screenHeight = 720;
					glfwWaitEvents();
					//glfwWaitEventsTimeout(0.1); could work, a bit weird tho
				}

				if (g->resID == g->TWOK) {
					g->resSetting = "< 1920 X 1080 >";
					g->resID = g->FHD;
					g->screenWidth = 1920;
					g->screenHeight = 1080;
					glfwWaitEvents();
				}
			}

			if (g->ScreenObject[0]->xpos <= 600.0 && g->ScreenObject[0]->xpos >= 547.0 && g->ScreenObject[0]->ypos >= 434.0 && g->ScreenObject[0]->ypos <= 500.0) {
				g->debugSetting = " OFF >";
				g->inDebugMode = false;
			}

			if (g->ScreenObject[0]->xpos <= 876.0 && g->ScreenObject[0]->xpos >= 822.0 && g->ScreenObject[0]->ypos >= 434.0 && g->ScreenObject[0]->ypos <= 500.0) {
				g->debugSetting = "< ON ";
				g->inDebugMode = true;
			}


			if (g->ScreenObject[0]->xpos <= 1106.0 && g->ScreenObject[0]->xpos >= 1048.0 && g->ScreenObject[0]->ypos >= 88.0 && g->ScreenObject[0]->ypos <= 146.0) {
				g->setting = g->AUDIOSET;
				g->settingType = "< AUDIO ";
				glfwWaitEvents();
			}
		}
		else if (g->setting == g->AUDIOSET) {
			if (g->ScreenObject[0]->xpos <= 451.0 && g->ScreenObject[0]->xpos >= 393.0 && g->ScreenObject[0]->ypos >= 430.0 && g->ScreenObject[0]->ypos <= 500.0) {
				g->sfxSetting = " OFF >";
				g->sfxOn = false;
			}

			else if (g->ScreenObject[0]->xpos <= 725.0 && g->ScreenObject[0]->xpos >= 670.0 && g->ScreenObject[0]->ypos >= 430.0 && g->ScreenObject[0]->ypos <= 500.0) {
				g->sfxSetting = "< ON ";
				g->sfxOn = true;
			}



			if (g->ScreenObject[0]->xpos <= 550.0 && g->ScreenObject[0]->xpos >= 495.0 && g->ScreenObject[0]->ypos >= 287.0 && g->ScreenObject[0]->ypos <= 350.0) {
				g->musicSetting = " OFF >";
				g->musicOn = false;
			}

			else if (g->ScreenObject[0]->xpos <= 820.0 && g->ScreenObject[0]->xpos >= 770.0 && g->ScreenObject[0]->ypos >= 287.0 && g->ScreenObject[0]->ypos <= 350.0) {
				g->musicSetting = "< ON ";
				g->musicOn = true;
			}

			if (g->ScreenObject[0]->xpos <= 720.0 && g->ScreenObject[0]->xpos >= 670.0 && g->ScreenObject[0]->ypos >= 88.0 && g->ScreenObject[0]->ypos <= 146.0) {
				g->setting = g->VIDEOSET;
				g->settingType = " VIDEO > ";
				glfwWaitEvents();
			}
		}
	}
	
		
	
}

void SettingScreen::remove(Game* g) {
	g->removeScreen(this);
}

void MainMenu::drawScreen(Game* g) {
	g->dtUpdate();
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->fonts[1]->drawString(600.0f, 150.0f, "PONGCHAMP!", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 350.0f, "PLAY", g->shaders[2]);

}

void MainMenu::remove(Game* g) {
	g->removeScreen(this);
}

void GameScreen::drawScreen(Game* g) {	

	if (g->pause == false || g->framestep > 0) {
		g->update();
		if (g->framestep > 0)
			g->framestep--;
	}
	if(g->pause == true)
		g->dtUpdate();

	

	//Exporting data & Render
	g->draw();
	//-----------------------------------------------------------------
	g->cameras[0]->updateMatrix(45.0f, 0.0f, 500.0f);

	//------------------------TEXT (NOTE: IMPLEMENT IN G.DRAW())----------------------------------------
	g->shaders[2]->Activate();



	g->fontSetup(g);

	g->texts[0]->update(g, g->gameWindow);
	g->texts[1]->update(g, g->gameWindow);

	g->fonts[0]->drawString(g->texts[0]->pos.x, g->texts[0]->pos.y, g->texts[0]->text, g->shaders[2]);
	g->fonts[0]->drawString(g->texts[1]->pos.x, g->texts[1]->pos.y, g->texts[1]->text, g->shaders[2]);

	g->tempText("No Limits!", 520.0f, 80.0f, 6, g);

	if (!g->gameStart) {
		if (countDown <= 10.0 && countDown > 4.0) {
			g->fonts[1]->drawString(700.0f, 560.0f, "READY?", g->shaders[2]);
			countDown -= 0.05;
		}

		else if (countDown <= 4.0) {
			g->fonts[1]->drawString(810.0f, 560.0f, "GO!", g->shaders[2]);
			countDown -= 0.05;
			if (countDown <= 0.0) {
				g->pause = false;
				g->gameStart = true;
			}
		}
	}

	//--------------DEBUG----------------------------
	g->debugGUI[0]->onClickDebug(g);

	g->debugGUI[0]->createDebugMenu(g);

	if (g->inDebugMode == true) {
		if (g->ScreenHandler[0]->renderDebugScreen) {
			g->debugGUI[0]->createDebugMenu(g->OBJList[0], g->ScreenHandler[0]->currentDebugObj, glm::vec3(-0.75f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.015f, 0.2f, 1.0f));
		}
	}


}

void GameScreen::updateScreen(Game* g) {
	if (glfwGetKey(g->gameWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS && g->gameStart) {
		g->pause;

		remove(g);
		g->gameStart = false;
		g->pause = true;
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::PAUSE, g);
		g->ScreenHandler[0]->ScreenInit(g);
	}

	if (g->texts[0]->score >= 5 || g->texts[1]->score >= 5)
		g->winReset(g, this);
}

void GameScreen::remove(Game* g) {
	g->removeScreen(this);
}
