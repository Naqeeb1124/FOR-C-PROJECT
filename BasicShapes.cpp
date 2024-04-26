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

void Rect::resize_up()
{
	wdth * 2;
	hght * 2;
}

void Rect::resize_down()
{
	wdth / 2;
	hght / 2;
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
} //circle doesnt need a rotate function.

void circle::resize_up()
{
	rad * 2;
}

void circle::resize_down()
{
	rad / 2;
}

void circle::flip()
{
}

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



void triangle::resize_up()
{
	RefPoint.x *= 2; vertex2.x *= 2; vertex3.x *= 2;
	RefPoint.y *= 2; vertex2.y *= 2; vertex3.y *= 2;
}

void triangle::resize_down()
{

	RefPoint.x /= 2; vertex2.x /= 2; vertex3.x /= 2;
	RefPoint.y /= 2; vertex2.y /= 2; vertex3.y /= 2;
}

void triangle::flip()
{
	RefPoint.y;
	vertex2.y;
	vertex3.y;
	double factor, factor22, factor3;
	if (vertex2.y < vertex3.y || vertex2.y == vertex3.y && RefPoint.y >vertex3.y && RefPoint.y > vertex2.y)
	{
		factor = RefPoint.y - vertex3.y;
		factor22 = RefPoint.y - vertex2.y;
		RefPoint.y -= factor;
		vertex3.y += factor;
		vertex2.y += factor22;
		factor3 = vertex3.y - vertex2.y;
		vertex3.y -= factor3;
	}

	else if (vertex2.y > vertex3.y && RefPoint.y > vertex3.y && RefPoint.y > vertex2.y)
	{
		factor = RefPoint.y - vertex2.y;
		factor22 = RefPoint.y - vertex3.y;
		RefPoint.y -= factor;
		vertex3.y += factor22;
		vertex2.y += factor;
		factor3 = vertex2.y - vertex3.y;
		vertex2.y -= factor3;
	}
	else if (vertex2.y < vertex3.y || vertex2.y == vertex3.y && RefPoint.y < vertex3.y && RefPoint.y < vertex2.y)
	{
		factor = vertex3.y - RefPoint.y;
		factor22 = vertex2.y - RefPoint.y;
		RefPoint.y += factor;
		vertex3.y -= factor;
		vertex2.y -= factor22;
		factor3 = vertex3.y - vertex2.y;
		vertex3.y -= factor3;
	}
	else if (vertex2.y > vertex3.y || vertex2.y == vertex3.y && RefPoint.y < vertex3.y && RefPoint.y < vertex2.y)
	{
		factor = -RefPoint.y + vertex2.y;
		factor22 = -RefPoint.y + vertex3.y;
		RefPoint.y += factor;
		vertex3.y -= factor22;
		vertex2.y -= factor;
		factor3 = vertex2.y - vertex3.y;
		vertex2.y -= factor3;
	}
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

void line::resize_up()
{
	length * 2;
}

void line::resize_down()
{
	length / 2;
}

void line::flip()
{

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
	int temp;
	for (int i = 0; i < 4; i++) {
		temp = RefPoint.x - y_coordinates_array[i];
		y_coordinates_array[i] = RefPoint.y + x_coordinates_array[i];
		x_coordinates_array[i] = temp;
	}
} //to be rechecked later



void polygon::resize_up()
{
	Pline1 * 2;
	Pline2 * 2;
	hght * 2;
}

void polygon::resize_down()
{

	Pline1 / 2;
	Pline2 / 2;
	hght / 2;
}

void polygon::flip()
{
	int temp;
	temp = Pline1;
	Pline1 = Pline2;
	Pline2 = temp;
}
