// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/texture.hpp>
#include <common/vboindexer.hpp>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraFree_position = glm::vec3(0.0f, .0f, 3.0f);
glm::vec3 cameraFree_target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFree_direction = glm::normalize(cameraFree_position - cameraFree_target); // /!\pointe dans la direction inverse
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFree_right = glm::normalize(glm::cross(up, cameraFree_direction));
glm::vec3 cameraFree_up = glm::cross(cameraFree_direction, cameraFree_right);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

glm::vec3 cameraOrbit_position = glm::vec3(0.0f, .0f, 3.0f);
glm::vec3 cameraOrbit_target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraOrbit_direction = glm::normalize(cameraOrbit_position - cameraOrbit_target); // /!\pointe dans la direction inverse
glm::vec3 cameraOrbit_right = glm::normalize(glm::cross(up, cameraOrbit_direction));
glm::vec3 cameraOrbit_up = glm::cross(cameraOrbit_direction, cameraFree_right);

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// rotation
float angle = 0.;
float zoom = 1.;

bool firstMouse = true;
float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

bool orbitmode = false;
bool presentationmode = true;
bool freemode = false;

/*******************************************************************************/

glm::mat4 ModelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projMatrix;
std::vector<unsigned short> indices; // Triangles concaténés dans une liste
std::vector<glm::vec3> indexed_vertices;
std::vector<float> texCoords;
GLuint vertexbuffer;
GLuint elementbuffer;
GLuint uv;
int resolutionX = 2;
int sizeX = 1;
int resolutionY = 2;
int sizeY = 1;

float vitesse = 0.05;

void makePlan(int nX, int nY, int sizeX, int sizeY)
{
    // float pas = 4 / resolution;
    indexed_vertices.clear();
    indices.clear();
    texCoords.clear();
    for (size_t i = 0; i <= nX; i++)
    {
        for (size_t j = 0; j <= nY; j++)
        {
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            indexed_vertices.push_back(vec3(((float)sizeX / (float)nX) * i, r, ((float)sizeY / (float)nY) * j));
            texCoords.push_back((float)i / (float)nX);
            texCoords.push_back((float)j / (float)nY);
        }
    }
    // std::cout<<indexed_vertices.size()<<std::endl;

    for (size_t i = 0; i < nX; i++)
    {
        for (size_t j = 0; j < nY; j++)
        {
            indices.push_back((i + 1) * (nX + 1) + j);
            indices.push_back((i + 1) * (nX + 1) + j + 1);
            indices.push_back(i * (nX + 1) + j + 1);
            /* ___
               \  |
                \ |
                 \| */

            indices.push_back(i * (nX + 1) + j);
            indices.push_back((i + 1) * (nX + 1) + j);
            indices.push_back(i * (nX + 1) + j + 1);
            /*
              |\
              | \
              |__\  */

            texCoords.push_back((float)(i + 1) / (float)nX);
            texCoords.push_back((float)j / (float)nY);

            texCoords.push_back((float)(i + 1) / (float)nX);
            texCoords.push_back((float)(j + 1) / (float)nY);

            texCoords.push_back((float)(i) / (float)nX);
            texCoords.push_back((float)(j + 1) / (float)nY);
        }
    }

    // Load it into a VBO

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uv);
    glBindBuffer(GL_ARRAY_BUFFER, uv);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(unsigned short), &texCoords[0], GL_STATIC_DRAW);
}

int main(void)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "TP1 - GLFW", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    // glEnable(GL_CULL_FACE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");

    /*****************TODO***********************/
    // Get a handle for our "Model View Projection" matrices uniforms
    ModelMatrix = glm::mat4(1.f);
    viewMatrix = glm::mat4(1.f);
    projMatrix = glm::mat4(1.f);
    /****************************************/
    std::vector<std::vector<unsigned short>> triangles;

    // Chargement du fichier de maillage
    std::string filename("chair.off");
    // loadOFF(filename, indexed_vertices, indices, triangles );
    makePlan(resolutionX, resolutionY, sizeX, sizeY);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    GLuint texture = loadBMP_custom("../lavabis.bmp");
    glActiveTexture(texture);

    // GLuint heightmap = loadTexture2DFromFilePath("../textures/Heightmap_Mountain.png");
    // glActiveTexture(heightmap);

    do
    {

        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change

        // View matrix : camera/view transformation lookat() utiliser cameraFree_position cameraFree_target cameraFree_up
        // LIBRE
        if (freemode)
        {
            std::cout << "Mode de caméra : libre" << std::endl;
            viewMatrix = glm::lookAt(cameraFree_position, cameraFree_position + cameraFront, cameraFree_up);
        }
        // ORBIT
        if (orbitmode)
        {
            std::cout << "Mode de caméra : orbital" << std::endl;
            viewMatrix = glm::lookAt(cameraOrbit_position, cameraOrbit_target, cameraOrbit_up);
        }
        // Rotate animation
        if (presentationmode)
        {
            std::cout << "Mode de caméra : présentation" << std::endl;
            const float radius = 5.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            viewMatrix = glm::lookAt(glm::vec3(camX, 0.0, camZ), cameraFree_target, up);
        }

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        projMatrix = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100.0f);
        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(programID, "modelM"), 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "viewM"), 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projM"), 1, GL_FALSE, &projMatrix[0][0]);

        /****************************************/

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,        // attribute
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uv);
        glVertexAttribPointer(
            1,        // attribute
            2,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      // mode
            indices.size(),    // count
            GL_UNSIGNED_SHORT, // type
            (void *)0          // element array buffer offset
        );

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    const float polarangle = 20;
    const float azimuthangle = 20;
    const float radius = 5;

    const float cameraSpeed = 4 * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (freemode)
        {
            cameraFree_position += cameraSpeed * cameraFront;
        }
        if (orbitmode)
        {
            cameraOrbit_position += glm::normalize((cameraOrbit_target - cameraOrbit_position) + cameraOrbit_up);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (freemode)
            cameraFree_position -= cameraSpeed * cameraFront;
        if (orbitmode)
            cameraOrbit_position -= glm::normalize((cameraOrbit_target - cameraOrbit_position) + cameraOrbit_up);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (freemode)
            cameraFree_position -= glm::normalize(glm::cross(cameraFront, cameraFree_up)) * cameraSpeed;
        if (orbitmode)
        {
            cameraOrbit_position -= glm::normalize(glm::cross((cameraOrbit_target - cameraOrbit_position), cameraOrbit_up)) * cameraSpeed;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (freemode)
            cameraFree_position += glm::normalize(glm::cross(cameraFront, cameraFree_up)) * cameraSpeed;
        if (orbitmode)
        {
            cameraOrbit_position += glm::normalize(glm::cross((cameraOrbit_target - cameraOrbit_position), cameraOrbit_up)) * cameraSpeed;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
    {
        resolutionX++;
        resolutionY++;
        makePlan(resolutionX, resolutionY, sizeX, sizeY);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    {
        if (resolutionX > 1 && resolutionY > 1)
        {
            resolutionX--;
            resolutionY--;
        }
        makePlan(resolutionX, resolutionY, sizeX, sizeY);
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        cameraFree_position += vec3(0, 10, 0);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {

        presentationmode = true;
        freemode = false;
        orbitmode = false;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        if (freemode)
        {
            presentationmode = false;
            freemode = false;
            orbitmode = true;
        }
        else
        {

            presentationmode = false;
            freemode = true;
            orbitmode = false;
        }
    }
    // TODO add translations
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
// void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
// {

//     float xpos = static_cast<float>(xposIn);
//     float ypos = static_cast<float>(yposIn);

//     if (firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.1f; // change this value to your liking
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw -= xoffset;
//     pitch -= yoffset;

//     // make sure that when pitch is out of bounds, screen doesn't get flipped
//     if (pitch > 89.0f)
//         pitch = 89.0f;
//     if (pitch < -89.0f)
//         pitch = -89.0f;

//     glm::vec3 front;
//     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front.y = sin(glm::radians(pitch));
//     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     cameraFree_target = glm::normalize(front);
// }

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}