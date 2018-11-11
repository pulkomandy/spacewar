/*
 * main.cpp
 * Copyright (C) 2018 Adrien Destugues <pulkomandy@pulkomandy.tk>
 *
 * Distributed under terms of the MIT license.
 */

#include "spacewar.h"

#include <Application.h>
#include <Joystick.h>
#include <MessageRunner.h>
#include <Screen.h>
#include <View.h>
#include <Window.h>

#include <stdio.h>

static int keys[2][4];
static BView* view;
static Spacewar game;



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
		game.run(NULL);
	}

	void (*callback)();
};

class SpaceView: public BView {
	public:
		SpaceView(BRect bounds)
			: BView(bounds, "spacewar", B_FOLLOW_NONE,
				B_SUBPIXEL_PRECISE)
		{
			SetLowColor(make_color(0, 0, 0, 64));
			SetViewColor(make_color(0, 0, 0, 255));
			SetDrawingMode(B_OP_ALPHA);
			SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_OVERLAY);
			SetScale((Bounds().Width() + 1) / 1024);
		}

		void Key(char, bool pressed)
		{
			BMessage* message = Looper()->CurrentMessage();
			int32 key = message->FindInt32("key");
			switch(key) {
				case 0x3C:
					keys[0][0] = pressed;
					break;
				case 0x3E:
					keys[0][1] = pressed;
					break;
				case 0x28:
					keys[0][2] = pressed;
					break;
				case 0x3D:
					keys[0][3] = pressed;
					break;

				case 0x44:
				case 0x61:
				case 0x48:
					keys[1][0] = pressed;
					break;
				case 0x46:
				case 0x63:
				case 0x4A:
					keys[1][1] = pressed;
					break;
				case 0x30:
				case 0x57:
				case 0x38:
					keys[1][2] = pressed;
					break;
				case 0x45:
				case 0x62:
				case 0x49:
					keys[1][3] = pressed;
					break;

				case 0x01:
					Window()->PostMessage(B_QUIT_REQUESTED);
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
#if 0
		brightness = brightness * 64 + 63;
		view->SetHighColor(make_color(255,255, 255, brightness));
#endif
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
		view->SetHighColor(make_color(255, 255, 255, 255));
		view->SetPenSize(brightness + 1);

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

static void Gamepad(BJoystick& gamepad, int player)
{
	if (gamepad.CountDevices() <= player)
		return;

	if (gamepad.Update() != B_OK) {
		char name[B_OS_NAME_LENGTH];
		gamepad.RescanDevices();
		gamepad.GetDeviceName(player, name);
		gamepad.Open(name, false);
	} else {
		keys[player][2] = !gamepad.button1;
		keys[player][3] = !gamepad.button2;

		keys[player][0] = (gamepad.horizontal < -5);
		keys[player][1] = (gamepad.horizontal > 5);

		// hyperspace
		if (gamepad.vertical > 5 || gamepad.vertical < -5)
			keys[player][0] = keys[player][1] = true;
	}

}

void _UI::readGamepads()
{
	static BJoystick gamepad0;
	static BJoystick gamepad1;

	Gamepad(gamepad0, 0);
	Gamepad(gamepad1, 1);

	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 4; j++)
	{
		static int lut[] = {LEFT, RIGHT, THRUST, FIRE};
		game.setControls(i, lut[j], keys[i][j]);
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
	BScreen screen;
	BRect frame = screen.Frame();
	float size = fmin(frame.Height(), frame.Width());

	view = new SpaceView(BRect(0, 0, size, size));

	BWindow* window = new BWindow(view->Bounds(), "Spacewar!",
		B_TITLED_WINDOW,
		B_QUIT_ON_WINDOW_CLOSE | B_NOT_RESIZABLE | B_NOT_ZOOMABLE, 0);
	window->AddChild(view);
	window->SetLook(window_look(25));
	window->CenterOnScreen();
	view->MakeFocus();
	window->Show();

	app.Run();
}
