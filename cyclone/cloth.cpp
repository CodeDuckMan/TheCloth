#include "cloth.h"


cyclone::Cloth::Cloth(real width, real height, real spacing, Vector3 startingPos, real clothMass)
{
	for (int y = 0; y <= height; y++)
	{
		for (int x = 0; x <= width; x++)
		{
			VerletParticle* p = new VerletParticle(clothMass, Vector3{ startingPos.x + x * spacing, startingPos.y + y * spacing, startingPos.z });

		}
	}
}
