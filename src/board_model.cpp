#include "board_model.hpp"

namespace FrogToad {
    void BoardModel::reset() {
        board = StartingBoard;
    }

    bool BoardModel::isSolved() const {
        return board == GoalBoard;
    }

    BoardModel::GameState BoardModel::state() const {
        if (isSolved()) return GameState::Solved;

        // TODO (student): Use canMove() to detect when no legal moves remain.
        for (int i{0}; i < BoardSize; ++i) {
            if (canMove(i)) {
                return GameState::Playing;
            } 
        }
        // Check for a solution first: the solved board also has no legal moves.
        return GameState::Lost;
    }

    bool BoardModel::canMove(int index) const {
        return moveDestination(index) != -1;
    }

    BoardModel::Cell BoardModel::cellAt(int index) const {
        return isIndexValid(index) ? board[index] : Cell::Empty;
    }

    bool BoardModel::tryMove(int index) {
        const int destination{ moveDestination(index) };
        if (destination == -1) return false;

        board[destination] = board[index];
        board[index] = Cell::Empty;
        return true;
    }

    constexpr bool BoardModel::isIndexValid(int index) {
        return index >= 0 && index < BoardSize;
    }

    constexpr int BoardModel::moveDirection(Cell cell) {
        return (cell == Cell::Frog) ? +1 : -1;
    }

    bool BoardModel::isCellEmpty(int index) const {
        return board[index] == Cell::Empty;
    }

    int BoardModel::moveDestination(int index) const {
        if (!isIndexValid(index) || isCellEmpty(index)) return -1;

        const int direction{ moveDirection(board[index]) };
        const int adjacentIndex{ index + direction };

        if (!isIndexValid(adjacentIndex)) return -1;
        if (isCellEmpty(adjacentIndex)) {
            // Slide into the adjacent empty cell.
            return adjacentIndex;
        }

        // Slide is not possible, so check for a hop. 
        // The adjacent cell must contain the opposite type of piece.
        if (board[adjacentIndex] == board[index]) return -1;

        const int jumpIndex{ adjacentIndex + direction };
        if (isIndexValid(jumpIndex) && isCellEmpty(jumpIndex)) {
            // Hop over the adjacent piece into the empty cell.
            return jumpIndex;
        }

        // No legal move is possible.
        return -1;
    }

} // namespace FrogToad
