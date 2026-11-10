#include "board_layout.hpp"
#include "board_model.hpp"
#include <cassert> // assert() in cellRect()

namespace FrogToad {
    Rectangle BoardLayout::board() {
        // A rectangle covering all cells.
        Rectangle rect{
            (float)(BoardLayout::xMargins), 
            (float)(BoardLayout::yAnchor), 
            (float)(BoardLayout::cellSize()*BoardModel::BoardSize), 
            (float)BoardLayout::cellSize()
        };
        return rect; 
    }

    Rectangle BoardLayout::cellRect(int index) {
        // Assert that the index is valid:
        assert(index >= 0 && index < BoardModel::BoardSize);
        // Create a rectangle where the given index would place a cell.
        Rectangle rect{
            (float)(BoardLayout::xMargins + BoardLayout::cellBorderWidth + (BoardLayout::cellSize() * index)), 
            (float)(BoardLayout::yAnchor + BoardLayout::cellBorderWidth), 
            (float)(BoardLayout::cellInterior()), 
            (float)(BoardLayout::cellInterior())
        };
        return rect; 
    }

    int BoardLayout::cellAt(Vector2 point) {
        // Skip per-cell collision checks if the point is not on the board.
        if (CheckCollisionPointRec(point, BoardLayout::board())) {
            // Loop through valid indices, and return the current index if you detect a collision with the current cell.
            for (int i {0}; i < BoardModel::BoardSize; i++) {
                if ( CheckCollisionPointRec(point, BoardLayout::cellRect(i)) ) {
                   return i;
                }
            } 
        }
        // Return -1 if you cannot detect a collision with any existing cells.
        return -1; 
    }
    
    int BoardLayout::cellSize() { return ( BoardLayout::windowW() - (2 * BoardLayout::xMargins) ) / BoardModel::BoardSize; }
    int BoardLayout::cellInterior() { return cellSize() - (BoardLayout::cellBorderWidth * 2); }
    
    int BoardLayout::windowW() { return 600; }
    int BoardLayout::windowH() { return 300; }
}
