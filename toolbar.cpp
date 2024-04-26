#include "toolbar.h"
#include "game.h"
//#include "grid.h"


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(game* pG)
{	
	height = config.toolBarHeight;
	width = config.windWidth;
	this->pGame = pG;
	window* pWind = pGame->getWind();
	
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each toolbar item
	//TODO: Prepare image for each toolbar item and add it to the list

	toolbarItemImages[ITM_BOAT] = "Icons\\B.jpg";
	toolbarItemImages[ITM_CAR] = "Icons\\C.jpg";
	toolbarItemImages[ITM_PLANE] = "Icons\\P.jpg";
	toolbarItemImages[ITM_ROCKET] = "Icons\\R.jpg";
	toolbarItemImages[ITM_TOWER] = "Icons\\TW.jpg";
	toolbarItemImages[ITM_TREE] = "Icons\\TR.jpg";
	toolbarItemImages[ITM_ZOOMIN] = "Icons\\1.jpg";
	toolbarItemImages[ITM_ZOOMOUT] = "Icons\\2.jpg";
	toolbarItemImages[ITM_ROTATE] = "Icons\\3.jpg";
	toolbarItemImages[ITM_REFRESH] = "Icons\\4.jpg";
	toolbarItemImages[ITM_HINT] = "Icons\\5.jpg";
	toolbarItemImages[ITM_DELETE] = "Icons\\6.jpg";
	toolbarItemImages[ITM_SAVE] = "Icons\\7.jpg";
	toolbarItemImages[ITM_LOAD] = "Icons\\8.jpg";
	toolbarItemImages[ITM_SELECTLEVEL] = "Icons\\9.jpg";
	toolbarItemImages[ITM_EXIT] = "Icons\\10.jpg";
	

	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);


	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height,width , height);

	//Draw Lives/ Score/ Level
	
	//--Draw Lives--
	const string sLives = "5 Lives ";
	const int XLives = (((config.windWidth - (config.toolbarItemWidth * (ITM_CNT - 1))) / 2) + (config.toolbarItemWidth * (ITM_CNT - 1)));
	const int YLives = 0 ;
	pWind->SetPen(BLACK, 1);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(XLives, YLives, sLives);

	//--Draw Score--
	const string sScore = "Score: 0 ";
	const int XScore = (((config.windWidth - (config.toolbarItemWidth * (ITM_CNT - 1))) / 2) + (config.toolbarItemWidth * (ITM_CNT - 1)));
	const int YScore = config.toolBarHeight/3 ;
	pWind->SetPen(BLACK,1);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(XScore, YScore, sScore);

	//--Draw Level--
	const string sLevel = "Level: 0 ";
	const int XLevel = (((config.windWidth - (config.toolbarItemWidth * (ITM_CNT - 1))) / 2) + (config.toolbarItemWidth * (ITM_CNT - 1)));
	const int YLevel = (2*config.toolBarHeight) / 3;
	pWind->SetPen(BLACK,1);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(XLevel, YLevel, sLevel);
}



//handles clicks on toolbar icons, returns ITM_CNT if the click is not inside the toolbar
toolbarItem toolbar::getItemClicked(int x)
{
	
	if (x > ITM_CNT * config.toolbarItemWidth)	//click outside toolbar boundaries
		return ITM_CNT;
	
	
	//Check whick toolbar item was clicked
	//==> This assumes that toolbar items are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

	return (toolbarItem)(x / config.toolbarItemWidth);

}

