#pragma once
#include"core.h"


namespace cyclone
{
	class VerletParticle;

	class Stick
	{
	public:

		Stick(VerletParticle* p1, VerletParticle* p2, real length);

		real getDistance();

		real getDifference(VerletParticle* p1, VerletParticle* p2);

		void distanceConstraint(real restLength);

		VerletParticle* getParticleOne() const { return m_particle1; }
		VerletParticle* getParticleTwo() const { return m_particle2; }


	private:
		VerletParticle* m_particle1;
		VerletParticle* m_particle2;

		real m_length;

	};
}
