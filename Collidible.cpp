#include "Collidible.h"

#include <math.h>
#include <stdlib.h>

static constexpr int torpedoSpaceWarpage = 9;  // the  sar 9s  (right shift)
double Random()
{
	return (double)random() / RAND_MAX;
}

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

void CollidibleObject::explosionHandler() {  /* (label mex) */
	double x, y;
	int mxc, f;
	this->y += dy / 8;
	this->x += dx / 8;
	toroidalize();
	// particles
	mxc = size >> 3;
	do {
		/*
			algorithm:
			1) set up number of right shifts: (mxc > 96)? 1:3
			2) set up number of left shifts: random number int 0..9
			(shifts apply to a combined 36-bit register, 18 bits x and y each,
               sign preserved in x. [x = AC, y = IO])
              3) set x and y to signed 9-bit random numbers
              4) apply right shifts (combined registers)
              5) apply left shifts (combined registers)
              6) add to position and display it
              (only bits 17..9 (hsb-first) are significant for co-ordinates)

              using floats, we apply mult/div instead of shifts:
              mult/div factors are 1 << n.
              any sign flips in y are ignored (just a random number).
            */
		f = (1 << (int)(floor(Random() * 9))) / ((mxc > 96)? 2:8);
		x = (Random() - 0.5) * 2 * f;
		y = (Random() - 0.5) * 2 * f;
		plot(this->x + x, this->y + y, 3);
	} while (--mxc > 0);
	if (--counter <= 0) handler = NULL;
}

void CollidibleObject::torpedoHandler() {  /* (label trc) */
	if (counter < 0) {
		// time fuse
		counter = 2;
		handler = &CollidibleObject::explosionHandler;
		collidible = false;
	}
	else {  /* (label t1c) */
		dy += x / (512 * (1 << torpedoSpaceWarpage));
		y += dy / 8;
		dx += y / (512 * (1 << torpedoSpaceWarpage));
		x += dx / 8;
		toroidalize();
		plot(x, y, 1);
	}
}

