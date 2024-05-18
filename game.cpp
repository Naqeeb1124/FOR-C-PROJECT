#include "game.h"
#include "gameConfig.h"



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
	delete pWind;
	delete shapesGrid;
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
	operation* op=nullptr;
	switch (clickedItem)
	{
	case ITM_BOAT:
		printMessage("You clicked on the Boat");
		op = new move_shape(this);
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
		op = new delete_shappe(this);
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
		op = new move_shape(this);
		break;
	//case ADD THE MOVE IMAGE HERE:
	//	printMessage("You clicked on the 'Select Level' operation");
	//	op = new move_shape(this);
	//	break;
	//case ITM_EXIT:
	//	op = new operExit(this);
	//	break;
	}
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

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}



////////////////////////////////////////////////////////////////////////
void game::run() 
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT (CIE 101 / CIE202 - project) - - - - - - - - - -");
	toolbarItem clickedItem=ITM_CNT;
	do
	{
		//printMessage("Ready...");
		//1- Get user click
		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem=gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			operation* op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();

			//4-Redraw the grid after each action
			shapesGrid->draw();


			//Print Message for the user in the statusbar if s/he clicked on an icon in the toolbar

		}	

	} while (clickedItem!=ITM_EXIT);
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

int game::incScore2() {
	int score = getScore();
	score += 2;
	setScore(score);
}

int game::setScore(int s){
	score = s;
}

int game::incScore1()
{
	int score = getScore();
	score++;
	setScore(score);
}


int game::decScore1() {
	int score = getScore();
	score--;
	setScore(score);
}

int game::getScore() const {
	return score;
}
