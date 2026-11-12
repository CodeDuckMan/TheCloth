#pragma once
#include"core.h"
#include <vector>
#include "verletParticle.h"

namespace cyclone
{
	class Cloth
	{
	public:
		Cloth(real width, real height, real spacing, Vector3 startingPos, real clothMass); // rn num of segments is for both width and height

		void integrate(real dt);


	private:

		std::vector<VerletParticles*> particles;
		std::vector<Sticks*> sticks;

		real m_clothWidth;
		real m_clothHeight;

		Vector3 m_gravity = { 0.0f, -9.8f, 0.0f };

		real m_constraintIterations = 50;

	};
}