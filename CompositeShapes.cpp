#include "CompositeShapes.h"


////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref)
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
	point topRef = top->getRefPoint();
	top->rotate();

	point baseRef = base->getRefPoint();
	point relativeBaseRef = { baseRef.x - topRef.x, baseRef.y - topRef.y };
	point rotatedRelativeBaseRef = multiplyByMatrix(relativeBaseRef);
	point newBaseRef = { topRef.x + rotatedRelativeBaseRef.x,topRef.y + rotatedRelativeBaseRef.y };
	base->setRefPoint(newBaseRef);
	base->rotate();

	stepCount++;
}
void Sign::resize_up()
{
	point topRef = RefPoint;	//top rect ref is the same as the sign
	point baseRef = { RefPoint.x, RefPoint.y + config.sighShape.topHeight + config.sighShape.baseHeight };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
	base->resize_up();
	top->resize_up();

	stepCount++;

}

void Sign::resize_down()
{
	point topRef = RefPoint;	//top rect ref is the same as the sign
	point baseRef = { RefPoint.x, RefPoint.y + config.sighShape.topHeight / 4 + config.sighShape.baseHeight / 4 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
	base->resize_down();
	top->resize_down();

	stepCount++;

}

void Sign::flip()
{
	point topRef = top->getRefPoint();	//top rect ref is the same as the sign
	point baseRef = base->getRefPoint();
	point newtopref = { baseRef.x,baseRef.y };
	point newbaseref = { topRef.x,topRef.y };
	top->setRefPoint(newtopref);
	base->setRefPoint(newbaseref);

	stepCount++;

}

void Sign::move(direction dir)
{
	switch (dir) {
	case Up:
		base->move(Up);
		top->move(Up);
		break;
	case Down:
		base->move(Down);
		top->move(Down);
		break;
	case Right:
		base->move(Right);
		top->move(Right);
		break;
	case Left:
		base->move(Left);
		top->move(Left);
		break;
	}

	stepCount++;

}

bool Sign::matches(const shape* target) const {
	const Sign* targetSign = dynamic_cast<const Sign*>(target);
	if (targetSign) {
		return top->matches(targetSign->top) && base->matches(targetSign->base);

	}

	return false;
}


/////////////////////////////////THIS BELOW SECTION IS ENTIRELY BY ABDELRAHMAN MOHAMMED ////////////////////////////////////
//// For the house:
House::House(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseref = ref;
	point roofRef = { ref.x - config.houseShape.roofWdth / 2, ref.y - config.houseShape.baseHeight / 2 };
	point chimneyRef = { ref.x - config.houseShape.baseWdth / 4, ref.y - config.houseShape.baseHeight / 2 - config.houseShape.chimneyHeight / 2 };
	point roof2 = { roofRef.x + config.houseShape.roofWdth,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth / 2,roofRef.y - config.houseShape.roofHeight };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
	chimney = new Rect(pGame, chimneyRef, config.houseShape.chimneyHeight, config.houseShape.chimneyWdth);


}

void House::draw() const
{
	base->draw();
	roof->draw();
	chimney->draw();
}

void House::rotate() {

	point baseRef = base->getRefPoint();
	base->rotate();


	point roofRef = roof->getRefPoint();
	point relativeRoofRef = { roofRef.x - baseRef.x, roofRef.y - baseRef.y };
	point rotatedRelativeRoofRef = multiplyByMatrix(relativeRoofRef);
	point newRoofRef = { baseRef.x + rotatedRelativeRoofRef.x, baseRef.y + rotatedRelativeRoofRef.y };
	roof->setRefPoint(newRoofRef);

	point roof2 = roof->getVert2();

	point relVert2 = { roof2.x - baseRef.x, roof2.y - baseRef.y };
	point rotRelVert2 = multiplyByMatrix(relVert2);
	point newRoof2 = { baseRef.x + rotRelVert2.x, baseRef.y + rotRelVert2.y };

	point roof3 = roof->getVert3();

	point relVert3 = { roof3.x - baseRef.x, roof3.y - baseRef.y };
	point rotRelVert3 = multiplyByMatrix(relVert3);
	point newRoof3 = { baseRef.x + rotRelVert3.x, baseRef.y + rotRelVert3.y };
	delete roof;
	roof = new triangle(pGame, newRoofRef, newRoof2, newRoof3);



	point chimneyRef = chimney->getRefPoint();
	point relativeChimneyRef = { chimneyRef.x - baseRef.x, chimneyRef.y - baseRef.y };
	point rotatedRelativeChimneyRef = chimney->multiplyByMatrix(relativeChimneyRef);
	chimneyRef.x = baseRef.x + rotatedRelativeChimneyRef.x;
	chimneyRef.y = baseRef.y + rotatedRelativeChimneyRef.y;
	chimney->setRefPoint(chimneyRef);
	chimney->rotate();

	stepCount++;

}

void House::resize_up()
{
	point baseref = RefPoint;
	point roofRef = { RefPoint.x - config.houseShape.roofWdth , RefPoint.y - config.houseShape.baseHeight };
	point chimneyRef = { RefPoint.x - config.houseShape.baseWdth / 2, RefPoint.y - config.houseShape.baseHeight - config.houseShape.chimneyHeight };
	point roof2 = { roofRef.x + config.houseShape.roofWdth * 2,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth ,roofRef.y - config.houseShape.roofHeight * 2 };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
	chimney = new Rect(pGame, chimneyRef, config.houseShape.chimneyHeight, config.houseShape.chimneyWdth);
	base->resize_up();
	chimney->resize_up();

	stepCount++;
}

void House::resize_down()
{
	point baseref = RefPoint;
	point roofRef = { RefPoint.x - config.houseShape.roofWdth / 4, RefPoint.y - config.houseShape.baseHeight / 4 };
	point chimneyRef = { RefPoint.x - config.houseShape.baseWdth / 8, RefPoint.y - config.houseShape.baseHeight / 4 - config.houseShape.chimneyHeight / 4 };
	point roof2 = { roofRef.x + config.houseShape.roofWdth / 2,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth / 4,roofRef.y - config.houseShape.roofHeight / 2 };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
	chimney = new Rect(pGame, chimneyRef, config.houseShape.chimneyHeight, config.houseShape.chimneyWdth);


	base->resize_down();
	chimney->resize_down();

	stepCount++;


}

void House::flip()
{

	point baseref = base->getRefPoint();
	base->flip();
	point roofref = roof->getRefPoint();
	point vertex3 = roof->getVert3();
	point chimmyref = chimney->getRefPoint();
	point newchimneyref = { chimmyref.x,baseref.y };
	point newbaseref = { baseref.x,chimmyref.y };
	point newver3 = { vertex3.x,newchimneyref.y };
	roof->setvert3(newver3);
	chimney->setRefPoint(newchimneyref);
	base->setRefPoint(newbaseref);

	stepCount++;


}

void House::move(direction dir)
{
	switch (dir) {
	case Up:
		base->move(Up);

		roof->move(Up);
		//delete roof;
		//roof = new triangle(pGame, {roof->getVert2());
		chimney->move(Up);
		break;
	case Down:
		base->move(Down);
		roof->move(Down);
		chimney->move(Down);
		break;
	case Right:
		base->move(Right);
		roof->move(Right);
		chimney->move(Right);
		break;
	case Left:
		base->move(Left);
		roof->move(Left);
		chimney->move(Left);
		break;
	}
	stepCount++;

}



bool House::matches(const shape* target) const {
	const House* targetHouse = dynamic_cast<const House*>(target);
	if (targetHouse) {
		return base->matches(targetHouse->base) && roof->matches(targetHouse->roof) && chimney->matches(targetHouse->chimney);

	}
	return false;
}


// For the car
Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{ //by back i mean left and front is right
	point bottomRef = ref;
	point topRef = { ref.x, ref.y - config.carShape.lowHeight / 2 - config.carShape.upHeight / 2 };
	point up1Ref = { topRef.x - config.carShape.upTOPWdth / 2, topRef.y + config.carShape.upHeight / 2 };
	point up2Ref = { topRef.x + config.carShape.upTOPWdth / 2, topRef.y + config.carShape.upHeight / 2 };
	point bTireRef = { ref.x - config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point fTireRef = { ref.x + config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point up12 = { up1Ref.x - (config.carShape.upBOTWdth - config.carShape.upTOPWdth) / 2, up1Ref.y };
	point up22 = { up2Ref.x + (config.carShape.upBOTWdth - config.carShape.upTOPWdth) / 2, up2Ref.y };
	point up13 = { up1Ref.x, up1Ref.y - config.carShape.upHeight };
	point up23 = { up2Ref.x, up2Ref.y - config.carShape.upHeight };


	lowBody = new Rect(pGame, bottomRef, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new Rect(pGame, topRef, config.carShape.upHeight, config.carShape.upTOPWdth);
	upBody1 = new triangle(pGame, up1Ref, up12, up13);
	upBody2 = new triangle(pGame, up2Ref, up22, up23);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
};

void Car::draw() const
{
	lowBody->draw();
	upBody->draw();
	upBody1->draw();
	upBody2->draw();
	frontTire->draw();
	backTire->draw();
}

void Car::rotate() {
	point baseRef = lowBody->getRefPoint();
	lowBody->rotate();

	point upBodyRef = upBody->getRefPoint();
	point relativeUpBodyRef = { upBodyRef.x - baseRef.x, upBodyRef.y - baseRef.y };
	point rotatedRelativeUpBodyRef = multiplyByMatrix(relativeUpBodyRef);
	point newUpBodyRef = { baseRef.x + rotatedRelativeUpBodyRef.x, baseRef.y + rotatedRelativeUpBodyRef.y };
	upBody->setRefPoint(newUpBodyRef);
	upBody->rotate();

	point upBody1Ref = upBody1->getRefPoint();
	point relativeUpBody1Ref = { upBody1Ref.x - baseRef.x, upBody1Ref.y - baseRef.y };
	point rotatedRelativeUpBody1Ref = multiplyByMatrix(relativeUpBody1Ref);
	point newUpBody1Ref = { baseRef.x + rotatedRelativeUpBody1Ref.x, baseRef.y + rotatedRelativeUpBody1Ref.y };
	upBody1->setRefPoint(newUpBody1Ref);

	point upBody1Vert2 = upBody1->getVert2();
	point relUpBody1Vert2 = { upBody1Vert2.x - baseRef.x, upBody1Vert2.y - baseRef.y };
	point rotRelUpBody1Vert2 = multiplyByMatrix(relUpBody1Vert2);
	point newUpBody1Vert2 = { baseRef.x + rotRelUpBody1Vert2.x, baseRef.y + rotRelUpBody1Vert2.y };

	point upBody1Vert3 = upBody1->getVert3();
	point relUpBody1Vert3 = { upBody1Vert3.x - baseRef.x, upBody1Vert3.y - baseRef.y };
	point rotRelUpBody1Vert3 = multiplyByMatrix(relUpBody1Vert3);
	point newUpBody1Vert3 = { baseRef.x + rotRelUpBody1Vert3.x, baseRef.y + rotRelUpBody1Vert3.y };
	delete upBody1;
	upBody1 = new triangle(pGame, newUpBody1Ref, newUpBody1Vert2, newUpBody1Vert3);

	point upBody2Ref = upBody2->getRefPoint();
	point relativeUpBody2Ref = { upBody2Ref.x - baseRef.x, upBody2Ref.y - baseRef.y };
	point rotatedRelativeUpBody2Ref = multiplyByMatrix(relativeUpBody2Ref);
	point newUpBody2Ref = { baseRef.x + rotatedRelativeUpBody2Ref.x, baseRef.y + rotatedRelativeUpBody2Ref.y };
	upBody2->setRefPoint(newUpBody2Ref);

	point upBody2Vert2 = upBody2->getVert2();
	point relUpBody2Vert2 = { upBody2Vert2.x - baseRef.x, upBody2Vert2.y - baseRef.y };
	point rotRelUpBody2Vert2 = multiplyByMatrix(relUpBody2Vert2);
	point newUpBody2Vert2 = { baseRef.x + rotRelUpBody2Vert2.x, baseRef.y + rotRelUpBody2Vert2.y };

	point upBody2Vert3 = upBody2->getVert3();
	point relUpBody2Vert3 = { upBody2Vert3.x - baseRef.x, upBody2Vert3.y - baseRef.y };
	point rotRelUpBody2Vert3 = multiplyByMatrix(relUpBody2Vert3);
	point newUpBody2Vert3 = { baseRef.x + rotRelUpBody2Vert3.x, baseRef.y + rotRelUpBody2Vert3.y };
	delete upBody2;
	upBody2 = new triangle(pGame, newUpBody2Ref, newUpBody2Vert2, newUpBody2Vert3);

	point frontTireRef = frontTire->getRefPoint();
	point relativeFrontTireRef = { frontTireRef.x - baseRef.x, frontTireRef.y - baseRef.y };
	point rotatedRelativeFrontTireRef = multiplyByMatrix(relativeFrontTireRef);
	point newFrontTireRef = { baseRef.x + rotatedRelativeFrontTireRef.x, baseRef.y + rotatedRelativeFrontTireRef.y };
	frontTire->setRefPoint(newFrontTireRef);

	point backTireRef = backTire->getRefPoint();
	point relativeBackTireRef = { backTireRef.x - baseRef.x, backTireRef.y - baseRef.y };
	point rotatedRelativeBackTireRef = multiplyByMatrix(relativeBackTireRef);
	point newBackTireRef = { baseRef.x + rotatedRelativeBackTireRef.x, baseRef.y + rotatedRelativeBackTireRef.y };
	backTire->setRefPoint(newBackTireRef);

	stepCount++;
}

void Car::flip()
{
	point bottomref = lowBody->getRefPoint();
	point uperref = upBody->getRefPoint();
	point Rcircleref = frontTire->getRefPoint();
	point Lcircref = backTire->getRefPoint();

	point newupperref = { uperref.x,Rcircleref.y };
	point newrRcircle = { Rcircleref.x,uperref.y };
	point newrLcircle = { Lcircref.x,uperref.y };
	upBody->setRefPoint(newupperref);
	upBody->flip();
	frontTire->setRefPoint(newrRcircle);
	backTire->setRefPoint(newrLcircle);

	stepCount++;

}

void Car::move(direction dir)
{
	switch (dir)
	{
	case Up:
		upBody->move(Up);
		upBody1->move(Up);
		upBody2->move(Up);
		lowBody->move(Up);
		frontTire->move(Up);
		backTire->move(Up);
		break;
	case Down:
		upBody->move(Down);
		upBody1->move(Down);
		upBody2->move(Down);
		lowBody->move(Down);
		frontTire->move(Down);
		backTire->move(Down);
		break;
	case Right:
		upBody->move(Right);
		upBody1->move(Right);
		upBody2->move(Right);
		lowBody->move(Right);
		frontTire->move(Right);
		backTire->move(Right);
		break;
	case Left:
		upBody->move(Left);
		upBody1->move(Left);
		upBody2->move(Left);
		lowBody->move(Left);
		frontTire->move(Left);
		backTire->move(Left);
		break;

	}

	stepCount++;

}


void Car::resize_up()
{
	double factor = 2;
	point ref = RefPoint;
	point topRef = { ref.x, ref.y - config.carShape.lowHeight / 2 - config.carShape.upHeight / 2 };
	point up1Ref = { topRef.x - config.carShape.upTOPWdth, topRef.y + config.carShape.upHeight / 2 };
	point up2Ref = { topRef.x + config.carShape.upTOPWdth, topRef.y + config.carShape.upHeight / 2 };
	point bTireRef = { ref.x - config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point fTireRef = { ref.x + config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point up12 = { up1Ref.x - (config.carShape.upBOTWdth - config.carShape.upTOPWdth) / 2, up1Ref.y };
	point up22 = { up2Ref.x + (config.carShape.upBOTWdth - config.carShape.upTOPWdth) / 2, up2Ref.y };
	point up13 = { up1Ref.x, up1Ref.y - config.carShape.upHeight };
	point up23 = { up2Ref.x, up2Ref.y - config.carShape.upHeight };


	lowBody = new Rect(pGame, ref, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new Rect(pGame, topRef, config.carShape.upHeight, config.carShape.upBOTWdth);
	upBody1 = new triangle(pGame, up1Ref, up12, up13);
	upBody2 = new triangle(pGame, up2Ref, up22, up23);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
	lowBody->resize_up();
	upBody->resize_up();
	frontTire->resize_up();
	backTire->resize_up();

	stepCount++;

}

void Car::resize_down()
{
	double factor = .5;
	point ref = RefPoint;
	point topRef = { ref.x, ref.y - config.carShape.lowHeight / 2 - config.carShape.upHeight / 2 };
	point up1Ref = { topRef.x - config.carShape.upTOPWdth, topRef.y + config.carShape.upHeight / 2 };
	point up2Ref = { topRef.x + config.carShape.upTOPWdth, topRef.y + config.carShape.upHeight / 2 };
	point bTireRef = { ref.x - config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point fTireRef = { ref.x + config.carShape.lowWdth / 4, ref.y + config.carShape.lowHeight / 2 };
	point up12 = { up1Ref.x - (config.carShape.upBOTWdth - config.carShape.upTOPWdth) / 2, up1Ref.y };
	point up22 = { up2Ref.x + (config.carShape.upBOTWdth - config.carShape.upTOPWdth) / 2, up2Ref.y };
	point up13 = { up1Ref.x, up1Ref.y - config.carShape.upHeight };
	point up23 = { up2Ref.x, up2Ref.y - config.carShape.upHeight };


	lowBody = new Rect(pGame, ref, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new Rect(pGame, topRef, config.carShape.upHeight, config.carShape.upBOTWdth);
	upBody1 = new triangle(pGame, up1Ref, up12, up13);
	upBody2 = new triangle(pGame, up2Ref, up22, up23);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
	stepCount++;


}

bool Car::matches(const shape* target) const {
	const Car* targetCar = dynamic_cast<const Car*>(target);
	if (targetCar) {
		bool match = lowBody->matches(targetCar->lowBody)
			&& upBody->matches(targetCar->upBody)
			&& frontTire->matches(targetCar->frontTire)
			&& backTire->matches(targetCar->backTire);
		if (match) {
			pGame->incScore(2);
		}
		else {
			pGame->decScore(1);
			delete targetCar;
			targetCar = nullptr;
		}
		return match;
	}
	return false;
}





///Boat



Boat::Boat(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point hullRef = ref;
	point hull1Ref = { ref.x - config.boatShape.RhullWdth / 2, ref.y - config.boatShape.hullHeight / 2 };
	point hull2Ref = { ref.x + config.boatShape.RhullWdth / 2, ref.y - config.boatShape.hullHeight / 2 };
	point sailRef = { ref.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,ref.y - config.boatShape.hullHeight / 2 };
	point mastRef = { sailRef.x + config.boatShape.sailHeight / 2.5, ref.y - config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5, sailRef.y - config.boatShape.hullHeight };
	point hull12 = { hull1Ref.x - config.boatShape.thullWdthT, hull1Ref.y };
	point hull22 = { hull2Ref.x + config.boatShape.thullWdthT, hull2Ref.y };
	point hull13 = { hull1Ref.x, hull1Ref.y + config.boatShape.hullHeight };
	point hull23 = { hull2Ref.x, hull2Ref.y + config.boatShape.hullHeight };


	hull = new Rect(pGame, hullRef, config.boatShape.hullHeight, config.boatShape.RhullWdth);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, { mastRef.x, mastRef.y - config.boatShape.mastHeight });
	hull1 = new triangle(pGame, hull1Ref, hull12, hull13);
	hull2 = new triangle(pGame, hull2Ref, hull22, hull23);
};

void Boat::draw() const
{
	hull->draw();
	hull1->draw();
	hull2->draw();
	sail->draw();
	mast->draw();
}

void Boat::rotate() {
	point baseRef = hull->getRefPoint();
	hull->rotate();

	point hull1Ref = hull1->getRefPoint();
	point relativeHull1Ref = { hull1Ref.x - baseRef.x, hull1Ref.y - baseRef.y };
	point rotatedRelativeHull1Ref = multiplyByMatrix(relativeHull1Ref);
	point newHull1Ref = { baseRef.x + rotatedRelativeHull1Ref.x, baseRef.y + rotatedRelativeHull1Ref.y };
	hull1->setRefPoint(newHull1Ref);

	point hull1Vert2 = hull1->getVert2();
	point relVert2 = { hull1Vert2.x - baseRef.x, hull1Vert2.y - baseRef.y };
	point rotRelVert2 = multiplyByMatrix(relVert2);
	point newHull1Vert2 = { baseRef.x + rotRelVert2.x, baseRef.y + rotRelVert2.y };

	point hull1Vert3 = hull1->getVert3();
	point relVert3 = { hull1Vert3.x - baseRef.x, hull1Vert3.y - baseRef.y };
	point rotRelVert3 = multiplyByMatrix(relVert3);
	point newHull1Vert3 = { baseRef.x + rotRelVert3.x, baseRef.y + rotRelVert3.y };
	delete hull1;
	hull1 = new triangle(pGame, newHull1Ref, newHull1Vert2, newHull1Vert3);

	point hull2Ref = hull2->getRefPoint();
	point relativeHull2Ref = { hull2Ref.x - baseRef.x, hull2Ref.y - baseRef.y };
	point rotatedRelativeHull2Ref = multiplyByMatrix(relativeHull2Ref);
	point newHull2Ref = { baseRef.x + rotatedRelativeHull2Ref.x, baseRef.y + rotatedRelativeHull2Ref.y };
	hull2->setRefPoint(newHull2Ref);

	point hull2Vert2 = hull2->getVert2();
	point relHull2Vert2 = { hull2Vert2.x - baseRef.x, hull2Vert2.y - baseRef.y };
	point rotRelHull2Vert2 = multiplyByMatrix(relHull2Vert2);
	point newHull2Vert2 = { baseRef.x + rotRelHull2Vert2.x, baseRef.y + rotRelHull2Vert2.y };

	point hull2Vert3 = hull2->getVert3();
	point relHull2Vert3 = { hull2Vert3.x - baseRef.x, hull2Vert3.y - baseRef.y };
	point rotRelHull2Vert3 = multiplyByMatrix(relHull2Vert3);
	point newHull2Vert3 = { baseRef.x + rotRelHull2Vert3.x, baseRef.y + rotRelHull2Vert3.y };
	delete hull2;
	hull2 = new triangle(pGame, newHull2Ref, newHull2Vert2, newHull2Vert3);

	point sailRef = sail->getRefPoint();
	point relativeSailRef = { sailRef.x - baseRef.x, sailRef.y - baseRef.y };
	point rotatedRelativeSailRef = multiplyByMatrix(relativeSailRef);
	point newSailRef = { baseRef.x + rotatedRelativeSailRef.x, baseRef.y + rotatedRelativeSailRef.y };
	sail->setRefPoint(newSailRef);

	point sailVert2 = sail->getVert2();
	point relSailVert2 = { sailVert2.x - baseRef.x, sailVert2.y - baseRef.y };
	point rotRelSailVert2 = multiplyByMatrix(relSailVert2);
	point newSailVert2 = { baseRef.x + rotRelSailVert2.x, baseRef.y + rotRelSailVert2.y };

	point sailVert3 = sail->getVert3();
	point relSailVert3 = { sailVert3.x - baseRef.x, sailVert3.y - baseRef.y };
	point rotRelSailVert3 = multiplyByMatrix(relSailVert3);
	point newSailVert3 = { baseRef.x + rotRelSailVert3.x, baseRef.y + rotRelSailVert3.y };
	delete sail;
	sail = new triangle(pGame, newSailRef, newSailVert2, newSailVert3);

	point mastRef = mast->getRefPoint();
	point relativeMastRef = { mastRef.x - baseRef.x, mastRef.y - baseRef.y };
	point rotatedRelativeMastRef = multiplyByMatrix(relativeMastRef);
	point newMastRef = { baseRef.x + rotatedRelativeMastRef.x, baseRef.y + rotatedRelativeMastRef.y };
	mast->setRefPoint(newMastRef);

	point mastEnd = mast->getPoint2();
	point relMastEnd = { mastEnd.x - baseRef.x, mastEnd.y - baseRef.y };
	point rotRelMastEnd = multiplyByMatrix(relMastEnd);
	point newMastEnd = { baseRef.x + rotRelMastEnd.x, baseRef.y + rotRelMastEnd.y };
	delete mast;
	mast = new line(pGame, newMastRef, newMastEnd);

	stepCount++;
}

void Boat::flip()
{
	point baseref = hull->getRefPoint();
	point sailref = sail->getRefPoint();
	point mastref = mast->getRefPoint();
	point sail3 = sail->getVert3();
	point newbaseref = { baseref.x,sail3.y };
	hull->flip();
	point newsailref = { sailref.x,sailref.y };
	point newmusref = { mastref.x,sailref.y };
	point vert33 = { sail3.x,baseref.y };
	sail->setRefPoint(newsailref);
	hull->setRefPoint(newbaseref);
	mast->setRefPoint(newmusref);
	sail->setvert3(vert33);

	stepCount++;

}

void Boat::move(direction dir)
{
	switch (dir) {
	case Up:
		hull->move(Up);
		hull1->move(Up);
		hull2->move(Up);
		sail->move(Up);
		mast->move(Up);
		break;
	case Down:
		hull->move(Down);
		hull1->move(Down);
		hull2->move(Down);
		sail->move(Down);
		mast->move(Down);
		break;
	case Right:
		hull->move(Right);
		hull1->move(Right);
		hull2->move(Right);
		sail->move(Right);
		mast->move(Right);
		break;
	case Left:
		hull->move(Left);
		hull1->move(Left);
		hull2->move(Left);
		sail->move(Left);
		mast->move(Left);
		break;
	}
	stepCount++;
}



void Boat::resize_up()
{
	double factor = 2;
	point ref = RefPoint;
	point hull1Ref = { ref.x - config.boatShape.RhullWdth / 2, ref.y - config.boatShape.hullHeight };
	point hull2Ref = { ref.x + config.boatShape.RhullWdth / 2, ref.y - config.boatShape.hullHeight };
	point sailRef = { ref.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,ref.y - config.boatShape.hullHeight / 2 };
	point mastRef = { sailRef.x + config.boatShape.sailHeight / 2.5, ref.y - config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5, sailRef.y - config.boatShape.hullHeight };
	point hull12 = { hull1Ref.x - config.boatShape.thullWdthT, hull1Ref.y };
	point hull22 = { hull2Ref.x - config.boatShape.thullWdthT, hull2Ref.y };
	point hull13 = { hull1Ref.x, hull1Ref.y + config.boatShape.hullHeight };
	point hull23 = { hull2Ref.x, hull2Ref.y + config.boatShape.hullHeight };


	hull = new Rect(pGame, ref, config.boatShape.hullHeight, config.boatShape.RhullWdth);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, { mastRef.x, mastRef.y - config.boatShape.mastHeight });
	hull1 = new triangle(pGame, hull1Ref, hull12, hull13);
	hull2 = new triangle(pGame, hull2Ref, hull22, hull23);
	hull->resize_up();


	stepCount++;


}

void Boat::resize_down()
{
	double factor = .5;
	point ref = RefPoint;
	point hull1Ref = { ref.x - config.boatShape.RhullWdth / 2, ref.y - config.boatShape.hullHeight };
	point hull2Ref = { ref.x + config.boatShape.RhullWdth / 2, ref.y - config.boatShape.hullHeight };
	point sailRef = { ref.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,ref.y - config.boatShape.hullHeight / 2 };
	point mastRef = { sailRef.x + config.boatShape.sailHeight / 2.5, ref.y - config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5, sailRef.y - config.boatShape.hullHeight };
	point hull12 = { hull1Ref.x - config.boatShape.thullWdthT, hull1Ref.y };
	point hull22 = { hull2Ref.x - config.boatShape.thullWdthT, hull2Ref.y };
	point hull13 = { hull1Ref.x, hull1Ref.y + config.boatShape.hullHeight };
	point hull23 = { hull2Ref.x, hull2Ref.y + config.boatShape.hullHeight };


	hull = new Rect(pGame, ref, config.boatShape.hullHeight, config.boatShape.RhullWdth);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, { mastRef.x, mastRef.y - config.boatShape.mastHeight });
	hull1 = new triangle(pGame, hull1Ref, hull12, hull13);
	hull2 = new triangle(pGame, hull2Ref, hull22, hull23);
	hull->resize_down();


	stepCount++;

}

bool Boat::matches(const shape* target) const {
	const Boat* targetBoat = dynamic_cast<const Boat*>(target);
	if (targetBoat) {
		return hull->matches(targetBoat->hull) && hull1->matches(targetBoat->hull1) && hull2->matches(targetBoat->hull2) && sail->matches(targetBoat->sail) && mast->matches(targetBoat->mast);
	}
	return false;
}


//PLANE 


Plane::Plane(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point fuselageRef = ref;
	point noseRef = { ref.x + config.planeShape.fuselageWdth / 2,ref.y - config.planeShape.fuselageHeight / 2 };
	point tailRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y - config.planeShape.fuselageHeight / 2 };
	point upWingRef = { ref.x + config.planeShape.fuselageWdth / 10, ref.y - config.planeShape.fuselageHeight / 2 };
	point lowWingRef = { ref.x + config.planeShape.fuselageWdth / 10, ref.y + config.planeShape.fuselageHeight / 2 };
	point upStabRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y - config.planeShape.fuselageHeight / 2 };
	point lowStabRef = { ref.x - config.planeShape.fuselageWdth / 2, ref.y + config.planeShape.fuselageHeight / 2 };
	point nose2 = { noseRef.x,noseRef.y + config.planeShape.noseHeight };
	point nose3 = { noseRef.x + config.planeShape.noseWdth, noseRef.y + config.planeShape.noseHeight / 2 };
	point tail2 = { tailRef.x,tailRef.y + config.planeShape.tailHeight };
	point tail3 = { tailRef.x - config.planeShape.tailWdth, tailRef.y + config.planeShape.tailHeight / 2 };
	point upWing2 = { upWingRef.x + config.planeShape.wingWidth, upWingRef.y };
	point upWing3 = { upWingRef.x - config.planeShape.wingSweep,upWingRef.y - config.planeShape.wingHeight };
	point lowWing2 = { lowWingRef.x + config.planeShape.wingWidth, lowWingRef.y };
	point lowWing3 = { lowWingRef.x - config.planeShape.wingSweep, lowWingRef.y + config.planeShape.wingHeight };
	point upStab2 = { upStabRef.x - config.planeShape.stabWdth, upStabRef.y + config.planeShape.fuselageWdth / 4 };
	point upstab3 = { upStabRef.x - config.planeShape.stabWdth - config.planeShape.stabSweep, upStabRef.y - config.planeShape.stabHeight };
	point lowStab2 = { upStabRef.x - config.planeShape.stabWdth, upStabRef.y };
	point lowStab3 = { lowStabRef.x - config.planeShape.stabWdth - config.planeShape.stabSweep, lowStabRef.y + config.planeShape.stabHeight };
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
{
	point ref = fuselage->getRefPoint();
	fuselage->rotate();

	// Rotate nose
	point noseRef = nose->getRefPoint();
	point relativeNoseRef = { noseRef.x - ref.x, noseRef.y - ref.y };
	point rotatedRelativeNoseRef = multiplyByMatrix(relativeNoseRef);
	point newNoseRef = { ref.x + rotatedRelativeNoseRef.x, ref.y + rotatedRelativeNoseRef.y };
	nose->setRefPoint(newNoseRef);

	point nose2 = nose->getVert2();
	point relNoseVert2 = { nose2.x - ref.x, nose2.y - ref.y };
	point rotRelNoseVert2 = multiplyByMatrix(relNoseVert2);
	point newNose2 = { ref.x + rotRelNoseVert2.x, ref.y + rotRelNoseVert2.y };

	point nose3 = nose->getVert3();
	point relNoseVert3 = { nose3.x - ref.x, nose3.y - ref.y };
	point rotRelNoseVert3 = multiplyByMatrix(relNoseVert3);
	point newNose3 = { ref.x + rotRelNoseVert3.x, ref.y + rotRelNoseVert3.y };

	delete nose;
	nose = new triangle(pGame, newNoseRef, newNose2, newNose3);

	// Rotate tail
	point tailRef = tail->getRefPoint();
	point relativeTailRef = { tailRef.x - ref.x, tailRef.y - ref.y };
	point rotatedRelativeTailRef = multiplyByMatrix(relativeTailRef);
	point newTailRef = { ref.x + rotatedRelativeTailRef.x, ref.y + rotatedRelativeTailRef.y };
	tail->setRefPoint(newTailRef);

	point tail2 = tail->getVert2();
	point relTailVert2 = { tail2.x - ref.x, tail2.y - ref.y };
	point rotRelTailVert2 = multiplyByMatrix(relTailVert2);
	point newTail2 = { ref.x + rotRelTailVert2.x, ref.y + rotRelTailVert2.y };

	point tail3 = tail->getVert3();
	point relTailVert3 = { tail3.x - ref.x, tail3.y - ref.y };
	point rotRelTailVert3 = multiplyByMatrix(relTailVert3);
	point newTail3 = { ref.x + rotRelTailVert3.x, ref.y + rotRelTailVert3.y };
	delete tail;
	tail = new triangle(pGame, newTailRef, newTail2, newTail3);

	// Rotate upWing
	point upWingRef = upWing->getRefPoint();
	point relativeUpWingRef = { upWingRef.x - ref.x, upWingRef.y - ref.y };
	point rotatedRelativeUpWingRef = multiplyByMatrix(relativeUpWingRef);
	point newUpWingRef = { ref.x + rotatedRelativeUpWingRef.x, ref.y + rotatedRelativeUpWingRef.y };
	upWing->setRefPoint(newUpWingRef);

	point upWing2 = upWing->getVert2();
	point relUpWingVert2 = { upWing2.x - ref.x, upWing2.y - ref.y };
	point rotRelUpWingVert2 = multiplyByMatrix(relUpWingVert2);
	point newUpWing2 = { ref.x + rotRelUpWingVert2.x, ref.y + rotRelUpWingVert2.y };
	point upWing3 = upWing->getVert3();
	point relUpWingVert3 = { upWing3.x - ref.x, upWing3.y - ref.y };
	point rotRelUpWingVert3 = multiplyByMatrix(relUpWingVert3);
	point newUpWing3 = { ref.x + rotRelUpWingVert3.x, ref.y + rotRelUpWingVert3.y };
	delete upWing;
	upWing = new triangle(pGame, newUpWingRef, newUpWing2, newUpWing3);

	// Rotate bottomWing
	point bottomWingRef = bottomWing->getRefPoint();
	point relativeBottomWingRef = { bottomWingRef.x - ref.x, bottomWingRef.y - ref.y };
	point rotatedRelativeBottomWingRef = multiplyByMatrix(relativeBottomWingRef);
	point newBottomWingRef = { ref.x + rotatedRelativeBottomWingRef.x, ref.y + rotatedRelativeBottomWingRef.y };
	bottomWing->setRefPoint(newBottomWingRef);

	point bottomWing2 = bottomWing->getVert2();
	point relBottomWingVert2 = { bottomWing2.x - ref.x, bottomWing2.y - ref.y };
	point rotRelBottomWingVert2 = multiplyByMatrix(relBottomWingVert2);
	point newBottomWing2 = { ref.x + rotRelBottomWingVert2.x, ref.y + rotRelBottomWingVert2.y };

	point bottomWing3 = bottomWing->getVert3();
	point relBottomWingVert3 = { bottomWing3.x - ref.x, bottomWing3.y - ref.y };
	point rotRelBottomWingVert3 = multiplyByMatrix(relBottomWingVert3);
	point newBottomWing3 = { ref.x + rotRelBottomWingVert3.x, ref.y + rotRelBottomWingVert3.y };
	delete bottomWing;
	bottomWing = new triangle(pGame, newBottomWingRef, newBottomWing2, newBottomWing3);

	// Rotate upStab
	point upStabRef = upStab->getRefPoint();
	point relativeUpStabRef = { upStabRef.x - ref.x, upStabRef.y - ref.y };
	point rotatedRelativeUpStabRef = multiplyByMatrix(relativeUpStabRef);
	point newUpStabRef = { ref.x + rotatedRelativeUpStabRef.x, ref.y + rotatedRelativeUpStabRef.y };
	upStab->setRefPoint(newUpStabRef);

	point upStab2 = upStab->getVert2();
	point relUpStabVert2 = { upStab2.x - ref.x, upStab2.y - ref.y };
	point rotRelUpStabVert2 = multiplyByMatrix(relUpStabVert2);
	point newUpStab2 = { ref.x + rotRelUpStabVert2.x, ref.y + rotRelUpStabVert2.y };

	point upStab3 = upStab->getVert3();
	point relUpStabVert3 = { upStab3.x - ref.x, upStab3.y - ref.y };
	point rotRelUpStabVert3 = multiplyByMatrix(relUpStabVert3);
	point newUpStab3 = { ref.x + rotRelUpStabVert3.x, ref.y + rotRelUpStabVert3.y };
	delete upStab;
	upStab = new triangle(pGame, newUpStabRef, newUpStab2, newUpStab3);

	// Rotate lowStab
	point lowStabRef = lowStab->getRefPoint();
	point relativeLowStabRef = { lowStabRef.x - ref.x, lowStabRef.y - ref.y };
	point rotatedRelativeLowStabRef = multiplyByMatrix(relativeLowStabRef);
	point newLowStabRef = { ref.x + rotatedRelativeLowStabRef.x, ref.y + rotatedRelativeLowStabRef.y };
	lowStab->setRefPoint(newLowStabRef);
	point lowStab2 = lowStab->getVert2();
	point relLowStabVert2 = { lowStab2.x - ref.x, lowStab2.y - ref.y };
	point rotRelLowStabVert2 = multiplyByMatrix(relLowStabVert2);
	point newLowStab2 = { ref.x + rotRelLowStabVert2.x, ref.y + rotRelLowStabVert2.y };

	point lowStab3 = lowStab->getVert3();
	point relLowStabVert3 = { lowStab3.x - ref.x, lowStab3.y - ref.y };
	point rotRelLowStabVert3 = multiplyByMatrix(relLowStabVert3);
	point newLowStab3 = { ref.x + rotRelLowStabVert3.x, ref.y + rotRelLowStabVert3.y };
	delete lowStab;
	lowStab = new triangle(pGame, newLowStabRef, newLowStab2, newLowStab3);

	stepCount++;

}

void Plane::resize_up()
{
	double  factor = 2;

	point fuselageRef = RefPoint;
	point noseRef = { RefPoint.x + config.planeShape.fuselageWdth / 2 * factor,RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point tailRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point upWingRef = { RefPoint.x + config.planeShape.fuselageWdth / 10 * factor, RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point lowWingRef = { RefPoint.x + config.planeShape.fuselageWdth / 10 * factor, RefPoint.y + config.planeShape.fuselageHeight / 2 * factor };
	point upStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point lowStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y + config.planeShape.fuselageHeight / 4 };
	point nose2 = { noseRef.x,noseRef.y + config.planeShape.noseHeight * factor };
	point nose3 = { noseRef.x + config.planeShape.noseWdth * factor, noseRef.y + config.planeShape.noseHeight / 2 * factor };
	point tail2 = { tailRef.x,tailRef.y + config.planeShape.tailHeight };
	point tail3 = { tailRef.x - config.planeShape.tailWdth * factor, tailRef.y + config.planeShape.tailHeight / 2 * factor };
	point upWing2 = { upWingRef.x + config.planeShape.wingWidth * factor, upWingRef.y };
	point upWing3 = { upWingRef.x - config.planeShape.wingSweep * factor,upWingRef.y - config.planeShape.wingHeight * factor };
	point lowWing2 = { lowWingRef.x + config.planeShape.wingWidth * factor, lowWingRef.y };
	point lowWing3 = { lowWingRef.x - config.planeShape.wingSweep * factor, lowWingRef.y + config.planeShape.wingHeight * factor };
	point upStab2 = { upStabRef.x - config.planeShape.stabWdth * factor, upStabRef.y + config.planeShape.fuselageWdth / 4 * factor };
	point upstab3 = { upStabRef.x - config.planeShape.stabWdth * factor - config.planeShape.stabSweep * factor, upStabRef.y - config.planeShape.stabHeight * factor };
	point lowStab2 = { upStabRef.x - config.planeShape.stabWdth * factor, upStabRef.y };
	point lowStab3 = { lowStabRef.x - config.planeShape.stabWdth * factor - config.planeShape.stabSweep * factor, lowStabRef.y + config.planeShape.stabHeight * factor };
	fuselage = new Rect(pGame, fuselageRef, config.planeShape.fuselageHeight, config.planeShape.fuselageWdth);
	nose = new triangle(pGame, noseRef, nose2, nose3);
	tail = new triangle(pGame, tailRef, tail2, tail3);
	upWing = new triangle(pGame, upWingRef, upWing2, upWing3);
	bottomWing = new triangle(pGame, lowWingRef, lowWing2, lowWing3);
	upStab = new triangle(pGame, upStabRef, upStab2, upstab3);
	lowStab = new triangle(pGame, lowStabRef, lowStab2, lowStab3);

	fuselage->resize_up();
	nose->resize_up();
	tail->resize_up();
	upWing->resize_up();
	bottomWing->resize_up();
	upStab->resize_up();
	lowStab->resize_up();

	stepCount++;

}

void Plane::resize_down()
{
	double  factor = .5;

	point fuselageRef = RefPoint;
	point noseRef = { RefPoint.x + config.planeShape.fuselageWdth / 2 * factor,RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point tailRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point upWingRef = { RefPoint.x + config.planeShape.fuselageWdth / 10 * factor, RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point lowWingRef = { RefPoint.x + config.planeShape.fuselageWdth / 10 * factor, RefPoint.y + config.planeShape.fuselageHeight / 2 * factor };
	point upStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y - config.planeShape.fuselageHeight / 2 * factor };
	point lowStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y + config.planeShape.fuselageHeight / 4 };
	point nose2 = { noseRef.x,noseRef.y + config.planeShape.noseHeight * factor };
	point nose3 = { noseRef.x + config.planeShape.noseWdth * factor, noseRef.y + config.planeShape.noseHeight / 2 * factor };
	point tail2 = { tailRef.x,tailRef.y + config.planeShape.tailHeight * factor };
	point tail3 = { tailRef.x - config.planeShape.tailWdth * factor, tailRef.y + config.planeShape.tailHeight / 2 * factor };
	point upWing2 = { upWingRef.x + config.planeShape.wingWidth * factor, upWingRef.y };
	point upWing3 = { upWingRef.x - config.planeShape.wingSweep * factor,upWingRef.y - config.planeShape.wingHeight * factor };
	point lowWing2 = { lowWingRef.x + config.planeShape.wingWidth * factor, lowWingRef.y };
	point lowWing3 = { lowWingRef.x - config.planeShape.wingSweep * factor, lowWingRef.y + config.planeShape.wingHeight * factor };
	point upStab2 = { upStabRef.x - config.planeShape.stabWdth * factor, upStabRef.y + config.planeShape.fuselageWdth / 4 * factor };
	point upstab3 = { upStabRef.x - config.planeShape.stabWdth * factor - config.planeShape.stabSweep * factor, upStabRef.y - config.planeShape.stabHeight * factor };
	point lowStab2 = { upStabRef.x - config.planeShape.stabWdth * factor, upStabRef.y };
	point lowStab3 = { lowStabRef.x - config.planeShape.stabWdth * factor - config.planeShape.stabSweep * factor, lowStabRef.y + config.planeShape.stabHeight * factor };
	fuselage = new Rect(pGame, fuselageRef, config.planeShape.fuselageHeight, config.planeShape.fuselageWdth);
	nose = new triangle(pGame, noseRef, nose2, nose3);
	tail = new triangle(pGame, tailRef, tail2, tail3);
	upWing = new triangle(pGame, upWingRef, upWing2, upWing3);
	bottomWing = new triangle(pGame, lowWingRef, lowWing2, lowWing3);
	upStab = new triangle(pGame, upStabRef, upStab2, upstab3);
	lowStab = new triangle(pGame, lowStabRef, lowStab2, lowStab3);

	fuselage->resize_down();

	stepCount++;

}

void Plane::flip()
{//fuselage and the two wings//
	point fuselageref = fuselage->getRefPoint();
	point upwingref = upWing->getRefPoint();
	point bottwingref = bottomWing->getRefPoint();
	point upwing2 = upWing->getVert2();
	point bottmwing2 = bottomWing->getVert2();
	point upwing3 = upWing->getVert3();
	point bottmwing3 = bottomWing->getVert3();
	point newupwingref = { upwingref.x,bottwingref.y };
	point newbottref = { bottwingref.x,upwingref.y };
	point newupwing2 = { upwing2.x,bottmwing2.y };
	point newbottwing2 = { bottmwing2.x,upwing2.y };
	point newupwing3 = { upwing3.x,bottmwing3.y };
	point newbottmwing3 = { bottmwing3.x,upwing3.y };
	upWing->setRefPoint(newupwingref);
	upWing->setvert2(newupwing2);
	upWing->setvert3(newupwing3);
	bottomWing->setRefPoint(newbottref);
	bottomWing->setvert2(newbottwing2);
	bottomWing->setvert3(newbottmwing3);
	//tail and up sta and lowsta//
	point tailref = tail->getRefPoint();
	point upstaref = upStab->getRefPoint();
	point upsta2 = upStab->getVert2();
	point upsta3 = upStab->getVert3();
	point lowstaref = lowStab->getRefPoint();
	point lowsta2 = lowStab->getVert2();
	point lowsta3 = lowStab->getVert3();

	point newupstabref = { upstaref.x,lowstaref.y };
	point newupsta2 = { upsta2.x,lowsta2.y };
	point newupsta3 = { upsta3.x,lowsta3.y };

	point newbottstabref = { lowstaref.x,upstaref.y };
	point newlowsta2 = { lowsta2.x,upsta2.y };
	point newlowsta3 = { lowsta3.x,upsta3.y };

	upStab->setRefPoint(newupstabref);
	upStab->setvert2(newupsta2);
	upStab->setvert3(newupsta3);
	lowStab->setRefPoint(newbottstabref);
	lowStab->setvert2(newlowsta2);
	lowStab->setvert3(newlowsta3);

	stepCount++;


}

void Plane::move(direction dir)
{
	switch (dir) {
	case Up:
		fuselage->move(Up);
		nose->move(Up);
		tail->move(Up);
		upWing->move(Up);
		bottomWing->move(Up);
		upStab->move(Up);
		lowStab->move(Up);
		break;
	case Down:
		fuselage->move(Down);
		nose->move(Down);
		tail->move(Down);
		upWing->move(Down);
		bottomWing->move(Down);
		upStab->move(Down);
		lowStab->move(Down);
		break;
	case Right:
		fuselage->move(Right);
		nose->move(Right);
		tail->move(Right);
		upWing->move(Right);
		bottomWing->move(Right);
		upStab->move(Right);
		lowStab->move(Right);
		break;
	case Left:
		fuselage->move(Left);
		nose->move(Left);
		tail->move(Left);
		upWing->move(Left);
		bottomWing->move(Left);
		upStab->move(Left);
		lowStab->move(Left);
		break;
	}
	stepCount++;
}

bool Plane::matches(const shape* target) const {
	const Plane* targetPlane = dynamic_cast<const Plane*>(target);
	if (targetPlane) {
		return fuselage->matches(targetPlane->fuselage)
			&& nose->matches(targetPlane->nose)
			&& tail->matches(targetPlane->tail)
			&& upWing->matches(targetPlane->upWing)
			&& bottomWing->matches(targetPlane->bottomWing)
			&& upStab->matches(targetPlane->upStab)
			&& lowStab->matches(targetPlane->lowStab);

	}
	return false;
}

//ARROW

Arrow::Arrow(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point shaftRef = ref;
	point headRef = { RefPoint.x + config.arrowShape.shaftWdth / 2, RefPoint.y - config.arrowShape.headHeight / 2 };
	shaft = new Rect(pGame, shaftRef, config.arrowShape.shaftHeight, 2.5 * config.arrowShape.headWdth);
	point head2 = { headRef.x, headRef.y + config.arrowShape.headHeight };
	point head3 = { headRef.x + config.arrowShape.headWdth, headRef.y + config.arrowShape.headHeight / 2 };
	head = new triangle(pGame, headRef, head2, head3);
};

void Arrow::draw() const
{
	shaft->draw();
	head->draw();
}

void Arrow::rotate()
{
	point shaftref = shaft->getRefPoint();
	shaft->rotate();

	// Rotate head
	point headRef = head->getRefPoint();
	point relativeHeadRef = { headRef.x - shaftref.x, headRef.y - shaftref.y };
	point rotatedRelativeHeadRef = multiplyByMatrix(relativeHeadRef);
	point newHeadRef = { shaftref.x + rotatedRelativeHeadRef.x, shaftref.y + rotatedRelativeHeadRef.y };
	head->setRefPoint(newHeadRef);

	point head2 = head->getVert2();
	point relHeadVert2 = { head2.x - shaftref.x, head2.y - shaftref.y };
	point rotRelHeadVert2 = multiplyByMatrix(relHeadVert2);
	point newHead2 = { shaftref.x + rotRelHeadVert2.x, shaftref.y + rotRelHeadVert2.y };

	point head3 = head->getVert3();
	point relHeadVert3 = { head3.x - shaftref.x, head3.y - shaftref.y };
	point rotRelHeadVert3 = multiplyByMatrix(relHeadVert3);
	point newHead3 = { shaftref.x + rotRelHeadVert3.x, shaftref.y + rotRelHeadVert3.y };
	delete head;
	head = new triangle(pGame, newHeadRef, newHead2, newHead3);


	stepCount++;


}

void Arrow::resize_up()
{
	double factor = 2;
	point shaftRef = RefPoint;
	point headRef = { RefPoint.x + config.arrowShape.shaftWdth / 2 * factor, RefPoint.y - config.arrowShape.headHeight / 2 * factor };
	shaft = new Rect(pGame, shaftRef, config.arrowShape.shaftHeight, 2.5 * config.arrowShape.headWdth);
	point head2 = { headRef.x, headRef.y + config.arrowShape.headHeight * factor };
	point head3 = { headRef.x + config.arrowShape.headWdth * factor, headRef.y + config.arrowShape.headHeight / 2 * factor };
	head = new triangle(pGame, headRef, head2, head3);

	shaft->resize_up();
	head->resize_up();

	stepCount++;

}

void Arrow::resize_down()
{
	double factor = .5;
	point shaftRef = RefPoint;
	point headRef = { RefPoint.x + config.arrowShape.shaftWdth / 2 * factor, RefPoint.y - config.arrowShape.headHeight / 2 * factor };
	shaft = new Rect(pGame, shaftRef, config.arrowShape.shaftHeight, 2.5 * config.arrowShape.headWdth);
	point head2 = { headRef.x, headRef.y + config.arrowShape.headHeight * factor };
	point head3 = { headRef.x + config.arrowShape.headWdth * factor, headRef.y + config.arrowShape.headHeight / 2 * factor };
	head = new triangle(pGame, headRef, head2, head3);

	shaft->resize_down();

	stepCount++;


}

void Arrow::flip()
{
	shaft->flip();
	head->flip();

	stepCount++;

}

void Arrow::move(direction dir)
{
	switch (dir)
	{
	case Right:
		head->move(Right);
		shaft->move(Right);
		break;
	case Up:
		head->move(Up);
		shaft->move(Up);
		break;
	case Left:
		head->move(Left);
		shaft->move(Left);
		break;
	case Down:
		head->move(Down);
		shaft->move(Down);
		break;
	}


	stepCount++;

}

bool Arrow::matches(const shape* target) const {
	const Arrow* targetArrow = dynamic_cast<const Arrow*>(target);
	if (targetArrow) {
		return shaft->matches(targetArrow->shaft)
			&& head->matches(targetArrow->head);

	}
	return false;
}

