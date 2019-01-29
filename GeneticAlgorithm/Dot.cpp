#include "Dot.h"
#include <cmath>

void Dot::draw(RenderWindow & window)
{
	if (!isBest)
	{
		dotCir.setRadius(2.5f);
		dotCir.setFillColor(Color::Black);
		dotCir.setPosition(pos);
	}
	else if (isBest)
	{
		dotCir.setRadius(3.5f);
		dotCir.setFillColor(Color::Red);
		dotCir.setPosition(pos);
	}
	window.draw(this->dotCir);
}

void Dot::move()
{
	
	if (brain._directions.size() > brain.step) {
		acc = brain._directions[brain.step];
		brain.step++;
	}
	else
	{
		isDead = true;
	}

	vel += acc;
	//Limit velocity
	if (vel.x > 5.0f) vel.x = 5.0f;
	if (vel.x < -5.0f) vel.x = -5.0f;
	if (vel.y > 5.0f) vel.y = 5.0f;
	if (vel.y < -5.0f) vel.y = -5.0f;

	pos += vel;
	dotCir.setPosition(pos);
}

void Dot::update(float goal_x, float goal_y)
{
	if (dist(pos.x, pos.y, goal_x, goal_y) < 5.0f)
	{
		reachedGoal = true;
	}
	else if(!this->isDead && !this->reachedGoal)
	{
		move();
		//check if outside the window
		if (this->pos.x > 640 - 3 || this->pos.x < 0 - 3
			|| this->pos.y > 480 - 3 || this->pos.y < 0 - 3) {
			isDead = true;
		}
	}
	//------------------------
	//Check for obstacles -- temp
	if ((pos.x > 0.0f && pos.x < 550.0f) && (pos.y > 300.0f && pos.y < 315.0f))
	{
		isDead = true;
	}



}

void Dot::calculateFitness(float goal_x, float goal_y)
{
	if (reachedGoal) {//if the dot reached the goal then the fitness is based on the amount of steps it took to get there
		fitness = 1.0f / 16.0f + 10000.0f / (float)(brain.step * brain.step);
	}
	else {
		float distToGoal = dist(pos.x, pos.y, goal_x, goal_y);
		fitness = 1.0f / (distToGoal * distToGoal);
	}
}

float Dot::dist(float x, float y, float a, float b) {
	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}


Dot Dot::gimmeBaby()
{
	Dot baby;
	baby.brain = brain.clone();//babies have the same brain as their parents
	return baby;
}
