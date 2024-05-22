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

bool Rect::matches(const shape* target) const {
	const Rect* targetRect = dynamic_cast<const Rect*>(target);
	if (targetRect) {
		
		return (hght - targetRect->hght) < config.gridSpacing && (wdth - targetRect->wdth) < config.gridSpacing && (RefPoint.x - targetRect->RefPoint.x) < config.gridSpacing && (RefPoint.y - targetRect->RefPoint.y) < config.gridSpacing;
		
	}
	return false;
}



void Rect::move(direction dir)
{
	point currentRef = getRefPoint();
	point newRef;
	switch (dir)
	{
	case Up:
		currentRef.y -= config.gridSpacing;
		break;
	case Left:
		currentRef.x -= config.gridSpacing;
		break;
	case Down:
		currentRef.y += config.gridSpacing;
		break;
	case Right:
		currentRef.x += config.gridSpacing;
		break;
	}setRefPoint(currentRef);
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
	pW->DrawCircle(RefPoint.x - rad, RefPoint.y - rad, rad, FILLED);
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

void circle::move(direction dir)
{
	point currentRef = getRefPoint();
	point newRef;
	switch (dir)
	{
	case Up:
		currentRef.y -= config.gridSpacing;
		break;
	case Left:
		currentRef.x -= config.gridSpacing;
		break;
	case Down:
		currentRef.y += config.gridSpacing;
		break;
	case Right:
		currentRef.x += config.gridSpacing;
		break;
	}setRefPoint(currentRef);
}

bool circle::matches(const shape* target) const {
	const circle* targetCircle = dynamic_cast<const circle*>(target);
	if (targetCircle) {
		return rad == targetCircle->rad && (RefPoint.x - targetCircle->RefPoint.x) < config.gridSpacing && (RefPoint.y - targetCircle->RefPoint.y) < config.gridSpacing;
	}
	return false;
}


////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////
//TODO: Add implementation for class triangle here
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

point triangle::getVert2() const
{
	return vertex2;
}
point triangle::getVert3() const
{
	return vertex3;
}

void triangle::setvert1(point v)
{
	vertex1 = v;
}

void triangle::setvert3(point vert)
{
	vertex3 = vert;
}

void triangle::setvert2(point vert)
{
	vertex2 = vert;
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
{
	point
		temp = vertex1;  // Store the first vertex temporarily
	vertex1 = vertex3;      // Assign the third vertex to the first position
	vertex3 = temp;
}

void triangle::move(direction dir)
{
	//just in case i have to update vertex2 and 3.
	point currentV2 = getVert2();
	point currentV3 = getVert3();
	switch (dir)
	{
	case Up:
		RefPoint.y -= config.gridSpacing;
		currentV2.y -= config.gridSpacing;
		currentV3.y -= config.gridSpacing;
		break;
	case Left:
		RefPoint.x -= config.gridSpacing;
		currentV2.x -= config.gridSpacing;
		currentV3.x -= config.gridSpacing;
		break;
	case Down:
		RefPoint.y += config.gridSpacing;
		currentV2.y += config.gridSpacing;
		currentV3.y += config.gridSpacing;
		break;
	case Right:
		RefPoint.x += config.gridSpacing;
		currentV2.x += config.gridSpacing;
		currentV3.x += config.gridSpacing;
		break;
	}setvert1(RefPoint), setvert2(currentV2), setvert3(currentV3);
}


bool triangle::matches(const shape* target) const {
	const triangle* targetTri = dynamic_cast<const triangle*>(target);
	if (targetTri) {
		return (vertex1.x - targetTri->vertex1.x) < config.gridSpacing  && (vertex1.y - targetTri->vertex1.y) < config.gridSpacing  && (vertex2.x - targetTri->vertex2.x) < config.gridSpacing && (vertex2.y - targetTri->vertex2.y) < config.gridSpacing && (vertex3.x - targetTri->vertex3.x) < config.gridSpacing && (vertex3.y - targetTri->vertex3.y) < config.gridSpacing;
	}
	return false;
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

point line::getPoint2() const
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

void line::setPoint2(point p)
{
	lineLength = p;
}
void line::flip()
{

}

void line::move(direction dir)
{
	point currentRef = getRefPoint();
	point newRef;
	point currPoint2 = getPoint2();
	switch (dir)
	{
	case Up:
		currentRef.y -= config.gridSpacing;
		currPoint2.y -= config.gridSpacing;
		break;
	case Left:
		currentRef.x -= config.gridSpacing;
		currPoint2.x -= config.gridSpacing;

		break;
	case Down:
		currentRef.y += config.gridSpacing;
		currPoint2.y += config.gridSpacing;

		break;
	case Right:
		currentRef.x += config.gridSpacing;
		currPoint2.x += config.gridSpacing;

		break;
	}setRefPoint(currentRef), setPoint2(currPoint2);
}

bool line::matches(const shape* target) const {
	const line* targetLine = dynamic_cast<const line*>(target);
	if (targetLine) {
		return (lineLength.x - targetLine->lineLength.x) < config.gridSpacing && (lineLength.y - targetLine->lineLength.y)<config.gridSpacing && (RefPoint.x - targetLine->RefPoint.x) < config.gridSpacing;
	}
	return false;
}




