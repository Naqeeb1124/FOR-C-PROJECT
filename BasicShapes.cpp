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
	hght = wdth;
	wdth = temp;
}

void Rect::resize_up()
{
	wdth *= 2;
	hght *= 2;

}

void Rect::resize_down()
{
	
	wdth /= 2;
	hght /= 2;
}

void Rect::flip()
{
	wdth *= -1;
	hght *= -1;

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
}
//circle doesnt need a rotate function.

void circle::resize_up()
{
	window* pW = pGame->getWind();	//get interface window
	pW->DrawCircle(RefPoint.x-rad, RefPoint.y-rad, rad, FILLED);
	rad *= 2;
}

void circle::resize_down()
{
	window* pW = pGame->getWind();	//get interface window
	pW->DrawCircle(RefPoint.x + rad, RefPoint.y + rad, rad, FILLED);
	rad /= 2;
}

void circle::flip()
{
}

void circle::rotate()
{

}


////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////
//TODO: Add implementation for class triangle here
triangle::triangle(game* r_pGame, point ref,point r_vert2, point r_vert3) :shape(r_pGame, ref)
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
	pW->DrawTriangle(vertex1.x,vertex1.y, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
}



void triangle::rotate()
{
	RefPoint = vertex1;
	// Translate the vertices relative to the reference point
	point rV2 = { vertex2.x - RefPoint.x, vertex2.y - RefPoint.y };
	point rV3 = { vertex3.x - RefPoint.x, vertex3.y - RefPoint.y };

	// Rotate the translated vertices
	point rotatedV2 = multiplyByMatrix(rV2);
	point rotatedV3 = multiplyByMatrix(rV3);

	// Update the vertices by adding the reference point back

	vertex2.x = RefPoint.x + rotatedV2.x;
	vertex2.y = RefPoint.y + rotatedV2.y;
	vertex3.x = RefPoint.x + rotatedV3.x;
	vertex3.y = RefPoint.y + rotatedV3.y;
}

point triangle::getVert2()
{
	return vertex2;
}
point triangle::getVert3()
{
	return vertex3;
}

point triangle::setvert3(point vert)
{
	return vertex3 = vert;
}

point triangle::setvert2(point vert)
{
	return vertex2 = vert;
}


void triangle::resize_up()
{
	 length_side_1 = sqrt(pow(vertex2.x - RefPoint.x, 2) + pow(vertex2.y - RefPoint.y, 2));
	 length_side_2 = sqrt(pow(vertex3.x - RefPoint.x, 2) + pow(vertex3.y - RefPoint.y, 2));
	 length_side_3 = sqrt(pow(vertex3.x - vertex2.x, 2) + pow(vertex3.y - vertex2.y, 2));
	 length_side_1 *= 2; length_side_2 *= 2; length_side_3 *= 2;
}

void triangle::resize_down()
{

	RefPoint.x /= 2; vertex2.x /= 2; vertex3.x /= 2;
	RefPoint.y /= 2; vertex2.y /= 2; vertex3.y /= 2;
}

void triangle::flip()
{	point
	temp = vertex1;  // Store the first vertex temporarily
	vertex1 = vertex3;      // Assign the third vertex to the first position
	vertex3 = temp;
}




////////////////////////////////////////////////////  class line  ///////////////////////////////////////
line::line(game* r_pGame, point ref, point Length) :shape(r_pGame, ref)
{
	lineLength = Length;
}

void line::draw() const {
	int x1 = RefPoint.x, y1 = RefPoint.y;
	int x2 = lineLength.x, y2 = lineLength.y;  
	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->DrawLine(x1, y1, x2, y2);
}

void line::rotate()
{
	//x1,y1 is the origin so no transformation will occur.
	point AbuOthman = { lineLength.x - RefPoint.x, lineLength.y - RefPoint.y };
	point newLength = multiplyByMatrix(AbuOthman);

	lineLength.x = RefPoint.x + newLength.x;
	lineLength.y = RefPoint.y + newLength.y;

}

point line::getPoint2()
{
	return lineLength;
}

void line::resize_up()
{
	lineLength.y *= 2; //////ISSUE
}

void line::resize_down()
{
	lineLength.y /= 2;	//////ISSUE
}

void line::flip()
{

}



////////////////////////////////////////////////////  class polygon  ///////////////////////////////////////
polygon::polygon(game* r_pGame, point ref, int r_pline1, int r_pline2, int r_hght) :shape(r_pGame, ref)
{
	Pline1 = r_pline1;
	Pline2 = r_pline2;
	hght = r_hght;


}

void polygon::draw() const
{
	int x1 = RefPoint.x - (Pline1 / 2), x2 = RefPoint.x + (Pline1 / 2), x3 = RefPoint.x - (Pline2 / 2), x4 = RefPoint.x + (Pline2 / 2);
	int y1 = RefPoint.y + (hght / 2), y2 = RefPoint.y - (hght / 2);
	const int x_coordinates_array[4] = { x3,x1,x2,x4 };
	const int y_coordinates_array[4] = { y1,y2,y2,y1 };

	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->SetBrush(fillColor);
	pW->DrawPolygon(x_coordinates_array, y_coordinates_array,4, FILLED);

}

void polygon::rotate()
{

}


void polygon::resize_up()
{
	Pline1 *= 2;
	Pline2 *= 2;
	hght *= 2;
}

void polygon::resize_down()
{

	Pline1 /= 2;
	Pline2 /= 2;
	hght /= 2;
}

void polygon::flip()
{
	int temp;
	temp = Pline1;
	Pline1 = Pline2;
	Pline2 = temp;
}
