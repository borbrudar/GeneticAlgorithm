#include "Brain.h"
#include <algorithm>

void Brain::randomize()
{
	std::random_device rd;
	std::default_random_engine generator(rd()); // rd() provides a random seed
	std::uniform_real_distribution<float> distribution(0.0, 360.0f);

	for (std::size_t i = 0; i < _directions.size(); ++i) {
		float randomAngle = distribution(generator);
		_directions[i].x = 2.5f * std::cos(randomAngle * (3.14159f / 180.0f)); 
		_directions[i].y = 2.5f * std::sin(randomAngle * (3.14159f / 180.0f));
	}
}


void Brain::mutate()
{

	//--------------------
	std::random_device rd;
	std::default_random_engine generator(rd()); // rd() provides a random seed
	std::uniform_real_distribution<float> angle(0.0, 360.0f);
	std::uniform_real_distribution<float> dist(0.0, 1.0f);

	float mutationRate = 0.01f;//chance that any vector in directions gets changed
	for (std::size_t i = 0; i < _directions.size(); ++i) {
		float rand = dist(generator);
		if (rand < mutationRate) {
			//set this direction as a random direction
			float randomAngle = angle(generator);
			_directions[i].x = 2.5f * std::cos(randomAngle * (3.14159f / 180.0f));
			_directions[i].y = 2.5f * std::sin(randomAngle * (3.14159f / 180.0f));
		}
	}
}


Brain Brain::clone()
{
	std::size_t size = _directions.size();
	Brain clone{ (int)size };
	for (std::size_t i = 0; i < _directions.size(); ++i) {
		clone._directions[i] = _directions[i];
	}
	return clone;
}
