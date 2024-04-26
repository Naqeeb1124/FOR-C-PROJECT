#include "CompositeShapes.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref):shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}

void Sign::draw() const
{
	base->draw();
	top->draw();
}

void Sign::rotate()
{
	point baseRef = { RefPoint.x, RefPoint.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	top->rotate();
	base->rotate();
	point newBaseRef = multiplyByMatrix(baseRef);
	base->setRefPoint(newBaseRef);
}
void Sign::resize_up()
{
	base->resize_up();
	top->resize_up();
}

void Sign::resize_down()
{
	base->resize_down();
	top->resize_down();
}

void Sign::flip()
{
	point topRef = RefPoint;	//top rect ref is the same as the sign
	point baseRef = { RefPoint.x, RefPoint.y - config.sighShape.topHeight / 2 - config.sighShape.baseHeight / 2 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}



/////////////////////////////////THIS BELOW SECTION IS ENTIRELY BY ABDELRAHMAN MOHAMMED ////////////////////////////////////
//// For the house:
House::House(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseref = ref;
	point roofRef = { ref.x - config.houseShape.roofWdth/2, ref.y - config.houseShape.baseHeight/2};
	point roof2 = {roofRef.x + config.houseShape.roofWdth,roofRef.y };
	point roof3 = {roofRef.x + config.houseShape.roofWdth / 2,roofRef.y - config.houseShape.roofHeight };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
}

void House::draw() const
{
	base->draw();
	roof->draw();
}

void House::rotate()
{
	point roofRef = { RefPoint.x - config.houseShape.roofWdth / 2, RefPoint.y - config.houseShape.baseHeight / 2 };
	base->rotate();
	point newRoofRef = multiplyByMatrix(roofRef);
	roof->rotate();

}

void House::resize_up()
{
	base->resize_up();
	roof->resize_up();
}

void House::resize_down()
{
	base->resize_down();
	roof->resize_down();
}

void House::flip()
{
	point baseref = RefPoint;
	point roofRef = { RefPoint.x - config.houseShape.roofWdth / 2, RefPoint.y + config.houseShape.baseHeight / 2 };
	point roof2 = { roofRef.x + config.houseShape.roofWdth,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth / 2,roofRef.y - config.houseShape.roofHeight };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
	roof->flip();
	base->flip();
}



// For the car
Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{ //by back i mean left and front is right
	point bottomRef = ref;
	point topRef = { ref.x, ref.y - config.carShape.lowHeight / 2 - config.carShape.upHeight / 2 };
	point bTireRef = {ref.x - config.carShape.lowWdth/4, ref.y + config.carShape.lowHeight/2};
	point fTireRef = { ref.x + config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	lowBody = new Rect(pGame, bottomRef, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new polygon(pGame, topRef, config.carShape.upTOPWdth, config.carShape.upBOTWdth, config.carShape.upHeight);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
};

void Car::draw() const
{
	lowBody->draw();
	upBody->draw();
	frontTire->draw();
	backTire->draw();
}

void Car::rotate()
{
	point ref = RefPoint;
	point topRef = { ref.x, ref.y - config.carShape.lowHeight / 2 - config.carShape.upHeight / 2 };
	point bTireRef = { ref.x - config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point fTireRef = { ref.x + config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point newTopRef = multiplyByMatrix(topRef);
	point newBTireRef = multiplyByMatrix(bTireRef);
	point newFTireRef = multiplyByMatrix(fTireRef);
	lowBody->rotate();
	upBody->rotate();
	frontTire->rotate();
	backTire->rotate();
}

void Car::flip()
{
	point bottomRef = RefPoint;
	point topRef = { RefPoint.x, RefPoint.y + config.carShape.lowHeight / 2 + config.carShape.upHeight / 2 };
	point bTireRef = { RefPoint.x - config.carShape.lowWdth / 4, RefPoint.y - config.carShape.lowHeight / 2 };
	point fTireRef = { RefPoint.x + config.carShape.lowWdth / 4, RefPoint.y - config.carShape.lowHeight / 2 };
	lowBody = new Rect(pGame, bottomRef, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new polygon(pGame, topRef, config.carShape.upTOPWdth, config.carShape.upBOTWdth, config.carShape.upHeight);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
	upBody->flip();
	lowBody->flip();
}


void Car::resize_up()
{
	lowBody->resize_up();
	lowBody->resize_up();
	lowBody->resize_up();
	lowBody->resize_up();
}

void Car::resize_down()
{
	lowBody->resize_down();
	lowBody->resize_down();
	lowBody->resize_down();
	lowBody->resize_down();
}

Boat::Boat(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point hullRef = ref;
	point sailRef = { ref.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,ref.y - config.boatShape.hullHeight / 2 };
	point mastRef = { ref.x - config.boatShape.tHullWdth/10, ref.y - config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y};
	point sail3 = { sailRef.x + config.boatShape.sailHeight/2.5, sailRef.y - config.boatShape.hullHeight };
	hull = new polygon(pGame, hullRef, config.boatShape.tHullWdth, config.boatShape.bHullWdth, config.boatShape.hullHeight);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, config.boatShape.mastHeight);
};

void Boat::draw() const
{
	hull->draw();
	sail->draw();
	mast->draw();
}

void Boat::rotate()
{
	point ref = RefPoint;
	point sailRef = { ref.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,ref.y - config.boatShape.hullHeight / 2 };
	point mastRef = { ref.x - config.boatShape.tHullWdth / 10, ref.y - config.boatShape.hullHeight / 2 };
	point newSailRef = multiplyByMatrix(sailRef);
	point newMastRef = multiplyByMatrix(mastRef);
	hull->rotate();
	sail->rotate();
	mast->rotate();

}

void Boat::flip()
{
	point hullRef = RefPoint;
	point sailRef = { RefPoint.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,RefPoint.y + config.boatShape.hullHeight / 2 };
	point mastRef = { RefPoint.x - config.boatShape.tHullWdth / 10, RefPoint.y + config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5, sailRef.y - config.boatShape.hullHeight };
	hull = new polygon(pGame, hullRef, config.boatShape.tHullWdth, config.boatShape.bHullWdth, config.boatShape.hullHeight);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, config.boatShape.mastHeight);
	hull->flip();
	sail->flip();
}

void Boat::resize_up()
{
	hull->resize_up();
	hull->resize_up();
	hull->resize_up();
}

void Boat::resize_down()
{
	hull->resize_down();
	hull->resize_down();
	hull->resize_down();
}

Plane::Plane(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point fuselageRef = ref;
	point noseRef = {ref.x + config.planeShape.fuselageWdth/2,ref.y - config.planeShape.fuselageHeight/2};
	point tailRef = {ref.x - config.planeShape.fuselageWdth/2, ref.y - config.planeShape.fuselageHeight/2};
	point upWingRef = { ref.x + config.planeShape.fuselageWdth / 10, ref.y - config.planeShape.fuselageHeight / 2 };
	point lowWingRef = { ref.x + config.planeShape.fuselageWdth / 10, ref.y + config.planeShape.fuselageHeight / 2 };
	point upStabRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y - config.planeShape.fuselageHeight / 2 };
	point lowStabRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y + config.planeShape.fuselageHeight / 2 };
	point nose2 = { noseRef.x,noseRef.y + config.planeShape.noseHeight };
	point nose3 = { noseRef.x + config.planeShape.noseWdth, noseRef.y + config.planeShape.noseHeight / 2 };
	point tail2 = { tailRef.x,tailRef.y + config.planeShape.tailHeight };
	point tail3 = {tailRef.x - config.planeShape.tailWdth, tailRef.y - config.planeShape.tailHeight/2};
	point upWing2 = { upWingRef.x + config.planeShape.wingWidth, upWingRef.y };
	point upWing3 = {upWingRef.x - config.planeShape.wingSweep,upWingRef.y - config.planeShape.wingHeight};
	point lowWing2 = {lowWingRef.x + config.planeShape.wingWidth, lowWingRef.y};
	point lowWing3 = { lowWingRef.x - config.planeShape.wingSweep, lowWingRef.y + config.planeShape.wingHeight };
	point upStab2 = {upStabRef.x - config.planeShape.stabWdth, upStabRef.y + config.planeShape.fuselageWdth/2};
	point upstab3 = {upStabRef.x - config.planeShape.stabWdth - config.planeShape.stabSweep, upStabRef.y - config.planeShape.stabHeight};
	point lowStab2 = { upStabRef.x - config.planeShape.stabWdth, upStabRef.y};
	point lowStab3 = {lowStabRef.x - config.planeShape.stabWdth - config.planeShape.stabSweep, lowStabRef.y + config.planeShape.stabHeight };
	fuselage = new Rect(pGame, fuselageRef, config.planeShape.fuselageHeight, config.planeShape.fuselageWdth);
	nose = new triangle(pGame, noseRef, nose2, nose3);
	tail = new triangle(pGame, tailRef, tail2, tail3);
	upWing = new triangle(pGame, upWingRef, upWing2, upWing3);
	bottomWing = new triangle(pGame, lowWingRef, lowWing2, lowWing3);
	upStab = new triangle(pGame, upStabRef, upStab2, upstab3);
	lowStab = new triangle(pGame, lowStabRef, lowStab2, lowStab3);
}

void Plane::draw() const
{
	fuselage->draw();
	nose->draw();
	tail->draw();
	upWing->draw();
	bottomWing->draw();
	upStab->draw();
	lowStab->draw();
};

void Plane::rotate()
{	point ref = RefPoint;
	point noseRef = { ref.x + config.planeShape.fuselageWdth / 2,ref.y - config.planeShape.fuselageHeight / 2 };
	point tailRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y - config.planeShape.fuselageHeight / 2 };
	point upWingRef = { ref.x + config.planeShape.fuselageWdth / 10, ref.y - config.planeShape.fuselageHeight / 2 };
	point lowWingRef = { ref.x + config.planeShape.fuselageWdth / 10, ref.y + config.planeShape.fuselageHeight / 2 };
	point upStabRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y - config.planeShape.fuselageHeight / 2 };
	point lowStabRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y + config.planeShape.fuselageHeight / 2 };

	point newNoseRef = multiplyByMatrix(noseRef);
	point newTailRef = multiplyByMatrix(tailRef);
	point newUpWingRef = multiplyByMatrix(upWingRef);
	point newLowWingRef = multiplyByMatrix(lowWingRef);
	point newUpStabRef = multiplyByMatrix(upStabRef);
	point newLowStabRef = multiplyByMatrix(lowStabRef);

	fuselage->rotate();
	nose->rotate();
	tail->rotate();
	upWing->rotate();
	bottomWing->rotate();
	upStab->rotate();
	lowStab->rotate();

}

void Plane::resize_up()
{
	fuselage->resize_up();
	nose->resize_up();
	tail->resize_up();
	upWing->resize_up();
	bottomWing->resize_up();
	upStab->resize_up();
	lowStab->resize_up();
}

void Plane::resize_down()
{
	fuselage->resize_down();
	nose->resize_down();
	tail->resize_down();
	upWing->resize_down();
	bottomWing->resize_down();
	upStab->resize_down();
	lowStab->resize_down();
}

void Plane::flip()
{
	upStab->flip();
	lowStab->flip();
	fuselage->flip();
	nose->flip();
}


arrow::arrow(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point shaftRef = ref;
	point headRef = { ref.x + config.arrowShape.shaftWdth / 2, ref.y - config.arrowShape.headHeight/2};
	shaft = new Rect(pGame, shaftRef, config.arrowShape.shaftHeight, 2.5*config.arrowShape.headWdth);
	point head2 = {headRef.x, headRef.y + config.arrowShape.headHeight};
	point head3 = {headRef.x + config.arrowShape.headWdth, headRef.y + config.arrowShape.headHeight/2};
	head = new triangle(pGame, headRef, head2, head3);
};

void arrow::draw() const
{
	shaft->draw();
	head->draw();
}

void arrow::rotate()
{
	point ref = RefPoint;
	point headRef = { ref.x + config.arrowShape.shaftWdth / 2, ref.y - config.arrowShape.headHeight / 2 };

	point newHeadRef = multiplyByMatrix(headRef);

	shaft->rotate();
	head->rotate();
}


void arrow::resize_up()
{
	shaft->resize_up();
	head->resize_up();
}

void arrow::resize_down()
{
	shaft->resize_down();
	head->resize_down();
}

void arrow::flip()
{
	shaft->flip();
	head->flip();
}
