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
#include <TP1/ObjectLoaded.hpp>
#include <pthread.h>
#include <chrono>
#include <thread>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void updateSpherePos();
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraFree_position = glm::vec3(0.0f, 1.0f, 3.0f);
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

ObjectPlan *planHeightMap;

int resolutionX = 2;
int sizeX = 1;
int resolutionY = 2;
int sizeY = 1;

float vitesse = 0.05;
float rotateSpeed = 0.05;

int renderDistance = 20;

ObjectLoaded Soleil;
vec3 centreSphere = vec3(0., 0, 0);

void newPlan(Object3D &Parent, vec3 &offSetPrec)
{

    if (cameraFree_position.z < -offSetPrec.z + renderDistance)
    {
        for (size_t i = 0; i < 5; i++)
        {
            Object3D *plan2 = new ObjectPlan(2, 2, 4, 4, offSetPrec.x + i - 2, offSetPrec.z + 1, true);
            plan2->loadTexture("../textures/rock.png");
            // Parent.addChild(*plan2);
        }
        for (size_t i = 0; i < Parent.getChilds().size(); i++)
        {
            vector<vec3> verticesfils = Parent.getChilds()[i]->getVertices();
            if (verticesfils[verticesfils.size() - 1].z > cameraFree_position.z + 3)
            {
                Parent.removeChild(i);
            }
        }

        offSetPrec.z++;
    }
}

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
    std::string filename("chair.off");
    // loadOFF(filename, indexed_vertices, indices, triangles );

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    // For speed computation
    double lastTime = glfwGetTime();

    Soleil.loadObject("./newbunnyPQ10.off");
    int ObjectState = 1;
    Soleil.loadTexture("../textures/sun.jpg");
    Soleil.transform.Translate(vec3(0, 0, 0));
    Soleil.transform.Scale(vec3(1, 1, 1));

    ObjectLoaded Terre;
    Terre.loadObject("./sphere.off");
    Terre.loadTexture("../textures/earth.jpg");

    float rayonTerre = 12;
    float rayonLune = 5;

    // Soleil.addChild(Terre);
    Terre.transform.Scale(vec3(0.2, 0.2, 0.2));
    Terre.transform.Translate(vec3(rayonTerre, 0., 0.));
    // Terre.transform.Rotation(vec3(0, 0, 1), glm::radians(23.44f));

    ObjectLoaded Lune;
    Lune.loadObject("./sphere.off");
    Lune.loadTexture("../textures/moon.jpg");

    Terre.addChild(&Lune);
    Lune.transform.Scale(vec3(0.5, 0.5, 0.5));
    Lune.transform.Translate(vec3(rayonLune, 0, 0));
    ObjectPlan plan2(resolutionX, resolutionY, 4, 4, 2, 2, true, "../textures/Heightmap_Mountain.png",1);
    plan2.loadTexture("../textures/snowrocks.png");

    planHeightMap = &plan2;

    Object3D planInfini;
    planInfini.addChild(&Soleil);
    vec3 currentOffSet = vec3(0, 0, 0);

    planInfini.addChild(&plan2);

    pthread_t thread;

    if (pthread_create(&thread, NULL, updateFPS, (void *)0) != 0)
    {
        perror("erreur creation thread");
        exit(1);
    }

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

        // Terre.transform.Translate(vec3(-rayonTerre, 0, 0));
        // Terre.transform.Rotation(vec3(0, 1, 0), glm::radians(2.0f));
        // Terre.transform.Translate(vec3(rayonTerre, 0, 0));

        // Lune.transform.Translate(vec3(-rayonLune, 0, 0));
        // Lune.transform.Rotation(vec3(0, 1, 0), glm::radians(2.0f));
        // Lune.transform.Translate(vec3(rayonLune, 0, 0));

        // SPHÈRE QUI SE BALADE SUR LE TERRAIN
        /* vector<unsigned short> indices = plan2.getIndices();
        vector<vec3> vertices = plan2.getVertices();
        vector<unsigned short> goodTri;

        float Goodalpha1=0;
        float Goodalpha2=0;
        float Goodalpha0=0;

        for (size_t i = 0; i < indices.size(); i += 6)
        {
            if (vertices[indices[i]].x > centreSphere.x && vertices[indices[i]].z > centreSphere.z ||
                vertices[indices[i + 1]].x > centreSphere.x && vertices[indices[i + 1]].z > centreSphere.z ||
                vertices[indices[i + 2]].x > centreSphere.x && vertices[indices[i + 2]].z > centreSphere.z)
            {
                vec3 vect1 = vertices[indices[i + 1]] - vertices[indices[i]];
                vec3 vect2 = vertices[indices[i + 2]] - vertices[indices[i]];
                vec3 vect3 = centreSphere - vertices[indices[i]];

                float dot11 = glm::dot(vect1, vect1);
                float dot12 = glm::dot(vect1, vect2);
                float dot22 = glm::dot(vect2, vect2);
                float dot31 = glm::dot(vect3, vect1);
                float dot32 = glm::dot(vect3, vect2);
                float denom = dot11 * dot22 - dot12 * dot12;
                float alpha1 = (float)(dot22 * dot31 - dot12 * dot32) / (float)denom;
                float alpha2 = (float)(dot11 * dot32 - dot12 * dot31) / (float)denom;
                float alpha0 = 1.0f - alpha1 - alpha2;
                if (alpha0 < 1 && alpha1 < 1 && alpha2 < 1 && alpha0 > 0 && alpha1 > 0 && alpha2 > 0)
                {
                    goodTri.push_back(indices[i]);
                    goodTri.push_back(indices[i + 1]);
                    goodTri.push_back(indices[i + 2]);
                    Goodalpha1 = alpha1;
                    Goodalpha2 = alpha2;
                    Goodalpha0 = alpha0;
                }
                else
                {
                    goodTri.push_back(indices[i + 3]);
                    goodTri.push_back(indices[i + 3 + 1]);
                    goodTri.push_back(indices[i + 3 + 2]);
                    vec3 vect1 = vertices[indices[i+3 + 1]] - vertices[indices[i+3]];
                    vec3 vect2 = vertices[indices[i +3+ 2]] - vertices[indices[i+3]];
                    vec3 vect3 = centreSphere - vertices[indices[i+3]];

                    float dot11 = glm::dot(vect1, vect1);
                    float dot12 = glm::dot(vect1, vect2);
                    float dot22 = glm::dot(vect2, vect2);
                    float dot31 = glm::dot(vect3, vect1);
                    float dot32 = glm::dot(vect3, vect2);
                    float denom = dot11 * dot22 - dot12 * dot12;
                    Goodalpha1 =  (float)(dot22 * dot31 - dot12 * dot32) / (float)denom;
                    Goodalpha2 =  (float)(dot11 * dot32 - dot12 * dot31) / (float)denom;
                    Goodalpha0 =  1.0f - alpha1 - alpha2;
                }
            }
        }

        vec3 n = cross(centreSphere - vertices[goodTri[1]], centreSphere - vertices[goodTri[2]]);
        n = normalize(n);
        float normecentre_centreprojete = dot((centreSphere - vertices[goodTri[0]]), n) / sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
        vec3 CentreProjete = centreSphere - n * normecentre_centreprojete;
        // cout<<CentreProjete.x<<" "<<CentreProjete.y<<" "<<CentreProjete.z<<endl;

        cout << Goodalpha0 << " " << Goodalpha1 << " " << Goodalpha2 << endl;
        
        vector<vec2> uvs = plan2.getUVs();
        vec2 UV = vec2(Goodalpha0 * uvs[goodTri[0]] + Goodalpha1 * uvs[goodTri[1]] + Goodalpha2 * uvs[goodTri[2]]);
        int w, h, c;
        unsigned char *HM = getData("../textures/rock.png", w, h, c);
        float val = (float)HM[((int)UV.x * w + (int)UV.y)] / 255.0;

        Soleil.transform.Translate(vec3(0, val * (1 / 0.2), 0));
 */
        // newPlan(planInfini, currentOffSet);


        //CHANGEMENT DE RESOLUTION SELON LA DISTANCE AVEC PLUSIEURS .off
        if (cameraFree_position.z > 20 && ObjectState != 3)
        {
            Soleil.loadObject("./newbunnyPQ3.off");
            ObjectState = 3;
        }
        else if (cameraFree_position.z > 10 && cameraFree_position.z < 20 && ObjectState != 2)
        {
            Soleil.loadObject("./newbunnyPQ5.off");
            ObjectState = 2;
        }else if (cameraFree_position.z < 10 && ObjectState != 0){
             Soleil.loadObject("./newbunnyPQ10.off");
            ObjectState = 0;
        }

        planInfini.updateMeAndChilds();
        planInfini.draw(programID);

        //Soleil.transform.Translate(vec3(0, -val * (1 / 0.2), 0));

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
            if (cameraOrbit_position.y < 6)
                cameraOrbit_position += glm::normalize(cameraOrbit_up) * cameraSpeed;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (freemode)
            cameraFree_position -= cameraSpeed * cameraFront;
        if (orbitmode)
            if (glm::dot(cameraOrbit_target - cameraOrbit_position, glm::vec3(0, 1, 0)) < 0)
                cameraOrbit_position -= glm::normalize(cameraOrbit_up) * cameraSpeed;
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
        planHeightMap->changeResolution(resolutionX, resolutionY);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    {
        if (resolutionX > 1 && resolutionY > 1)
        {
            resolutionX--;
            resolutionY--;
        }
        planHeightMap->changeResolution(resolutionX, resolutionY);
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
        Soleil.transform.Translate(vec3(0.2, 0, 0));
        centreSphere.x += 0.2 * 0.02;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        Soleil.transform.Translate(vec3(-0.2, 0, 0));
        centreSphere.x += -0.2 * 0.2;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        Soleil.transform.Translate(vec3(0., 0, -0.2));
        centreSphere.z += -0.2 * 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        Soleil.transform.Translate(vec3(0, 0, 0.2));
        centreSphere.z += 0.2 * 0.2;
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
