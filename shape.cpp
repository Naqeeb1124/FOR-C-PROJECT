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





point shape::multiplyByMatrix(point& p)
{
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

void shape::move(direction dir)
{
	point newRef{};
	switch (dir)
	{
	case Up:
		newRef.y = RefPoint.y - config.gridSpacing;
		break;
	case Down:
		newRef.y = RefPoint.y + config.gridSpacing;
		break;
	case Left:
		newRef.x = RefPoint.x - config.gridSpacing;
		break;
	case Right:
		newRef.x = RefPoint.x + config.gridSpacing;
		break;
	}
	this->setRefPoint(newRef);
}
