#ifndef PLANETARIUM_H
#define PLANETARIUM_H

#include <string>

class Planetarium {
	public:
		Planetarium();

		void reset();
		void update();

	private:
		void setOption(std::string key, int value);
};

void plot(double x, double y, int b);


#endif /* !PLANETARIUM_H */
