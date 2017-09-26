#include "Screen.h"
#include "Renderable.h"
#include "Input.h"

#include "FrameCounter.h"

#include "Player.h"

int main()
{
	DWORD burn;
	Screen screen;
	Input input;
	bool running = true;

	Player player({ 0, 0 }, 1);

	input.AddHandler(VK_LEFT, [&](bool keydown)->void {keydown ? player.SetMovement(Player::MOVE_LEFT) : player.ClearMovement(Player::MOVE_LEFT); });
	input.AddHandler(VK_RIGHT, [&](bool keydown)->void {keydown ? player.SetMovement(Player::MOVE_RIGHT) : player.ClearMovement(Player::MOVE_RIGHT); });
	input.AddHandler(VK_UP, [&](bool keydown)->void {keydown ? player.SetMovement(Player::MOVE_UP) : player.ClearMovement(Player::MOVE_UP); });
	input.AddHandler(VK_DOWN, [&](bool keydown)->void {keydown ? player.SetMovement(Player::MOVE_DOWN) : player.ClearMovement(Player::MOVE_DOWN); });
	input.AddHandler(VK_ESCAPE, [&](bool keydown)->void {running = false; });

	input.Start();
	while (running)
	{
		player.Update();
		player.Render(screen);
		screen.swap();
		Sleep(10);
	}
	input.Stop();

	return 0;
}