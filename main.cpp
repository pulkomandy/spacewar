/*
 * main.cpp
 * Copyright (C) 2018 Adrien Destugues <pulkomandy@pulkomandy.tk>
 *
 * Distributed under terms of the MIT license.
 */

#include "spacewar.h"

#include <Application.h>
#include <MessageRunner.h>
#include <View.h>
#include <Window.h>

#include <stdio.h>

int keys[2][4];

BView* view;

class SpacewarApp: public BApplication {
	public:
	SpacewarApp()
		: BApplication("application/x-vnd.PulkoMandy-SpaceWar")
		, callback(NULL)
	{
	}

		void SetPulseCallback(void(callback)())
		{
			this->callback = callback;
		}

	private:
	void Pulse() override
	{
		if (callback)
			callback();
	}

	void ReadyToRun() override
	{
		Start();
	}

	void (*callback)();
};

class SpaceView: public BView {
	public:
		SpaceView()
			: BView(BRect(0, 0, 511, 511), "spacewar", B_FOLLOW_NONE,
				B_SUBPIXEL_PRECISE)
		{
			SetLowColor(make_color(0, 0, 0, 100));
			SetViewColor(make_color(0, 0, 0, 255));
			SetDrawingMode(B_OP_ALPHA);
			SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_OVERLAY);
			SetScale(0.5);
		}

		void Key(char key, bool pressed)
		{
			switch(key) {
				case 'q':
					keys[0][0] = pressed;
					break;
				case 'd':
					keys[0][1] = pressed;
					break;
				case 'z':
					keys[0][2] = pressed;
					break;
				case 's':
					keys[0][3] = pressed;
					break;

				case 'k':
					keys[1][0] = pressed;
					break;
				case 'm':
					keys[1][1] = pressed;
					break;
				case 'o':
					keys[1][2] = pressed;
					break;
				case 'l':
					keys[1][3] = pressed;
					break;
			}
		}

		void KeyDown(const char* bytes, int32 numBytes) override
		{
			Key(bytes[0], true);
		}

		void KeyUp(const char* bytes, int32 numBytes) override
		{
			Key(bytes[0], false);
		}

};

SpacewarApp app;

void _CRT::update()
{
	if (view->LockLooper()) {
		view->FillRect(BRect(0, 0, 1023, 1023), B_SOLID_LOW);
		view->UnlockLooper();
	}
}

void _CRT::plot(double x, double y, int brightness)
{
	if (view->LockLooper()) {
		brightness = brightness * 64 + 63;
		view->SetHighColor(make_color(255,255, 255, brightness));
#if 0
		rgb_color color;
		switch (brightness) {
			case 0: color = make_color(  0, 0,   255, 255); break;
			case 1: color = make_color(  0, 255, 0,   255); break;
			case 2: color = make_color(  0, 255, 255, 255); break;
			case 3: color = make_color(255, 255, 255, 255); break;
		}
		view->SetHighColor(color);
#endif
#if 0
		view->SetHighColor(make_color(255, 255, 255, 255));
		view->SetPenSize(brightness + 0.5);
#endif

		view->StrokeLine(BPoint(x, y), BPoint(x, y));
		view->UnlockLooper();
	}
}

void _UI::showScores(int a, int b)
{
	printf("Scores %d %d\n", a, b);
}

void _UI::halted()
{
	printf("Halted!\n");
}

void _UI::readGamepads()
{
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 4; j++)
	{
		static int lut[] = {LEFT, RIGHT, THRUST, FIRE};
		SetControls(i, lut[j], keys[i][j]);
	}
}

void clearInterval(int)
{
	app.SetPulseCallback(NULL);
}

int setInterval(void(callback)(), double interval)
{
	static BMessageRunner* runner;

	app.SetPulseCallback(callback);

	if (runner == NULL) {
		BMessage pulse(B_PULSE);
		runner = new BMessageRunner(be_app_messenger, &pulse, true);
	}
	runner->SetInterval(interval * 1000);
	return 0;
}

int main(void) {
	view = new SpaceView();

	BWindow* window = new BWindow(BRect(30, 30, 541, 541), "Spacewar!",
		B_TITLED_WINDOW, B_QUIT_ON_WINDOW_CLOSE | B_NOT_RESIZABLE, 0);
	window->AddChild(view);
	window->CenterOnScreen();
	view->MakeFocus();
	window->Show();

	app.Run();
}
