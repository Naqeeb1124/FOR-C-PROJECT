#pragma once
#include "CMUgraphicsLib/CMUgraphics.h"


//The folowing struct contains all game configurations
// (MAY be loaded from a configuration file later)
__declspec(selectany) //This line to prevent "redefinition error"
struct 		
{
	int	windWidth=1300, windHeight=700,	//Window width and height
		wx=5, wy=5,			//Window starting coordinates

		//The window is divded into 3 areas: toolbar, Working area, and statusbar
		toolBarHeight=60,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		toolbarItemWidth = 70,			//Width of each icon in toolbar
		statusBarHeight=50;	//Status Bar Height
	
	int remainingHeight = windHeight - toolBarHeight - statusBarHeight;

	int gridHeight = int(remainingHeight * (2 / 3.0)); 		//The grid is where bricks can be drawn

	//Default colors
	color	penColor = RED,			//color used to draw borders/write messages
			fillColor = RED,			//shapes fill color (Default)
			bkGrndColor= LAVENDER,		//Screen Background color
			statusBarColor = LIGHTSEAGREEN;	//background color of the status
	int penWidth=3;			//width of the pen that draws shapes


	color gridDotsColor = RED;
	int gridSpacing=30;	//spacing between grid points

	////// Configuration for the composite shapes //////
	// default Ref Point for any newly created shape 
	int RefX = windWidth *  (2.0 / 3);
	int RefY = windHeight * (0.5);

	////-----  Sign Shape Confoguration ---------////
	// For the Sign shape, define width and height of both rectangles
	struct {
		int baseWdth = 20, baseHeight = 80;
		int topWdth = 100, topHeight = 50;
	}sighShape;
	// FOLLOWING STRUCTS ARE BY ABDELRAHMAN MOHAMED
	struct {
		int baseWdth = 100, baseHeight = 80;
		int roofWdth = 120, roofHeight = 60;
	}houseShape;

	struct {
		int lowWdth = 100, lowHeight = 30;
		int upTOPWdth = 70, upBOTWdth = 100, upHeight = 20;
		int tireRadius = 10;
	}carShape;

	struct {
		int tHullWdth = 100, bHullWdth = 60, hullHeight = 30;
		int sailWdth = 80, sailHeight = 40;
		int mastHeight = 40;
	}boatShape;

	struct {
		int fuselageWdth = 100, fuselageHeight = 25;
		int noseWdth = 25, noseHeight = 25;
		int tailWdth = 35, tailHeight = 25;
		int wingHeight = 50, wingWidth = 20, wingSweep = 10;
		int stabHeight = 25, stabWdth = 20, stabSweep = 10;
	}planeShape;

	struct {
		int shaftWdth = 100, shaftHeight = 30;
		int headWdth = 40, headHeight = 60;
	}arrowShape;
}config;


enum toolbarItem //The items of the  toolbar (you should add more items)
{
	//Note: Items are ordered here as they appear in the toolbar
	//If you want to change the toolbar items order, just change the order here
	ITM_BOAT,		//Draw Boat on the grid

	ITM_CAR,		//Draw Car on the grid

	ITM_PLANE,		//Draw Plane on the grid

	ITM_ROCKET,		//Draw Rocket on the grid

	ITM_TOWER,		//Draw Tower on the grid

	ITM_TREE,		//Draw Tree on the grid
	
	ITM_ZOOMIN,		//Zoom in shape

	ITM_ZOOMOUT,	//Zoom out shape

	ITM_ROTATE,		//Rotate shape CW

	ITM_FLIP,		//Flip Shape

	ITM_REFRESH,	//Reset game

	ITM_HINT,		//Give hint to player

	ITM_DELETE,		//Delete shape

	ITM_SAVE,	//Save game

	ITM_LOAD,	//Load game

	ITM_SELECTLEVEL,  //Select game level

	ITM_EXIT,		//Exit game
	//TODO: Add more items names here

	ITM_CNT		//no. of toolbar items ==> This should be the last line in this enum

};

//function to make rotate easier:

point multiplyByMatrix(const point& p) {
	int newX = p.y;
	int newY = -p.x;
	point newP = { newX,newY };

	return newP;
}

