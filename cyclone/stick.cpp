#include "stick.h"


cyclone::Stick::Stick(VerletParticle* p1, VerletParticle* p2, real length)
{
	m_particle1 = p1;
	m_particle2 = p2;
	m_length = length;
}

cyclone::real cyclone::Stick::getDistance(VerletParticle* p1, VerletParticle* p2)
{
	real dX = p1->getCurrentPosition().x - p2->getCurrentPosition().x;
	real dY = p1->getCurrentPosition().y - p2->getCurrentPosition().y;
	real dZ = p1->getCurrentPosition().z - p2->getCurrentPosition().z;

	return sqrt(dX * dX + dY * dY + dZ + dZ);


}