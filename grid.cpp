#include "game.h"
#include "gameConfig.h"
#include "time.h"
#include "cstdlib"
#include <iostream>

grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	height = hght;
	width = wdth;
	pGame = pG;
	rows = height / config.gridSpacing;
	cols = width / config.gridSpacing;
	shapeCount = 0;

	//for (int i = 0; i < MaxShapeCount; i++)
	//	shapeList[i] = nullptr;

	activeShape = nullptr;

}

grid::~grid()
{
	//for (int i = 0; i < shapeCount; i++)
	//	delete shapeList[i];
}

void grid::draw() const
{
	clearGridArea();
	window* pWind = pGame->getWind();

	pWind->SetPen(config.gridDotsColor, 1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
	//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);

//Draw ALL shapes
	for (int i = 0; i < genShapeList.size(); i++)
		if (genShapeList[i])
			genShapeList[i]->draw();	//draw each shape

	//Draw the active shape
	if (activeShape)
		activeShape->draw();
}

void grid::clearGridArea() const
{
	window* pWind = pGame->getWind();
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(uprLeft.x, uprLeft.y, uprLeft.x + width, uprLeft.y + height);
}

//Adds a shape to the randomly created shapes list.
bool grid::addShape(shape* newShape)
{
	//TODO:
	// 1- Check that the shape can be drawn witout being clipped by grid boundaries
	// 2- check shape count doesn't exceed maximum count
	// return false if any of the checks fail
	return 0;
	//Here we assume that the above checks are passed
	//shapeList[shapeCount++] = newShape;
	//return true;
}

void grid::setActiveShape(shape* actShape)
{
	if (activeShape)
	{
		delete activeShape;
		activeShape = nullptr;
	}
	activeShape = actShape;
}


shape* grid::getActiveShape()
{
	return activeShape;
}

void grid::deleteActiveShape()
{
	if (activeShape) {
		delete activeShape;
		activeShape = nullptr;
	}
}

void grid::randShapeGen()
{
	int lev = pGame->getLevel();
	int noOfShapes = (2 * lev) - 1;
	srand(time(0));

	for (int i = 0; i < noOfShapes; i++)
	{

		toolbarItem gItem = toolbarItem((rand() % 6));
		int WindowWidth = config.windWidth;
		int WindowHeight = config.gridHeight;
		int boundaryOffsetX = config.gridSpacing*2;
		int boundaryOffsetY = config.gridSpacing * 3;
		int x = rand() % ((WindowWidth - 2 * boundaryOffsetX)/config.gridSpacing);
		int y = rand() % ((WindowHeight- 2 * boundaryOffsetY)/config.gridSpacing);
		point gPoint = { x*config.gridSpacing + boundaryOffsetX,y*config.gridSpacing + config.toolBarHeight + boundaryOffsetY};
		shape* genShape = nullptr;
		switch (gItem)
		{
		case ITM_CAR:
			genShape = new Car(pGame, gPoint);
			break;

		case ITM_BOAT:
			genShape = new Boat(pGame, gPoint);
			break;

		case ITM_ARR:
			genShape = new Arrow(pGame, gPoint);
			break;

		case ITM_PLANE:
			genShape = new Plane(pGame, gPoint);
			break;

		case ITM_HOUSE:
			genShape = new House(pGame, gPoint);
			break;

		case ITM_SIGN:
			genShape = new Sign(pGame, gPoint);
			break;
		}

		if (rand() % 2 == 0)
		{
			genShape->resize_down();
		}
		else
		{
			genShape->resize_up();
		}



		for (int i = 0; i < rand() % 4; i++)
		{
			genShape->rotate();
		}

		genShapeList.push_back(genShape);
	}
	shapeCount = genShapeList.size();
}

void grid::clearShapeVector()
{

	for (int i = 0; i < genShapeList.size(); i++)
	{
		delete genShapeList[i];
		genShapeList[i] = nullptr;
	}

	genShapeList.clear();
}

void grid::DrawRandomShapes()
{
	for (int i = 0; i < genShapeList.size(); i++)
	{
		genShapeList[i]->draw();

	}
}

int grid::Getnumrandshape()
{
	return genShapeList.size();
}

vector<shape*> grid::GetShapeVector()
{
	return genShapeList;
}

void grid::matching()
{
	int numShapes = (2 * pGame->getLevel()) - 1;
	int ms = 0;
	bool boolean = false;
	int c = 0;
	for (int i = 0; i < shapeCount; i++)
	{

		if (activeShape->matches(genShapeList[i]))
		{
			boolean = true;
			c = i;
			break;
		}

	}
	if(boolean){
		pGame->incScore(2);
		pGame->clearLevelScoreLives();
		pGame->DrawLevelScoreLives();
		delete activeShape;
		activeShape = nullptr;
		delete genShapeList[c];
		genShapeList[c] = nullptr;
		draw();
		numShapes--;
		ms++;
		pGame->printMessage("Matched shapes as of now: " + to_string(ms));
	}
	else
	{
		pGame->decScore(1);
		pGame->clearLevelScoreLives();
		pGame->DrawLevelScoreLives();
		pGame->printMessage("Matched shapes as of now: " + to_string(ms));

	}
}

int grid::getMatchedShapes() const
{
	return matchedShapes;
}



