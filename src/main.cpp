#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <cstdio>
#include <vector>

static const char *vertex_shader_text =
    "#version 330\n"
    "layout (location = 0) in vec2 aPos;"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos, 0.0, 1.0)"
    "}\n";

static const char *fragment_shader_text =
    "#version 330\n"
    "out vec4 FragColor;"
    "void main()\n"
    "{\n"
    "FragColor = vec4(0.8, 0.8, 0.8, 1.0);"
    "}\n";

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    const uint16_t num_cols = 10;
    const uint16_t num_rows = 10;
    const float row_spacing = 1.0f / static_cast<float>(num_rows);
    const float col_spacing = 1.0f / static_cast<float>(num_cols);

    std::vector<float> vertices;

    if (!glfwInit())
    {
        printf("GLFW Init Failed\n");
        return 0;
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow *window = glfwCreateWindow(1200, 700, "GOL", NULL, NULL);
    if (!window)
    {
        printf("GLFW Window Creation Failed\n");
        return 0;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(
        window, true); // Second param install_callback=true will install
                       // GLFW callbacks and chain to existing ones.

    glfwMakeContextCurrent(window);
    ImGui_ImplOpenGL3_Init();

    vertices.reserve((num_cols - 1) * (num_rows - 1) * 4);

    // Vertical lines
    for (uint16_t i = 0; i < num_cols; i++)
    {
        float x = -1.0f + (i * col_spacing);

        vertices.push_back(x);
        vertices.push_back(1.0f);
        vertices.push_back(x);
        vertices.push_back(-1.0f);
    }

    // Horizontal lines
    for (uint16_t i = 0; i < num_cols; i++)
    {
        float y = -1.0f + (i * col_spacing);

        vertices.push_back(-1.0f);
        vertices.push_back(y);
        vertices.push_back(1.0f);
        vertices.push_back(y);
    }

    GLuint gl_vertex_buffer, gl_array_buffer, fragment_shader, vertex_shader, program;

    glGenBuffers(1, &gl_array_buffer);
    glGenVertexArrays(1, &gl_array_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, gl_array_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glDrawArrays(GL_LINES, 0, vertices.size() / 2);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}