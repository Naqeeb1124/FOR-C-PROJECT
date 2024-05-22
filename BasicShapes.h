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
	color c;
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	virtual void move(direction dir);
	bool matches(const shape* target) const override;




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
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	virtual void rotate();
	virtual void move(direction dir);
	bool matches(const shape* target) const;

};


////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////
//Reference point of the triangle is at the vertex
class triangle :public shape
{
	//Add data memebrs for class triangle
	point vertex1, vertex2, vertex3;
	double length_side_1 = 0;
	double length_side_2 = 0;
	double length_side_3 = 0;
public:
	triangle(game* r_pGame, point ref, point r_vert2, point r_vert3);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	virtual void move(direction dir);

	point getVert2() const;
	point getVert3() const;
	void setvert1(point v);
	void setvert3(point vert);
	void setvert2(point vert);
	bool matches(const shape* target) const;



};

////////////////////////////////////////////////////  class line  ///////////////////////////////////////
//Reference point of the triangle is at a point of two points of the line
class line :public shape
{
	//Add data memebrs for class line
	point lineLength;

public:
	line(game* r_pGame, point ref, point Length);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	virtual void move(direction dir);
	point getPoint2() const;
	void setPoint2(point p);
	bool matches(const shape* target) const;


};



