#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Collidible.h"

// "interesting and often changed constants"
// (original values in octal, not allowed in JS strict-mode, see comments)

                                                     // sym   value  unit/comment
                                                     // -------------------------------
static constexpr int
	torpedoSupply =                         32,  // tno     040  (number of)
	torpedoVelocity =                        4,  // tvl  sar 4s  (right shift)
 	torpedoReloadTime =                     16,  // rlt     020  (frames)
	torpedoLife =                           96,  // tlf    0140  (frames)
	fuelSupply =                          8192,  // foo  020000  (per exhaust blip)
	spaceshipAcceleration =                  4,  // sac  sar 4s  (right shift)
	starCaptureRadius =                      1,  // str      01  (greater zero)
	collisionRadius =                       48,  // me1   06000  (screen coors)
	collisionRadius2 =                      24,  // me2   03000  (above/2)
	hyperspaceShots =                        8,  // mhs     010  (number of)
	hyperspaceTimeBeforeBreakout =          32,  // hd1     040  (frames)
	hyperspaceTimeInBreakout =              64,  // hd2    0100  (frames)
	hyperspaceRechargeTime =               128,  // hd3    0200  (frames)
	hyperspaceDisplacement =                 9,  // hr1  scl 9s  (left shift)
	hyperspaceInducedVelocity =              4,  // hr2  scl 4s  (left shift)
	hyperspcaceUncertancy =              16384;  // hur  040000  (threshold bonus)

struct Point {double x; double y;};
typedef Point (*Outline)(double, double, double, double, double, double, double, double, double, double, int);
class Spaceship: public CollidibleObject {
	public:
		Spaceship();
		Spaceship(double x, double y, double theta, Outline outline, int color);

		void spaceshipHandler();
		void hyperspaceHandler();
		void hyperspaceHandler2();

        double theta;
		const Outline outline;
        int torpedoes;
        int fuel;
		void(CollidibleObject::*hyp1)(void);
        int hyp2;
        int hyp3;
        int hyp4;
        int ctrl;
        double angularMomentum;
        int lastCtrl;
		int color;
};


#endif /* !SPACESHIP_H */
