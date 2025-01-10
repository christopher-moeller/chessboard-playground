#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "Camera.h"

Camera cam(800, 600);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    cam.UpdateWindowSize(width, height);
}

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
    
    int numberValue;
    
    Shader sh("rectangle-vert.glsl", "rectangle-frag.glsl");
    VertexBuffer vb;
    
    vb.SetVertices({
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-right
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f // Top-right
    });
    
    vb.SetIndices({
        0, 1, 2, // First triangle
        2, 1, 3  // Second triangle
    });
    
    vb.AddAttributePointers(3, 6);
    vb.AddAttributePointers(3, 6);
    vb.Apply();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example ImGui window
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a sample ImGui window.");
        ImGui::SliderInt("Number Value", &numberValue, 2, 20);
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        {
            sh.Use();
            
            glm::mat4 view = cam.GetViewMatrix();
            glm::mat4 projection = cam.GetProjectionMatrix();
            
            glm::mat4 model = glm::mat4(1.0f);
            //model = glm::rotate(model, glm::degrees(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            
            sh.SetUniform4Mat("model", model);
            sh.SetUniform4Mat("view", view);
            sh.SetUniform4Mat("projection", projection);
            
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
        }
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
    
    /*
    Shader("rectangle-vert.glsl", "rectangle-frag.glsl");
    VertexBuffer vb;
    
    vb.SetVertices({
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-right
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f // Top-right
    });
    
    vb.SetIndices({
        0, 1, 2, // First triangle
        2, 1, 3  // Second triangle
    });
    
    vb.AddAttributePointers(3, 6);
    vb.AddAttributePointers(3, 6);
    
    vb.Apply();
    
    return 0;
     */
}
