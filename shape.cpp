#include "shape.h"
#include "game.h"
#include "gameConfig.h"


shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
}

void shape::setRefPoint(point p)
{
	RefPoint = p;
}

void shape::move(direction dir)
{	
	switch (dir)
	{
	case right:
		RefPoint.x += config.gridSpacing;
		break;
	case up:
		RefPoint.y += config.gridSpacing;
		break;
	case left:
		RefPoint.x -= config.gridSpacing;
		break;
	case down:
		RefPoint.y -= config.gridSpacing;
		break;
	}

}

point shape::multiplyByMatrix(point& p)
{
	//will be changed once approval for cmath is obtained.
	int newX = -p.y;
	int newY = p.x;
	point newP = { newX,newY };

	return newP;
}

point shape::getRefPoint()
{
	return RefPoint;
}

int shape::getStepCount() const 
{
	return stepCount;
}
