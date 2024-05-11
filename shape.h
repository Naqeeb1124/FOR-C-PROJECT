#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration
struct point
{
	int x, y;
public:
	
	bool operator==(const point& other) const {
		return x == other.x && y == other.y;
	}
};

enum ShapeType
{
	//Basic shapes
	RCT,	//rectangle
	CRC,	//circle
	TRI,	//triangle
	LNE,	//line
	POL,	//Polygon

	//Composite shapes
	SIGN,	//a street sign
	HOUSE, // TOP G BIG RICH DADDY NAQEEB TRILLIONAIRE MANSION
	CAR, //BUGATTI RAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH
	BOAT, //TOP G YACHT RAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH
	PLANE, //TOP G PRIVATE JET RAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH
	arrow, //TOP G ARROW SHOW US THE WAY TO SUCCESS BIG TOP G RAAAAAAAAAAAAAAAAAAAAAAAAAAAH
};

enum direction
{
	right,
	up,
	left,
	down
};

//Base class for all shapes including Basic shapes, Composite shapes
class shape
{
protected:
	point RefPoint;		//Each shape must have a reference point
	game* pGame;        //pointer to game object
	color fillColor;	//shape fill color
	color borderColor;	//shape border color
public:
	shape(game* r_pGame, point ref);
	virtual void draw() const = 0;//for a shape to draw itself on the screen
	void setRefPoint(point p);
	virtual void rotate() = 0;
	virtual void move(direction dir);
	point getRefPoint();


	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function	

	/*virtual void rotate() = 0;*/	//Rotate the shape
	virtual void flip()=0;
	virtual void resize_up()=0;	//Resize the shape
	virtual void resize_down()=0;
	/*virtual void move(direction dir)=0;*/		//Move the shape
	//virtual void save(ofstream &OutFile) = 0;	//Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0;	//Load the shape parameters to the file
	static point multiplyByMatrix(point& p);

};
