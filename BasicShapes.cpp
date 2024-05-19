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

void Rect::setFillColor(color c)
{
	fillColor = c;
}

void Rect::save(ofstream& OutFile)const
{
	OutFile << "RECT " << RefPoint.x << " " << RefPoint.y << " " << hght << " " << wdth << " "
		<< fillColor.ucRed << " " << fillColor.ucGreen << " " << fillColor.ucBlue << " " << borderColor.ucRed
		<< " " << borderColor.ucGreen << " " << borderColor.ucBlue << endl;
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

bool Rect::matches(const shape* target) const {
	const Rect* targetRect = dynamic_cast<const Rect*>(target);
	if (targetRect) {
		return hght == targetRect->hght && wdth == targetRect->wdth;
	}
	return false;
}

	bool Rect::check_boundries()
	{
		POINT upper_right, lower_left;
		upper_right.y = RefPoint.y - hght / 2;
		upper_right.x = RefPoint.x + wdth / 2;
		lower_left.y = RefPoint.y + hght / 2;
		lower_left.x = RefPoint.x - wdth / 2;
		if (upper_right.y > config.remainingHeight || upper_right.y<config.toolBarHeight || lower_left.y>config.remainingHeight || lower_left.y < config.toolBarHeight)
		{
			return true;
		}
		if (upper_right.x > config.windWidth || upper_right.x < config.wx)
		{
			return true;
		}
		else
			return false;
	}

////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//TODO: Add implementation for class circle here
circle::circle(game* r_pGame, point ref, int r) :shape(r_pGame, ref)
{
	rad = r;
}


void circle::save(ofstream& OutFile) const
{
	OutFile << "CIRCLE " << RefPoint.x << " " << RefPoint.y << " " << rad << " " <<
		fillColor.ucRed << " " << fillColor.ucGreen << " " << fillColor.ucBlue << " " <<
		borderColor.ucRed << " " << borderColor.ucGreen << " " << borderColor.ucBlue << endl;
}

void circle::setFillColor(color c)
{
	fillColor = c;
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

bool circle::check_boundries()
{
	point upper_right, lower_left;
	upper_right.x = rad + RefPoint.x;
	upper_right.y = rad - RefPoint.y;
	lower_left.x = rad - RefPoint.x;
	lower_left.y = rad + RefPoint.y;
	if (upper_right.y > config.remainingHeight || upper_right.y<config.toolBarHeight || lower_left.y>config.remainingHeight || lower_left.y < config.toolBarHeight)
		return true;
	if (upper_right.x > config.windWidth || upper_right.x < config.wx || lower_left.x > config.windWidth || lower_left.x < config.wx)
		return true;
	else
		return false;
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

void triangle::setFillColor(color c)
{
	fillColor = c;
}

void triangle::save(ofstream& OutFile) const
{
	OutFile << "TRINGLE " << vertex1.x << " " << vertex1.y << " " << vertex2.x << " " << vertex2.y << " "
		<< vertex3.x << " " << vertex3.y << " " << fillColor.ucRed << " " << fillColor.ucGreen << " " << fillColor.ucBlue <<
		" " << borderColor.ucRed << " " << borderColor.ucGreen << " " << borderColor.ucBlue << endl;
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

bool triangle::check_boundries()
{
	point ver1 = getvert1(), ver3 = getVert3(), ver2 = getVert2();
	if (ver1.y > config.remainingHeight || ver1.y<config.toolBarHeight || ver2.y>config.remainingHeight || ver2.y < config.toolBarHeight || ver3.y>config.remainingHeight || ver3.y < config.toolBarHeight)
		return true;
	if (ver1.x > config.windWidth || ver1.x<config.wx || ver2.x>config.windWidth || ver2.x < config.wx || ver3.x>config.windWidth || ver3.x < config.wx)
		return true;
	else
		return false;
}


////////////////////////////////////////////////////  class line  ///////////////////////////////////////
line::line(game* r_pGame, point ref, point Length) :shape(r_pGame, ref)
{
	lineLength = Length;
}

void line::setFillColor(color c)
{
	fillColor = c;
}

void line::draw() const {
	int x1 = RefPoint.x, y1 = RefPoint.y;
	int x2 = lineLength.x, y2 = lineLength.y;  
	window* pW = pGame->getWind();
	pW->SetPen(borderColor, config.penWidth);
	pW->DrawLine(x1, y1, x2, y2);
}


void line::save(ofstream& OutFile) const
{
	OutFile << "LINE " << RefPoint.x << " " << RefPoint.y << " " << lineLength.x << " " << lineLength.y << " "
		<< fillColor.ucRed << " " << fillColor.ucGreen << " " << fillColor.ucBlue << " " <<
		borderColor.ucRed << " " << borderColor.ucGreen << " " << borderColor.ucBlue << endl;
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

bool line::check_boundries()
{
	point point1 = RefPoint, point2 = lineLength;
	if (point2.x > config.windWidth || point2.x<config.wx || point1.x>config.windWidth || point1.x < config.wx)
		return true;
	if (point1.y > config.remainingHeight || point2.y > config.remainingHeight || point1.y < config.toolBarHeight || point2.y < config.toolBarHeight)
		return true;
	else
		return false;
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

void polygon::save(ofstream& OutFile) const
{
	OutFile << "POLYGON " << RefPoint.x << " " << RefPoint.y << " " << Pline1 << " " << Pline2 << " " << hght << " " <<
		fillColor.ucRed << " " << fillColor.ucGreen << " " << fillColor.ucBlue << " " << borderColor.ucRed << " " <<
		borderColor.ucGreen << " " << borderColor.ucBlue << endl;
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

void polygon::setFillColor(color c)
{
	fillColor = c;
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

bool polygon::check_boundries()
{
	point upper_right, upper_left, upper, lower_right, lower_left;
	upper_right = { Pline1 / 2 + RefPoint.x,hght / 2 - RefPoint.y };
	upper_left = { Pline1 / 2 - RefPoint.x,hght / 2 - RefPoint.y };
	lower_right = { Pline2 / 2 + RefPoint.x,hght / 2 + RefPoint.y };
	lower_left = { Pline2 / 2 - RefPoint.x,hght / 2 + RefPoint.y };
	if (upper_right.x > config.windWidth || upper_left.x<config.wx || upper_left.x>config.windWidth || upper_right.x < config.wx)
		return true;
	if (lower_right.x > config.windWidth || lower_left.x<config.wx || lower_left.x>config.windWidth || lower_right.x < config.wx)
		return true;
	if (upper_right.y > config.remainingHeight || upper_left.y<config.toolBarHeight || upper_left.y>config.remainingHeight || upper_right.y < config.toolBarHeight)
		return true;
	if (lower_right.y > config.remainingHeight || lower_left.y<config.toolBarHeight || lower_left.y>config.remainingHeight || lower_right.y < config.toolBarHeight)
		return true;
	else
		return false;
}
