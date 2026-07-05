#include "graphics_opengl.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Phobos::Graphics::OpenGL {

GraphicsOpenGL::GraphicsOpenGL()
    //: projectionMatrix(1.0f), viewMatrix(1.0f) {
{
}

void GraphicsOpenGL::initialize()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("No se pudo inicializar GLEW");
    }
    window = EngineBaseInterface::getInstance()->getWindowComponent();
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(window->getNativeWindow()));
    logMessage("OpenGlGraphicsInitialized");
}

void DrawGreenTriangle(GLFWwindow *win)
{
    static GLuint vao = 0;
    static GLuint vbo = 0;
    static GLuint program = 0;

    if (program == 0)
    {
        const float vertices[] =
        {
             0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f
        };

        const char* vsSource = R"(
            #version 460 core

            layout(location = 0) in vec3 position;

            void main()
            {
                gl_Position = vec4(position, 1.0);
            }
        )";

        const char* fsSource = R"(
            #version 460 core

            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(0.0, 1.0, 0.0, 1.0);
            }
        )";

        auto CompileShader = [](GLenum type, const char* source)
        {
            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);

            GLint ok = GL_FALSE;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

            if (!ok)
            {
                char log[1024];
                glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
                throw std::runtime_error(log);
            }

            return shader;
        };

        GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
        GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

        program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        GLint ok = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &ok);

        if (!ok)
        {
            char log[1024];
            glGetProgramInfoLog(program, sizeof(log), nullptr, log);
            throw std::runtime_error(log);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(vertices),
                     vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            3 * sizeof(float),
            nullptr);
        glfwSwapBuffers(win);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        Phobos::Graphics::OpenGL::ShaderStageOpenGl stage(Phobos::ShaderStageType::VertexShader, fsSource, "foo");

        struct a {int d;} xx;
        xx.d = 4;

        std::vector<a> p{4};
        p[0].d = 255;

        stage.addParameter<a>(1, xx);
        stage.addParameter<std::vector<a>>(1, p);


        stage.logMessage(stage.getCode());

    }

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    

}
void GraphicsOpenGL::execute()
{
    auto win = static_cast<GLFWwindow*>(window->getNativeWindow());
    DrawGreenTriangle(win);
    glfwSwapBuffers(win);
}

/*

void GraphicsOpenGL::shutdown() {
}

void GraphicsOpenGL::render() {
}

glm::mat4 GraphicsOpenGL::getProjectionMatrix() const {
    return projectionMatrix;
}

glm::mat4 GraphicsOpenGL::getViewMatrix() const {
    return viewMatrix;
}
*/

} // namespace Phobos::Graphics::OpenGL
