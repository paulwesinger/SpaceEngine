#include "engine/engine.h"


int main(int argc,char ** argv)
{


    CEngine * engine = new CEngine("Engine started");

    if ( ! engine ) {
        printf( "Failed to Create Object !!! \n Aborting ......");
        return 1;
    }

    if ( engine->InitSDL2()) {

        engine->Run();

    }
    else {
        printf(" Init SDL2 failed !! \n aborting ....");
        return 2;
    }
    engine->Done();

    delete engine;
}
