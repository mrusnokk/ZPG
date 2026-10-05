#include "Application.h"          

int main()
{
    Application* app = new Application(800,600,"ZPG");

    app->initialization();

    app->createShaders();
    app->createModels();
    app->createScenes();

    app->run();

    delete app;
    return 0;
}