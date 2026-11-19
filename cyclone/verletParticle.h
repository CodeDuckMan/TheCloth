#pragma once
#include "core.h"
#include "stick.h"

namespace cyclone
{
	class VerletParticle
	{
	public:

		VerletParticle(real mass, Vector3 pos);

		void integrate(real deltaTime);


		void setInverseMass(const real mass);
		real getInverseMass() const { return m_inverseMass; }


		void addPosition(Vector3 pos) { m_position += pos; }
		void setCurrentPosition(const Vector3 position) { m_position = position; }
		Vector3 getCurrentPosition() const { return m_position; }

		Vector3 getPreviousPos() const { return m_previousPos; }

		void setPreviousPosition(Vector3 pos) { m_previousPos = pos; }


		void addStick(Stick* stick, int index) { m_sticks[index] = stick; }
		void pin() { m_isAnchor = true; }

	private:
		Vector3 m_position = Vector3{ 0, 0, 0 };
		Vector3 m_previousPos = m_position;
		real m_inverseMass;

		Vector3 m_acceleration = cyclone::Vector3{ 0, -9.8f, 0 };
		real m_damping = 0.995;

		Stick* m_sticks[2] = { nullptr }; // one horizontal and one vertical stick referenced

		bool m_isAnchor = false;
	};
}