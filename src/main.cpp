#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Controller.h"

Controller controller;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    controller.UpdateWindowSize(width, height);
}

void ProcessInput(GLFWwindow* window, float deltaTime);

int initContext() {

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLApp", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Initialize ImGui backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    controller.SetupChessboard();
    
    int chessboardX = controller.GetChessboard()->GetX();
    int chessboardY = controller.GetChessboard()->GetY();
    
    float deltaTime = 0.0f;    // time between current frame and last frame
    float lastFrame = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example ImGui window
        ImGui::Begin("Chessboard");
        ImGui::Text("Dimentions");
        
        int oldX = chessboardX;
        int oldY = chessboardY;
        ImGui::SliderInt("X", &chessboardX, 2, 20);
        ImGui::SliderInt("Y", &chessboardY, 2, 20);
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        
        if(oldX != chessboardX || oldY != chessboardY) {
            controller.UpdateChessboardDimensions(chessboardX, chessboardY);
            controller.SetupChessboard();
        }
        
        
        glClear(GL_COLOR_BUFFER_BIT);
        controller.DrawElements();
        ProcessInput(window, deltaTime);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;

}

int main() {
    return initContext();
}

void ProcessInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }
    
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        controller.ProcessInput(PRESSED_UP, deltaTime);
    }
    
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        controller.ProcessInput(PRESSED_DOWN, deltaTime);
    }
    
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        controller.ProcessInput(PRESSED_LEFT, deltaTime);
    }
    
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        controller.ProcessInput(PRESSED_RIGHT, deltaTime);
    }
}
