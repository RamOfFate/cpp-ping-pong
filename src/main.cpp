#include "raylib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>

constexpr float SCREEN_WIDTH = 800.0f;
constexpr float SCREEN_HEIGHT = 450.0f;

constexpr float PADDING = 20.0f;

constexpr int FONT_SIZE = 50;

constexpr float DEFAULT_BALL_SPEED = 400.0f;

constexpr float BALL_ACCELERATION = -1.1f;

struct Paddle {
    Vector2 size = {15.0f, 150.0f};
    Vector2 position;
    float speed = DEFAULT_BALL_SPEED;

    Paddle(bool isLeftPaddle = true) :position
        {
            isLeftPaddle ? PADDING: SCREEN_WIDTH - PADDING - size.x, 
            (SCREEN_HEIGHT / 2.0f) - (size.y / 2.0f)
        }{}

    void Draw() const{
        DrawRectangleV(position, size, WHITE);
    }

    void Move(float dir, float dt){
        position.y += dir * speed * dt;
        position.y = std::clamp(position.y, PADDING, SCREEN_HEIGHT - size.y - PADDING);
    }

    Rectangle getRectangle() const{
        return {position.x, position.y, size.x, size.y};
    }

};

struct Ball {
    float radius = 15;
    Vector2 position;
    Vector2 speed = {0.0f, 0.0f};

    Ball() : position{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}{}
    
    void Draw() const{
        DrawCircleV(position, radius, WHITE);
    }

    void Update(float dt){
        position.x += speed.x * dt;
        position.y += speed.y * dt;

        if (position.y + radius  >= SCREEN_HEIGHT || position.y - radius <= 0.0f) speed.y *= -1.0f;

        position.y = std::clamp(position.y, radius, SCREEN_HEIGHT  - radius);
    }

    void Reset(){
        speed = {0, 0};
        position = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    }

    void Launch(){
        float direction_x = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
        float direction_y = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
        if(speed.x == 0) speed = {DEFAULT_BALL_SPEED * direction_x, DEFAULT_BALL_SPEED * direction_y};
    }

};


int main(){
    SetRandomSeed(time(0));
    InitWindow(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT), "My first game of ping pong :>");
    SetTargetFPS(60);

    Paddle paddle_a, paddle_b(false);

    Ball ball;

    int score_a = 0, score_b = 0;

    while(!WindowShouldClose()){
        float delta_time = GetFrameTime();
        
        float direction_a = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));
        float direction_b = static_cast<float>(IsKeyDown(KEY_DOWN)) - static_cast<float>(IsKeyDown(KEY_UP));
        
        if(IsKeyPressed(KEY_SPACE)) ball.Launch();
        
        paddle_a.Move(direction_a, delta_time);
        paddle_b.Move(direction_b, delta_time);
        
        ball.Update(delta_time);

        if(CheckCollisionCircleRec(ball.position, ball.radius, paddle_a.getRectangle())){
            if (ball.speed.x < 0) ball.speed.x *= BALL_ACCELERATION; 
        }
        
        if(CheckCollisionCircleRec(ball.position, ball.radius, paddle_b.getRectangle())){
            if (ball.speed.x > 0) ball.speed.x *= BALL_ACCELERATION; 
        }
        
        if(ball.position.x > SCREEN_WIDTH){
            score_a++;
            ball.Reset();
        } 
        if(ball.position.x < 0.0f){
            score_b++;
            ball.Reset();
        } 
        


        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("%d", score_a), static_cast<int>(SCREEN_WIDTH) / 2 - MeasureText(TextFormat("%d", score_a), FONT_SIZE) - PADDING, PADDING, FONT_SIZE, WHITE);
        DrawText(TextFormat("%d", score_b), static_cast<int>(SCREEN_WIDTH) / 2 + PADDING, PADDING, FONT_SIZE, WHITE);
        paddle_a.Draw();
        paddle_b.Draw();
        ball.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}