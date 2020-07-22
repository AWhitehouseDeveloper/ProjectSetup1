#include "core.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

nc::Scene scene;

float frametime;
float spawntimer{ 0 };

bool Update(float dt) {//delta time (60fps) (1/60 = 0.016
    //dt = current frame time - previous frame time
    //DWORD time = GetTickCount();

    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    frametime = dt;
    spawntimer += dt;
    if (spawntimer >= 3.0f) {
        spawntimer = 0.0f;

        //add enemy to scene
        nc::Actor* actor = new Enemy;
        actor->Load("enemy.txt");
        dynamic_cast<Enemy*>(actor)->SetTarget(scene.GetActor<Player>());
        actor->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
        dynamic_cast<Enemy*>(actor)->SetThrust(nc::random(50, 100));
        
        scene.AddActor(actor);
    }

    Player* player = scene.GetActor<Player>();

    if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
        int x, y;
        Core::Input::GetMousePos(x, y);
        
        nc::Color colors[] = { nc::Color::yellow, nc::Color::blue, nc::Color::green };
        nc::Color color = colors[rand() % 3];

        g_particleSystem.Create(nc::Vector2{ x, y }, 0, 180, 30, color, 1, 100, 200);

    }

    scene.Update(dt);
    g_particleSystem.Update(dt);

    return quit;
}

void Draw(Core::Graphics& graphics) {
    graphics.DrawString(10, 10, std::to_string(frametime).c_str());
    graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
    
    scene.Draw(graphics);
    g_particleSystem.Draw(graphics);
}

int main()
{
    scene.Startup();
    g_particleSystem.StartUp();

    nc::Actor* player = new Player;
    player->Load("player.txt");
    scene.AddActor(player);

    for (int i = 0; i < 10; i++) {//dynamic_cast allows enemy to see enemy functions when made as an actor
        nc::Actor* enemy = new Enemy;
        enemy->Load("enemy.txt");
        dynamic_cast<Enemy*>(enemy)->SetTarget(scene.GetActor<Player>());
        enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
        dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));
        scene.AddActor(enemy);
    }

    char name[] = "AWhitehouse";
    Core::Init(name, 800, 600, 90);
    Core::RegisterUpdateFn(Update);
    Core::RegisterDrawFn(Draw);

    Core::GameLoop();
    Core::Shutdown();

    scene.Shutdown();
    g_particleSystem.ShutDown();
}