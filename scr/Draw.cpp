#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vars.h"
// STRUCTS


// FUNCTION PROMISES

void miniMax(Tile(&)[3][3]);
void initVars(); 
void initGLFW(); 
void loop(); 
void draw(); 
void events(); 
void getCursorPos(int(&arr)[2]);
void drawLine(int, int, int, int);
void drawCircle(GLfloat, GLfloat, GLfloat); 
void drawCross(int, int);
void drawRect(const float x, const float y, const float w, const float h);
int determineWinner(Tile(&field)[3][3]);


// VARS

GLFWwindow* window;

const int width = 750; 
const int height = 750; 

Tile field[3][3];

int player = -2; 

// MAIN FUNCTIONS

int main() {
    initGLFW();

    initVars();

    loop();

    return 0;
}

void loop() { 
    while (!glfwWindowShouldClose(window)) {

        int winner = 0; 

        if ((winner = determineWinner(field)) != 0) {
            std::cout << "Winner: " << winner << std::endl;
            GLFWwindowclosefun(window); 
            break; 
        }

        if (player == 2) {
            miniMax(field);
        }

        events(); 

        draw();

        glfwPollEvents();
    }

    glfwTerminate();
}

void events() {
    static bool pressedOnce = false; 

    if (glfwGetMouseButton(window, 0) == GL_TRUE) {
        if (!pressedOnce) {
            pressedOnce = true; 

            int arr[2]; 
            getCursorPos(arr); 

            for (int i = 0; i < 3; i++) {
                for (int i2 = 0; i2 < 3; i2++) {
                    if (field[i][i2].hit(arr)) {
                        if (field[i][i2].used == 0) {

                            field[i][i2].used = player; 
                            player *= -1; 
                        }
                    }
                }
            }

        }
    }
    else {
        pressedOnce = false; 
    }
}

void draw() {

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = width / 3; i < width; i += width / 3) {
        drawRect(i, 0, 2, height); 
        drawRect(0, i, width, 2); 
    }

    for (int i = 0; i < 3; i++) {
        for (int i2 = 0; i2 < 3; i2++) {
            if (field[i][i2].used == 2) {
                drawCross(field[i][i2].x + field[i][i2].w/2, field[i][i2].y + field[i][i2].h/2);
            }
            else {
                if (field[i][i2].used == -2) {
                    drawCircle(field[i][i2].x + field[i][i2].w/2, field[i][i2].y + field[i][i2].h/2, 50);
                }
            }
        }
    }

    glfwSwapBuffers(window);
}


// UTILITY FUNCTIONS

void drawRect(const float x, const float y, const float w, const float h) {
    glBegin(GL_QUADS); 
        glColor4f(0.3, 0.3, 0.3, 1.0);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd(); 
}

void drawLine(int x1, int y1, int x2, int y2) {

    glBegin(GL_LINES); 
        glVertex2f(x1, y1); 
        glVertex2f(x2, y2); 
    glEnd(); 
}

void drawCross(int x, int y) {
    drawLine(x - (width / 3)/4, y - (height / 3)/4, x + (width / 3) / 4, y + (height / 3)/4);
    drawLine(x - (width / 3)/4, y + (height / 3)/4, x + (width / 3) / 4, y - (height / 3)/4);
}

void drawCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.141592;

    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}

void getCursorPos(int (&arr)[2]) {
    double x; 
    double y; 
    glfwGetCursorPos(window, &x, &y); 
    arr[0] = (int)x; 
    arr[1] = (int)y; 
}


// INIT FUNCTIONS

void initGLFW() {

    if (!glfwInit()) {
        throw "Failed to initialize";
    }

    window = glfwCreateWindow(width, height, "Tic Tac Toe", NULL, NULL);
    if (!window){
        glfwTerminate();
        throw "Failed to create window"; 
    }

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    glewInit();

    glOrtho(0.f, width, height, 0.f, 0.f, 1.f);

    glClearColor(0.9f, 0.9f, 0.9f, 1.f);

    glLineWidth(3);

}

void initVars() {
    for (int i = 0; i < 3; i++) {
        for (int i2 = 0; i2 < 3; i2++) {
            field[i][i2] = Tile(i2 * (width / 3), i * (height / 3), (width / 3), (height / 3));
        }
    }
}