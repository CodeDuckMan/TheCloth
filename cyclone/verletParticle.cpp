#include "verletParticle.h"

cyclone::VerletParticle::VerletParticle(real mass, Vector3 pos)
{
	setInverseMass(mass);
	setCurrentPosition(pos);
	setPreviousPosition(pos);
}

void cyclone::VerletParticle::integrate(real deltaTime)
{
	Vector3 initPos = m_position;
	if (m_isAnchor)
	{
		m_position = initPos;
		return;
	}

	if (m_inverseMass <= 0.0f) return;
	Vector3 velocity = (m_position - m_previousPos) * pow(m_damping, deltaTime);
	Vector3 nextPos = m_position + velocity + m_acceleration * deltaTime * deltaTime;
	m_previousPos = m_position;
	m_position = nextPos;
}

void cyclone::VerletParticle::setInverseMass(real mass)
{
	if (mass <= 0) mass = 0;

	m_inverseMass = (1.0 / mass);
}