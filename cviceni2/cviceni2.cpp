#include "Application.h"          
#include "ForestScene.h"
#include "LoginScene.h"
#include "TriangleScene.h"
#include "SphereScene.h"

int main()
{
    Application* app = new Application(800,600,"ZPG");

    app->initialization();

    app->addScene(new TriangleScene());
    //app->addScene(new SphereScene());
    //app->addScene(new ForestScene());
    //app->addScene(new LoginScene());

    app->run();

    delete app;
    return 0;
}