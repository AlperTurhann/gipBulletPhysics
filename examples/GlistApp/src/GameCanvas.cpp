/*
 * GameCanvas.cpp
 *
 *  Edited on : 16.02.2023
 *  	Author: Remzi ISCI
 */


#include "GameCanvas.h"


GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
	gBulletObj->clean();
}

void GameCanvas::setup() {
	gBulletObj = new gipBulletPhysics(gipBulletPhysics::WORLDCOORDINATETYPE::WORLD2D);
	sky.loadImage("layer-1-sky.png");
	mountain.loadImage("layer-2-mountain.png");
	ground.loadImage("layer-3-ground.png");
	ramp.loadImage("ramp.png");
	gameIcon.loadImage("gameicon/icon.png");

	// create object with image referance
	groundobject   = new gImageGameObject(gBulletObj);
	groundobject->setTag(1); //1 for grouping grounds
	groundobject->setName("Ground Object");
	groundobject->setImage(&ground);
	groundobject->setPosition(0.0f, getHeight() - ground.getHeight());
	groundobject->setBounce(0.1f);

	// create object without image referance
	rampobject   = new gImageGameObject(gBulletObj);
	rampobject->setTag(1); //1 for grouping grounds, you can set any integer as you wish
	rampobject->setName("Ramp Object");
	rampobject->setColliderSize(200.0f, 40.0f);
	rampobject->setPosition(getWidth() * 0.8f, getHeight() * 0.7f);
	rampobject->setRotation(135.0f);
	rampobject->setBounce(0.1f);
	//rampobject->setFriction(100.f);
	//rampobject->setRollingFriction(100.f);
	//rampobject->setSpinningFriction(100.f);

	// create object with image referance
	gameiconobject   = new gImageGameObject(gBulletObj);
	gameiconobject->setTag(2); //2 for grouping non ground statics, you can set any integer as you wish
	gameiconobject->setImage(&gameIcon);
	gameiconobject->setName("Gameicon Object");
	gameiconobject->setPosition(0.0f, getHeight() * 0.4f);

	// create object with loading image
	softballobject = new gImageGameObject(gBulletObj);
	gameiconobject->setTag(3); //3 for balls, you can set any integer as you wish
	softballobject->setName("Softball Object");
	softballobject->loadImage("ball.png");
	softballobject->setShapeType(gipBaseGameObject::SHAPETYPE::SHAPETYPE_SPHERE);
	softballobject->setPosition(getWidth() - softballobject->getWidth(), getHeight() * 0.1f);
	softballobject->setMass(4.0f);
	softballobject->setBounce(0.4f);
	softballobject->setOnCollided(std::bind(&GameCanvas::onCollidedBall,this, std::placeholders::_1));

	//create object with loading image
	ghostballobject = new gImageGameObject(gBulletObj);
	//you can lock or unlock size of collider and image
	//ghostballobject->setIsSizeLocked(false);
	ghostballobject->loadImage("ball.png");
	//you can set image render size
	//ghostballobject->setObjectSize(400.0f, 400.0f);
	ghostballobject->setTag(3); //3 for balls, you can set any integer as you wish
	ghostballobject->setName("Softball Object");
	ghostballobject->setColliderSize(80.0f, 80.0f);
	ghostballobject->setShapeType(gipBaseGameObject::SHAPETYPE::SHAPETYPE_SPHERE);
	ghostballobject->setPosition(0 + ghostballobject->getWidth(), getHeight() * 0.1f);
	ghostballobject->setMass(4.0f);
	ghostballobject->setBounce(0.1f);
	//softballobject->setOnCollided(std::bind(&GameCanvas::onCollidedBall,this, std::placeholders::_1));

}

void GameCanvas::update() {

	// Physics calculations doing here.
	gBulletObj->runPhysicWorldStep();
	// force and impulse methods can call here.
	//ghostballobject->applyTorque(glm::vec3(0.0f, 0.0f, -40.0f));
	//ghostballobject->applyCentralForce(glm::vec3(10.0f, 0.0f, 0.0f));
	//ghostballobject->applyImpulse(glm::vec3(0.0f, 0.0f, -100.0f), glm::vec3(0.0f, 0.0f, 0.0f)); //will add velocity instant
}

void GameCanvas::draw() {
	//Draws nimages without colliders
	sky.draw(getWidth() / 2 - sky.getWidth() / 2, getHeight() - sky.getHeight());
	mountain.draw(getWidth() / 2 - mountain.getWidth() / 2, getHeight() - mountain.getHeight() / 2);

	//Draw physic objects
	ghostballobject->draw();
	gameiconobject->draw();
	rampobject->draw();
	softballobject->draw();
	groundobject->draw();

	//This line for draw collider, delete or comment this line when get release
	gBulletObj->drawDebug();
}

void GameCanvas:: onCollidedBall(int targetid) {
	gLogi("Ball Collison") << gBulletObj->getObject(targetid)->getName() << " Hitted me";
}

void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
}

void GameCanvas::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;
}

void GameCanvas::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void GameCanvas::mousePressed(int x, int y, int button) {
//	gLogi("GameCanvas") << "mousePressed" << ", button:" << button;
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
}

void GameCanvas::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::windowResized(int w, int h) {
}

void GameCanvas::showNotify() {
}

void GameCanvas::hideNotify() {
}

void GameCanvas::startCleanup() {

}
