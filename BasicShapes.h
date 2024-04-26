//Header file for Basic shapes in the game
#pragma once
#include "shape.h"

////////////////////////////////////////////////////  class Rect  ///////////////////////////////////////
//Rectanle class
/*							wdth
					---------------------
					|					|
			hght    |		 x			|     x is the reference point of the rectangle
					|					|
					--------------------
*/
//Reference point of the rectangle is at the centre of it

class Rect :public shape
{
	int hght, wdth;	//height and width of the recangle
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw() const;
	virtual void rotate();


};


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	int rad;
public:
	circle(game* r_pGame, point ref, int r);	//add more parameters for the constructor if needed
	virtual void draw() const;
};


////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////
//Reference point of the triangle is at the vertex
class triangle :public shape
{
	//Add data memebrs for class triangle
	point vertex1, vertex2, vertex3;
public:
	triangle(game* r_pGame, point ref, point r_vert2, point r_vert3);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void rotate();
};

////////////////////////////////////////////////////  class line  ///////////////////////////////////////
//Reference point of the triangle is at a point of two points of the line
class line :public shape
{
	//Add data memebrs for class line
	point lineLength;
public:
	line(game* r_pGame, point ref, point length);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void rotate();
};

////////////////////////////////////////////////////  class polygon  ///////////////////////////////////////
//Reference point of the polygon is at the centre of the height taken from the centre of the base
class polygon :public shape
{
	//Add data memebrs for class polygon
	int Pline1;
	int Pline2;
	int hght;
	int x_coordinates_array[4];
	int y_coordinates_array[4];
public:
	polygon(game* r_pGame, point ref, int r_pline1, int r_pline2, int r_hght);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void rotate();
};