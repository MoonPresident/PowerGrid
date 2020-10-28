






#ifndef WORLD_DATA_H
#define WORLD_DATA_H


#include <chrono>
#include "DisplayObject.h"

using namespace std::chrono;

class WorldData {
public:
    //Timing
    time_point<steady_clock>  previous_timestamp;
    time_point<steady_clock>  current_timestamp;
    time_point<steady_clock>  fps_timestamp;
    int fps;
    
    GameState() {
        //Set up time step and fps timestamp
        fps = 0;
        current_timestamp = steady_clock::now();
        previous_timestamp = current_timestamp;
        fps_timestamp = current_timestamp;
    }
    
    void set_timer() {
        current_timestamp = steady_clock::now();
    }
    
    int get_delta_t() {
        previous_timestamp = current_timestamp;
        current_timestamp = steady_clock::now();
        
        return duration_cast<microseconds>(current_timestamp - previous_timestamp).count();
    }
    
    
    /**
     * @brief Checks the fps output
     * @return 
     */
    int check_fps() {
        auto delta_fps = duration_cast<seconds>(current_timestamp - fps_timestamp).count();
        auto fps_output = 0;
        
        if(delta_fps) {
            fps_timestamp = current_timestamp;
            fps_output = fps;
            fps = 0;
        }
        
        fps++;
        return fps_output;
    }
};

#endif /* WORLD_DATA_H */