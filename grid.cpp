#include "grid.h"
#include "game.h"
#include "gameConfig.h"


grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	height = hght;
	width = wdth;
	pGame = pG;
	rows = height / config.gridSpacing;
	cols = width / config.gridSpacing;
	shapeCount = 0;

	for (int i = 0; i < MaxShapeCount; i++)
		shapeList[i] = nullptr;

	activeShape = nullptr;

}

grid::~grid()
{
	for (int i = 0; i < shapeCount; i++)
		delete shapeList[i];
}

void grid::draw() const
{
	clearGridArea();
	window* pWind = pGame->getWind();
	
	pWind->SetPen(config.gridDotsColor,1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
			//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);

	//Draw ALL shapes
	for (int i = 0; i < shapeCount; i++)
			if (shapeList[i])
				shapeList[i]->draw();	//draw each shape

	//Draw the active shape
	if(activeShape)
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
	
	//Here we assume that the above checks are passed
	shapeList[shapeCount++] = newShape;
	return true;
}


void grid::setActiveShape(shape* activeShape)
{
	activeShape = actShape;
}

shape* grid::getActiveShape()
{
	return activeShape;
}

void grid::deleteActiveShape(shape* activeShape)
{
	delete activeShape;
	activeShape = nullptr;   ///Done by Ziad and it will be a comment until we find the problem
}

//void grid::draw_delete() const
//{
	//clearGridArea();
	//window* pWind = pGame->getWind();

	//pWind->SetPen(config.gridDotsColor, 1);
	//pWind->SetBrush(config.gridDotsColor);

	////draw dots showing the grid reference points
	//for (int r = 1; r < rows; r++)
		//for (int c = 0; c < cols; c++)
			//pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
	////pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);

////Draw ALL shapes
	//for (int i = 0; i < shapeCount; i++)
		//if (shapeList[i])
			//shapeList[i]->draw();	//draw each shape
//}

shape* grid::getRandomShape() const {
    if (shapeCount > 0) {
        int randomIndex = rand() % shapeCount;
        return shapeList[randomIndex];
    }
    return nullptr; // if no naqqar available
}




void grid::addshapes()
{
	toolbar* toool = pGame->gettoolbar();
	int level = toool->getlevel();
	int numShapesToAdd = 0;

	switch (level-1)
	{
	case level1:
		numShapesToAdd = 1;
		break;
	case level2:
		numShapesToAdd = 3;
		break;
	case level3:
		numShapesToAdd = 5;
		break;
	case leveln:
		numShapesToAdd = 2 * level - 1;
		break;
	default:
		return; 
	}

	for (int i = 0; i < numShapesToAdd; i++)
	{
		int randomNum = rand() % 6; // Generate a new random number for each shape
		point randomPoint = { config.ranRefx,config.ranRefy };
		shape* newShape = nullptr;
		switch (randomNum)
		{
		case 0: 
			newShape = new House(pGame, randomPoint); 
			break;
		case 1: 
			newShape = new Sign(pGame, randomPoint); 
			break;
		case 2: 
			newShape = new Boat(pGame, randomPoint); 
			break;
		case 3: 
			newShape = new Plane(pGame, randomPoint); 
			break;
		case 4: 
			newShape = new Car(pGame, randomPoint); 
			break;
		case 5: 
			newShape = new Arrow(pGame, randomPoint); 
			break;
		}
		if (newShape) {
			int rotate = rand() % 3;
			switch (rotate)
			{case 1:
				newShape->resize_up();
				break;
			case 2:
				newShape->resize_down();
			case 3:
				newShape->rotate();
				break;
			default:
				break;
			}
			int rotate = rand() % 3;
			switch (rotate)
			{case 1:
				newShape->rotate();
				break;
			case 2:
				newShape->rotate();
				newShape->rotate();
				break;
			case 3:
				newShape->rotate();
				newShape->rotate();
				newShape->rotate();
				break;
			default:
				break;
			}
			
			addShape(newShape);
		} 
		else {
			delete newShape; // Failed to add shape, delete it
		}
	}
}




