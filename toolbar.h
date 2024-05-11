#pragma once
#include "gameConfig.h"
////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class game;
class toolbar
{

private:
	int height, width;	
	string toolbarItemImages[ITM_CNT]; //array to hold paths to images of diffrent items in the toolbar
	game* pGame;
	int level = 1;
	int lives = 5;
	int score = 0;

public:
	toolbar(game* r_pGame);
	toolbarItem getItemClicked(int x);	//handles clicks on toolbar icons, returns the "enum" of the clicekd item
};

