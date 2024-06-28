#include "./header.h"
#include "./core/camera.h"
#include "./core/model.h"
#include "./core/shader.h"
#include "./utils/utils.h"
#include "./skybox.h"

typedef enum {
    INTERSTELLAR = 0,
    MIRAMAR,
    STORM
} Box_Type;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Box_Type current_box = INTERSTELLAR;
bool pressed = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sky Box OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    Shader skyboxShader("./shaders/skybox.vs", "./shaders/skybox.fs");

    vector<std::string> interstellar
    {
        "./textures/interstellar/front.tga",
        "./textures/interstellar/back.tga",

        "./textures/interstellar/top.tga",
        "./textures/interstellar/bottom.tga",

        "./textures/interstellar/right.tga",
        "./textures/interstellar/left.tga",
    };

    vector<std::string> storm
    {
        "./textures/storm/front.tga",
        "./textures/storm/back.tga",

        "./textures/storm/top.tga",
        "./textures/storm/bottom.tga",

        "./textures/storm/right.tga",
        "./textures/storm/left.tga",
    };
 
    vector<std::string> miramar
    {
        "./textures/miramar/front.tga",
        "./textures/miramar/back.tga",

        "./textures/miramar/top.tga",
        "./textures/miramar/bottom.tga",

        "./textures/miramar/right.tga",
        "./textures/miramar/left.tga",
    };
    

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    Box Interstellar(interstellar);
    Box Miramar(miramar);
    Box Storm(storm);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skyboxShader.use();
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);

        switch (current_box)
        {
        case INTERSTELLAR:
            Interstellar.Draw(skyboxShader);
            break;
        case MIRAMAR:
            Miramar.Draw(skyboxShader);
            break;
        case STORM:
            Storm.Draw(skyboxShader);
            break;
        default:
            break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if(!pressed) {

            switch (current_box)
            {
            case INTERSTELLAR:
                current_box = MIRAMAR;
                break;

            case MIRAMAR:
                current_box = STORM;
                break;

            case STORM:
                current_box = INTERSTELLAR;
                break;
            default:
                break;
            }
            pressed = true;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
        pressed = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}