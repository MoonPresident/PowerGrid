/**
 * @file main.cpp
 * @author MoonPresident
 * @date January 4th 2020
 * 
 * Needs links included to opengl32 and gdi32
 * Get GLM installed. Or make your own vector math, up to you.
 */

//https://www.glprogramming.com/red/chapter02.html
//https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html
//https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects

//https://www.haroldserrano.com/articles

//http://www-cs-students.stanford.edu/%7Eamitp/gameprog.html

//https://www.gamasutra.com/blogs/MichaelKissner/20151027/257369/Writing_a_Game_Engine_from_Scratch__Part_1_Messaging.php

//https://www.youtube.com/watch?v=Cfe3sO_L0fM&feature=share



//Working out the difference between using a VAO and using VertexAttrib/Uniforms
//https://www.reddit.com/r/opengl/comments/4e9jmw/is_it_better_to_separate_the_vbo_update_from_the/d1ydon0/

//https://teaching.csse.uwa.edu.au/units/CITS3003/lectures/04-OpenGL-Example-Program.pdf




/**
 * THIS!!! https://docs.gl/gl4/glBufferData
**/


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
//Idk tho
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
**/



//https://thebookofshaders.com/07/


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

//  Engine makes the actual game take years to design. This was expected, but jesus.
//  Get Terminal Working
//  Get an input interface
//  Work out model for state machine


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
int main(int argc, char **argv) {
    //LearnOpenGL inspired examples:
    #if defined debug_all || defined debug_flow
    std::cout << "Starting program..." << std::endl;
    #endif

    // SimpleSquare simpleSquare; simpleSquare.run(); std::cout << "\n";
    // TexturedSquare texturedSquare; texturedSquare.run(); std::cout << "\n";
    // TransformedSquare transformedSquare; transformedSquare.run(); std::cout << "\n";
    // SimpleCube simpleCube; simpleCube.run(); std::cout << "\n";
    // CameraExample cameraExample; cameraExample.run(); std::cout << "\n";
    // TextRenderingExample textRenderingExample; textRenderingExample.run(); std::cout << "\n";
    auto lightingExample = new LightingExample; lightingExample->run(); delete lightingExample; std::cout << "\n";

    // Original Creations
    // squares_original_game(); std::cout << "\n";
    ExampleGame3D target; target.run(); std::cout << "\n";
}
