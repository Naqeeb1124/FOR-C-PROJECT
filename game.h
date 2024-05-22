#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"
#include "Timer.h"
#include "shape.h"
#include <sstream>


//Main class that coordinates the game operation
class game
{

	/// Add more members if needed

	toolbar* gameToolbar;
	
	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;
	int score;
	Timer gameTimer;
	bool isTimedGame;
	int Level = 1;
	int Score = 0;
	int Lives = 5;
public:
	game();
	~game();

	string getSrting() const;	 //Returns a string entered by the user
	void createWind(int, int, int, int); //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg) const;	//Print a message on Status bar
	void createToolBar();		//creates the toolbar
	void createGrid();		//creates the shapes grid

	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid

	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);
	void incScore(int s);
	void decScore(int s);
	bool checkStoI(string st);
	void clearLevelScoreLives() const;
	void DrawLevelScoreLives() const;
	void setLevel(int lev);
	int getLevel() const;
	void setScore(int sco);
	int getScore() const;
	void setLives(int liv);
	int getLives() const;
	void declives(int l);
	void shapeGeneration() const;
	void clearshapeVec() const;
	void run();	//start the game	
	//for the timer:
	//void startTimedGame(std::chrono::seconds duration);
	//void handleTimerTimeout();
	//void handleUserAction();


};

