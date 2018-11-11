#ifndef COLLIDIBLE_H
#define COLLIDIBLE_H


class CollidibleObject {
	public:
		CollidibleObject();
		void toroidalize();

		bool collidible;
		double x,y;
		double dx,dy;
		void(*handler)(CollidibleObject*);
		int size;
		int counter;
};

// display constants (for readability)
static const int SCREENWIDTH = 1024,
    COORS_MAX = SCREENWIDTH/2;

#endif /* !COLLIDIBLE_H */
