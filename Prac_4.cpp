#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Structure to represent a 2D point
struct Point {
    float x, y;
};

// Global array to store the vertices of the polygon (now a pentagon)
Point points[5];

// Global variables to store transformation parameters
int choice;
float tx = 0, ty = 0, sx = 1, sy = 1, angle = 0, shx = 0, shy = 0;

// Function to draw the solid X and Y axes with tick marks
void drawAxesWithTicks() {
    glColor3f(0, 0, 0);         // Black color for axes
    glLineWidth(2.0);           // Set axis line width

    // Draw main X and Y axes
    glBegin(GL_LINES);
    glVertex2f(-100, 0);
    glVertex2f(100, 0); // X-axis
    glVertex2f(0, -100);
    glVertex2f(0, 100); // Y-axis
    glEnd();

    glLineWidth(1.0);           // Reset line width to default

    // Draw tick marks on the axes
    glBegin(GL_LINES);
    for (int i = -100; i <= 100; i += 10) {
        if (i != 0) {            // Skip drawing a tick at the origin
            glVertex2f(i, -2);
            glVertex2f(i, 2);     // X-axis ticks
            glVertex2f(-2, i);
            glVertex2f(2, i);     // Y-axis ticks
        }
    }
    glEnd();
}

// Function to draw a polygon (filled or outlined)
void drawPolygon(Point pts[5], float r, float g, float b, float thickness, bool fill) {
    glColor3f(r, g, b);       // Set polygon color
    glLineWidth(thickness);   // Set polygon line thickness

    // Begin drawing the polygon
    if (fill) {
        glBegin(GL_POLYGON); // Filled polygon
    } else {
        glBegin(GL_LINE_LOOP); // Polygon outline
    }

    // Iterate through the points and define the vertices
    for (int i = 0; i < 5; i++) {
        glVertex2f(pts[i].x, pts[i].y);
    }

    glEnd(); // End drawing the polygon
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to modelview
    glLoadIdentity();             // Load the identity matrix

    // Draw the coordinate axes with tick marks
    drawAxesWithTicks();

    // Draw the original polygon (before transformation) in red outline
    drawPolygon(points, 1, 0, 0, 3.0, false);

    // Create a copy of the original points for transformation
    Point transformed[5];
    for (int i = 0; i < 5; i++) {
        transformed[i] = points[i]; // Copy original points
    }

    // Apply the selected transformation to the copied points
    if (choice == 1) {
        // Translation
        for (int i = 0; i < 5; i++) {
            transformed[i].x += tx;
            transformed[i].y += ty;
        }
    } else if (choice == 2) {
        // Scaling
        for (int i = 0; i < 5; i++) {
            transformed[i].x *= sx;
            transformed[i].y *= sy;
        }
    } else if (choice == 3) {
        // Rotation (about the origin)
        float rad = angle * 3.14159f / 180; // Convert degrees to radians
        for (int i = 0; i < 5; i++) {
            float x = transformed[i].x;
            float y = transformed[i].y;
            transformed[i].x = x * cos(rad) - y * sin(rad); // Rotation formula
            transformed[i].y = x * sin(rad) + y * cos(rad); // Rotation formula
        }
    } else if (choice == 4) {
        // Shearing
        for (int i = 0; i < 5; i++) {
            float x = transformed[i].x;
            float y = transformed[i].y;
            transformed[i].x = x + y * shx; // Shearing in x-direction
            transformed[i].y = y + x * shy; // Shearing in y-direction
        }
    }

    // Draw the transformed polygon (after transformation) in green fill
    drawPolygon(transformed, 0, 1, 0, 4.0, true);

    glFlush(); // Flush the graphics pipeline
}

// Main function
int main(int argc, char** argv) {
    // Input the original pentagon's five vertices
    cout << "Enter 5 points (x, y) for the pentagon: ";
    for (int i = 0; i < 5; i++)
        cin >> points[i].x >> points[i].y;

    // Ask the user to choose a transformation type
    cout << "Choose Transformation: 1-Translate, 2-Scale, 3-Rotate, 4-Shear\n";
    cin >> choice;

    // Input transformation parameters based on the user's choice
    if (choice == 1) {
        cout << "Enter translation values (tx, ty): ";
        cin >> tx >> ty;
    } else if (choice == 2) {
        cout << "Enter scale factors (sx, sy): ";
        cin >> sx >> sy;
    } else if (choice == 3) {
        cout << "Enter rotation angle (in degrees): ";
        cin >> angle;
    } else if (choice == 4) {
        cout << "Enter shear factors (shx, shy): ";
        cin >> shx >> shy;
    }

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);          // Set window size
    glutCreateWindow("2D Transformations with Tick Mark Axes"); // Create window with title

    // Set the background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Set the projection matrix to orthographic
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100); // Define the 2D orthographic projection

    // Register the display function and start the GLUT main loop
    glutDisplayFunc(display);
    glutMainLoop();

    return 0; // End of program
}

