#include "raylib_controller.hpp"
#include <iostream>

#include "board_layout.hpp"
#include "raylib.h"

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {
		// TODO (student): Implement non-blocking keyboard input.
		
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			model.tryMove( BoardLayout::cellAt(GetMousePosition()) );
		}
		
		// Loop through our number key indexes (49 -> 59) and try to move the index that matches the first input.
		// EXPLANATION: keys 0-9 occupy the above indexes. But, we only need enough for the amount of cells, so we'll cap it at model.BoardSize
		for (int i{0}; i < model.BoardSize; i++) {
			if (IsKeyPressed(49+i)) {
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
