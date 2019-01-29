#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>

using namespace sf;
class Brain {
public:
	std::size_t step = 0;
	Brain(int size) : _directions{ size }
	{
		//-------------------------
		randomize();
	}
	std::vector<Vector2f> _directions;
	void randomize();
	void mutate();
	Brain clone();

};