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
using namespace std;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>
#include <TP1/ObjectPlan.hpp>
#include <TP1/Vehicule.hpp>
#include <pthread.h>
#include <chrono>
#include <thread>

#define GRAVITY 9.8

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void updateSpherePos();
void turnPneu(Object3D &roueDirectionnelleDroite, Object3D &roueDirectionnelleGauche, bool reInit);
void checkFreinAMain(Vehicule &Bolide, ObjectPlan &planInfini, ObjectPlan &lastChild);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraFree_position = glm::vec3(0.0f, 2.0f, 5.0f);
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
int nbFrames = 0;

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

glm::mat4 viewMatrix;
glm::mat4 projMatrix;
std::vector<unsigned short> indices; // Triangles concaténés dans une liste
std::vector<glm::vec3> indexed_vertices;
std::vector<float> texCoords;
GLuint vertexbuffer;
GLuint elementbuffer;
GLuint uv;
GLuint hmap;

int resolutionX = 2;
int sizeX = 1;
int resolutionY = 2;
int sizeY = 1;

float vitesse = 0.05;
float rotateSpeed = 0.05;

int renderDistance = 20;

Vehicule Bolide;
ObjectPlan plan1;
ObjectPlan plan2;
ObjectPlan plan3;
ObjectPlan plan4;
ObjectPlan plan5;
ObjectPlan planInfini;
int planToMove = 1;

bool letsgo = false;

void *updateFPS(void *params)
{
    string s = "FPS - ";
    while (true)
    {

        glfwSetWindowTitle(window, (s + to_string(nbFrames)).c_str());
        nbFrames = 0;
        this_thread::sleep_for(1000ms);
    }
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
    viewMatrix = glm::mat4(1.f);
    projMatrix = glm::mat4(1.f);
    /****************************************/
    std::vector<std::vector<unsigned short>> triangles;

    // Chargement du fichier de maillage

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    // For speed computation
    double lastTime = glfwGetTime();

    int ObjectState = 1;
    Bolide.transform.Scale(vec3(1, 1, 1));
    Object3D roueDirectionnelleDroite;
    Object3D roueDirectionnelleGauche;
    roueDirectionnelleDroite.transform.Translate(vec3(1, 0, -2));
    roueDirectionnelleGauche.transform.Translate(vec3(-1, 0, -2));

    Bolide.addChild(&roueDirectionnelleGauche);
    Bolide.addChild(&roueDirectionnelleDroite);
    ObjectLoaded pneuAvantGauche;
    pneuAvantGauche.loadObject("./pneu.obj", 1);
    pneuAvantGauche.loadTexture("../textures/textPneu.jpg");
    pneuAvantGauche.transform.Rotation(vec3(0, 0, 1), radians(90.0));
    pneuAvantGauche.transform.Scale(vec3(0.5, 0.5, 0.5));
    roueDirectionnelleGauche.addChild(&pneuAvantGauche);

    ObjectLoaded pneuAvantDroit;
    pneuAvantDroit.loadObject("./pneu.obj", 1);
    pneuAvantDroit.loadTexture("../textures/textPneu.jpg");
    pneuAvantDroit.transform.Rotation(vec3(0, 0, 1), radians(90.0));
    pneuAvantDroit.transform.Scale(vec3(0.5, 0.5, 0.5));
    roueDirectionnelleDroite.addChild(&pneuAvantDroit);

    ObjectLoaded pneuArriereGauche;
    pneuArriereGauche.loadObject("./pneu.obj", 1);
    pneuArriereGauche.loadTexture("../textures/textPneu.jpg");
    pneuArriereGauche.transform.Translate(vec3(-1, 0, 0));
    pneuArriereGauche.transform.Rotation(vec3(0, 0, 1), radians(90.0));
    pneuArriereGauche.transform.Scale(vec3(0.5, 0.5, 0.5));
    Bolide.addChild(&pneuArriereGauche);

    ObjectLoaded pneuArriereDroit;
    pneuArriereDroit.loadObject("./pneu.obj", 1);
    pneuArriereDroit.loadTexture("../textures/textPneu.jpg");
    pneuArriereDroit.transform.Translate(vec3(1, 0, 0));
    pneuArriereDroit.transform.Rotation(vec3(0, 0, 1), radians(90.0));
    pneuArriereDroit.transform.Scale(vec3(0.5, 0.5, 0.5));
    Bolide.addChild(&pneuArriereDroit);

    float masseBolide = 2.1;

    plan1.makePlan(resolutionX, resolutionY, 12, 12, 6, 6, 1, "../textures/moon.jpg", false, "../textures/Heightmap_Mountain.png");
    plan1.loadTexture("../textures/moon.jpg");
    plan2.makePlan(resolutionX, resolutionY, 12, 12, 6, 18, 1, "../textures/moon.jpg", false, "../textures/Heightmap_Mountain.png");
    plan2.loadTexture("../textures/moon.jpg");
    plan3.makePlan(resolutionX, resolutionY, 12, 12, 6, 30, 1, "../textures/moon.jpg", false, "../textures/Heightmap_Mountain.png");
    plan3.loadTexture("../textures/moon.jpg");
    plan4.makePlan(resolutionX, resolutionY, 12, 12, 6, 42, 1, "../textures/moon.jpg", false, "../textures/Heightmap_Mountain.png");
    plan4.loadTexture("../textures/moon.jpg");
    plan5.makePlan(resolutionX, resolutionY, 12, 12, 6, 54, 1, "../textures/moon.jpg", false, "../textures/Heightmap_Mountain.png");
    plan5.loadTexture("../textures/moon.jpg");

    planInfini.addChild(&plan1);
    planInfini.addChild(&plan2);
    planInfini.addChild(&plan3);
    planInfini.addChild(&plan4);
    planInfini.addChild(&plan5);

    Object3D racine;
    racine.addChild(&planInfini);
    racine.addChild(&Bolide);

    pthread_t thread;

    if (pthread_create(&thread, NULL, updateFPS, (void *)0) != 0)
    {
        perror("erreur creation thread");
        exit(1);
    }
    bool test = false;
    vec3 centre = vec3(-1, 1, 0);

    // ALuint buffer;
    // alGenBuffers(1, &buffer);
    // ALsizei size, freq;
    // ALenum format;
    // ALvoid *data;
    // alBufferData(buffer, format, data, size, freq);

    // // Jouez le fichier audio
    // ALuint source;
    // alGenSources(1, &source);
    // alSourcei(source, AL_BUFFER, buffer);
    // alSourcePlay(source);

    // // Arrêtez la lecture du fichier audio
    // alSourceStop(source);

    do
    {
        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        nbFrames++;

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
            viewMatrix = glm::lookAt(cameraFree_position, cameraFree_position + cameraFront, cameraFree_up);
        }
        // ORBIT
        if (orbitmode)
        {
            // std::cout << "Mode de caméra : orbital" << std::endl;
            viewMatrix = glm::lookAt(cameraOrbit_position, cameraOrbit_target, cameraOrbit_up);
        }
        // Rotate animation
        if (presentationmode)
        {
            // ModelMatrix = rotate(ModelMatrix,rotateSpeed,glm::vec3(0,1,0));
            viewMatrix = glm::lookAt(glm::vec3(0, 3, 3), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        }

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        projMatrix = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100.0f);
        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(programID, "viewM"), 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projM"), 1, GL_FALSE, &projMatrix[0][0]);

        // // MOUVEMENT
        // if (letsgo)
        // {
        //     vec3 GravityForce = vec3(0, -(masseBolide * GRAVITY), 0);

        //     if (centre.x <= maxXPlan)
        //     {
        //         vec3 acceleration = GravityForce /* /masseBolide */;
        //         vitesseBolide += acceleration * deltaTime;
        //         Bolide.transform.Translate(vitesseBolide * deltaTime);
        //         centre += vitesseBolide * deltaTime;
        //         if (centre.y < 1)
        //         {
        //             // vitesseBolide=vec3(0.,0.,0.);
        //             vitesseBolide *= -1;
        //             vitesseBolide.x *= -1;
        //         }
        //     }
        //     else
        //     {
        //         centre += GravityForce * deltaTime;
        //         Bolide.transform.Translate(GravityForce * deltaTime);
        //     }
        // }

        planInfini.transform.Translate(-(Bolide.getSpeed() * cameraFront));
        Bolide.addSpeed(vec3(0, 0, -(0.005 * Bolide.getSpeed().z * Bolide.getSpeed().z)));
        if (Bolide.getSpeed().z < 0.1 && !Bolide.getStop())
        {
            Bolide.addSpeed(vec3(0, 0, 0.1));
        }

        pneuAvantGauche.transform.Rotation(vec3(0, 1, 0), Bolide.getSpeed().z);
        pneuAvantDroit.transform.Rotation(vec3(0, 1, 0), Bolide.getSpeed().z);
        pneuArriereGauche.transform.Rotation(vec3(0, 1, 0), Bolide.getSpeed().z);
        pneuArriereDroit.transform.Rotation(vec3(0, 1, 0), Bolide.getSpeed().z);

        checkFreinAMain(Bolide, planInfini, plan1);

        if (planInfini.transform.t[2] > 6 && planToMove == 1)
        {
            plan1.transform.Translate(vec3(0, 0, -60));
            planToMove = 2;
        }
        else if (planInfini.transform.t[2] > 18 && planToMove == 2)
        {
            plan2.transform.Translate(vec3(0, 0, -60));
            planToMove = 3;
        }
        else if (planInfini.transform.t[2] > 30 && planToMove == 3)
        {
            plan3.transform.Translate(vec3(0, 0, -60));
            planToMove = 4;
        }
        else if (planInfini.transform.t[2] > 42 && planToMove == 4)
        {
            plan4.transform.Translate(vec3(0, 0, -60));
            planToMove = 5;
        }
        else if (planInfini.transform.t[2] > 54 && planToMove == 5)
        {
            plan5.transform.Translate(vec3(0, 0, -60));
            planToMove = 1;
            planInfini.transform.t.z -= 60;
        }

        turnPneu(roueDirectionnelleDroite, roueDirectionnelleGauche, false);

        racine.updateMeAndChilds();
        racine.draw(programID);

        turnPneu(roueDirectionnelleDroite, roueDirectionnelleGauche, true);

        // BALADEMENT SUR LA PLAN
        // vector<vec3> verticesPlan = plan.getVertices();
        // vector<unsigned short> indicesPlan = plan.getIndices();

        // vector<vec2> uvsPlan = plan.getUVs();

        //  if (!test)
        //  {

        //     cout << "centre " << centre.x << " " << centre.y << " " << centre.z << endl;
        //     for (size_t i = 0; i < indicesPlan.size(); i += 3)
        //     {
        //         cout << indicesPlan[i] << " ; " << indicesPlan[i + 1] << " ; " << indicesPlan[i + 2] << endl;
        //     }
        //     test = true;

        //     cout << endl;

        //     int debIndice;
        //     vector<unsigned short> carrétrouvé;
        //     for (size_t i = 0; i < indicesPlan.size(); i += 6)
        //     {
        //         if (centre.z > verticesPlan[indicesPlan[i]].z && centre.z < verticesPlan[indicesPlan[i + 1]].z && centre.x < verticesPlan[indicesPlan[i]].x && centre.x > verticesPlan[indicesPlan[i + 2]].x /*  && verticesPlan[indicesPlan[i + 1]].x > centre.x && verticesPlan[indicesPlan[i]].x < centre.x */)
        //         {
        //             cout << "carré trouvé" << endl;
        //             cout << indicesPlan[i] << " ; " << indicesPlan[i + 1] << " ; " << indicesPlan[i + 2] << " ; " << indicesPlan[i + 3] << endl;
        //             for (size_t k = 0; k < 6; k++)
        //             {
        //                 carrétrouvé.push_back(indicesPlan[i + k]);
        //             }
        //         }
        //     }
        //     vector<unsigned short> traingletrouvé;
        //     float u;
        //     float v;
        //     float w;

        //     if (carrétrouvé.size() == 6)
        //     {
        //         for (size_t k = 0; k < 2; k++)
        //         {
        //             vec3 A = verticesPlan[carrétrouvé[0 + k * 3]];
        //             vec3 B = verticesPlan[carrétrouvé[2 + k * 3]];
        //             vec3 C = verticesPlan[carrétrouvé[1 + k * 3]];

        //             glm::vec3 AB = B - A;
        //             glm::vec3 AC = C - A;
        //             glm::vec3 N = glm::cross(AB, AC);

        //             float D = -(N.x * A.x + N.y * A.y + N.z * A.z);
        //             float t = -(N.x * centre.x + N.y * centre.y + N.z * centre.z + D) / glm::dot(N, N);
        //             glm::vec3 Q = centre + t * N;
        //             cout << "Pproj :" << Q.x << " " << Q.y << " " << Q.z << endl;

        //             glm::vec3 v0 = C - A;
        //             glm::vec3 v1 = B - A;
        //             glm::vec3 v2 = Q - A;

        //             float dot00 = glm::dot(v0, v0);
        //             float dot01 = glm::dot(v0, v1);
        //             float dot02 = glm::dot(v0, v2);
        //             float dot11 = glm::dot(v1, v1);
        //             float dot12 = glm::dot(v1, v2);

        //             float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
        //             u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        //             v = (dot00 * dot12 - dot01 * dot02) * invDenom;
        //             w = 1.0f - u - v;

        //             if ((u >= 0) && (v >= 0) && (u + v < 1))
        //             {
        //                 traingletrouvé.push_back(carrétrouvé[0 + k * 3]);
        //                 traingletrouvé.push_back(carrétrouvé[1 + k * 3]);
        //                 traingletrouvé.push_back(carrétrouvé[2 + k * 3]);
        //             }
        //         }
        //         cout << traingletrouvé[0] << " " << traingletrouvé[1] << " " << traingletrouvé[2] << endl;
        //     }

        //     if (traingletrouvé.size() == 3)
        //     {
        //         float uA=uvsPlan[traingletrouvé[0]].x;
        //         float uB=uvsPlan[traingletrouvé[2]].x;
        //         float uC=uvsPlan[traingletrouvé[1]].x;
        //         float vA=uvsPlan[traingletrouvé[0]].y;
        //         float vB=uvsPlan[traingletrouvé[2]].y;
        //         float vC=uvsPlan[traingletrouvé[1]].y;
        //         float uP = u * uA + v * uB + w * uC;
        //         float vP = u * vA + v * vB + w * vC;
        //         cout<<"uP :"<<uP<< " ; "<<"vP :"<<vP<<endl;
        //     }
        // }

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

    const float cameraSpeed = 10 * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (freemode)
        {
            if (!Bolide.getStop())
            {
                Bolide.addSpeed(vec3(0, 0, 0.01));
                if (Bolide.getSpeed().z > 2)
                {
                    Bolide.addSpeed(vec3(0, 0, 2));
                }
            }
        }
        if (orbitmode)
        {
            if (cameraOrbit_position.y < 6)
                cameraOrbit_position += glm::normalize(cameraOrbit_up) * cameraSpeed;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (freemode)
        {
            if (!Bolide.getStop())
            {
                Bolide.addSpeed(vec3(0, 0, -0.02));
                if (Bolide.getSpeed().z < 0.1)
                {
                    Bolide.addSpeed(vec3(0, 0, 0.1));
                }
            }
        }
        if (orbitmode)
            if (glm::dot(cameraOrbit_target - cameraOrbit_position, glm::vec3(0, 1, 0)) < 0)
                cameraOrbit_position -= glm::normalize(cameraOrbit_up) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !Bolide.getStop())
    {
        if (freemode)
        {
            vec3 move = glm::normalize(glm::cross(cameraFront, cameraFree_up)) * cameraSpeed;
            planInfini.transform.Translate(move);
            planInfini.transform.t += move;
            Bolide.setTurn(1);
        }
        if (orbitmode)
        {
            cameraOrbit_position -= glm::normalize(glm::cross((cameraOrbit_target - cameraOrbit_position), cameraOrbit_up)) * cameraSpeed;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !Bolide.getStop())
    {
        if (freemode)
        {
            vec3 move = glm::normalize(glm::cross(cameraFront, cameraFree_up)) * cameraSpeed;
            planInfini.transform.Translate(-move);
            planInfini.transform.t -= move;
            Bolide.setTurn(2);
        }

        if (orbitmode)
        {
            cameraOrbit_position += glm::normalize(glm::cross((cameraOrbit_target - cameraOrbit_position), cameraOrbit_up)) * cameraSpeed;
        }
    }

    if (!(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && !(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
    {
        Bolide.setTurn(0);
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
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        presentationmode = false;
        freemode = false;
        orbitmode = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        presentationmode = false;
        freemode = true;
        orbitmode = false;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotateSpeed += 0.001;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rotateSpeed -= 0.001;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        Bolide.transform.Translate(vec3(0.2, 0, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        Bolide.transform.Translate(vec3(-0.2, 0, 0));
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        Bolide.transform.Translate(vec3(0., 0, -0.2));
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        Bolide.transform.Translate(vec3(0, 0, 0.2));
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        letsgo = true;
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        letsgo = false;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        Transform t;
        Transform t1;
        Bolide.setStop(true);
        Bolide.transform = t;
        planInfini.transform = t1;
        for (size_t i = 0; i < planInfini.getChilds().size(); i++)
        {
            Transform t2;
            planInfini.getChilds()[i]->transform = t;
            planToMove = 1;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void turnPneu(Object3D &roueDirectionnelleDroite, Object3D &roueDirectionnelleGauche, bool reInit)
{
    if (reInit)
    {
        if (Bolide.getTurn() == 1)
        {
            roueDirectionnelleDroite.transform.Rotation(vec3(0, 1, 0), -radians(22.0));
            roueDirectionnelleGauche.transform.Rotation(vec3(0, 1, 0), -radians(22.0));
        }
        if (Bolide.getTurn() == 2)
        {
            roueDirectionnelleDroite.transform.Rotation(vec3(0, 1, 0), radians(22.0));
            roueDirectionnelleGauche.transform.Rotation(vec3(0, 1, 0), radians(22.0));
        }
    }
    else
    {
        if (Bolide.getTurn() == 1)
        {
            roueDirectionnelleDroite.transform.Rotation(vec3(0, 1, 0), radians(22.0));
            roueDirectionnelleGauche.transform.Rotation(vec3(0, 1, 0), radians(22.0));
        }
        if (Bolide.getTurn() == 2)
        {
            roueDirectionnelleDroite.transform.Rotation(vec3(0, 1, 0), -radians(22.0));
            roueDirectionnelleGauche.transform.Rotation(vec3(0, 1, 0), -radians(22.0));
        }
    }
}

void checkFreinAMain(Vehicule &Bolide, ObjectPlan &planInfini, ObjectPlan &lastChild)
{
    Bolide.setStop(false);
    if (planInfini.transform.t.x < -lastChild.getsizeX())
    {
        cout << "HORS LIMITE DROITE" << endl;
        Bolide.setTurn(2);
        Bolide.mulSpeed(vec3(1, 1, 0.8));
        if (Bolide.getSpeed().z < 0.1)
        {
            Bolide.setSpeed(vec3(1, 1, 0));
            Bolide.setStop(true);
        }
        else
        {
            planInfini.transform.Translate(vec3(0, 0, Bolide.getSpeed().z));
            Bolide.transform.Rotation(vec3(0, 1, 0), radians(-Bolide.getSpeed().z * 5));
            Bolide.getChilds()[2]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 5));
            Bolide.getChilds()[3]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 5));
        }
    }
    else
    {
        if (planInfini.transform.t.x > lastChild.getsizeX())
        {
            cout << "HORS LIMITE GAUCHE" << endl;
        }
    }
}
