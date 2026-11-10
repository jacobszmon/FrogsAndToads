#pragma once
#include <optional> // std::optional &  std::nullopt in cellAt()
#include "raylib.h"

namespace FrogToad {
    /** @brief Pixel geometry of the game board. Used by both RaylibView and RaylibController. 
      *
      * All methods are static and so are called like this: Rectangle cell{ FrogToad::BoardLayout::cellRect(3) };
      * Some methods will need to query the model. See cellRect for a use of BoardModel::BoardSize
      */
    struct BoardLayout {
        // Positioning
        static constexpr int xMargins = 40; // The margins on either end of the board.
        static constexpr int yAnchor = 185; // The draw y position of the board.
        // Cell Dimensions
        static constexpr int cellBorderWidth = 4; // The width of the borders of each cell.
        
        /** @brief Returns the size of a given cell where: 
         * - there are [BoardModel::BoardSize] cells
         * - All cells fit on screen with an x-clearance of [xMargins] on either side
        */
        static int cellSize();
        /** @brief Returns the dimensions of a cell's interior square.*/
        static int cellInterior();
        

        /** @brief Raylib screen rectangle that perfectly wraps all N cells. */
        static Rectangle board();

        /** @brief Screen rectangle of a zero-based cell. Assertion: The index must be valid. */
        static Rectangle cellRect(int index);

        /** @brief Zero-based cell under a point, or -1 if the point is off the board.*/
        static int cellAt(Vector2 point);
        
        static int windowW();
        static int windowH();
    };
}

