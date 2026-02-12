#include "raylib.h"

constexpr float SCREEN_WIDTH = 800.0f;
constexpr float SCREEN_HEIGHT = 450.0f;

constexpr float PADDING = 20.0f;

struct Paddle {
    Vector2 size = {20.0f, 150.0f};
    Vector2 position;

    Paddle(bool isLeftPaddle = true){
        float center_y = (SCREEN_HEIGHT / 2.0f) - (size.y / 2.0f);
        isLeftPaddle ? position = {PADDING,   center_y} : position = {SCREEN_WIDTH - PADDING - size.x, center_y};
    }

    void Draw() const{
        DrawRectangleV(position, size, WHITE);
    }
};

struct Ball {
    float radius = 15;
    Vector2 position;

    Ball(){
        position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    }
    
    void Draw() const{
        DrawCircleV(position, radius, WHITE);
    }
};


int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first game of ping pong :>");
    SetTargetFPS(60);

    Paddle paddle_a;
    Paddle paddle_b(false);

    Ball ball;

    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(BLACK);


        paddle_a.Draw();
        paddle_b.Draw();

        ball.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}