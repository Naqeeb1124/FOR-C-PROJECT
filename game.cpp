#include "game.h"
#include "gameConfig.h"

#include <iostream>

game::game()
{

	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//Create and draw the toolbar
	createToolBar();

	//Create and draw the grid
	createGrid();
	shapesGrid->draw();	//draw the grid and all shapes it contains.

	//Create and clear the status bar
	clearStatusBar();
}

game::~game()
{
	this->clearshapeVec();
	delete pWind;
	delete shapesGrid;
	delete gameToolbar;
}


//////////////////////////////////////////////////////////////////////////////////////////
void game::createWind(int w, int h, int x, int y) 
{
	pWind = new window(w, h, x, y);
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->DrawRectangle(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}
//---------------Clear Sc/lev/live-------------

void game::clearLevelScoreLives() const
{

	int Xco = (config.toolbarItemWidth * (ITM_CNT));
	int Yco = config.toolBarHeight;
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(Xco, 0, 1350, Yco - 1);
}
//---------------Draw Level/score/live---------------------
void game::DrawLevelScoreLives() const
{
	string sLevel = "Level: " + to_string(Level);
	int XLevel = (((config.windWidth - (config.toolbarItemWidth * (ITM_CNT - 1))) / 2) + (config.toolbarItemWidth * (ITM_CNT - 1)));
	int YLevel = (2 * config.toolBarHeight) / 3;
	pWind->SetPen(BLACK, 1);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(XLevel - 15, YLevel, sLevel);


	string sScore = "Score: " + to_string(Score);
	int XScore = (((config.windWidth - (config.toolbarItemWidth * (ITM_CNT - 1))) / 2) + (config.toolbarItemWidth * (ITM_CNT - 1)));
	int YScore = config.toolBarHeight / 3;
	pWind->SetPen(BLACK, 1);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(XScore - 15, YScore, sScore);

	string sLives = "Lives: " + to_string(Lives);
	int XLives = (((config.windWidth - (config.toolbarItemWidth * (ITM_CNT - 1))) / 2) + (config.toolbarItemWidth * (ITM_CNT - 1)));
	int YLives = 0;
	pWind->SetPen(BLACK, 1);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(XLives - 15, YLives, sLives);
}
//--------------- Level---------------------

void game::setLevel(int lev)
{
	Level = lev;
}

int game::getLevel() const
{
	return Level;
}

//--------------- Score---------------------

void game::setScore(int sco)
{
	Score = sco;
}

int game::getScore() const
{
	return Score;
}

//--------------- Lives---------------------

void game::setLives(int liv)
{
	Lives = liv;
}

int game::getLives() const
{
	return Lives;
}

void game::declives(int l)
{
	Lives = Lives - l;
}

//--------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the mode
void game::createToolBar()
{
	gameToolbar = new toolbar(this);
}

void game::createGrid()
{	
	//calc some grid parameters
	point gridUpperLeftPoint = { 0, config.toolBarHeight };
	int gridHeight = config.windHeight - config.toolBarHeight - config.statusBarHeight;
	//create the grid
	shapesGrid = new grid(gridUpperLeftPoint, config.windWidth, gridHeight, this);
}


operation* game::createRequiredOperation(toolbarItem clickedItem)
{
	operation* op = nullptr;
	switch (clickedItem)
	{
	case ITM_BOAT:
		printMessage("You clicked on the Boat");
		op = new operAddBoat(this);
		break;
	case ITM_CAR:
		printMessage("You clicked on the Car");
		op = new operAddCar(this);
		break;
	case ITM_PLANE:
		printMessage("You clicked on the Plane");
		op = new operAddPlane(this);
		break;
	case ITM_ARR:
		printMessage("You clicked on the Arrow");
		op = new operAddArrow(this);
		break;
	case ITM_HOUSE:
		printMessage("You clicked on the House");
		op = new operAddHouse(this);
		break;
	case ITM_SIGN:
		printMessage("You clicked on the Sign");
		op = new operAddSign(this);
		break;
	case ITM_ZOOMIN:
		printMessage("You clicked on the 'Zoom In' operation");
		op = new operZoomIn(this);
		break;
	case ITM_ZOOMOUT:
		printMessage("You clicked on the 'Zoom Out' operation");
		op = new operZoomOut(this);
		break;
	case ITM_ROTATE:
		printMessage("You clicked on the 'Rotate' operation");
		op = new operRotate(this);
		break;
	case ITM_FLIP:
		printMessage("You clicked on the 'Flip' operation");
		op = new operFlip(this);
		break;
	case ITM_REFRESH:
		printMessage("You clicked on the 'Refresh' operation");
		op = new operRefresh(this);
		break;
	case ITM_HINT:
		printMessage("You clicked on the 'Hint' operation");
		op = new operHint(this);
		break;
	case ITM_DELETE:
		printMessage("You clicked on the 'Delete' operation");
		op = new operDelete(this);
		break;
	case ITM_SAVE:
		printMessage("You clicked on the 'Save' operation");
		op = new operSave(this);
		break;
	case ITM_LOAD:
		printMessage("You clicked on the 'Load' operation");
		op = new operLoad(this);
		break;
	case ITM_SELECTLEVEL:
		printMessage("You clicked on the 'Select Level' operation");
		op = new operSelectLevel(this);
		break;
	}
	//case ADD THE MOVE IMAGE HERE:
	//	printMessage("You clicked on the 'Select Level' operation");
	//	op = new move_shape(this);
	//	break;
	//case ITM_EXIT:
	//	op = new operExit(this);
	//	break;
	return op;
}


//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}



string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

bool game::checkStoI(string st)
{
	int counter = 0;
	for (int i = 0; i < st.length(); i++)
	{
		if (st[i] >= '0' && st[i] <= '9')
		{
			counter++;
		}

	}
	if (counter == st.length())
		return true;
	else
		return false;
}
grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}



////////////////////////////////////////////////////////////////////////
void game::run()
{
	srand(time(0));

	char PressedKey{};
	keytype K;
	pWind->FlushKeyQueue();
	pWind->FlushMouseQueue();
	grid* pGrid = this->getGrid();
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	shape* actShape = pGrid->getActiveShape();

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT (CIE 101 / CIE202 - project) - - - - - - - - - -");
	toolbarItem clickedItem = ITM_CNT;
	this->shapeGeneration();
	//matching();
	do
	{

		actShape = pGrid->getActiveShape();
		pWind->GetKeyPress(PressedKey);
		if (actShape != nullptr) {

			if (PressedKey) {
				cout << " " << actShape->getRefPoint().x << " " << actShape->getRefPoint().y << endl;

				if (PressedKey == 32)
				{
					pGrid->matching();

				}
				if (PressedKey == 8 || PressedKey == 'w' || PressedKey == 'W')
				{
					pGrid->getActiveShape()->move(Up);
					pGrid->draw();

				}
				if (PressedKey == 2 || PressedKey == 's' || PressedKey == 'S')
				{
					pGrid->getActiveShape()->move(Down);
					pGrid->draw();
				}
				if (PressedKey == 6 || PressedKey == 'd' || PressedKey == 'D')
				{
					pGrid->getActiveShape()->move(Right);
					pGrid->draw();
				}
				if (PressedKey == 4 || PressedKey == 'a' || PressedKey == 'A')
				{
					pGrid->getActiveShape()->move(Left);
					pGrid->draw();
				}
			}
		}


		//printMessage("Ready...");
		//1- Get user click
		pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem = gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			operation* op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

			//4-Redraw the grid after each action
			shapesGrid->draw();


			//Print Message for the user in the statusbar if s/he clicked on an icon in the toolbar
		}

	} while (clickedItem != ITM_EXIT);
}



void game::shapeGeneration() const
{
	grid* pGrid = this->getGrid();
	pGrid->randShapeGen();
	pGrid->DrawRandomShapes();

}
void game::clearshapeVec() const
{
	grid* pGrid = this->getGrid();
	pGrid->clearShapeVector();
}




//for timer


//void game::startTimedGame(std::chrono::seconds duration) {
//	isTimedGame = true;
//	gameTimer.start(duration, [this]() {
//		// Handle timer timeout
//		handleTimerTimeout();
//		});
////}
//
//void game::handleTimerTimeout() {
//	// Decrement player lives
//	decrementPlayerLives();
//
//	// Reset the timer
//	gameTimer.stop();
//
//	// Restart the timer if the player still has lives left
//	if (hasRemainingLives()) {
//		startTimedGame(/* desired duration */);
//	}
//	else {
//		// Game over
//		handleGameOver();
//	}
//}

//void game::handleUserAction() {
//	// Start the timer if it's a timed game and the timer is not running
//	if (isTimedGame && !gameTimer.isTimerRunning()) {
//		startTimedGame(//later);
//	}
//
//	// Handle user action (rotate, resize, move, etc.)
//	// ...
//}

void game::incScore(int s) {
	Score += s;
	setScore(Score);
}





void game::decScore(int s) {
	Score -= s;
	setScore(Score);
}
