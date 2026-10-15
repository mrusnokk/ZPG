#include "Application.h"          
#include "ForestScene.h"
#include "LoginScene.h"
#include "TriangleScene.h"
#include "SphereScene.h"
#include "SolarScene.h"
#include "ClockScene.h"

int main()
{
    int width = 800, height = 600;
    Application* app = new Application(width,height,"ZPG");

    app->initialization();
    app->addScene(new ForestScene(width, height));
    app->addScene(new SolarScene());
    app->addScene(new ClockScene());
    app->run();

    delete app;
    return 0;
}