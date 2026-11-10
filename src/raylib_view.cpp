#include "raylib_view.hpp"

#include <string>

#include "board_layout.hpp"
#include "raylib.h"

namespace FrogToad {
	void RaylibView::draw(const BoardModel& model) {
		// 0 ----- BACKGROUND COLOR (Determined by game state) -----
		{
			Color BGColor = RAYWHITE;
			if (model.state() == BoardModel::GameState::Lost){
				BGColor = RED;
			}
			else if (model.state() == BoardModel::GameState::Solved) {
				BGColor = GREEN;
			}
			ClearBackground(BGColor);
		}
		

		// 1 ----- POSITIONS AND NUMBERS -----
		// MARGINS & BORDERS
		constexpr int margins = BoardLayout::xMargins;
		constexpr int borderWidth = BoardLayout::cellBorderWidth;
		// SIZES
		const int cellSize = BoardLayout::cellSize();
		const int cellInterior = BoardLayout::cellInterior();
		// Y Position of cells
		const int posY = BoardLayout::yAnchor;
		
		
		// 2 ----- GAME TITLE -----
		Color dropShadow{0, 0, 0, 128};
		{
			const int titleCenterX = MeasureText("Frogs    &   Toads", 50)/2;
			DrawText("Frogs    &   Toads", RaylibView::windowW()/2-titleCenterX+5, 15, 50, dropShadow); // Drop Shadow
			DrawText("Frogs    &   Toads", RaylibView::windowW()/2-titleCenterX, 10, 50, BLACK);			 // Title Text
		}
		
		
		
		// 3 ----- CELLS -----
		for (int i = 0; i < model.BoardSize; i++)
		{
			// Get draw pos X for current cell.
			const int cellPosX = (i * cellSize) + margins;
			
			// DRAW CELLS
			{
				DrawRectangle(cellPosX, posY, cellSize, cellSize, BLACK);
				Color cellFill = RAYWHITE;
				if (i == BoardLayout::cellAt(GetMousePosition())) { cellFill = GRAY; }
				DrawRectangle(borderWidth+cellPosX, posY+borderWidth, cellInterior, cellInterior, cellFill);
			}
			
			// CELL CONTENTS (Frogs, then Toads)
			{
				if (model.cellAt(i) == BoardModel::Cell::Frog) {
					RaylibView::DrawFrog(cellPosX+(cellSize/2), posY+cellSize/2, (cellSize/2)-(borderWidth*2));
				}
				else if (model.cellAt(i) == BoardModel::Cell::Toad) {
					RaylibView::DrawToad(cellPosX+(cellSize/2), posY+cellSize/2, (cellSize/2)-(borderWidth*2));
				}
			}
			
			// DRAW CELL LABELS
			{
				Color labelColor = GRAY;
				const std::string index = std::to_string(i+1); // Create a string we can convert to a c_str for various raylib funcs.
				const int labelCenter = MeasureText(index.c_str(), 30)/2;
				// If the current cell can move, make the label black and add a drop shadow
				if (model.canMove(i)){
					labelColor = BLACK;
					DrawText(index.c_str(), cellPosX+(cellSize/2)-labelCenter+3, posY+cellSize+borderWidth+3, 30, dropShadow);
				}
				DrawText(index.c_str(), cellPosX+(cellSize/2)-labelCenter, posY+cellSize+borderWidth, 30, labelColor);
			}
			
		}
		
		// 4 ----- GAME STATE BANNER w/ INSTRUCTIONS -----
		// SHOW CONTROLS WHILE PLAYING
		if (model.state() == BoardModel::GameState::Playing) {
			RaylibView::DrawBanner("CONTROLS", "1 - 7 = Move | R = Restart", RAYWHITE, RAYWHITE);
		}
		// LOST = Tell them the bad news & how to restart
		else if (model.state() == BoardModel::GameState::Lost) {
			RaylibView::DrawBanner("YOU HAVE LOST", "R = Restart", RED, RAYWHITE);
		}
		// WIN = Tell them the good news & how to play again
		else if (model.state() == BoardModel::GameState::Solved) {
			RaylibView::DrawBanner("YOU HAVE WON!!", "R = Play Again", GREEN, RAYWHITE);
		}
	}
	
	
	// REUSABLE DRAW FUNCTIONS
	void RaylibView::DrawFrog(int posX, int posY, float size) {
		//BODY
		DrawCircle(posX, posY, size, GREEN);
		// EYEBALLS
		DrawCircle(posX+10, posY-15, 10, WHITE);
		DrawCircle(posX+10, posY+15, 10, WHITE);
		// PUPILS
		DrawCircle(posX+15, posY-15, 5, BLACK);
		DrawCircle(posX+15, posY+15, 5, BLACK);
	}
	void RaylibView::DrawToad(int posX, int posY, float size) {
		//BODY
		DrawCircle(posX, posY, size, BLUE);
		// EYEBALLS
		DrawCircle(posX-10, posY-15, 10, WHITE);
		DrawCircle(posX-10, posY+15, 10, WHITE);
		// PUPILS
		DrawCircle(posX-15, posY-15, 5, BLACK);
		DrawCircle(posX-15, posY+15, 5, BLACK);
	}
	void RaylibView::DrawBanner(const char* Title, const char* Instructions, Color TitleColor, Color InstColor) {
		// BANNER
		DrawRectangle(0, 70, RaylibView::windowW(), 100, GRAY);
		Color dropShadow{0, 0, 0, 128};
		// Text Measurements (For Centering)
		const int stateCenterX = MeasureText(Title, 40)/2;
		const int controlCenterX = MeasureText(Instructions, 20)/2;
		// TITLE TEXT
		DrawText(Title, RaylibView::windowW()/2-stateCenterX+4, 84, 40, dropShadow);
		DrawText(Title, RaylibView::windowW()/2-stateCenterX, 80, 40, TitleColor);
		// INSTRUCTIONS
		DrawText(Instructions, RaylibView::windowW()/2-controlCenterX+2, 137, 20, dropShadow);
		DrawText(Instructions, RaylibView::windowW()/2-controlCenterX, 135, 20, InstColor);
	}
	
	// WINDOW DIMENSIONS
	int RaylibView::windowW() { return 600; }
	int RaylibView::windowH() { return 300; }
}
