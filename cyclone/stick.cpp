#include "stick.h"
#include "verletParticle.h"

cyclone::Stick::Stick(VerletParticle* p1, VerletParticle* p2, real length)
{
	m_particle1 = p1;
	m_particle2 = p2;
	m_length = length;
}

cyclone::real cyclone::Stick::getDistance()
{
	real dX = m_particle1->getCurrentPosition().x - m_particle2->getCurrentPosition().x;
	real dY = m_particle1->getCurrentPosition().y - m_particle2->getCurrentPosition().y;
	real dZ = m_particle1->getCurrentPosition().z - m_particle2->getCurrentPosition().z;

	return sqrt(dX * dX + dY * dY + dZ + dZ);
}

void cyclone::Stick::distanceConstraint(real restLength)
{
	real weight1 = m_particle1->getInverseMass();
	real weight2 = m_particle2->getInverseMass();
	real weigthSum = weight1 + weight2;
	// basically checking if the particles are pinned so the weight gets applied accordingly
	if (weigthSum == 0) return;

	Vector3 deltaPos = m_particle2->getCurrentPosition() - m_particle1->getCurrentPosition();

	real deltaLength = deltaPos.magnitude();

	real diff = (deltaLength - restLength) / (deltaLength * (weight1 + weight2));

	m_particle1->addPosition(deltaPos * weight1 * diff);
	m_particle2->addPosition(deltaPos * weight2 * -diff);
}