#include "Population.h"
#include <random>
#include <iostream>


void Population::draw(RenderWindow & window)
{
	for (std::size_t i = 0; i < _dots.size(); ++i)
	{
		_dots[i].draw(window);
	}
}

void Population::update(float goal_x, float goal_y)
{
	for (std::size_t i = 0; i < _dots.size(); ++i)
	{
		if (_dots[bestDot].brain.step > minStep) _dots[i].isDead = true;
		else _dots[i].update(goal_x, goal_y);
	}
}

void Population::calculateFitness(float goal_x, float goal_y)
{
	for (std::size_t i = 0; i < _dots.size(); ++i)
	{
		_dots[i].calculateFitness(goal_x,goal_y);
	}
}

bool Population::areDotsDead()
{
	for (std::size_t i = 0; i < _dots.size(); ++i)
	{
		if (!_dots[i].isDead && !_dots[i].reachedGoal)
		{
			return false;
		}
	}

	return true;
}

void Population::naturalSelection()
{
	std::vector<Dot> _newDots;
	std::size_t size = _dots.size();
	_newDots.resize(size);

	setBestDot();
	calculateFitnessSum();

	//the champion lives on 
	_newDots[0] = _dots[bestDot].gimmeBaby();
	_newDots[0].isBest = true;

	for (std::size_t i = 1; i < _newDots.size(); ++i)
	{
		//select parent based on fitness
		Dot parent = selectParent();
		//get baby from them
		_newDots[i] = parent.gimmeBaby();
	}
	_dots = _newDots;

	gen++;

}


void Population::calculateFitnessSum()
{
	fitnessSum = 0;
	for (std::size_t i = 0; i < _dots.size(); ++i) {
		fitnessSum += _dots[i].fitness;
	}
}

void Population::mutateDemBabies()
{
	for (std::size_t i = 1; i< _dots.size(); ++i) {
		_dots[i].brain.mutate();
	}
}

void Population::setBestDot()
{
	float max = 0.0f;
	int maxIndex = 0;
	for (std::size_t i = 0; i < _dots.size(); ++i) {
		if (_dots[i].fitness > max) {
			max = _dots[i].fitness;
			maxIndex = i;
		}
	}
	bestDot = maxIndex;

	std::cout << "Gen " << gen << ": ";
	if (_dots[bestDot].reachedGoal) {
		minStep = _dots[bestDot].brain.step;
		std::cout << _dots[bestDot].brain.step << " steps." << std::endl;
	} else if (!_dots[bestDot].reachedGoal) std::cout << "Didn't reach goal. " << std::endl;
}

Dot Population::selectParent()
{

	std::random_device rd;
	std::default_random_engine generator(rd()); // rd() provides a random seed
	std::uniform_real_distribution<float> distribution(0.0, fitnessSum);

	float rand = distribution(generator);

	float runningSum = 0;

	for (std::size_t i = 0; i < _dots.size(); ++i)
	{
		runningSum += _dots[i].fitness;
		if (runningSum > (float)rand) {
			return _dots[i];
		}
	}

	// never here

	return _dots[0];
}
