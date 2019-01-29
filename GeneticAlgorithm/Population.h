#pragma once
#include "Dot.h"
#include <vector>

class Population{
public:
	Population(int size) : _dots{ size }
	{
	}

	int bestDot = 0;
	float fitnessSum;
	int gen = 1;
	int minStep = 400;
	std::vector<Dot> _dots;
	Dot selectParent();

	void draw(RenderWindow &window);
	void update(float goal_x, float goal_y);
	void calculateFitness(float goal_x,float goal_y);
	bool areDotsDead();
	void naturalSelection();
	void calculateFitnessSum();
	void mutateDemBabies();
	void setBestDot();
};