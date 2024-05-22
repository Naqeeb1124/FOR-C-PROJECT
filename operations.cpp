#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include "toolbar.h"
/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

//operAddSign::operAddSign(game* r_pGame):operation(r_pGame)

operAddBoat::operAddBoat(game* r_pGame) : operation(r_pGame)
{
}

operAddCar::operAddCar(game* r_pGame) : operation(r_pGame)
{
}


operAddPlane::operAddPlane(game* r_pGame) : operation(r_pGame)
{
}

operAddArrow::operAddArrow(game* r_pGame) : operation(r_pGame)
{
}


operAddHouse::operAddHouse(game* r_pGame) : operation(r_pGame)
{
}


operAddSign::operAddSign(game* r_pGame) : operation(r_pGame)
{
}



operZoomIn::operZoomIn(game* r_pGame) : operation(r_pGame)
{
}


operZoomOut::operZoomOut(game* r_pGame) : operation(r_pGame)
{
}


operRotate::operRotate(game* r_pGame) : operation(r_pGame)
{
}


operRefresh::operRefresh(game* r_pGame) : operation(r_pGame)
{
}

operFlip::operFlip(game* r_pGame) : operation(r_pGame)
{
}

operHint::operHint(game* r_pGame) : operation(r_pGame)
{
}


operDelete::operDelete(game* r_pGame) : operation(r_pGame)
{
}


operSave::operSave(game* r_pGame) : operation(r_pGame)
{
}


operLoad::operLoad(game* r_pGame) : operation(r_pGame)
{
}


operSelectLevel::operSelectLevel(game* r_pGame) : operation(r_pGame)
{
}

operExit::operExit(game* r_pGame) : operation(r_pGame)
{
}


void operAddBoat::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point BoatShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Boat(pGame, BoatShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

void operAddCar::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point CarShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Car(pGame, CarShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}


void operAddPlane::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point PlaneShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Plane(pGame, PlaneShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

void operAddArrow::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point ArrowShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Arrow(pGame, ArrowShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}


void operAddHouse::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point HouseShapeRef = { xGrid,yGrid };

	//create a house shape
	shape* psh = new House(pGame, HouseShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

void operAddSign::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

void operZoomIn::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
	{
		psh->resize_up();
	}
}

void operZoomOut::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
	{
		psh->resize_down();
	}
}

void operRotate::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
	{
		psh->rotate();
	}
}

void operFlip::Act()
{
	grid* pGrid = pGame->getGrid();
	shape* psh = pGrid->getActiveShape();
	if (psh)
	{
		psh->flip();
	}
}

void operRefresh::Act()
{
	int lives = pGame->getLives();
	if (lives > 0)
	{
		pGame->clearshapeVec();
		pGame->shapeGeneration();
		pGame->declives(1);
		pGame->clearLevelScoreLives();
		pGame->DrawLevelScoreLives();

	}
	else
	{
		pGame->printMessage("You cannot refresh Anymore");
	}

}

void operHint::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}

void operDelete::Act()
{
	grid* pGrid = pGame->getGrid();
	pGrid->deleteActiveShape();
}

void operSave::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

void operLoad::Act()
{

	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

void operSelectLevel::Act()
{
	window* pw = pGame->getWind();
	string level = pGame->getSrting();
	if (pGame->checkStoI(level))
	{
		int lev = stoi(level);
		switch (lev)
		{
		case 0:
			pGame->printMessage("Please Enter a valid number");
			break;
		default:
			pGame->clearshapeVec();
			pGame->clearLevelScoreLives();
			pGame->setLevel(lev);
			pGame->DrawLevelScoreLives();
			pw->FlushKeyQueue();
			pw->FlushMouseQueue();
			pGame->shapeGeneration();
		}
	}
	else
		pGame->printMessage("Please Enter a valid number");

}

void operExit::Act()
{
	grid* grid = pGame->getGrid();
	shape* psh = grid->getActiveShape();

	delete psh;
	psh = nullptr;

}
