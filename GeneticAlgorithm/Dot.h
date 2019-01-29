#pragma once
#include <SFML/Graphics.hpp>
#include "Brain.h"


using namespace sf;
class Dot 
{
public:
	Vector2f pos;
	Vector2f vel;
	Vector2f acc;
	Brain brain{ 400 };

	float fitness = 0.0f;
	int step = 0;
	bool isDead = false;
	bool reachedGoal = false;
	bool isBest = false;
public:
	Dot() {
		pos = Vector2f(320.0f, 470.0f);
		vel = Vector2f(0, 0);
		acc = Vector2f(0, 0);

	}

	CircleShape dotCir;
	void draw(RenderWindow &window);
	void move();
	void update(float goal_x, float goal_y);
	void calculateFitness(float goal_x, float goal_y);
	float dist(float x, float y, float a, float b);
	Dot gimmeBaby();
};