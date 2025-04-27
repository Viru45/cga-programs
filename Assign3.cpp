#include <GL/glut.h>
#include <iostream>
using namespace std;

// Variables for circle coordinates and radius
int centerX = 400, centerY = 400, radius = 100;
float circleColor[3] = {0.0, 0.5, 1.0}; // Default color: Blue

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Default drawing color
    glPointSize(2);                   // Point size for pixels
    gluOrtho2D(0, 800, 0, 800);       // Set 2D orthographic projection
}

void drawPixel(int x, int y, int xc, int yc) {
    glColor3f(circleColor[0], circleColor[1], circleColor[2]); // Set circle color
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

void bresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POINTS); // Start drawing points

    while (x <= y) {
        drawPixel(x, y, xc, yc);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    glEnd(); // End point drawing
    glFlush(); // Flush to render
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Black for axes
    glBegin(GL_LINES);
    glVertex2i(0, 400);
    glVertex2i(800, 400); // X-axis
    glVertex2i(400, 0);
    glVertex2i(400, 800); // Y-axis
    glEnd();
    glFlush();
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    drawAxes();                   // Draw coordinate axes
    bresenhamCircle(centerX, centerY, radius); // Draw the circle
}

void changeColor(int value) {
    // Update circleColor based on menu selection
    switch (value) {
    case 0: // Red
        circleColor[0] = 1.0; circleColor[1] = 0.0; circleColor[2] = 0.0;
        break;
    case 1: // Green
        circleColor[0] = 0.0; circleColor[1] = 1.0; circleColor[2] = 0.0;
        break;
    case 2: // Blue
        circleColor[0] = 0.0; circleColor[1] = 0.5; circleColor[2] = 1.0;
        break;
    case 3: // Yellow
        circleColor[0] = 1.0; circleColor[1] = 1.0; circleColor[2] = 0.0;
        break;
    case 4: // Purple
        circleColor[0] = 0.5; circleColor[1] = 0.0; circleColor[2] = 0.5;
        break;
    }
    glutPostRedisplay();
}

void getInputFromUser() {
    cout << "Enter the X-coordinate of the circle's center (0 to 800): ";
    cin >> centerX;
    cout << "Enter the Y-coordinate of the circle's center (0 to 800): ";
    cin >> centerY;
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    // Validate the input
    if (centerX < 0 || centerX > 800 || centerY < 0 || centerY > 800) {
        cout << "Coordinates must be between 0 and 800. Using default values." << endl;
        centerX = 400;
        centerY = 400;
    }
    if (radius <= 0 || radius > 400) {
        cout << "Radius must be positive and less than 400. Using default radius." << endl;
        radius = 100;
    }
}

int main(int argc, char** argv) {
    // Get user input
    getInputFromUser();

    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle with User Input");

    myInit();
    glutDisplayFunc(myDisplay);

    // Create a menu for color selection
    glutCreateMenu(changeColor);
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Yellow", 3);
    glutAddMenuEntry("Purple", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach the menu to the right mouse button

    glutMainLoop();
    return 0;
}

