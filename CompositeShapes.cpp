#include "CompositeShapes.h"
#include "gameConfig.h"
#include <fstream>



////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref):shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}

void Sign::setFillColor(color c)
{
	fillColor = c;
}

void Sign::save(ofstream& OutFile) const
{
	OutFile << "SIGN " << RefPoint.x << " " << RefPoint.y << " " << rotateCount << " " << flipCount << " " << resizeUpCount <<
		" " << resizeDownCount << " " << movecount << endl;
	top->save(OutFile);
	base->save(OutFile);
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
	point newBaseRef = {topRef.x + rotatedRelativeBaseRef.x,topRef.y + rotatedRelativeBaseRef.y };
	base->setRefPoint(newBaseRef);
	base->rotate();

	stepCount++;
	rotateCount++;
}
void Sign::resize_up()
{
	point topRef = RefPoint;	//top rect ref is the same as the sign
	point baseRef = { RefPoint.x, RefPoint.y + config.sighShape.topHeight  + config.sighShape.baseHeight  };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
	base->resize_up();
	top->resize_up();

	stepCount++;
resizeUpCount++;
}

void Sign::resize_down()
{
	point topRef = RefPoint;	//top rect ref is the same as the sign
	point baseRef = { RefPoint.x, RefPoint.y + config.sighShape.topHeight/4 + config.sighShape.baseHeight/4 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
	base->resize_down();
	top->resize_down();

	stepCount++;
resizeDownCount++;
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
	flipCount++;
}

void Sign::move(direction dir)
{
	base->move(dir);
	top->move(dir);

	stepCount++;
movecount++;
}
bool Sign::check_boundries()
{
	return  base->check_boundries();
	return top->check_boundries();
}

bool Sign::matches(const shape* target) const {
	const Sign* targetSign = dynamic_cast<const Sign*>(target);
	if (targetSign) {
		// Compare top and base rectangles
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
	point chimneyRef = { ref.x - config.houseShape.baseWdth /4, ref.y - config.houseShape.baseHeight / 2 - config.houseShape.chimneyHeight / 2 };
	point roof2 = { roofRef.x + config.houseShape.roofWdth,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth / 2,roofRef.y - config.houseShape.roofHeight };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame,roofRef, roof2, roof3);
	chimney = new Rect(pGame, chimneyRef, config.houseShape.chimneyHeight, config.houseShape.chimneyWdth);


}

void House::setFillColor(color c)
{
	fillColor = c;
}


void House::save(ofstream& OutFile) const
{
	OutFile << "HOUSE " << RefPoint.x << " " << RefPoint.y << " " << rotateCount << " " << flipCount << " " << resizeUpCount <<
		" " << resizeDownCount << " " << movecount << endl;
	base->save(OutFile);
	roof->save(OutFile);
	chimney->save(OutFile);
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
	point relativeRoofRef = {roofRef.x - baseRef.x, roofRef.y - baseRef.y };
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

	roof = new triangle(pGame, newRoofRef, newRoof2, newRoof3);



	point chimneyRef = chimney->getRefPoint();
	point relativeChimneyRef = { chimneyRef.x - baseRef.x, chimneyRef.y - baseRef.y };
	point rotatedRelativeChimneyRef = chimney->multiplyByMatrix(relativeChimneyRef);
	chimneyRef.x = baseRef.x + rotatedRelativeChimneyRef.x;
	chimneyRef.y = baseRef.y + rotatedRelativeChimneyRef.y;
	chimney->setRefPoint(chimneyRef);
	chimney->rotate();

	stepCount++;
	rotateCount++;

}

void House::resize_up()
{
	point baseref = RefPoint;
	point roofRef = { RefPoint.x - config.houseShape.roofWdth , RefPoint.y - config.houseShape.baseHeight  };
	point chimneyRef = { RefPoint.x - config.houseShape.baseWdth / 2, RefPoint.y - config.houseShape.baseHeight  - config.houseShape.chimneyHeight  };
	point roof2 = { roofRef.x + config.houseShape.roofWdth*2,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth ,roofRef.y - config.houseShape.roofHeight*2 };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
	chimney = new Rect(pGame, chimneyRef, config.houseShape.chimneyHeight, config.houseShape.chimneyWdth);
	base->resize_up();
	chimney->resize_up();

	stepCount++;
	resizeUpCount++;

}

void House::resize_down()
{
	point baseref = RefPoint;
	point roofRef = { RefPoint.x - config.houseShape.roofWdth / 4, RefPoint.y - config.houseShape.baseHeight / 4 };
	point chimneyRef = { RefPoint.x - config.houseShape.baseWdth / 8, RefPoint.y - config.houseShape.baseHeight / 4 - config.houseShape.chimneyHeight / 4 };
	point roof2 = { roofRef.x + config.houseShape.roofWdth/2,roofRef.y };
	point roof3 = { roofRef.x + config.houseShape.roofWdth / 4,roofRef.y - config.houseShape.roofHeight/2 };
	base = new Rect(pGame, baseref, config.houseShape.baseHeight, config.houseShape.baseWdth);
	roof = new triangle(pGame, roofRef, roof2, roof3);
	chimney = new Rect(pGame, chimneyRef, config.houseShape.chimneyHeight, config.houseShape.chimneyWdth);


	base->resize_down();
	chimney->resize_down();

	stepCount++;
	resizeDownCount++;


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
	flipCount++;
	
}

void House::move(direction dir){
	
	
		switch (dir)
		{
		case right:
			RefPoint.x += config.gridSpacing;
			break;
		case up:
			RefPoint.y += config.gridSpacing;
			break;
		case left:
			RefPoint.x -= config.gridSpacing;
			break;
		case down:
			RefPoint.y -= config.gridSpacing;
			break;
		}
		point roofRef = { RefPoint.x - config.houseShape.roofWdth / 2, RefPoint.y - config.houseShape.baseHeight / 2 };
		point roof2 = { roofRef.x + config.houseShape.roofWdth,roofRef.y };
		point roof3 = { roofRef.x + config.houseShape.roofWdth / 2,roofRef.y - config.houseShape.roofHeight };
		roof = new triangle(pGame, roofRef, roof2, roof3);
	base->move(dir);
	chimney->move(dir);

	stepCount++;
movecount++;
}

bool House::check_boundries()
{
	return	base -> check_boundries();
	return roof->check_boundries();
	return chimney->check_boundries();
}


bool House::matches(const shape* target) const {
	const House* targetHouse = dynamic_cast<const House*>(target);
	if (targetHouse) {
		// Compare base, roof, and chimney
		return base->matches(targetHouse->base) &&
			roof->matches(targetHouse->roof) &&
			chimney->matches(targetHouse->chimney);
	}
	return false;
}


bool House::matches(const shape* target) const {
	const House* targetHouse = dynamic_cast<const House*>(target);
	if (targetHouse) {
		return roof->matches(targetHouse->roof) && base->matches(targetHouse->base) && chimney->matches(targetHouse->chimney);
	}
	return false;
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


void Car::setFillColor(color c)
{
	fillColor = c;
}
;



void Car::save(ofstream& OutFile) const
{
	OutFile << "CAR " << RefPoint.x << " " << RefPoint.y << " " << rotateCount << " " << flipCount << " " << resizeUpCount <<
		" " << resizeDownCount << " " << movecount << endl;
	lowBody->save(OutFile);
	upBody->save(OutFile);
	frontTire->save(OutFile);
	backTire->save(OutFile);


void Car::draw() const
{
	lowBody->draw();
	upBody->draw();
	frontTire->draw();
	backTire->draw();
}

void Car::rotate()
{
	point ref = lowBody->getRefPoint();

	point topRef = upBody->getRefPoint();

	point relTopRef = { topRef.x - ref.x, topRef.y - ref.y };
	point rotatedRelativeTopRef = upBody->multiplyByMatrix(relTopRef);
	topRef.x = ref.x + rotatedRelativeTopRef.x;
	topRef.y = ref.y + rotatedRelativeTopRef.y;
	upBody->setRefPoint(topRef);

	point bTireRef = backTire->getRefPoint();

	point relativeBTireRef = { bTireRef.x - ref.x, bTireRef.y - ref.y };
	point rotatedRelativeBTireRef = backTire->multiplyByMatrix(relativeBTireRef);
	bTireRef.x = ref.x + rotatedRelativeBTireRef.x;
	bTireRef.y = ref.y + rotatedRelativeBTireRef.y;
	backTire->setRefPoint(bTireRef);

	point fTireRef = frontTire->getRefPoint();

	point relativeFTireRef = { fTireRef.x - ref.x, fTireRef.y - ref.y };
	point rotatedRelativeFTireRef = frontTire->multiplyByMatrix(relativeFTireRef);
	fTireRef.x = ref.x + rotatedRelativeFTireRef.x;
	fTireRef.y = ref.y + rotatedRelativeFTireRef.y;
	frontTire->setRefPoint(fTireRef);


	
	
	lowBody->rotate();
	upBody->rotate();

	stepCount++;
	rotateCount++;


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
		flipCount++;

}

void Car::move(direction dir)
{
	lowBody->move(dir);
	upBody->move(dir);
	frontTire->move(dir);
	backTire->move(dir);

	stepCount++;
movecount++;
}

bool Car::check_boundries()
{
	return lowBody->check_boundries();
	return upBody->check_boundries();
	return frontTire->check_boundries();
	return backTire->check_boundries();
}

void Car::resize_up()
{
	double factor = 2;
	point bottomRef = RefPoint;
	point topRef = { RefPoint.x, RefPoint.y - config.carShape.lowHeight / 2  * factor - config.carShape.upHeight / 2 * factor };
	point bTireRef = { RefPoint.x - config.carShape.lowWdth / 4 * factor , RefPoint.y + config.carShape.lowHeight / 2 * factor };
	point fTireRef = { RefPoint.x + config.carShape.lowWdth / 4 * factor , RefPoint.y + config.carShape.lowHeight / 2 * factor };
	lowBody = new Rect(pGame, bottomRef, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new polygon(pGame, topRef, config.carShape.upTOPWdth, config.carShape.upBOTWdth, config.carShape.upHeight);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
	lowBody->resize_up();
	upBody->resize_up();
	frontTire->resize_up();
	backTire->resize_up();

	stepCount++;
	resizeUpCount++;

}

void Car::resize_down()
{
	double factor = .5;
	point bottomRef = RefPoint;
	point topRef = { RefPoint.x, RefPoint.y - config.carShape.lowHeight / 2 * factor - config.carShape.upHeight / 2 * factor };
	point bTireRef = { RefPoint.x - config.carShape.lowWdth / 4 * factor , RefPoint.y + config.carShape.lowHeight / 2 * factor };
	point fTireRef = { RefPoint.x + config.carShape.lowWdth / 4 * factor , RefPoint.y + config.carShape.lowHeight / 2 * factor };
	lowBody = new Rect(pGame, bottomRef, config.carShape.lowHeight, config.carShape.lowWdth);
	upBody = new polygon(pGame, topRef, config.carShape.upTOPWdth, config.carShape.upBOTWdth, config.carShape.upHeight);
	frontTire = new circle(pGame, fTireRef, config.carShape.tireRadius);
	backTire = new circle(pGame, bTireRef, config.carShape.tireRadius);
	lowBody->resize_down();
	upBody->resize_down();
	frontTire->resize_down();
	backTire->resize_down();

	stepCount++;
	resizeDownCount++;

	
}


///Boat



Boat::Boat(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point hullRef = ref;
	point sailRef = { ref.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,ref.y - config.boatShape.hullHeight / 2 };
	point mastRef = { sailRef.x + config.boatShape.sailHeight / 2.5, ref.y - config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y};
	point sail3 = { sailRef.x + config.boatShape.sailHeight/2.5, sailRef.y - config.boatShape.hullHeight };
	hull = new polygon(pGame, hullRef, config.boatShape.tHullWdth, config.boatShape.bHullWdth, config.boatShape.hullHeight);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, { mastRef.x, mastRef.y - config.boatShape.mastHeight});
};

void Boat::setFillColor(color c)
{
	fillColor = c;
}
;


void Boat::save(ofstream& OutFile) const
{
	OutFile << "BOAT " << RefPoint.x << " " << RefPoint.y << " " << rotateCount << " " << flipCount << " " << resizeUpCount <<
		" " << resizeDownCount << " " << movecount << endl;
	hull->save(OutFile);
	sail->save(OutFile);
	mast->save(OutFile);
}


void Boat::draw() const
{
	hull->draw();
	sail->draw();
	mast->draw();
}

void Boat::rotate()
{
	point hullRef = hull->getRefPoint();
	hull->rotate();

	point sailRef = sail->getRefPoint();
	point relativeSailRef = { sailRef.x - hullRef.x, sailRef.y - hullRef.y };
	point rotatedRelativeSailRef = multiplyByMatrix(relativeSailRef);
	point newSailRef = { hullRef.x + rotatedRelativeSailRef.x, hullRef.y + rotatedRelativeSailRef.y };
	sail->setRefPoint(newSailRef);

	point sail2 = sail->getVert2();
	point relSailVert2 = { sail2.x - hullRef.x, sail2.y - hullRef.y };
	point rotRelSailVert2 = multiplyByMatrix(relSailVert2);
	point newSail2 = { hullRef.x + rotRelSailVert2.x, hullRef.y + rotRelSailVert2.y };

	point sail3 = sail->getVert3();
	point relSailVert3 = { sail3.x - hullRef.x, sail3.y - hullRef.y };
	point rotRelSailVert3 = multiplyByMatrix(relSailVert3);
	point newSail3 = { hullRef.x + rotRelSailVert3.x, hullRef.y + rotRelSailVert3.y };

	sail = new triangle(pGame, newSailRef, newSail2, newSail3);

	point mastRef = mast->getRefPoint();
	point relativeMastRef = { mastRef.x - hullRef.x, mastRef.y - hullRef.y };
	point rotatedRelativeMastRef = multiplyByMatrix(relativeMastRef);
	point newMastRef = { hullRef.x + rotatedRelativeMastRef.x, hullRef.y + rotatedRelativeMastRef.y };
	mast->setRefPoint(newMastRef);

	point mast2 = mast->getPoint2();
	point relMastVert2 = { mast2.x - hullRef.x, mast2.y - hullRef.y };
	point rotRelMastVert2 = multiplyByMatrix(relMastVert2);
	point newMast2 = { hullRef.x + rotRelMastVert2.x, hullRef.y + rotRelMastVert2.y };
	mast = new line(pGame, newMastRef, newMast2);

	stepCount++;
	rotateCount++;

}

void Boat::flip()
{
	point baseref = hull->getRefPoint();
	point sailref = sail->getRefPoint();
	point mastref = mast->getRefPoint();
	point sail3 = sail->getVert3();
	point newbaseref = { baseref.x,sail3.y};
	hull->flip();
	point newsailref = { sailref.x,sailref.y };
	point newmusref = { mastref.x,sailref.y };
	point vert33 = { sail3.x,baseref.y };
	sail->setRefPoint(newsailref);
	hull->setRefPoint(newbaseref);
	mast->setRefPoint(newmusref);
	sail->setvert3(vert33);

	stepCount++;
	flipCount++;
}

void Boat::move(direction dir)
{

	switch (dir)
	{
	case right:
		RefPoint.x += config.gridSpacing;
		break;
	case up:
		RefPoint.y += config.gridSpacing;
		break;
	case left:
		RefPoint.x -= config.gridSpacing;
		break;
	case down:
		RefPoint.y -= config.gridSpacing;
		break;
	}

	point sailRef = { RefPoint.x - config.boatShape.bHullWdth / 2 - config.boatShape.tHullWdth / 10,RefPoint.y - config.boatShape.hullHeight / 2 };
	point sail2 = { sailRef.x + config.boatShape.sailWdth, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5, sailRef.y - config.boatShape.hullHeight };
	sail = new triangle(pGame, sailRef, sail2, sail3);


	hull->move(dir);
	
	mast->move(dir);


	stepCount++;
movecount++;
}


bool Boat::check_boundries()
{
	return sail->check_boundries();
	return hull->check_boundries();
	return mast->check_boundries();
}


void Boat::resize_up()
{
	double factor = 2;
	point hullRef = RefPoint;
	point sailRef = { RefPoint.x - config.boatShape.bHullWdth / 2 * factor - config.boatShape.tHullWdth / 10 * factor,RefPoint.y - config.boatShape.hullHeight / 2 * factor };
	point mastRef = { sailRef.x + config.boatShape.sailHeight / 2.5 * factor, RefPoint.y - config.boatShape.hullHeight / 2 * factor * factor };
	point sail2 = { sailRef.x + config.boatShape.sailWdth * factor, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5 * factor, sailRef.y - config.boatShape.hullHeight * factor };
	hull = new polygon(pGame, hullRef, config.boatShape.tHullWdth, config.boatShape.bHullWdth, config.boatShape.hullHeight);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, { mastRef.x, mastRef.y - config.boatShape.mastHeight });
	hull->resize_up();


	stepCount++;
resizeUpCount++;
	
}

void Boat::resize_down()
{
	double factor = .5;
	point hullRef = RefPoint;
	point sailRef = { RefPoint.x - config.boatShape.bHullWdth / 2 * factor - config.boatShape.tHullWdth / 10 * factor,RefPoint.y - config.boatShape.hullHeight / 2 * factor };
	point mastRef = { sailRef.x + config.boatShape.sailHeight / 2.5 * factor, RefPoint.y + config.boatShape.hullHeight/2  *factor  };
	point sail2 = { sailRef.x + config.boatShape.sailWdth * factor, sailRef.y };
	point sail3 = { sailRef.x + config.boatShape.sailHeight / 2.5 * factor, sailRef.y - config.boatShape.hullHeight * factor };
	hull = new polygon(pGame, hullRef, config.boatShape.tHullWdth, config.boatShape.bHullWdth, config.boatShape.hullHeight);
	sail = new triangle(pGame, sailRef, sail2, sail3);
	mast = new line(pGame, mastRef, { mastRef.x, mastRef.y - config.boatShape.mastHeight });
	hull->resize_down();


	stepCount++;
	resizeDownCount++;

}



//PLANE 


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
	point tail3 = {tailRef.x - config.planeShape.tailWdth, tailRef.y + config.planeShape.tailHeight/2};
	point upWing2 = { upWingRef.x + config.planeShape.wingWidth, upWingRef.y };
	point upWing3 = {upWingRef.x - config.planeShape.wingSweep,upWingRef.y - config.planeShape.wingHeight};
	point lowWing2 = {lowWingRef.x + config.planeShape.wingWidth, lowWingRef.y};
	point lowWing3 = { lowWingRef.x - config.planeShape.wingSweep, lowWingRef.y + config.planeShape.wingHeight };
	point upStab2 = {upStabRef.x - config.planeShape.stabWdth, upStabRef.y + config.planeShape.fuselageWdth/4};
	point upstab3 = {upStabRef.x - config.planeShape.stabWdth - config.planeShape.stabSweep, upStabRef.y - config.planeShape.stabHeight};
	point lowStab2 = { upStabRef.x - config.planeShape.stabWdth, upStabRef.y};
	point lowStab3 = {lowStabRef.x - config.planeShape.stabWdth - config.planeShape.stabSweep, lowStabRef.y + config.planeShape.stabHeight };
	fuselage = new Rect(pGame, fuselageRef, config.planeShape.fuselageHeight, config.planeShape.fuselageWdth);
	nose = new triangle(pGame, noseRef, nose2, nose3);
	tail = new triangle(pGame, tailRef, tail2, tail3 );
	upWing = new triangle(pGame, upWingRef, upWing2, upWing3);
	bottomWing = new triangle(pGame, lowWingRef, lowWing2, lowWing3);
	upStab = new triangle(pGame, upStabRef, upStab2, upstab3);
	lowStab = new triangle(pGame, lowStabRef, lowStab2, lowStab3);
}

void Plane::setFillColor(color c)
{
	fillColor = c;
}


void Plane::save(ofstream& OutFile) const
{
	OutFile << "PLANE  " << RefPoint.x << " " << RefPoint.y << " " << rotateCount << " " << flipCount << " " << resizeUpCount <<
		" " << resizeDownCount << " " << movecount << endl;
	fuselage->save(OutFile);
	nose->save(OutFile);
	tail->save(OutFile);
	upWing->save(OutFile);
	bottomWing->save(OutFile);
	upStab->save(OutFile);
	lowStab->save(OutFile);
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

	lowStab = new triangle(pGame, newLowStabRef, newLowStab2, newLowStab3);

	stepCount++;
	rotateCount++;

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
	point lowStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2 * factor, RefPoint.y + config.planeShape.fuselageHeight/4  };
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
	point lowStab2 = { upStabRef.x - config.planeShape.stabWdth * factor, upStabRef.y  };
	point lowStab3 = { lowStabRef.x - config.planeShape.stabWdth * factor - config.planeShape.stabSweep * factor, lowStabRef.y + config.planeShape.stabHeight* factor };
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
resizeUpCount++;
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
	resizeDownCount++;

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
	flipCount++;

}

void Plane::move(direction dir)
{
	switch (dir)
	{
	case right:
		RefPoint.x += config.gridSpacing;
		break;
	case up:
		RefPoint.y += config.gridSpacing;
		break;
	case left:
		RefPoint.x -= config.gridSpacing;
		break;
	case down:
		RefPoint.y -= config.gridSpacing;
		break;
	}

	point noseRef = { RefPoint.x + config.planeShape.fuselageWdth / 2,RefPoint.y - config.planeShape.fuselageHeight / 2 };
	point tailRef = { RefPoint.x - config.planeShape.fuselageWdth / 2, RefPoint.y - config.planeShape.fuselageHeight / 2 };
	point upWingRef = { RefPoint.x + config.planeShape.fuselageWdth / 10, RefPoint.y - config.planeShape.fuselageHeight / 2 };
	point lowWingRef = { RefPoint.x + config.planeShape.fuselageWdth / 10, RefPoint.y + config.planeShape.fuselageHeight / 2 };
	point upStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2, RefPoint.y - config.planeShape.fuselageHeight / 2 };
	point lowStabRef = { RefPoint.x - config.planeShape.fuselageWdth / 2, RefPoint.y + config.planeShape.fuselageHeight / 2 };
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
	nose = new triangle(pGame, noseRef, nose2, nose3);
	tail = new triangle(pGame, tailRef, tail2, tail3);
	upWing = new triangle(pGame, upWingRef, upWing2, upWing3);
	bottomWing = new triangle(pGame, lowWingRef, lowWing2, lowWing3);
	upStab = new triangle(pGame, upStabRef, upStab2, upstab3);
	lowStab = new triangle(pGame, lowStabRef, lowStab2, lowStab3);


	 fuselage->move(dir);


	 stepCount++;
movecount++;
}

bool Plane::check_boundries()
{
	 return nose->check_boundries();
	 return tail->check_boundries();
	 return upWing->check_boundries();
	 return bottomWing->check_boundries();
	 return upStab->check_boundries();
	 return lowStab->check_boundries();
	 return fuselage->check_boundries();
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

void Arrow::setFillColor(color c)
{
	fillColor = c;
}
;

void Arrow::save(ofstream& OutFile) const
{
	OutFile << "ARROW " << RefPoint.x << " " << RefPoint.y << " " << rotateCount << " " << flipCount << " " << resizeUpCount <<
		" " << resizeDownCount << " " << movecount << endl;
	shaft->save(OutFile);
	head->save(OutFile);
}


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

	head = new triangle(pGame, newHeadRef, newHead2, newHead3);


	stepCount++;
	rotateCount++;


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
resizeUpCount++;
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
	resizeDownCount++;

	
}

void Arrow::flip()
{
	shaft->flip();
	head->flip();

	stepCount++;
	flipCount++;
}

void Arrow::move(direction dir)
{
	switch (dir)
	{
	case right:
		RefPoint.x += config.gridSpacing;
		break;
	case up:
		RefPoint.y += config.gridSpacing;
		break;
	case left:
		RefPoint.x -= config.gridSpacing;
		break;
	case down:
		RefPoint.y -= config.gridSpacing;
		break;
	}
	point headRef = { RefPoint.x + config.arrowShape.shaftWdth / 2 , RefPoint.y - config.arrowShape.headHeight / 2 };
	point head2 = { headRef.x, headRef.y + config.arrowShape.headHeight  };
	point head3 = { headRef.x + config.arrowShape.headWdth , headRef.y + config.arrowShape.headHeight / 2  };
	head = new triangle(pGame, headRef, head2, head3);
	shaft->move(dir);

	stepCount++;
movecount++;
}

bool Arrow::check_boundries()
{
	return head->check_boundries();
	return shaft->check_boundries();
}


