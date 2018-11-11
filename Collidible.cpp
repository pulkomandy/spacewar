#include "Collidible.h"

#include <stdlib.h>

CollidibleObject::CollidibleObject()
{
	handler = NULL;       //              (symbol: mtb, pointer: ml1)
	collidible = false;   //            (sign-bit in handler address)
	x = 0;                // pos x                         (nx1, mx1)
	y = 0;                // pos y                         (ny1, my1)
	dx = 0;               // delta x                       (ndx, mdx)
	dy = 0;               // delta y                       (ndy, mdy)
	counter = 0;          // time of torpedo or explosion  (na1, ma1)
	size = 0;             // used for explosions           (nb1, mb1)
}

void CollidibleObject::toroidalize()
{
	// util for toroidal space (in original maintained by word length)
	if (x <= -COORS_MAX) {
		x += SCREENWIDTH;
	}
	else if (x > COORS_MAX) {
		x -= SCREENWIDTH;
	}
	if (y <= -COORS_MAX) {
		y += SCREENWIDTH;
	}
	else if (y > COORS_MAX) {
		y -= SCREENWIDTH;
	}
}

