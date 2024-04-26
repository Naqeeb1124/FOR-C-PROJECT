#pragma once

class game;
/////////////////////////////////// class operation  //////////////////
//Base class of all operations supported by the application
class operation
{
protected:
	game* pGame;	//pointer to the game class
public:
	operation(game* r_pGame);

	//Function Act:
	//Implements the action that should be taken by this operation
	//Should be overriden by derived classes
	virtual void Act() = 0;
};
/////////////////////////////////// class operAddSign  //////////////////
//Responsible for 
//1- collectign data about a new Sign shape to add
//2- Adding the new shape to the list of shapes (throgh the grid class)
//class operAddSign:public operation
//{
//public:
//	operAddSign(game* r_pGame);
//	virtual void Act();
//};
//---------------------------
class operAddBoat :public operation
{
public:
	operAddBoat(game* r_pGame);
	virtual void Act();
};

//---------------------------
class operAddCar :public operation
{
public:
	operAddCar(game* r_pGame);
	virtual void Act();
};

//---------------------------
class operAddPlane :public operation
{
public:
	operAddPlane(game* r_pGame);
	virtual void Act();
};

//---------------------------
class operAddArrow :public operation
{
public:
	operAddArrow(game* r_pGame);
	virtual void Act();
};

//---------------------------
class operAddHouse :public operation
{
public:
	operAddHouse(game* r_pGame);
	virtual void Act();
};

//---------------------------
class operAddSign :public operation
{
public:
	operAddSign(game* r_pGame);
	virtual void Act();
};

//---------------------------
class operZoomIn:public operation
{
public:
	operZoomIn(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operZoomOut :public operation
{
public:
	operZoomOut(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operRotate :public operation
{
public:
	operRotate(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operRefresh :public operation
{
public:
	operRefresh(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operHint :public operation
{
public:
	operHint(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operDelete :public operation
{
public:
	operDelete(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operSave :public operation
{
public:
	operSave(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operLoad :public operation
{
public:
	operLoad(game* r_pGame);
	virtual void Act();
};

//---------------------------

class operSelectLevel :public operation
{
public:
	operSelectLevel(game* r_pGame);
	virtual void Act();
};



class move_shape :public operation {
public:
	move_shape(game* r_pGame);
	virtual void Act();
};
