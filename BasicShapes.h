//Header file for Basic shapes in the game
#pragma once
#include "shape.h"
#include <fstream>

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

class Rect:public shape
{
	int hght, wdth;	//height and width of the recangle
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void setFillColor(color c);
	virtual void save(ofstream& OutFile)const;
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	bool matches(const shape* target) const;
virtual bool check_boundries();

};


////////////////////////////////////////////////////  class circle  ///////////////////////////////////////
//Reference point of the circle is its center
class circle :public shape
{
	//Add data memebrs for class circle
	int rad;
public:	
	circle(game* r_pGame, point ref, int r);
	void save(ofstream& OutFile) const;
	virtual void setFillColor(color c);//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	virtual void rotate();
virtual bool check_boundries();

};


////////////////////////////////////////////////////  class triangle  ///////////////////////////////////////
//Reference point of the triangle is at the vertex
class triangle :public shape
{
	//Add data memebrs for class triangle
	point vertex1,vertex2,vertex3;
	double length_side_1;
	double length_side_2;	
	double length_side_3;
public:
	triangle(game* r_pGame, point ref, point r_vert2,point r_vert3);	//add more parameters for the constructor if needed
	virtual void setFillColor(color c);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void save(ofstream& OutFile)const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
virtual bool check_boundries();
	point getVert2();
	point getVert3();
	point getvert1();
	point setvert3(point vert);
	point setvert2(point vert);



};

////////////////////////////////////////////////////  class line  ///////////////////////////////////////
//Reference point of the triangle is at a point of two points of the line
class line :public shape
{
	//Add data memebrs for class line
	point lineLength;

public:
	line(game* r_pGame, point ref, point Length);	//add more parameters for the constructor if needed
		virtual void setFillColor(color c);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void save(ofstream& OutFile)const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
virtual bool check_boundries();
	point getPoint2();

};

////////////////////////////////////////////////////  class polygon  ///////////////////////////////////////
//Reference point of the polygon is at the centre of the height taken from the centre of the base
class polygon :public shape
{
	//Add data memebrs for class polygon
	int Pline1;
	int Pline2;
	int hght;
	point vertex1;
	point vertex2;
	point vertex3;
	point vertex4;
public:
	polygon(game* r_pGame, point ref, int r_pline1,int r_pline2,int r_hght);	//add more parameters for the constructor if needed
	virtual void draw() const;
	virtual void setFillColor(color c);
	virtual void save(ofstream& OutFile)const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	virtual bool check_boundries();
	point setV1(point p);
	point setV2(point p);
	point setV3(point p);
	point setV4(point p);
	point getV1() const;
	point getV2() const;
	point getV3() const;
	point getV4() const;
	bool matches(const shape* target) const;



};

