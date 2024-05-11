#pragma once
#include "Basicshapes.h"


////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
//This class reprsents the composite shape "sign"
//The sign is composed of 2 Recatngles
/*				

					 ------------------
					|				   |
					|		 x		   |     x is the reference point of the Sign shape
					|			       |
					 ------------------
						   |   |
						   |   |
						   | . |
						   |   |
						   |   |
							---
*/

//Note: sign reference point is the center point of the top rectangle
class Sign :public shape
{
	Rect* base;
	Rect* top;
public:
	Sign(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	void move(direction dir) override;

};



/// //////////////////////////// THE FOLLOWING CODE IS ENTIRELY WRITTEN BY ABDELRAHMAN MOHAMED////////////

class House :public shape
{
	Rect* base;
	triangle* roof;
	Rect* chimney;
public:
	House(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	void move(direction dir) override;
};

class Car :public shape
{
	Rect* lowBody;
	polygon* upBody;
	circle* frontTire;
	circle* backTire;
public:
	Car(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	void move(direction dir) override;
};

class Boat :public shape
{
	polygon* hull;
	triangle* sail;
	line* mast;
public:
	Boat(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	void move(direction dir) override;
};

class Plane :public shape
{
	Rect* fuselage;
	triangle* nose;
	triangle* tail;
	triangle* upWing;
	triangle* bottomWing;
	triangle* upStab;
	triangle* lowStab;
public:
	Plane(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	void move(direction dir) override;
};

class Arrow :public shape
{
	Rect* shaft;
	triangle* head;
public:

	Arrow(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void rotate();
	virtual void resize_up();
	virtual void resize_down();
	virtual void flip();
	void move(direction dir) override;

};



/////////////////////////////////////////////////////////////////////////////////////////////////////////
