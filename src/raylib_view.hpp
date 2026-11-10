#pragma once
#include "interfaces.hpp"
#include "raylib.h"

namespace FrogToad {
    /**
     * @brief Presents the board with Raylib (student exercise).
     * Construct after InitWindow() and destroy before CloseWindow(); load textures
     * once in the constructor and unload them in the destructor.
     */
    class RaylibView : public IView {
    public:
        /** @brief Render the current model using already loaded resources. */
        void draw(const BoardModel& model) override;
        
        /** @brief Draws a GREEN frog at the given position using Raylib Circles. */
        static void DrawFrog(int posX, int posY, float size);
        /** @brief Draws a BLUE toad at the given position using Raylib Circles. */
        static void DrawToad(int posX, int posY, float size);
        /** @brief Draws a Banner with a Title and Instructions to communicate game state to the player.*/
        static void DrawBanner(const char* Title, const char* Instructions, Color TitleColor, Color InstColor);
        
        /** @brief Window width in pixels, available before view construction. */
        static int windowW();
        /** @brief Window height in pixels, available before view construction. */
        static int windowH();
    };
}
