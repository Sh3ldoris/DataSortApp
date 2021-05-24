#pragma once
class Level
{
public:
	virtual void doLevel() = 0;
	virtual ~Level();
};

inline Level::~Level()
{
}