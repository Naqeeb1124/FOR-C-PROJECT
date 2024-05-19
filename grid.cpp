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





void grid::addshapes(int level) {
	int numShapesToAdd = getnumofshapes(level);
	color shapecolor;

	for (int i = 0; i < numShapesToAdd; i++) {
		int shapeType = rand() % 6;
		shape* newShape = nullptr;
		point randomPoint;

		do {
			int ranRefx = (rand() % (width - 10)) + uprLeft.x + 30;
			int ranRefy = (rand() % (height - 10)) + uprLeft.y + 30;
			randomPoint = { ranRefx, ranRefy };

			if (level >= 3) {
				shapecolor = BLACK;
			}
			else {
				shapecolor = color(rand() % 256, rand() % 256, rand() % 256);
			}

			switch (shapeType) {
			case 0: newShape = new House(pGame, randomPoint); break;
			case 1: newShape = new Sign(pGame, randomPoint); break;
			case 2: newShape = new Boat(pGame, randomPoint); break;
			case 3: newShape = new Plane(pGame, randomPoint); break;
			case 4: newShape = new Car(pGame, randomPoint); break;
			case 5: newShape = new Arrow(pGame, randomPoint); break;
			}

			if (newShape) {
				newShape->setFillColor(shapecolor);

				bool shouldRotate = rand() % 2;
				if (shouldRotate) {
					newShape->flip();
				}

				bool shouldResize = rand() % 2;
				if (shouldResize) {
					int upordown = rand() % 2;
					if (upordown == 0) {
						newShape->resize_down();
					}
					else {
						newShape->resize_up();
					}
				}
			}
		} while (newShape && newShape->check_boundries());

		if (newShape) {
			addShape(newShape);
		}
	}
}



int grid::geetshapecount()
{
	return shapeCount;
}

shape** grid::shapelistt()
{
	return shapeList;
}








