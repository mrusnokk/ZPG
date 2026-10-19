#include "Application.h"          
#include "ForestScene.h"
#include "LoginScene.h"
#include "TriangleScene.h"
#include "SphereScene.h"
#include "SolarScene.h"
#include "ClockScene.h"
#include "BallsScene.h"

int main()
{
    int width = 1920, height = 1080;
    Application* app = new Application(width,height,"ZPG");

    app->initialization();
    app->addScene(new ForestScene(width, height));
    app->addScene(new BallsScene(width, height));
	app->addScene(new SolarScene(width, height));
    app->addScene(new ClockScene());
    app->run();

    delete app;
    return 0;
}