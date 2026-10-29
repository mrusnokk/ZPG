#include "core/Application.h"          
#include "scenes/ForestScene.h"
#include "scenes/LoginScene.h"
#include "scenes/TriangleScene.h"
#include "scenes/SphereScene.h"
#include "scenes/SolarScene.h"
#include "scenes/ClockScene.h"
#include "scenes/BallsScene.h"

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