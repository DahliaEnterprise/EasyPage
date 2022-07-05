#include <stdio.h>
#include <glib-2.0/gio/gio.h>
#include "/usr/include/glib-2.0/glib.h"
#include <gio-unix-2.0/gio/gunixsocketaddress.h>
#include "/usr/include/gtk-3.0/gtk/gtk.h"
#include <stdlib.h>
#include <string.h>

#include "/usr/include/GL/glew.h"
#include "/usr/include/GL/gl.h"
#include "/usr/include/GL/glut.h"
#include "/usr/include/GLFW/glfw3.h"



																										 
void display() {  // Display function will draw the image.
 
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin(GL_TRIANGLES);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0, 0.9 );
    glEnd(); 
    
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
 
}



int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    
    glutMainLoop();
return 0;
}
