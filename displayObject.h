/**
 * @file displayObject.h
 * @author MoonPresident
 * @date October 25th 2020
 * 
 * A class for any object that will be displayed on screen.
 */
 
 
 #ifndef DISPLAY_OBJECT_H
 #define DISPLAY_OBJECT_H
 
class DisplayObject {
public:
     Program program;
     GLfloat location[4];
     
     DisplayObject() {
         for(int i = 0; i < 4; i++) location[i] = 0.f;
     }
     
 };
 
 #endif /* DISPLAY_OBJECT_H */