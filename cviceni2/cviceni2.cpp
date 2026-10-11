#include "Application.h"          
#include "ForestScene.h"
#include "LoginScene.h"
#include "TriangleScene.h"
#include "SphereScene.h"
#include "SolarScene.h"

int main()
{
    Application* app = new Application(800,600,"ZPG");

    app->initialization();
    app->addScene(new ForestScene());
    app->addScene(new SolarScene());
    app->run();

    delete app;
    return 0;
}