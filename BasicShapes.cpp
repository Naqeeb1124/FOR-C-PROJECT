#include "BasicShapes.h"
#include "gameConfig.h"
#include "game.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////

Rect::Rect(game* r_pGame, point ref, int r_hght, int r_wdth) :shape(r_pGame, ref)
{
	pGame = r_pGame;
	hght = r_hght;
	wdth = r_wdth;
}

void Rect::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(config.penColor, config.penWidth);
	pW->SetBrush(config.fillColor);
	point upperLeft, lowerBottom;
	upperLeft.x = RefPoint.x - wdth / 2;
	upperLeft.y = RefPoint.y - hght / 2;
	lowerBottom.x = RefPoint.x + wdth / 2;
	lowerBottom.y = RefPoint.y + hght / 2;

	pW->DrawRectangle(upperLeft.x, upperLeft.y, lowerBottom.x, lowerBottom.y, FILLED);
}

void Rect::rotate()
{
	int temp = hght;
	wdth = hght;
	hght = wdth;
}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//TODO: Add implementation for class circle here
circle::circle(game* r_pGame, point ref, int r) :shape(r_pGame, ref)
{
	rad = r;
}

void circle::draw() const
{
	window* pW = pGame->getWind();	//get interface window
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawCircle(RefPoint.x, RefPoint.y, rad, FILLED);
} //circle doesnt need a rotate function.



////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////

triangle::triangle(game* r_pGame, point ref, point r_vert2, point r_vert3) :shape(r_pGame, ref)
{
	//vertex1 is the ref point
	vertex1 = ref;
	vertex2 = r_vert2;
	vertex3 = r_vert3;
}

void triangle::draw() const
{

	point v1 = vertex1, v2 = vertex2, v3 = vertex3;

	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawTriangle(vertex1.x, vertex1.y, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
}

void triangle::rotate()
{
	/*since the reference point of the triangle is at one of it's vertices, we can take it as the origin,
	and apply the transformation [[0,1],[-1,0]] to the other 2 vertices, giving us a 90 deg CLOCKWISE rotation.*/
	//after rotation the points will be:


	//check out the multiplybyMatrix() function in gameconfig.h.
	// vertex1 doesnt change.

	//for vertex 2
	vertex2 = multiplyByMatrix(vertex2);
	//for vertex 3
	vertex3 = multiplyByMatrix(vertex3);

}

////////////////////////////////////////////////////  class line  ///////////////////////////////////////

//THIS CLASS HAS BEEN MODIFIED BY ABDELRAHMAN MOHAMED TO BE ABLE TO ROTATE THE LINE.
line::line(game* r_pGame, point ref, point length) :shape(r_pGame, ref)
{
	lineLength = length;
}

void line::draw() const
{
	int x1 = RefPoint.x, y1 = RefPoint.y, x2 = x1 + lineLength.x;
	int y2 = y1 + lineLength.y;
	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->DrawLine(x1, y1, x2, y2);
}

void line::rotate()
{
	//x1,y1 is the origin so no transformation will occur.
	lineLength = multiplyByMatrix(lineLength);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////  class polygon  ///////////////////////////////////////
polygon::polygon(game* r_pGame, point ref, int r_pline1, int r_pline2, int r_hght) :shape(r_pGame, ref)
{
	Pline1 = r_pline1;
	Pline2 = r_pline2;
	hght = r_hght;
}

void polygon::draw() const
{
	int x1 = RefPoint.x - (Pline1 / 2), x2 = RefPoint.x + (Pline1 / 2), x3 = RefPoint.x - (Pline2 / 2), x4 = RefPoint.x + (Pline2 / 2), y1 = RefPoint.y + (hght / 2), y2 = RefPoint.y - (hght / 2);

	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawPolygon(x_coordinates_array, y_coordinates_array, FILLED);
}


void polygon::rotate()
{
	int temp;
	for (int i = 0; i < 4; i++) {
		temp = RefPoint.x - y_coordinates_array[i];
		y_coordinates_array[i] = RefPoint.y + x_coordinates_array[i];
		x_coordinates_array[i] = temp;
	}
}