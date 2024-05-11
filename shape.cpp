#include "shape.h"
#include "game.h"
#include "gameConfig.h"


shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	stepCount = 0;
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
