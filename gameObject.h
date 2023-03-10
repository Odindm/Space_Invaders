#pragma once
#include "Util.h"

class Collidable
{
public:
        virtual ~Collidable() {}
	virtual Disk getCollisionHull() const = 0;
};

class GameObject
{

public:	
        virtual ~GameObject() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};
