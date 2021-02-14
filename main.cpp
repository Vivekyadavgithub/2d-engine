#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1920, 1080, "opengl", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error\n";
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load("../2D/container.jpg", &width, &height, &nrChannels, 0);

    /*float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };*/

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    /*float position[] = {
     0.5f/2.0f,  0.5f/2.0f, 0.0f/2.0f,  // top right
     0.5f/2.0f, -0.5f/2.0f, 0.0f/2.0f,  // bottom right
    -0.5f/2.0f, -0.5f/2.0f, 0.0f/2.0f,  // bottom left
    -0.5f/2.0f,  0.5f/2.0f, 0.0f,   // top left
     1.0f     ,  1.0f     , 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle
    };
    float texCoords[] = {
            0.0f, 0.0f,  // lower-left corner
            1.0f, 0.0f,  // lower-right corner
            0.5f, 1.0f   // top-center corner
    };*/


    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        //"layout(location = 1) in vec3 aColor;\n"
        "layout(location = 1) in vec2 aTexCoord;\n"
        //"out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        // "uniform mat4 transform;\n"
        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main()\n"
        "{\n"
        "gl_Position = projection * view * model  * vec4(aPos, 1.0f);\n"
        //"ourColor = aColor;\n"
        "TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        //"in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(ourTexture, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}\n";

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBuffer
    glBufferData(GL_ARRAY_BUFFER, 5 * 6 * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, 8 * sizeof(unsigned), 0);
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    /*unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned), indices, GL_STATIC_DRAW);*/



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);


    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
   // ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    // 0. copy our vertices array in a buffer for OpenGL to use
    /*glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);*/
    // 3. now draw the object
    //someOpenGLFunctionThatDrawsOurTriangle();
    //float timeValue = glfwGetTime();
    //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //glUseProgram(shaderProgram);
    //glUseProgram(shaderProgram);
    //float timeValue = glfwGetTime();
    //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    // Setup Dear ImGui context



    bool demoWindow = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    std::vector<glm::vec3>boxes;
    float pos = 0.5f;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();
       // ImGui_ImplOpenGL3_NewFrame();
       // ImGui_ImplGlfw_NewFrame();
        // be sure to activate the shader before any calls to glUniform
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
         //float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::scale(trans, glm::vec3(0.3, 0.3, 0.3));
        //trans = glm::rotate(trans, /*(float)glfwGetTime() **/ glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        //unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)700 / (float)700, 0.1f, 100.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        unsigned int projection_loc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));
        unsigned int view_loc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            //glm::mat4 transform = glm::mat4(1.0f);
           // transform = glm::rotate(transform, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            //transform = glm::scale(transform, glm::vec3(1.5f, 1.0f, 1.0f));
            //unsigned int transform_loc = glGetUniformLocation(shaderProgram, "transform");
            //glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                scale += 0.02f;
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                scale -= 0.02f;
            }
            model = glm::scale(model, scale);

            unsigned int postions_loc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(postions_loc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
            {
                static float f = 0.0f;
                static int counter = 0;
                ImGui::Text("hello world");
                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
                ImGui::ColorEdit3("clear color", (float*)&clear_color);
                ImGui::Checkbox("demo window", &demoWindow);
                ImGui::Checkbox("another window", &show_another_window);

                if (ImGui::Button("Button")) {
                    boxes.push_back({ pos, 0.0f, 0.0f });
                    pos += pos;

                }
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);
                ImGui::Text("Application avg %f ms/frame ()", f++);
            }
            for (auto it : boxes) {
                model = glm::translate(model, it);
                glUniformMatrix4fv(postions_loc, 1, GL_FALSE, glm::value_ptr(model));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        ImGui::Render();

        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        // check and call events and swap the buffers
        glfwPollEvents();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    stbi_image_free(data);
    glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &index_buffer);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
   // glViewport(0, 0, width, height);
}
