#pragma once
#include"core.h"
#include "verletParticle.h"

namespace cyclone
{
	class Stick
	{
	public:

		Stick(VerletParticle* p1, VerletParticle* p2, real length);

		real getDistance(VerletParticle* p1, VerletParticle* p2);

		getDifference(VerletParticle* p1, VerletParticle* p2);

	private:
		VerletParticle* m_particle1;
		VerletParticle* m_particle2;

		real m_length;

	};
}
