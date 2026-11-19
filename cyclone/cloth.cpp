#include "cloth.h"


cyclone::Cloth::Cloth(real width, real height, real spacing, Vector3 startingPos, real clothMass)
{
	m_stickLength = spacing;
	for (int y = 0; y <= height; y++)
	{
		for (int x = 0; x <= width; x++)
		{
			VerletParticle* p = new VerletParticle(clothMass, Vector3{ startingPos.x + x * spacing, startingPos.y - y * spacing, startingPos.z });

			if (x != 0) {
				VerletParticle* leftPoint = m_particles[m_particles.size() - 1];
				Stick* s = new Stick(p, leftPoint, spacing);
				leftPoint->addStick(s, 0);
				p->addStick(s, 0);
				m_sticks.push_back(s);
			}

			if (y != 0)
			{
				VerletParticle* upPoint = m_particles[x + (y - 1) * (width + 1)];
				Stick* s = new Stick(p, upPoint, spacing);
				upPoint->addStick(s, 1);
				p->addStick(s, 1);
				m_sticks.push_back(s);
			}

			// the two anchor points (pin sets the isAnchor mem variable to true so it doesn't get updated by forces in integration)
			if (y == 0 && (x == 0 || x == width)) {
				p->pin();
			}

			m_particles.push_back(p);
		}
	}
}

void cyclone::Cloth::integrate(real dt)
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->integrate(dt);
	}

	for (int i = 0; i < m_constraintIterations; i++)
	{
		for (int i = 0; i < m_sticks.size(); i++)
		{
			m_sticks[i]->distanceConstraint(m_stickLength);
		}
	}
	
}
