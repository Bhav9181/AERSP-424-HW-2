//Bhavya Patel
//AERSP 424
//HW 2

//Question 4

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

// Function to calculate profile power coefficient of a rotor using advance ratio
float profilePowerCoefficient(float advanceRatio) {
    return 1 * advanceRatio * advanceRatio;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Plot of Power Curve for Rotor", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set the clear color for the window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1, 0.5, -0.01, 0.1, -1.0, 1.0);  // Adjusted for better visualization

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Begin drawing lines
        glBegin(GL_LINES);
        // Draw X and Y axis
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-0.1, 0.0);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.0, -0.01);
        glVertex2f(0.0, 0.1);

        // Plot power curve for a rotor
        glColor3f(0.0, 1.0, 0.0);
        for (float advanceRatio = 0.01; advanceRatio <= 0.5; advanceRatio += 0.001) {
            float C_P1 = profilePowerCoefficient(advanceRatio);
            glVertex2f(advanceRatio, C_P1);
        }
        glEnd(); // End drawing lines

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
