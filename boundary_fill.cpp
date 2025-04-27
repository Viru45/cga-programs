#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath> // <-- Add this line


using namespace std;

void my_init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 800);
}

void my_display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle boundary in BLACK
    glColor3f(0, 0, 0); 
    glBegin(GL_LINE_LOOP);
        glVertex2i(400, 600);
        glVertex2i(600, 200);
        glVertex2i(200, 200);
    glEnd();

    glFlush();
}

// Helper function to compare color with small tolerance
bool isSameColor(float* color1, float* color2)
{
    float epsilon = 0.01; // Allow small difference
    return (fabs(color1[0] - color2[0]) < epsilon &&
            fabs(color1[1] - color2[1]) < epsilon &&
            fabs(color1[2] - color2[2]) < epsilon);
}

void boundary_fill(int x, int y, float* fillColor, float* boundaryColor)
{
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    if (!isSameColor(current, boundaryColor) && !isSameColor(current, fillColor))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursive calls
        boundary_fill(x + 1, y, fillColor, boundaryColor);
        boundary_fill(x - 1, y, fillColor, boundaryColor);
        boundary_fill(x, y + 1, fillColor, boundaryColor);
        boundary_fill(x, y - 1, fillColor, boundaryColor);
    }
}

void mouse(int btn, int state, int x, int y)
{
    y = 800 - y; // Invert y axis for OpenGL
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float boundaryColor[] = {0.0, 0.0, 0.0}; // Black color
        float fillColor[] = {1.0, 0.0, 0.0};     // Red color to fill

        boundary_fill(x, y, fillColor, boundaryColor);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Boundary Fill Algorithm - Working Version");
    cout << "Click inside the triangle to fill using Boundary Fill." << endl;
    glutDisplayFunc(my_display);
    glutMouseFunc(mouse);
    my_init();
    glutMainLoop();
    return 0;
}
