/*
 * gipBaseGameObject.h
 *
 *  Created on: 5 03 2023
 *      Author: Remzi ISCI
 */

#ifndef SRC_GIPBASEGAMEOBJECT_H_
#define SRC_GIPBASEGAMEOBJECT_H_

#include "glm/glm.hpp"
#include <Functional>
#include "bullet/btBulletDynamicsCommon.h"

#include "gModel.h"
#include "gImage.h"

class gipBulletPhysics;

class gipBaseGameObject {

public:

	enum COORDINATE { COORDINATE2D = 0, COORDINATE3D = 1 };
	/*
	 * Tranform type for collision shapes
	 *
	 * Box = 0
	 * Sphere = 8
	 * Compound = 31
	 */
	enum TRANSFORMTYPE {
		TRANSFORMTYPE_BOX = 0,
		TRANSFORMTYPE_SPHERE = 8,
		TRANSFORMTYPE_COMPOUND = 31,
	};

	enum SHAPETYPE {
		SHAPETYPE_BOX,
		SHAPETYPE_SPHERE,
		SHAPETYPE_CYLINDER,
		SHAPETYPE_CAPSULE,
		SHAPETYPE_CONE
	};

	enum OBJECTRENDERTYPE {
		OBJECTRENDERTYPE_IMAGE,
		OBJECTRENDERTYPE_MODEL,
		OBJECTRENDERTYPE_NONE
	};
	gipBaseGameObject();
	virtual ~gipBaseGameObject();


	friend class gipBulletPhysics;

	/*
	 * Use this function for setting Oncollision fu
	 * use std::bind for parameter
	 */
	void setOnCollided(std::function<void(int, glm::vec3, glm::vec3)> onColl);

	//get with of conten(image, model etc)
	int getWidth();

	//get height of conten(image, model etc)
	int getHeight();

	void setTag(int newtag);
	int getTag();

	std::string getName();
	void setName(std::string newname);

	int getID();

	glm::vec3 getPosition();
	void setPosition(float x, float y, float z = 0.0f);

	//degree
	glm::vec3 getRotation();
	void setRotation(float degrex, float degrey, float degrez);
	//degree
	//This for 2d object and world
	void setRotation(float degrez);

	/*
	 * set size of object 1 is default
	 * size need to be between 0.04 and 100000
	 * For BOX : each axis means one egde
	 * For SPHERE : all axis means radius can be same
	 * for Cylinder X means radius, y means height
	 * for Cone x means raadius, y means height
	 */
	void setColliderSize(float x, float y, float z = -1.0f);
	glm::vec3 getColliderSize();
	void setObjectSize(float width, float height, float depth = -1.0f);
	glm::vec3 getObjectSize();

	/*
	 * Set lock size of object and collider
	 */
	void setIsSizeLocked(bool islocked);
	bool getIsSizeLocked();


	//Call this function for changing shape type
	void setShapeType(SHAPETYPE shapetype);
	int getShapeType();

	glm::vec3 getOrigin();

	//Set base physic methods ---------------------------------------------------------------
	float getMass();
	void setMass(float newmass);
	void setFriction(float newvalue);
	float getFriction();
	void setRollingFriction(float newvalue);
	float getRollingFriction();
	void setSpinningFriction(float newvalue);
	float getSpinnigFriction();
	void setAnisotropicFriction(glm::vec3 newvalue, int anisotropicfrictionmode = 1);


	//value should become between 0 and 1
	void setBounce(float newvalue = 0.0f);


	// These apply methods should be used in update method.
	void applyCentralForce(glm::vec3 forcevalue);
	void applyCentralImpulse(glm::vec3 impulsevalue);
	void applyForce(glm::vec3 forcevalue,glm::vec3 forcepos);
	void applyImpulse(glm::vec3 impulsevalue,glm::vec3 impulsepos);
	void applyTorque(glm::vec3 torquevalue);
	void applyTorqueImpulse(glm::vec3 torquevalue);

	//----------------------------------------------------------------------------------------


	btTransform* getTransform();
	btCollisionShape* getCollisionShape();
	btRigidBody* getRigidBody();

	void destroy();

	bool getIsStatic();



protected:

	/*
	 * This function will be called when object collided with another object
	 *
	 * !!!
	 *  Dont call this function manuel
	 *  This function will be used by physic engine
	 */
	void warnCollided(int targetobjectid, glm::vec3 selfcollpos, glm::vec3 targetcollpos);

	/*
	 * This function is for physic engine dont use manualy
	 */
	void updatePositionVariable();

	/*
	 * This function is for physic engine dont use manualy
	 */
	void updateRotationVariable();

	/*
	 *This function referans for onCollided func
	 *This referance will connect Canvas function to physic object function
	 *You need use std::bind with setOncollided to using this referance
	 */
	std::function<void(int, glm::vec3, glm::vec3)> _onColl;


	//Referances--------------------------------
	gImage* _image;
	gModel* _model;
	gipBulletPhysics*_physicworld;
	btTransform _transform;
	btCollisionShape* _collisionshape;
	btRigidBody* _rigidbody;
	//----------------------------------------------


	//Game world properties-------------------------
	//id is comes from physic engine object list id
	int _id = -1;
	int _width = 200;
	int _height = 200;
	int _depth = 1.0f;
	glm::vec3 _sizecollider = glm::vec3(200.0f, 200.0f, 1.0f);
	bool _isrenderersizelocked = true;
	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	btQuaternion _rotation;
	//------------------------------------------------

	//Physic properties-------------------------------

	float _mass = 0.0f;
	float _friction = 0.0f;
	float _rollingfriction = 0.0f;
	float _spinningFriction = 0.0f;
	glm::vec3 _anisotropicfriction;
	int _anistropicfrictionmode;
	//-------------------------------------------------


	//True if setted OnCollided Function
	bool _isOnCollidedFuncSetted = false;


	OBJECTRENDERTYPE _renderobjecttype = OBJECTRENDERTYPE_IMAGE;
	SHAPETYPE _shapetype = SHAPETYPE_BOX;

	//True if renderer object setted
	bool _isrenderobjectloaded = false;

	/*
	 * 0 = 2D
	 * 1 = 3D
	 */
	COORDINATE _coordinatetype = COORDINATE2D;

	/*
	 * This function is for chil object to set rotation
	 */
	bool _isstatic = true;

	/*
	 * Tag is for grouping objects
	 */
	int _tag = 0;

	/*
	 * for naming object
	 */
	std::string _objectname = "new object";

	/*
	 * object layer has
	 *
	 */
	int _objectlayers = 1<<1;

	/*
	 * mask layer, object will collide which object has this layers
	 * Layer is bitwise
	 * All layer  collide for default
	 */
	int _masklayers = 1<<1 |1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7 | 1<<8 | 1<<9 | 1<<10
			| 1<<11 | 1<<12 | 1<<13 | 1<<14 | 1<<15 | 1<<16 | 1<<17 | 1<<18 | 1<<19 | 1<<20
			| 1<<21 | 1<<22;
};


#endif /* SRC_GIPBASEGAMEOBJECT_H_ */
