/*
 * spacewar.h
 * Copyright (C) 2018 Adrien Destugues <pulkomandy@pulkomandy.tk>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SPACEWAR_H
#define SPACEWAR_H

// dictionary for controls (exported as property)
enum Controls {
	SPACESHIP1 =  0,
	SPACESHIP2 =  1,
	LEFT =        8,
	RIGHT =       4,
	THRUST =      2,
	FIRE =        1,
	HYPERSPACE = 12,  // left + right
	RESET =      15,  // use to clear all
	ALL =        15,
};

class _CRT {
	public:
	void update();
	void plot(double x, double y, int brightness);
};

class _UI {
	public:
	void showScores(int, int);
	void halted();
	void readGamepads();
};

void clearInterval(int timer);
int setInterval(void(callback)(), double delay);

void Start();
void SetControls(int ship, int key, int value);
#endif /* !SPACEWAR_H */
