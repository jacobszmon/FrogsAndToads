#include "board_model.hpp"
#include "ansi_view.hpp"
#include "console_controller.hpp"
#include "raylib_controller.hpp"
#include "raylib_view.hpp"
#include "raylib.h"

namespace FrogToad {
    /** @brief Run the console game with the ANSI View, drawing before each blocking input call. */
    int runConsole() {
        BoardModel model;
        AnsiView view;
        ConsoleController controller;

        while (true) {
            view.draw(model);
            controller.handleInput(model);
        }

        return 0;
    }

    /** @brief Run the graphical game, handling input and drawing each frame. */
    int runRaylib() {
        BoardModel model;
        RaylibController controller;

        InitWindow(RaylibView::windowW(), RaylibView::windowH(), "Toads & Frogs - Raylib");
        SetTargetFPS(60);

        {   // Open a scope to control the lifetime of our RaylibView. 
            // The View's textures must live entirely within the Window's lifetime.
            RaylibView view;
            //AnsiView view;

            while (!WindowShouldClose()) {
                controller.handleInput(model);

                BeginDrawing();
                view.draw(model);
                EndDrawing();
            }
        } // Destroy the view (and unload its textures) before closing the window.
        // Clean and ready to close.

        CloseWindow();
        return 0;
    }
}

int main() {
    return FrogToad::runRaylib(); // Change to runRaylib() for Parts 1–3.
}
