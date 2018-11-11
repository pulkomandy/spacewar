#ifndef COLLIDIBLE_H
#define COLLIDIBLE_H


class CollidibleObject {
	public:
		CollidibleObject();

		bool collidible;
		double x,y;
		double dx,dy;
		void(*handler)(CollidibleObject*);
		int size;
		int counter;
};

#endif /* !COLLIDIBLE_H */
