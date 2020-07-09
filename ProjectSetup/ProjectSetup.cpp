#include "core.h"
#include "Math\Math.h"
#include "Math\Transform.h"
#include "Math\Color.h"
#include "Math\Vector2.h"
#include "Math\Random.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>
float speed = 300.0;

std::vector<nc::Vector2> points = { {0.0f, 1.0f}, {-0.25f, 0.3f}, {-0.85f, 0.3f}, {-0.45f, -0.1f}, {-0.55f, -0.8f}, {-0.4f, 0.0f}, {0.55f, -0.8f}, {0.45f, -0.1f}, {0.85f, 0.3f}, {0.25f, 0.3f}, {0.0f, 1.0f} };

nc::Color color(0, 1, 1);
//nc::Shape ship{ points, color };

nc::Transform transform{ {400, 300}, 20, 0};

nc::Shape ship;

float t{ 0 };

float frametime;
float roundTime{0};
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) {//delta time (60fps) (1/60 = 0.016
    //dt = current frame time - previous frame time
    DWORD time = GetTickCount();
    deltaTime = time - prevTime;
    prevTime = time;

    t += dt;

    frametime = dt;
    roundTime += dt;

    if (roundTime >= 5.0f) gameOver = true;

    if (gameOver) dt = 0;

    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    int x, y;
    Core::Input::GetMousePos(x, y);

    //nc::Vector2 target = nc::Vector2{ x, y };
    //nc::Vector2 direction = target - position;//(head <- tail)

    nc::Vector2 force{ 0, 0 };
    if (Core::Input::IsPressed('W')) {
        force = nc::Vector2::forward * speed * dt; 
    }
    nc::Vector2 direction = force;
    direction = nc::Vector2::Rotate(direction, transform.angle);
    transform.position += direction;

    //position += direction.Normalized() * 5.0f;

    if (Core::Input::IsPressed('A')) { transform.angle -= (nc::math::DregreesToRadians(360.0f) * dt); }
    if (Core::Input::IsPressed('D')) { transform.angle += (nc::math::DregreesToRadians(360.0f) * dt); }

    transform.position = nc::math::Clamp(transform.position, { 0, 0 }, { 800, 600 });

    //transform.position.x = nc::math::Clamp(transform.position.x, 0.0f, 800.0f);
    //transform.position.y = nc::math::Clamp(transform.position.y, 0.0f, 600.0f);

    /*if (Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A')) {
        position += nc::Vector2::left * speed * dt;
    }
    if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D')) {
        position += nc::Vector2::right * speed * dt;
    }
    if (Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W')) {
        position += nc::Vector2::up * speed * dt;
    }
    if (Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S')) {
        position += nc::Vector2::down * speed * dt;
    }*/

   /* for (nc::Vector2& point : points) {
        point = nc::Vector2{ nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
    }*/

    return quit;
}

void Draw(Core::Graphics& graphics) {
    graphics.DrawString(10, 10, std::to_string(frametime).c_str());
    graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
    graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

    float v = (std::sin(t) + 1.0) * 0.5f;

    nc::Color c = nc::math::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
    nc::Vector2 p = nc::math::Lerp(nc::Vector2{ 400, 300}, nc::Vector2{ 100, 100}, v);
    graphics.SetColor(c);
    graphics.DrawString(p.x, p.y, "AWhitehouse");


    if (gameOver) graphics.DrawString(400, 300, "Game Over");
    //rgb (8bits/1byte, 8, 8) (0-255, 0-255, 0-255)
    //rgb (float, float, float) (0-1.0, 0-1.0, 0-1.0)

    //graphics.SetColor(color);
    //graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600),
        //static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
    ship.Draw(graphics, transform);
}

int main()
{
    DWORD ticks = GetTickCount();//how many ticks in a second
    std::cout << ticks / 1000 << std::endl;//turns to how many seconds

    ship.Load("ship.txt");
    ship.SetColor(nc::Color{ 1, 1, 1 });

    /*for (size_t i = 0; i < NUM_POINTS; i++) {
        points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
    }*/

    char name[] = "AWhitehouse";
    Core::Init(name, 800, 600, 90);
    Core::RegisterUpdateFn(Update);
    Core::RegisterDrawFn(Draw);

    Core::GameLoop();
    Core::Shutdown();
}