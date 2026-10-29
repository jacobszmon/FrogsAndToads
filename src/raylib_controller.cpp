#include "raylib_controller.hpp"
#include <iostream>
#include "raylib.h"

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {
		// TODO (student): Implement non-blocking keyboard input.
		
		
		// Loop through our number key indexes (49 -> 59) and try to move the index that matches the first input.
		for (int i{0}; i < 9; i++)
		{
			if (IsKeyPressed(49+i))
			{
				model.tryMove(i);
				return;
			}
		}
		// Otherwise, check the R key and reset if it's pressed.
		if (IsKeyPressed(KEY_R))
		{
			model.reset();
		}
	}
}
