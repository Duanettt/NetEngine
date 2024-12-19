#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/Model.h"
#include "OpenGL/RenderTarget.h"
#include "Core/Window.h"


#include <iostream>
#include "Input/InputManager.h"
#include "Game/Player.h"
#include "OpenGL/Cube.h"
#include "Game/Terrain/NoiseTerrain.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0, 0.0, 3.0f));
Cursor* cursor;
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------

    Window window(800, 600, "LearnOpenGL");

    window.CreateWindow();

    Cursor cursor;
    window.SetWindowUserPointer(&cursor);
    window.SetCurrentContext();

    window.SetCallbacks(mouse_callback);

    window.SetInputMode();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader shader("res/shaders/vertexShader.vert", "res/shaders/fragmentShader.frag");
    Shader cubeShader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");
    Shader screenShader("res/shaders/screenShader.vert", "res/shaders/screenShader.frag");
    Shader terrainShader("res/shaders/terrainShader.vert", "res/shaders/terrainShader.frag");

    //InputManager::Initialize(window);

    Player player1(camera);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cubeVertices[] = {
        // positions          // texture Coords
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
    float planeVertices[] = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    float mirrorVertices[] = {
        // positions   // texCoords
        -0.25f,  0.25f,  0.0f, 1.0f,   // Top-left corner
        -0.25f, -0.25f,  0.0f, 0.0f,   // Bottom-left corner
         0.25f, -0.25f,  1.0f, 0.0f,   // Bottom-right corner

        -0.25f,  0.25f,  0.0f, 1.0f,   // Top-left corner
         0.25f, -0.25f,  1.0f, 0.0f,   // Bottom-right corner
         0.25f,  0.25f,  1.0f, 1.0f    // Top-right corner
    };



    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // screen quad VAO
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Mirror VAO
    unsigned int mirrorVAO, mirrorVBO;
    glGenVertexArrays(1, &mirrorVAO);
    glGenBuffers(1, &mirrorVBO);
    glBindVertexArray(mirrorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mirrorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mirrorVertices), &mirrorVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


    NoiseTerrain nt;

    // load textures
    // -------------
    unsigned int cubeTexture = loadTexture("res/textures/container.jpg");
    unsigned int floorTexture = loadTexture("res/textures/metal.png");

    Cube cube(cubeTexture);


    // shader configuration
    // --------------------
    shader.use();
    shader.setInt("texture1", 0);

    screenShader.use();
    screenShader.setInt("screenTexture", 0);

    // framebuffer configuration
    // -------------------------


    RenderTarget currentRenderTarget;
    TextureAttachment colorTextureBuffer;
    RenderBuffer rboObject;

    currentRenderTarget.CreateRenderTarget();
    currentRenderTarget.Bind();
    colorTextureBuffer.CreateAttachment();
    rboObject.CreateBufferObject();
    currentRenderTarget.AttachTextureAttachment(colorTextureBuffer);
    currentRenderTarget.AttachRenderBuffer(rboObject);
    currentRenderTarget.Unbind();


    // 
    // 
    // render loop
    // -----------

    cube.SetShader(cubeShader);

    cube.SetShader(cubeShader);





    while (!glfwWindowShouldClose(window.GetWindow()))

    {

        // per-frame time logic

        // --------------------

        float currentFrame = static_cast<float>(glfwGetTime());

        deltaTime = currentFrame - lastFrame;

        lastFrame = currentFrame;



        // input

        // -----

        processInput(window.GetWindow());







        // render

        // ------

        // bind to framebuffer and draw scene as we normally would to color texture 

        //glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        currentRenderTarget.Bind();

        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)



        // make sure we clear the framebuffer's content

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);







        //// cubes

        //glBindVertexArray(cubeVAO);

        //glActiveTexture(GL_TEXTURE0);

        //glBindTexture(GL_TEXTURE_2D, cubeTexture);

        //model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));

        //shader.setMat4("model", model);

        //glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);

        // 



        cubeShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);







        camera.SetTarget(&cube);

        cube.HandleInput(window.GetWindow(), deltaTime);

        camera.Update(deltaTime);





        glm::mat4 view = camera.GetViewMatrix();

        cube.Draw(view, projection);

        // Terrain

        nt.DrawTerrain(terrainShader, projection, view);

        // floor

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);

        shader.setMat4("view", view);

        shader.setMat4("projection", projection);

        glBindVertexArray(planeVAO);

        glBindTexture(GL_TEXTURE_2D, floorTexture);

        shader.setMat4("model", glm::mat4(1.0f));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);



        //player1.Draw();





        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture

        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

        currentRenderTarget.Unbind();

        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

        // clear all relevant buffers

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)

        glClear(GL_COLOR_BUFFER_BIT);



        screenShader.use();

        glBindVertexArray(quadVAO);

        colorTextureBuffer.Bind();

        //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane

        glDrawArrays(GL_TRIANGLES, 0, 6);





        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)

        // -------------------------------------------------------------------------------

        glfwSwapBuffers(window.GetWindow());

        glfwPollEvents();

    }



    // optional: de-allocate all resources once they've outlived their purpose:

    // ------------------------------------------------------------------------

    glDeleteVertexArrays(1, &cubeVAO);

    glDeleteVertexArrays(1, &planeVAO);

    glDeleteVertexArrays(1, &quadVAO);

    glDeleteBuffers(1, &cubeVBO);

    glDeleteBuffers(1, &planeVBO);

    glDeleteBuffers(1, &quadVBO);

    //glDeleteRenderbuffers(1, &rbo);

    //glDeleteFramebuffers(1, &framebuffer);



    glfwTerminate();

    return 0;

}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //// Basic user inputs for movements
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //{
    //    std::cout << "W Key Detected!" << std::endl;
    //    camera.ProcessKeyboard(FORWARD, deltaTime);
    //}
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    camera.ProcessKeyboard(BACKWARD, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    camera.ProcessKeyboard(LEFT, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    camera.ProcessKeyboard(RIGHT, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    //    camera.ProcessKeyboard(UP, deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    //    camera.ProcessKeyboard(DOWN, deltaTime);


    // Switching between fly mode and FPS mode.

    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    //{
    //    camera.SwitchMode();
    //}
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    Cursor* cursor = static_cast<Cursor*>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (cursor->firstMouse)
    {
        cursor->lastX = xpos;
        cursor->lastY = ypos;
        cursor->firstMouse = false;
    }

    float xoffset = xpos - cursor->lastX;
    float yoffset = cursor->lastY - ypos; // reversed since y-coordinates go from bottom to top

    cursor->lastX = xpos;
    cursor->lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}