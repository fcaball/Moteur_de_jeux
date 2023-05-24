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
#include <Projet/ObjectPlan.hpp>
#include <Projet/Vehicule.hpp>
#include <Projet/Camera.hpp>
#include <pthread.h>
#include <chrono>
#include <thread>

#define GRAVITY 9.8

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void turnPneu(Object3D &roueDirectionnelleDroite, Object3D &roueDirectionnelleGauche, bool reInit);
void checkFreinAMain(Vehicule &Bolide, ObjectPlan &planInfini, ObjectPlan &lastChild);
void InfiniPlan(ObjectPlan &planInfini);
void crash(Object3D &CivilCar, Vehicule &voit);
void desseleration(Vehicule &car);
void vitesseAdv(Vehicule &pilote, Vehicule &adv);
void crashAdv(Object3D &voitures, Vehicule &bol);
void acceleration(Vehicule &voiture, float v);
void depassement(Object3D &voitures, Vehicule &bol);
void createVoiture(Vehicule &voiture, int Joueur);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera *Cam;

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
ObjectLoaded testSphereSky;

bool orbitmode = false;
bool presentationmode = false;
bool freemode = true;

bool play = false;

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
GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Couleur du brouillard (R, G, B, A)

float vitesse = 0.05;
float rotateSpeed = 0.05;

Vehicule Bolide(1.5, 2.0);

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
    vector<vec3> BE;
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
    window = glfwCreateWindow(1920, 1080, "Projet", NULL, NULL);
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

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // Dark blue background
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Enable depth test
    glDisable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


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
    pthread_t thread;

    if (pthread_create(&thread, NULL, updateFPS, (void *)0) != 0)
    {
        perror("erreur creation thread");
        exit(1);
    }

    ////////////////NE PAS VENIR PLUS HAUT

    Cam = new Camera(vec3(0.0f, 2.0f, 6.0f), vec3(), vec3(0, 1, 0), vec3(0, 0, -1));
    int ObjectState = 1;

    Bolide.transform.Scale(vec3(1, 1, 1));
    Bolide.transform.Translate(vec3(2, 0, 0));

    createVoiture(Bolide,0);
    Bolide.addChild(Cam);

    Vehicule CivilCars;
    CivilCars.transform.Translate(vec3(-1, 0, 0));

    Vehicule voitvoit(169.0, 19.76);
    Vehicule voitvoit3(169.0, 19.76);
    createVoiture(voitvoit,1);
    createVoiture(voitvoit3,2);

    CivilCars.addChild(&voitvoit);
    CivilCars.addChild(&voitvoit3);

    float masseBolide = 2.1;

    ObjectPlan plan1;
    ObjectPlan plan2;
    ObjectPlan plan3;
    ObjectPlan plan4;
    ObjectPlan plan5;
    ObjectPlan plan6;
    ObjectPlan plan7;
    ObjectPlan plan8;
    ObjectPlan plan9;
    ObjectPlan plan10;
    ObjectPlan plan11;
    ObjectPlan plan12;
    int resolutionX = 2;
    int resolutionY = 2;
    int sizeX = 16;
    int sizeY = 16;
    plan1.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan1.loadTexture("../textures/Route.png");
    plan1.transform.Translate(vec3(0, 0, -(float)(sizeY / 2)));
    plan2.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan2.loadTexture("../textures/Route.png");
    plan2.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + sizeY)));
    plan3.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan3.loadTexture("../textures/Route.png");
    plan3.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 2 * sizeY)));
    plan4.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan4.loadTexture("../textures/Route.png");
    plan4.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 3 * sizeY)));
    plan5.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan5.loadTexture("../textures/Route.png");
    plan5.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 4 * sizeY)));
    plan6.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan6.loadTexture("../textures/Route.png");
    plan6.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 5 * sizeY)));
    plan7.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan7.loadTexture("../textures/Route.png");
    plan7.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 6 * sizeY)));
    plan8.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan8.loadTexture("../textures/Route.png");
    plan8.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 7 * sizeY)));
    plan9.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan9.loadTexture("../textures/Route.png");
    plan9.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 8 * sizeY)));
    plan10.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan10.loadTexture("../textures/Route.png");
    plan10.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 9 * sizeY)));
    plan11.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan11.loadTexture("../textures/Route.png");
    plan11.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 10 * sizeY)));
    plan12.makePlan(resolutionX, resolutionY, sizeX, sizeY, (float)(sizeX / 2), 0, 1, false, "../textures/Heightmap_Mountain.png");
    plan12.loadTexture("../textures/Route.png");
    plan12.transform.Translate(vec3(0, 0, -(float)((sizeY / 2) + 11 * sizeY)));

    planInfini.addChild(&plan1);
    planInfini.addChild(&plan2);
    planInfini.addChild(&plan3);
    planInfini.addChild(&plan4);
    planInfini.addChild(&plan5);
    planInfini.addChild(&plan6);
    planInfini.addChild(&plan7);
    planInfini.addChild(&plan8);
    planInfini.addChild(&plan9);
    planInfini.addChild(&plan10);
    planInfini.addChild(&plan11);
    planInfini.addChild(&plan12);

    testSphereSky.loadObject("../models/sphere.off", 0);
    testSphereSky.loadTexture("../textures/spheremap.jpg");
    testSphereSky.transform.Scale(vec3(160, 160, 160));
    testSphereSky.transform.Rotation(vec3(0, 1, 0), radians(-21.0));
    Object3D racine;

    racine.addChild(&planInfini);
    racine.addChild(&Bolide);
    racine.addChild(&CivilCars);
    racine.addChild(&testSphereSky);
    voitvoit.transform.Translate(vec3(0, 0, -10));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 10.0f);
    glFogf(GL_FOG_END, 50.0f);
    glFogfv(GL_FOG_COLOR, fogColor);
    do
    {

        //  Measure speed
        //  per-frame time logic
        //  --------------------
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
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, -10.0f);
        glFogf(GL_FOG_END, -50.0f);
        glFogfv(GL_FOG_COLOR, fogColor);


        if (play)

        {

            planInfini.transform.Translate(-(Bolide.getSpeed() * Cam->getFront()));
            for (size_t i = 0; i < CivilCars.getChilds().size(); i++)
            {
                Vehicule *civilCar = dynamic_cast<Vehicule *>(CivilCars.getChilds()[i]);
                if (!civilCar->getStop())
                {
                    civilCar->transform.Translate((-(Bolide.getSpeed() * Cam->getFront())) + civilCar->getSpeed() * Cam->getFront());
                    desseleration(*civilCar);
                    civilCar->getChilds()[0]->transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
                    civilCar->getChilds()[1]->transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
                    civilCar->getChilds()[2]->transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
                    civilCar->getChilds()[3]->transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
                    vitesseAdv(Bolide, *civilCar);
                    acceleration(*civilCar, 1.5);
                }
                else
                {
                    civilCar->transform.Translate((-(Bolide.getSpeed() * Cam->getFront())));
                }
            }
            crashAdv(CivilCars, Bolide);
            depassement(CivilCars, Bolide);

            Bolide.getChilds()[3]->transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
            Bolide.getChilds()[2]->transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);

            desseleration(Bolide);
            InfiniPlan(planInfini);

            checkFreinAMain(Bolide, planInfini, plan1);
        }

        turnPneu(*Bolide.getChilds()[1], *Bolide.getChilds()[0], false);

        crash(CivilCars, Bolide);

        // On actualise tout notre graphe de scène
        racine.updateMeAndChilds();

        // Puis on définit les caractériqtiques de notre caméra pour éviter
        viewMatrix = glm::lookAt(Cam->getPosition(), Cam->getPosition() + Cam->getFront(), Cam->getUp());

        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        projMatrix = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 250.0f);

        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(programID, "viewM"), 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projM"), 1, GL_FALSE, &projMatrix[0][0]);

        racine.draw(programID);

        turnPneu(*Bolide.getChilds()[1], *Bolide.getChilds()[0], true);

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

float angleSM = 0;
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (freemode)
        {
            if (!Bolide.getStop())
            {
                acceleration(Bolide, Bolide.getVMax());
            }
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
                    Bolide.setSpeed(vec3(0, 0, 0.1));
                }
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !Bolide.getStop())
    {
        if (freemode)
        {
            vec3 move = glm::normalize(glm::cross(Cam->getFront(), Cam->getUp())) * (10 * deltaTime);
            Bolide.transform.Translate(-move);
            Bolide.setTurn(1);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !Bolide.getStop())
    {
        if (freemode)
        {
            vec3 move = glm::normalize(glm::cross(Cam->getFront(), Cam->getUp())) * (10 * deltaTime);
            Bolide.transform.Translate(move);
            Bolide.setTurn(2);
        }
    }

    if (!(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && !(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
    {
        Bolide.setTurn(0);
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

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        play = true;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        if(!Cam->getFirstPerson()){
            Cam->setDepPosition(Cam->getDepPosition()+vec3(0,0,-6));
            Cam->setFirstPerson(true);

        }
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if(Cam->getFirstPerson()){
            Cam->setDepPosition(Cam->getDepPosition()+vec3(0,0,6));
            Cam->setFirstPerson(false);

        }
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        Transform t;
        Transform t1;
        Bolide.setStop(true);
        Bolide.transform = t;
        Bolide.transform.Translate(vec3(2, 0, 0));
        planInfini.transform = t1;
        for (size_t i = 0; i < planInfini.getChilds().size(); i++)
        {
            Transform t2;
            ObjectPlan *currentPlan = dynamic_cast<ObjectPlan *>(planInfini.getChilds()[i]);

            currentPlan->transform = t2;
            currentPlan->transform.Translate(vec3(0, 0, -((float)(currentPlan->getsizeY() / 2) + i * currentPlan->getsizeY())));
            Cam->setPosition(Cam->getDepPosition());
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
    if (Bolide.transform.t.x > lastChild.getOffsetX())
    {
        std::cout << "HORS LIMITE DROITE" << endl;
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
            Bolide.transform.Rotation(vec3(0, 1, 0), radians(-Bolide.getSpeed().z * 10));
            Bolide.getChilds()[2]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 10));
            Bolide.getChilds()[3]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 10));
        }
    }
    else
    {
        if (Bolide.transform.t.x < -lastChild.getOffsetX())
        {
            std::cout << "HORS LIMITE GAUCHE" << endl;
            Bolide.setTurn(1);
            Bolide.mulSpeed(vec3(1, 1, 0.8));
            if (Bolide.getSpeed().z < 0.1)
            {
                Bolide.setSpeed(vec3(1, 1, 0));
                Bolide.setStop(true);
            }
            else
            {
                planInfini.transform.Translate(vec3(0, 0, Bolide.getSpeed().z));
                Bolide.transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 5));
                Bolide.getChilds()[2]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 10));
                Bolide.getChilds()[3]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 10));
            }
        }
    }
}

void InfiniPlan(ObjectPlan &planInfini)
{

    for (size_t i = 1; i <= planInfini.getChilds().size(); i++)
    {

        ObjectPlan *currentPlan = dynamic_cast<ObjectPlan *>(planInfini.getChilds()[i - 1]);
        if (planInfini.transform.t.z > (float)(currentPlan->getsizeY() / 2) + (i - 1) * currentPlan->getsizeY() + 2 && planToMove == i)
        {

            currentPlan->transform.Translate(vec3(0, 0, -(currentPlan->getsizeY() * (int)planInfini.getChilds().size())));
            // std::cout << "Plan Bougé " << planToMove << endl;
            planToMove = i + 1;
            if (i == (int)planInfini.getChilds().size())
            {
                planToMove = 1;
                planInfini.transform.t.z -= currentPlan->getsizeY() * (int)planInfini.getChilds().size();
            }
        }
    }
}


void crash(Object3D &CivilCar, Vehicule &voit)
{

    Vehicule *voiture;
    glm::vec3 pilotePosition = glm::vec3(Cam->getPosition()[0], 0, 0);

    glm::vec3 advPosition;
    vector<glm::vec3> BEadv;
    vector<glm::vec3> BEpilote = voit.getBE();

    vec4 min = vec4(BEpilote[0], 1);
    min = voit.transform.modelMatrix * min;
    vec4 max = vec4(BEpilote[1], 1);
    max = voit.transform.modelMatrix * max;
    vec3 diff;
    vec3 vitesseRelative;
    vec4 minV, maxV;
    vec3 vitesseBolide, vitesseAdv;
    vitesseBolide = voit.getSpeed();
    for (size_t i = 0; i < CivilCar.getChilds().size(); i++)
    {

        voiture = dynamic_cast<Vehicule *>(CivilCar.getChilds()[i]);
        advPosition = voiture->transform.t;
        BEadv = voiture->getBE();


        minV = vec4(BEadv[0], 1.0);
        minV = voiture->transform.modelMatrix * minV;
        maxV = vec4(BEadv[1], 1.0);
        maxV = voiture->transform.modelMatrix * maxV;

        vitesseAdv = voiture->getSpeed();
        diff = vec3(advPosition.x - Cam->getPosition()[0], 0, 0);
        normalize(diff);
     
        if ((min.x > minV.x && min.x < maxV.x && min.z > minV.z && min.z < maxV.z) || (max.x > minV.x && max.x < maxV.x && min.z > minV.z && min.z < maxV.z) ||
            (min.x > minV.x && min.x < maxV.x && max.z > minV.z && max.z < maxV.z) || (max.x > minV.x && max.x < maxV.x && max.z > minV.z && max.z < maxV.z))
        {
           
            vitesseRelative = vitesseBolide - vitesseAdv;
            if (vitesseRelative.z < 0)
            {
               
                voiture->transform.Translate(vec3(0, 0, 1));
                voiture->setSpeed(vec3(0, 0, 0));
                Bolide.setSpeed(vec3(0, 0, 0.2));
            }
            if (vitesseRelative.z > 0)
            {

                Bolide.setSpeed(vec3(0, 0, 0));
                voiture->transform.Translate(vec3(diff.x, 0, -1));
                voiture->setSpeed(vec3(0, 0, 0.1));
            }
        }
    }
}


void desseleration(Vehicule &car)
{
    car.addSpeed(vec3(0, 0, -(0.005 * car.getSpeed().z * car.getSpeed().z)));
    if (car.getSpeed().z < 0.1 && !car.getStop())
    {
        car.addSpeed(vec3(0, 0, 0.1));
    }
}

void acceleration(Vehicule &car)
{
}


void crashAdv(Object3D &CivilCar, Vehicule &voit)
{
    vector<Object3D *> childs = CivilCar.getChilds();
    Vehicule *voiture1, *voiture2;
    int taille = CivilCar.getChilds().size();
    vector<glm::vec3> BEvoit1;
    vector<glm::vec3> BEvoit2;
    vec4 minvoit1, minvoit2, maxvoit1, maxvoit2;
    vec3 vitesse1, vitesse2;
    vec3 vitesseRelative;
    for (size_t i = 0; i < taille; i++)
    {

        voiture1 = dynamic_cast<Vehicule *>(childs[i]);
        if (!voiture1->getStop())
        {
            BEvoit1 = voiture1->getBE();
            vitesse1 = voiture1->getSpeed();
            minvoit1 = vec4(BEvoit1[0], 1.0);
            minvoit1 = voiture1->transform.modelMatrix * minvoit1;
            maxvoit1 = vec4(BEvoit1[1], 1.0);
            maxvoit1 = voiture1->transform.modelMatrix * maxvoit1;

            for (int j = 0; j < taille; j++)
            {
                if (j > i)
                {

                    voiture2 = dynamic_cast<Vehicule *>(childs[j]);
                    BEvoit2 = voiture2->getBE();
                    vitesse2 = voiture2->getSpeed();
                    minvoit2 = vec4(BEvoit2[0], 1.0);
                    minvoit2 = voiture2->transform.modelMatrix * minvoit2;
                    maxvoit2 = vec4(BEvoit2[1], 1.0);
                    maxvoit2 = voiture2->transform.modelMatrix * maxvoit2;
                    vitesseRelative = vitesse1 - vitesse2;
                    if ((minvoit1.x >= minvoit2.x && minvoit1.x <= maxvoit2.x && minvoit1.z >= minvoit2.z && minvoit1.z <= maxvoit2.z) || (maxvoit1.x >= minvoit2.x && maxvoit1.x <= maxvoit2.x && minvoit1.z >= minvoit2.z && minvoit1.z <= maxvoit2.z) ||
                        (minvoit1.x >= minvoit2.x && minvoit1.x <= maxvoit2.x && maxvoit1.z >= minvoit2.z && maxvoit1.z <= maxvoit2.z) || (maxvoit1.x >= minvoit2.x && maxvoit1.x <= maxvoit2.x && maxvoit1.z >= minvoit2.z && maxvoit1.z <= maxvoit2.z))
                    {
                        std::cout << "CRASH     !!! " << endl;
                        if (vitesseRelative.z > 0)
                        {
                            voiture1->setSpeed(vec3(vitesse1.x, vitesse1.y, 0.98 * vitesse1.z));
                            voiture2->setSpeed(vec3(vitesse2.x, vitesse2.y, 0.96 * vitesse2.z));
                        }
                        if (vitesseRelative.z < 0)
                        {
                            voiture2->setSpeed(vec3(vitesse2.x, vitesse2.y, 0.98 * vitesse2.z));
                            voiture1->setSpeed(vec3(vitesse1.x, vitesse1.y, 0.96 * vitesse1.z));
                        }
                    }
                }
            }
        }
    }
}

void depassement(Object3D &CivilCar, Vehicule &voit)
{
    vector<Object3D *> childs = CivilCar.getChilds();
    Vehicule *voiture1, *voiture2;
    int taille = CivilCar.getChilds().size();
    vector<glm::vec3> BEvoit1;
    vector<glm::vec3> BEvoit2;
    vec4 minvoit1, minvoit2, maxvoit1, maxvoit2;
    vec3 vitesse1, vitesse2;
    vec3 vitesseRelative;
    vector<glm::vec3> BEpilote = voit.getBE();

    vec4 minPilote = vec4(BEpilote[0], 1);
    minPilote = voit.transform.modelMatrix * minPilote;
    vec4 maxPilote = vec4(BEpilote[1], 1);
    maxPilote = voit.transform.modelMatrix * maxPilote;
    for (size_t i = 0; i < taille; i++)
    {
        voiture1 = dynamic_cast<Vehicule *>(childs[i]);
        if (!voiture1->getStop())
        {
            BEvoit1 = voiture1->getBE();
            vitesse1 = voiture1->getSpeed();
            minvoit1 = vec4(BEvoit1[0], 1.0);
            minvoit1 = voiture1->transform.modelMatrix * minvoit1;
            maxvoit1 = vec4(BEvoit1[1], 1.0);
            maxvoit1 = voiture1->transform.modelMatrix * maxvoit1;
            if (maxvoit1.z < -170)
            {
                voiture1->setSpeed(vec3(0, 0, 0));
            }
            if (maxvoit1.z > 15)
            {
                voiture1->addSpeed(vec3(0, 0, 0.01));
            }
            for (int j = 0; j < taille; j++)
            {
                if (j < i)
                {

                    voiture2 = dynamic_cast<Vehicule *>(childs[j]);
                    BEvoit2 = voiture2->getBE();
                    vitesse2 = voiture2->getSpeed();
                    minvoit2 = vec4(BEvoit2[0], 1.0);
                    minvoit2 = voiture2->transform.modelMatrix * minvoit2;
                    maxvoit2 = vec4(BEvoit2[1], 1.0);
                    maxvoit2 = voiture2->transform.modelMatrix * maxvoit2;
                    vitesseRelative = vitesse1 - vitesse2;
                    if ((minvoit1.x + maxvoit1.x) / 2 > minvoit2.x && (minvoit1.x + maxvoit1.x) / 2 < maxvoit2.x && maxvoit1.z > minvoit2.z + 50 )
                    {
                        std::cout << "crashAdv IAAAAA     !!! " << endl;
                        voiture1->addSpeed(vec3(0, 0, 0.001));
                    }
                    if ((minvoit2.x + maxvoit2.x) / 2 < 0 && minvoit1.x < maxvoit2.x + 1 && maxvoit1.z < minvoit2.z + 50 && minvoit1.z > maxvoit2.z)
                    {
                        if (minPilote.z - 10 > maxvoit1.z)
                        {
                            voiture1->transform.Translate(vec3(0.02, 0, 0));
                            voiture1->addSpeed(vec3(0, 0, 0.001));

                        }
                    }
                    if ((minvoit2.x + maxvoit2.x) / 2 > 0 && maxvoit1.x > minvoit2.x - 1 && maxvoit1.z < minvoit2.z + 50 && minvoit1.z > maxvoit2.z)
                    {
                        std::cout << "DANGEEER    !!! " << endl;
                        if (minPilote.z - 10 > maxvoit1.z)
                        {
                            voiture1->transform.Translate(vec3(-0.02, 0, 0));
                            voiture1->addSpeed(vec3(0, 0, 0.001));
                        }
                    }
                }
            }
            voiture2 = &Bolide;
            BEvoit2 = voiture2->getBE();
            vitesse2 = voiture2->getSpeed();
            minvoit2 = vec4(BEvoit2[0], 1.0);
            minvoit2 = voiture2->transform.modelMatrix * minvoit2;
            maxvoit2 = vec4(BEvoit2[1], 1.0);
            maxvoit2 = voiture2->transform.modelMatrix * maxvoit2;
            std::cout << "minVoit2 z BOLIDE : " << minvoit2.z << endl;
            std::cout << "maxVoit2 z BOLIDE : " << maxvoit2.z << endl;
            std::cout << "minVoit1 z : " << minvoit1.z << endl;
            std::cout << "maxVoit1 z : " << maxvoit1.z << endl;
            if ((minPilote.x + maxPilote.x) / 2 < 0 && minvoit1.x < maxPilote.x + 1 && maxvoit1.z < minPilote.z + 50 && minvoit1.z > maxPilote.z)
            {
                std::cout << "DANGEEER    !!! " << endl;

                voiture1->transform.Translate(vec3(0.02, 0, 0));
                voiture1->addSpeed(vec3(0, 0, 0.001));
            }
            if ((minPilote.x + maxPilote.x) / 2 > 0 && maxvoit1.x > minPilote.x - 1 && maxvoit1.z < minPilote.z + 50 && minvoit1.z > maxPilote.z)
            {
                std::cout << "DANGEEER    !!! " << endl;
                voiture1->transform.Translate(vec3(-0.02, 0, 0));
                voiture1->addSpeed(vec3(0, 0, 0.001));

            }
            if (minvoit1.x < -9 || maxvoit1.x > 9)
            {
                voiture1->setStop(true);
            }
        }
    }
}

void vitesseAdv(Vehicule &pilote, Vehicule &adv)
{
    vec3 advPosition = adv.transform.t;

    vec3 vitessePilote = pilote.getSpeed();
    vector<glm::vec3> BEadv = adv.getBE();
    vec4 min = vec4(BEadv[0], 1);
    min = adv.transform.modelMatrix * min;
    vec4 max = vec4(BEadv[1], 1);
    max = adv.transform.modelMatrix * max;
    vec3 positionPilote = pilote.transform.t;
    vector<glm::vec3> BE = pilote.getBE();
    if (advPosition.z < -100 && vitessePilote.z > 0.8)
    {
        adv.setSpeed(vec3(0, 0, vitessePilote.z - 0.01));
    }
    if (advPosition.z > 20 && vitessePilote.z > 0.8)
    {
        adv.setSpeed(vec3(0, 0, vitessePilote.z + 0.1));
    }
    if (advPosition.z < 0 && advPosition.z > -100 && Cam->getPosition().x > min.x && Cam->getPosition().x < max.x && vitessePilote.z > 0.8)
    {
        adv.setSpeed(vec3(0, 0, vitessePilote.z + 1 / advPosition.z));

    }

}

void acceleration(Vehicule &voiture, float vitesseMax)
{
    vec3 vitesse = voiture.getSpeed();
    if (vitesse.z < vitesseMax * 2 / 3)
    {
        voiture.setSpeed(vec3(vitesse.x, vitesse.y, vitesse.z + 0.005));
    }
    else if (vitesse.z < vitesseMax)
    {
        voiture.setSpeed(vec3(vitesse.x, vitesse.y, vitesse.z + 0.001));
    }
}


void createVoiture(Vehicule &voiture, int Joueur)
{
    Object3D *roueDirectionnelleDroite = new Object3D();

    Object3D *roueDirectionnelleGauche = new Object3D();

    roueDirectionnelleDroite->transform.Translate(vec3(0.9, 0, -0.95));
    roueDirectionnelleGauche->transform.Translate(vec3(-0.9, 0, -0.95));

    voiture.addChild(roueDirectionnelleGauche);
    voiture.addChild(roueDirectionnelleDroite);
    ObjectLoaded *roueAvantGauche = new ObjectLoaded();
    roueAvantGauche->loadObject("../models/pneu.obj", 1);
    roueAvantGauche->loadTexture("../textures/textRoue.png");
    roueAvantGauche->transform.Scale(vec3(0.4, 0.45, 0.45));
    roueDirectionnelleGauche->addChild(roueAvantGauche);

    ObjectLoaded *roueAvantDroite = new ObjectLoaded();
    roueAvantDroite->loadObject("../models/pneu.obj", 1);
    roueAvantDroite->loadTexture("../textures/textRoue.png");
    roueAvantDroite->transform.Rotation(vec3(0, 1, 0), radians(180.0));
    roueAvantDroite->transform.Scale(vec3(0.4, 0.45, 0.45));
    roueDirectionnelleDroite->addChild(roueAvantDroite);

    ObjectLoaded *roueArriereGauche = new ObjectLoaded();
    roueArriereGauche->loadObject("../models/pneu.obj", 1);
    roueArriereGauche->loadTexture("../textures/textRoue.png");
    roueArriereGauche->transform.Translate(vec3(-0.9, 0., 0.95));
    roueArriereGauche->transform.Scale(vec3(0.4, 0.45, 0.45));
    voiture.addChild(roueArriereGauche);

    ObjectLoaded *roueArriereDroite = new ObjectLoaded();
    roueArriereDroite->loadObject("../models/pneu.obj", 1);
    roueArriereDroite->loadTexture("../textures/textRoue.png");
    roueArriereDroite->transform.Translate(vec3(0.9, 0., 0.95));
    roueArriereDroite->transform.Rotation(vec3(0, 1, 0), radians(180.0));
    roueArriereDroite->transform.Scale(vec3(0.4, 0.45, 0.45));
    voiture.addChild(roueArriereDroite);

    ObjectLoaded *carrosserie = new ObjectLoaded();
    carrosserie->loadObject("../models/Jeep.obj", 1);
    if (Joueur == 0)
    {
        carrosserie->loadTexture("../textures/textJeepB.png");
    }
    else if (Joueur == 1)
    {
        carrosserie->loadTexture("../textures/textJeepG.png");
    }
    else
    {
        carrosserie->loadTexture("../textures/textJeepO.png");
    }
    carrosserie->transform.Translate(vec3(0, -0.35, 0));
    carrosserie->transform.Scale(vec3(0.6, 0.6, 0.6));
    voiture.addChild(carrosserie);

    vector<vec3> BE = carrosserie->boiteEnglobante();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            BE[i][j] = BE[i][j] * 0.6;
        }
    }
    voiture.setBE(BE);
}
