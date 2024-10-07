/**
 * @file main.cpp
 * @author MoonPresident
 * @date January 4th 2020
 * 
 * Needs links included to opengl32 and gdi32
 * Get GLM installed. Or make your own vector math, up to you.
 */

/********************************************************************************
 *******                             Includes                             *******
 *******************************************************************************/
//Include this everywhere
#include "my_debug.h"

//Games
// #include "games/squares_original.h"
#include "games/example_game_3D.h"
#include "games/opengl_examples/SimpleSquare.h"
#include "games/opengl_examples/textured_square.h"
#include "games/opengl_examples/transformed_square.h"
#include "games/opengl_examples/SimpleCube.h"
#include "games/opengl_examples/CameraExample.h"
#include "games/opengl_examples/TextRenderingExample.h"
#include "games/opengl_examples/LightingExample.h"

//Freetype kinda sucks to get working
//https://www.gregwessels.com/dev/2017/05/02/freetype-harfbuzz.html

/********************************************************************************
 *******                           Namespaces                             *******
********************************************************************************/
using namespace std::chrono;

/********************************************************************************
 *******                             Defines                              *******
********************************************************************************/

/**
 * DEBUG DEFINES
 * debug_all
 * debug_shaders
 * debug_flow
 * debug_mouse
**/

/********************************************************************************
*******                              Startup                              *******
********************************************************************************/

//GOALS ACHIEVED:
//  Square drawn and rotating with mouse
//  Movement with WASD
//  Abstract out the drawing and the game logic
//  Bullets shooting, object addition implemented.
//  Passing lifecycle and movement behaviour around as std::functions.
//  Print Character Bitmaps
//  Good text rendering from a TTF.

//NEXT STEP:
//  Implement a Resource Manager
//  Implement key mapping
//  Look into how passing 3D models works. That will answers a lot of questions.
//  Get buttons working.
//  Get a menu going.
// Convert everything to h and cpp instead of header only.
//  Get Terminal Working
//  Get an input interface
//  Work out model for state machine

//Do some shader toy and PBR stuff, or something fun a la this:
//https://thebookofshaders.com/07/

// glm stuff:
//These are other important includes for when it goes nutty.
// #include <gtc/matrix_transform.hpp>
// #include <gtc/type_ptr.hpp>
// #include <ext.hpp>

/**
 * @brief Main function for Powergrid program
 * @param argc
 * @param argv
 * @return Error value
 */
auto main(int argc, char **argv) -> int {
    //LearnOpenGL inspired examples:
    #if defined debug_all || defined debug_flow
    std::cout << "Starting program..." << std::endl;
    #endif

    //Might be nice to turn this into a CLI
    //Also would be nice to be able to have this running and choose via gui or
    //tui which demo to run.
    if(argc > 1) {
        //testcases = argv[1...]
        for(size_t i = 1; i < argc; i++) {
            const char* demo = argv[i];
            
            std::cout << "demo: \"" << demo << "\"\n";

            if (demo == "simple") {
                SimpleSquare simpleSquare; simpleSquare.run(); std::cout << "\n";
            } else if (demo == "textured") {
                TexturedSquare texturedSquare; texturedSquare.run(); std::cout << "\n";
            } else if (demo == "transformed") {
                TransformedSquare transformedSquare; transformedSquare.run(); std::cout << "\n";
            } else if (demo == "cube") {
                SimpleCube simpleCube; simpleCube.run(); std::cout << "\n";
            } else if (demo == "camera") {
                CameraExample cameraExample; cameraExample.run(); std::cout << "\n";
            } else if (demo == "text") {
                TextRenderingExample textRenderingExample; textRenderingExample.run(); std::cout << "\n";
            } else if (demo == "lighting") {
                auto lightingExample = new LightingExample; lightingExample->run(); delete lightingExample; std::cout << "\n";
            } else if (demo == "sandbox") {
                ExampleGame3D target; target.run(); std::cout << "\n";
            } else if (demo == "squaregame") {
                // squares_original_game(); std::cout << "\n";
            } else if (demo == "-h" || demo == "help" || demo == "--help") {
                std::cout << "Programs are: simple, textured, transformed, cube, camera, text, lighting, sandbox, squaregame\n";
            }
        }
    } else {
        ExampleGame3D target; target.run(); std::cout << "\n";
    }
}
