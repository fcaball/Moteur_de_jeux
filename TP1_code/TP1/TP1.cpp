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
#include <TP1/Camera.hpp>
#include <pthread.h>
#include <chrono>
#include <thread>

#define GRAVITY 9.8

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void updateSpherePos();
void turnPneu(Object3D &roueDirectionnelleDroite, Object3D &roueDirectionnelleGauche, bool reInit);
void checkFreinAMain(Vehicule &Bolide, ObjectPlan &planInfini, ObjectPlan &lastChild);
void InfiniPlan(ObjectPlan &planInfini);
void UpdateObjects(ObjectPlan &plan);
void crash(Object3D &CivilCar, Object3D &voit);
void desseleration(Vehicule &car);
void RandomAcceleration(Vehicule &car);
void vitesseAdv(Vehicule &pilote, Vehicule &adv);
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

float vitesse = 0.05;
float rotateSpeed = 0.05;

Vehicule Bolide;

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
    pthread_t thread;

    if (pthread_create(&thread, NULL, updateFPS, (void *)0) != 0)
    {
        perror("erreur creation thread");
        exit(1);
    }

    Cam = new Camera(vec3(2.0f, 2.0f, 5.0f), vec3(), vec3(0, 1, 0), vec3(0, 0, -1));
    int ObjectState = 1;

    Bolide.transform.Scale(vec3(1, 1, 1));
    Bolide.transform.Translate(vec3(2, 0, 0));
    vec3 translationPneuAVG, translationPneuAVD, translationPneuARG, translationPneuARD;
    // translationPneuAVG = vec3(2,0,0);
    // translationPneuAVD = vec3(2,0,0);
    // translationPneuARG = vec3(2,0,0);
    // translationPneuARD = vec3(2,0,0);
    Object3D roueDirectionnelleDroite;
    Object3D roueDirectionnelleGauche;
    roueDirectionnelleDroite.transform.Translate(vec3(1, 0, -2));
    roueDirectionnelleGauche.transform.Translate(vec3(-1, 0, -2));

    translationPneuAVG = roueDirectionnelleGauche.modifTranslation(translationPneuAVG, vec3(-1, 0, -2));
    translationPneuAVD = roueDirectionnelleGauche.modifTranslation(translationPneuAVD, vec3(1, 0, -2));

    Bolide.addChild(&roueDirectionnelleGauche);
    Bolide.addChild(&roueDirectionnelleDroite);
    ObjectLoaded roueAvantGauche;
    ObjectLoaded pneuAvantGauche;
    pneuAvantGauche.loadObject("./pneu/PneuRoue.obj", 1);
    pneuAvantGauche.loadTexture("../textures/textPneu.jpg");
    roueAvantGauche.addChild(&pneuAvantGauche);

    ObjectLoaded janteAvantGauche;
    janteAvantGauche.loadObject("./pneu/jante.obj", 1);
    janteAvantGauche.loadTexture("../textures/sun.jpg");
    roueAvantGauche.addChild(&janteAvantGauche);

    roueAvantGauche.transform.Scale(vec3(0.5, 0.5, 0.5));
    roueDirectionnelleGauche.addChild(&roueAvantGauche);
    cout << "roueAvantGauche : " << roueDirectionnelleGauche.transform.t[0] << endl;

    ObjectLoaded roueAvantDroite;
    ObjectLoaded janteAvantDroite;
    janteAvantDroite.loadObject("./pneu/jante.obj", 1);
    janteAvantDroite.loadTexture("../textures/sun.jpg");
    roueAvantDroite.addChild(&janteAvantDroite);

    ObjectLoaded pneuAvantDroit;

    pneuAvantDroit.loadObject("./pneu/PneuRoue.obj", 1);
    pneuAvantDroit.loadTexture("../textures/textPneu.jpg");
    roueAvantDroite.addChild(&pneuAvantDroit);

    roueAvantDroite.transform.Rotation(vec3(0, 1, 0), radians(180.0));
    roueAvantDroite.transform.Scale(vec3(0.5, 0.5, 0.5));
    roueDirectionnelleDroite.addChild(&roueAvantDroite);
    cout << "roueAvantDroite : " << roueDirectionnelleDroite.transform.t[0] << endl;
    translationPneuAVG = roueAvantDroite.modifTranslationBis(translationPneuAVG, vec3(0.5, 0.5, 0.5));
    translationPneuAVD = roueAvantGauche.modifTranslationBis(translationPneuAVD, vec3(0.5, 0.5, 0.5));

    ObjectLoaded roueArriereGauche;
    ObjectLoaded pneuArriereGauche;
    pneuArriereGauche.loadObject("./pneu/PneuRoue.obj", 1);
    pneuArriereGauche.loadTexture("../textures/textPneu.jpg");
    roueArriereGauche.addChild(&pneuArriereGauche);

    ObjectLoaded janteArriereGauche;
    janteArriereGauche.loadObject("./pneu/jante.obj", 1);
    janteArriereGauche.loadTexture("../textures/sun.jpg");
    roueArriereGauche.addChild(&janteArriereGauche);
    roueArriereGauche.transform.Translate(vec3(-1, 0, 0));
    roueArriereGauche.transform.Scale(vec3(0.5, 0.5, 0.5));
    Bolide.addChild(&roueArriereGauche);

    ObjectLoaded roueArriereDroite;
    ObjectLoaded pneuArriereDroite;
    pneuArriereDroite.loadObject("./pneu/PneuRoue.obj", 1);
    pneuArriereDroite.loadTexture("../textures/textPneu.jpg");
    roueArriereDroite.addChild(&pneuArriereDroite);

    ObjectLoaded janteArriereDroite;
    janteArriereDroite.loadObject("./pneu/jante.obj", 1);
    janteArriereDroite.loadTexture("../textures/sun.jpg");
    roueArriereDroite.addChild(&janteArriereDroite);
    roueArriereDroite.transform.Translate(vec3(1, 0, 0));
    roueArriereDroite.transform.Rotation(vec3(0, 1, 0), radians(180.0));
    roueArriereDroite.transform.Scale(vec3(0.5, 0.5, 0.5));
    Bolide.addChild(&roueArriereDroite);
    translationPneuARG = roueArriereGauche.modifTranslation(translationPneuARG, vec3(-1, 0, 0));
    translationPneuARD = roueArriereDroite.modifTranslation(translationPneuARD, vec3(1, 0, 0));

    translationPneuARG = roueArriereGauche.modifTranslationBis(translationPneuARG, vec3(0.5, 0.5, 0.5));
    translationPneuARD = roueArriereDroite.modifTranslationBis(translationPneuARD, vec3(0.5, 0.5, 0.5));

    float masseBolide = 2.1;

    ObjectPlan plan1;
    ObjectPlan plan2;
    ObjectPlan plan3;
    ObjectPlan plan4;
    ObjectPlan plan5;
    ObjectPlan plan6;
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

    Vehicule CivilCars;
    CivilCars.transform.Translate(vec3(-1, 0, 0));

    Vehicule voitvoit(vec3(0, 0, 0.4));
    Vehicule voitvoit3(vec3(0, 0, 0.3));
    CivilCars.addChild(&voitvoit);
    CivilCars.addChild(&voitvoit3);

    voitvoit.loadObject("./sphere.off", 0);
    voitvoit.loadTexture("../textures/rock.png");
    voitvoit3.loadObject("./sphere.off", 0);
    voitvoit3.loadTexture("../textures/sun.jpg");

    Vehicule voitvoit2;

    voitvoit2.loadObject("./sphere.off", 0);
    voitvoit2.loadTexture("../textures/sun.jpg");

    vector<vec3> BEvoit1, BEvoit2;

    planInfini.addChild(&plan1);
    planInfini.addChild(&plan2);
    planInfini.addChild(&plan3);
    planInfini.addChild(&plan4);
    planInfini.addChild(&plan5);
    planInfini.addChild(&plan6);

    Object3D racine;

    racine.addChild(&planInfini);
    racine.addChild(&Bolide);
    racine.addChild(&CivilCars);

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
    BEvoit1 = voitvoit.boiteEnglobante();
    BEvoit2 = voitvoit3.boiteEnglobante();
    BE = pneuAvantGauche.boiteEnglobante();
    vec4 min = vec4(BE[0], 1);
    min = Bolide.transform.modelMatrix * min;
    vec4 max = vec4(BE[1], 1);
    cout << "min z : " << min.z << endl;
    max = Bolide.transform.modelMatrix * max;
    min.x = translationPneuAVG.x + min.x;
    max.x = translationPneuAVD.x + max.x;
    cout << "ici : " << min.x << endl;
    cout << "ici : " << max.x << endl;
    min.z = translationPneuAVG.z + min.z;
    max.z = translationPneuARG.z + max.z;
    cout << "min y : " << translationPneuAVG.z << endl;
    cout << "ici : " << min.z << endl;
    cout << "ici : " << max.z << endl;
    vec2 centre = vec2((max.x + min.x) / 2, (max.z + min.z) / 2);
    cout << "voir la: " << centre.x << endl;
    cout << Cam->getPosition()[0] << " ; " << translationPneuARD.z << endl;
    vec3 trans;
    vector<vec3> boite = {{min.x, 0, min.z}, {max.x, 0, max.z}};
    Bolide.setBE(boite);
    cout << "BE = "
         << "(" << BE[0][0] << " ; " << BE[0][1] << " ; " << BE[0][2] << ") ; (" << BE[1][0] << " ; " << BE[1][1] << " ; " << BE[1][2] << ") ; " << endl;
    do
    {
        // BEvoit1 = boiteEnglobante(voitvoit);
        // BEvoit2 = boiteEnglobante(voitvoit2);
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

        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change

        // View matrix : camera/view transformation lookat() utiliser cameraFree_position cameraFree_target cameraFree_up
        // LIBRE
        if (freemode)
        {
            viewMatrix = glm::lookAt(Cam->getPosition(), Cam->getPosition() + Cam->getFront(), Cam->getUp());
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

        if (play)
        {
            // cout<<voitvoit.transform.t[0]<<" ; "<<voitvoit.getVertices()[0][1]<<" ; "<<voitvoit.getVertices()[0][2]<<std::endl ;
            planInfini.transform.Translate(-(Bolide.getSpeed() * Cam->getFront()));
            trans = Bolide.getSpeed() * Cam->getFront();
            // centre = vec2(centre.x+trans.x, centre.y+trans.z);
            std::cout << Cam->getPosition()[0] << std::endl;
            //for (size_t i = 0; i < CivilCars.getChilds().size(); i++)
            //{
                //Vehicule *civilCar = dynamic_cast<Vehicule *>(CivilCars.getChilds()[i]);
                // vector<vec3> BE = civilCar->getBE();
                // vec4 min = vec4(BE[0], 1);
                // min = civilCar->transform.modelMatrix * min;
                // // vec4 max = vec4(BE[1], 1);
                // // max = car.transform.modelMatrix*max;
                // cout << "voir ici eheh : " << min.z << endl;
                //civilCar->transform.Translate(-(Bolide.getSpeed() * Cam->getFront()) + civilCar->getSpeed() * Cam->getFront());
                // cout << civilCar->transform.t[0] << endl;
                // if(min.z<-200){
                // desseleration(*civilCar);
                // RandomAcceleration(*civilCar);
                // civilCar->setSpeed(Bolide.getSpeed());
                //}
                //vitesseAdv(Bolide, *civilCar);
            //}

            //roueAvantGauche.transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
            //roueAvantDroite.transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
            //roueArriereGauche.transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);
            //roueArriereDroite.transform.Rotation(vec3(1, 0, 0), Bolide.getSpeed().z);

            desseleration(Bolide);

            InfiniPlan(planInfini);

            checkFreinAMain(Bolide, planInfini, plan1);
        }

        //     cout << endl;

        //     int debIndice;
        //     vector<unsigned short> carrétrouvé;
        //     for (size
        turnPneu(roueDirectionnelleDroite, roueDirectionnelleGauche, false);
        crash(CivilCars, Bolide);

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
                    Bolide.setSpeed(vec3(0, 0, 2));
                }
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
            vec3 move = glm::normalize(glm::cross(Cam->getFront(), Cam->getUp())) * cameraSpeed;
            Bolide.transform.Translate(-move);
            Cam->setPosition(Cam->getPosition() - move);
            // cout<<"move : "<<Cam->getPosition()[0]<<endl ;
            Bolide.setTurn(1);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !Bolide.getStop())
    {
        if (freemode)
        {
            vec3 move = glm::normalize(glm::cross(Cam->getFront(), Cam->getUp())) * cameraSpeed;
            Bolide.transform.Translate(move);
            Cam->setPosition(Cam->getPosition() + move);
            //  cout<<"move : "<<Cam->getPosition()[0]<<endl ;
            Bolide.setTurn(2);
        }
    }

    if (!(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && !(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
    {
        Bolide.setTurn(0);
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        Cam->getPosition() += vec3(0, 10, 0);
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
    // if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    // {
    //     rotateSpeed += 0.001;
    // }

    // if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    // {
    //     rotateSpeed -= 0.001;
    // }

    // if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    // {
    //     Bolide.transform.Translate(vec3(0.2, 0, 0));
    // }
    // if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    // {
    //     Bolide.transform.Translate(vec3(-0.2, 0, 0));
    // }

    // if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    // {
    //     Bolide.transform.Translate(vec3(0., 0, -0.2));
    // }
    // if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    // {
    //     Bolide.transform.Translate(vec3(0, 0, 0.2));
    // }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        letsgo = true;
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        letsgo = false;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        play = true;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        vec3 newPos = Cam->getPosition();
        newPos.z = 0;
        Cam->setPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        vec3 newPos = Cam->getPosition();
        newPos.z = 5;
        Cam->setPosition(newPos);
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
            Bolide.transform.Rotation(vec3(0, 1, 0), radians(-Bolide.getSpeed().z * 10));
            Bolide.getChilds()[2]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 10));
            Bolide.getChilds()[3]->transform.Rotation(vec3(0, 1, 0), radians(Bolide.getSpeed().z * 10));
        }
    }
    else
    {
        if (Bolide.transform.t.x < -lastChild.getOffsetX())
        {
            cout << "HORS LIMITE GAUCHE" << endl;
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
            // cout<<"Plan Bougé "<<planToMove<<endl;
            planToMove = i + 1;
            if (i == (int)planInfini.getChilds().size())
            {
                planToMove = 1;
                planInfini.transform.t.z -= currentPlan->getsizeY() * (int)planInfini.getChilds().size();
            }
        }
    }
}

void UpdateObjects(ObjectPlan &plan)
{
    for (Object3D *child : plan.getChilds())
    {
        Transform t;
        child->transform = t;

        float randFloatX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        // Generate a random float between a specified range
        float minValX = -plan.getOffsetX();
        float maxValX = plan.getOffsetX();
        float randRangeX = (maxValX - minValX) * randFloatX + minValX;

        float randFloatZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        // Generate a random float between a specified range
        float minValZ = -plan.getOffsetZ();
        float maxValZ = plan.getOffsetZ();
        float randRangeZ = (maxValZ - minValZ) * randFloatZ + minValZ;
        // cout << "ici : " << minValZ << endl;
        child->transform.Translate(vec3(randRangeX, 0, randRangeZ));
    }
}

void crash(Object3D &CivilCar, Object3D &voit)
{
    Vehicule *voiture;
    glm::vec3 pilotePosition = glm::vec3(Cam->getPosition()[0], 0, 0);

    glm::vec3 advPosition;
    vector<glm::vec3> BEadv;
    vector<glm::vec3> BEpilote = voit.getBE();
    // cout << "BE = "
    //<< "(" << BEpilote[0][0] << " ; " << BEpilote[0][1] << " ; " << BEpilote[0][2] << ") ; (" << BEpilote[1][0] << " ; " << BEpilote[1][1] << " ; " << BEpilote[1][2] << ") ; " << endl;
    vec4 min = vec4(BEpilote[0], 1);
    min = voit.transform.modelMatrix * min;
    vec4 max = vec4(BEpilote[1], 1);
    max = voit.transform.modelMatrix * max;
    vec3 diff;
    //  cout<<"yoooooYmin "<<BEpilote[0][1]<<endl;
    //  cout<<"yoooooYmax "<<BEpilote[1][1]<<endl;
    // cout<<"min = "<<min.x<<endl ;
    // cout<<"max = "<<max.x<<endl ;
    for (size_t i = 0; i < CivilCar.getChilds().size(); i++)
    {
        voiture = dynamic_cast<Vehicule *>(CivilCar.getChilds()[i]);
        advPosition = voiture->transform.t;
        BEadv = voiture->getBE();

        // cout << "advPosition z : " << advPosition.z << endl;
        //  cout<<"advPosition x : "<<advPosition.x<<endl ;

        vec4 minV = vec4(BEadv[0], 1.0);
        minV = voiture->transform.modelMatrix * minV;
        vec4 maxV = vec4(BEadv[1], 1.0);
        maxV = voiture->transform.modelMatrix * maxV;
        // cout<<"min = "<<minV.x<<endl ;
        // cout<<"max = "<<maxV.x<<endl ;
        //  cout << "yooooo " << minV[0] <<" ; "<< minV[1] <<" ; "<< minV[2] <<" ; "<< maxV[0] <<" ; "<< maxV[1] <<" ; "<< maxV[2] <<" ; "<< endl;
        vec3 vitesseBolide = Bolide.getSpeed();
        vec3 vitesseAdv = voiture->getSpeed();
        diff = vec3(advPosition.x - Cam->getPosition()[0], 0, advPosition.z);
        if (((Bolide.getTurn() == 1 && min.x < maxV.x) || (Bolide.getTurn() == 2 && max.x > minV.x) || (Bolide.getTurn() == 0 && min.x < maxV.x && max.x > minV.x)) && (/* (advPosition[2]+max.z>-abs(maxV.z - minV.z)) */ advPosition[2] + abs(maxV.z - minV.z) / 2 > min.z) && (advPosition[2] + abs(maxV.z - minV.z) / 2 < max.z) /*  && pilotePosition.z-BEpilote[7].z<advPosition.z+BEadv[0].z */)
        {
            // std::cout<<"can I get some burgers "<<cvbhjn<<std::endl ;
            // cout << min.z << " ; " << max.z << " ou " << minV.z << " ; " << maxV.z << endl;
            // cout << "Position : " << advPosition[2] << endl;

            // cvbhjn++;

            Bolide.setSpeed(vec3(vitesseBolide[0], vitesseBolide[1], vitesseBolide[2] * 0.05));
            // planInfini.transform.Translate(vec3(diff.x, 0,0 ));
            voiture->transform.Translate(diff);
            diff *= -1 / 2;
            // diff.z -= 0.5 ;
            Bolide.transform.Translate(diff);
            Cam->setPosition(Cam->getPosition() + diff);
            voiture->setSpeed(vec3(vitesseAdv[0], vitesseAdv[1], vitesseAdv[2] * 1.05));
        }
    }
}

void desseleration(Vehicule &car)
{

    car.addSpeed(vec3(0, 0, -(0.005 * car.getSpeed().z * car.getSpeed().z)));
    cout << "laaaaaaaaaaaaaaaaaa : " << car.getSpeed().z << endl;
    if (car.getSpeed().z < 0.1 && !car.getStop())
    {
        car.addSpeed(vec3(0, 0, 0.1));
    }
}

void RandomAcceleration(Vehicule &car)
{

    int k = rand() % 2;
    if (k == 1)
    {
        car.addSpeed(vec3(0, 0, 0.01));
        if (car.getSpeed().z > 2)
        {
            car.setSpeed(vec3(0, 0, 2));
        }
    }
}

void vitesseAdv(Vehicule &pilote, Vehicule &adv)
{
    vec3 advPosition = adv.transform.t;
    cout<<"ehehehehe : "<<pilote.transform.t.x ;
    vec3 vitessePilote = pilote.getSpeed();
    vector<glm::vec3> BEadv = adv.getBE();
    // cout << "BE = "
    //<< "(" << BEpilote[0][0] << " ; " << BEpilote[0][1] << " ; " << BEpilote[0][2] << ") ; (" << BEpilote[1][0] << " ; " << BEpilote[1][1] << " ; " << BEpilote[1][2] << ") ; " << endl;
    vec4 min = vec4(BEadv[0], 1);
    min = adv.transform.modelMatrix * min;
    vec4 max = vec4(BEadv[1], 1);
    max = adv.transform.modelMatrix * max;
    if (advPosition.z < -20 && vitessePilote.z>1.5)
    {
        adv.setSpeed(vec3(0, 0, vitessePilote.z + advPosition.z*0.01));

    }
    // else if (advPosition.z > 10)
    else if (advPosition.z > 10){
        adv.setSpeed(vec3(0, 0, vitessePilote.z + 0.01));
    }
    else if(advPosition.z < -10 && advPosition.z > -20 && vitessePilote.z>1.5 && pilote.transform.t.x>min.x && pilote.transform.t.x<max.x && vitessePilote.z>1){
        pilote.setSpeed(vec3(0,0,vitessePilote.z+0.5));
    }
    // else
    // {
    //     adv.setSpeed(vec3(0, 0, vitessePilote.z));
    // }
}