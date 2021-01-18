


#ifndef TERMINAL_H
#define TERMINAL_H

#include "./Font.h"

class Terminal {
public:
    Font times;
    
    Terminal() : times("c:/windows/fonts/times.ttf")
    {
//        Font times = Font("c:/windows/fonts/times.ttf");
    }
};

#endif /* TERMINAL_H */