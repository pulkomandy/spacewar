#ifndef COLLIDIBLE_H
#define COLLIDIBLE_H


class CollidibleObject {
	public:
		CollidibleObject();
		void toroidalize();

		void explosionHandler();
		void torpedoHandler();

		bool collidible;
		double x,y;
		double dx,dy;
		typedef void(CollidibleObject::*Handler)(void);
		Handler handler;
		int size;
		int counter;
};

// display constants (for readability)
static const int SCREENWIDTH = 1024,
    COORS_MAX = SCREENWIDTH/2;

double Random();
void plot(double x, double y, int b);

#endif /* !COLLIDIBLE_H */
