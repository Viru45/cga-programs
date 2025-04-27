#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

bool firstClick = true; // Tracks first mouse click
int lineType = 0;       // Default: Simple line

// Store triangle vertices globally
int triX[] = {400, 500, 300};
int triY[] = {500, 300, 300};

void draw_pixel(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glPointSize(3);
    gluOrtho2D(0, 800, 0, 800);
}

void DDA(int x1, int y1, int x2, int y2, int currentLineType) {
    int dx = x2 - x1, dy = y2 - y1, step;
    float incx, incy, x = x1, y = y1;
    step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    incx = (float)dx / step;
    incy = (float)dy / step;

    switch (currentLineType) {
 case 0: // Simple Line
        for (int i = 0; i <= step; i++) {
            draw_pixel(x, y);
            x += incx;
            y += incy;
        }
        break;
    case 1: // Dotted Line
        for (int i = 0; i <= step; i++) {
            if (i % 5 == 0)
                draw_pixel(x, y);
            x += incx;
            y += incy;
        }
        break;
    case 2: // Dashed Line
        for (int i = 0; i <= step; i++) {
            if (i % 10 < 5) // 5 pixels on, 5 off
                draw_pixel(x, y);
            x += incx;
            y += incy;
        }
        break;
    case 3: // Solid Line (Thicker)
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        break;
    }
}

void drawLine(int x1, int y1, int x2, int y2) {
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void drawAxis() {
    glColor3f(0.0, 0.0, 0.0);
    drawLine(0, 400, 800, 400); // X-axis
    drawLine(400, 0, 400, 800); // Y-axis

    for (int x = 0; x <= 800; x += 20)
        drawLine(x, 395, x, 405);
    for (int y = 0; y <= 800; y += 20)
        drawLine(395, y, 405, y);
}

void drawTriangle() {
    glColor3f(0.0, 1.0, 0.0); // Green color for triangle

    // Draw triangle edges with the currently selected line type
    for (int i = 0; i < 3; i++) {
        DDA(triX[i], triY[i], triX[(i + 1) % 3], triY[(i + 1) % 3], lineType);
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    if (!firstClick) {
        drawTriangle();
    }
    glFlush();
}

void menu(int option) {
    lineType = option;
    glutPostRedisplay(); // Redraw with the new line type
}

void mouse(int btn, int state, int x, int y) {
    y = 800 - y; // Convert to OpenGL coordinates
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        firstClick = false;
        glutPostRedisplay();
    } else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glutCreateMenu(menu);
        glutAddMenuEntry("Simple Line", 0);
        glutAddMenuEntry("Dotted Line", 1);
        glutAddMenuEntry("Dashed Line", 2);
        glutAddMenuEntry("Solid Line (Thicker)", 3);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Triangle Drawing with Line Type Menu");

    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);

    myInit();
    glutMainLoop();
    return 0;
}
