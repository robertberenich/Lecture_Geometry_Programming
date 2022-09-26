#define GLEW_STATIC
#include <iostream>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

GLFWwindow* window; 

GLuint vbo;
GLuint vao;
GLuint vertexShader; 
GLuint fragmentShader;
GLuint shader; 

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char* vertexShaderText = "#version 330 core\nlayout(location = 0) in vec3 position;\nvoid main()\n{\ngl_Position = vec4(position.x, position.y, position.z, 1);\n}";
const char* fragmentShaderText = "#version 330 core\nout vec4 color;\nvoid main()\n{\ncolor = vec4(0.7f, 0.1f, 0.1f, 1.0f);\n}";


void keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}



int main()
{
    if (!glfwInit())
    {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return 1; 
    }

    glfwSetKeyCallback(window, keyCallBack);

    printf("GLEWVERSION %s\n", glewGetString(GLEW_VERSION));

    int width;
    int hight;

    glfwGetFramebufferSize(window, &width, &hight);

    glViewport(0, 0, width, hight);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    

    {
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderText, NULL);

        glCompileShader(vertexShader);

        GLint success;
        GLchar log[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, log);

            std::cout << "Shader compile log: \n" << log << std::endl;
        }
    }

    {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);

        glCompileShader(fragmentShader);

        GLint success;
        GLchar log[512];

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, log);

            std::cout << "Shader compile log: \n" << log << std::endl;
        }
    }

    {
        shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);

        GLint success;
        GLchar log[512];

        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, log);

            std::cout << "Shader link log: \n" << log << std::endl;
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.1f, 0.35f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //тут буде інпут
        //тут буде апдейт
        //тут буде рендер
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0; 
}

