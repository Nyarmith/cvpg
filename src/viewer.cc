#include <glad/glad.h>
#include <imgui.h>
#include <imfilebrowser.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

static int VIEWER_WIDTH = 1024;
static int VIEWER_HEIGHT = 768;


class Window
{
    virtual void draw()=0;
    virtual ~Window()=0;
};

class ErrorMessageWindow
{
public:
    std::string error;
private:
    ErrorMessageWindow(std::string name)
    {
    }

    draw()
    {
        ImGui::Begin("error");
        ImGui::Text(name.c_str());
        ImGui::End();
    }

    ~ErrorMessageWindow(){}
};

std::vector<ImageSource> g_sources;
std::vector<Window> g_wins;


void DrawSources()
{
    for (auto& source : g_sources)
    {
        ImGui::Begin(g_sources->name())
        {
            switch(format)
            {
                case format::rgb8:
                    glTexImage2D();
                    break;
                case format::rgba8:
                    glTexImage2D();
                    break;
            }
        }
    }
}

void ToolMenu()
{
    ImGui::Begin("Image Tools");
    if (ImGui::BeginTabBar("##ToolGroups"))
    {
        // TODO: Something like "for each toolgroup"
        if (ImGui::BeginTabItem("Filter"))
        {
            // e.g. colorspaces, smoothing, gradients, edge
            // https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_imgproc/py_table_of_contents_imgproc/py_table_of_contents_imgproc.html
            if (ImGui::TreeNode("smoothing"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("colorspace"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("gradient"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("edges"))
            {
                ImGui::TreePop();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Homography"))
        {
            if (ImGui::TreeNode("Correction"))
            {
                ImGui::TreePop();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Distortion"))
        {
            if (ImGui::TreeNode("Correction"))
            {
                ImGui::TreePop();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Feature Extraction"))
        {
            if (ImGui::TreeNode("SIFT"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Akaze"))
            {
                ImGui::TreePop();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}

void FileDialog
{
    fileDialog.Display();
    if (fileDialog.HasSelected())
    {
        std::string file = fileDialog.GetSelected().string();
        int i = file.rfind(".");
        if (file.substr(i+1) == "ppm)
        {
            g_sources.push_back(std::move(PpmSource(file));
        }
        else
        {
            g_wins.push_back(ErrorMessageWindow("Unsupported file format!"));
        }

        fileDialog.ClearSelected();
    }
}


static void glfw_error_callback(int error, const char* description)
{
        std::cerr << "GLFW error: " << error << ", " << description << std::endl;
}

static void glfw_resize_cb(GLFWwindow*, int w, int h)
{
        VIEWER_WIDTH = w;
        VIEWER_HEIGHT = h;
}

static void DrawMainImageWindow()
{
    ImGuiWindowFlags mm = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground;
    

    ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(
        ImVec2(static_cast<float>(VIEWER_WIDTH),static_cast<float>(VIEWER_HEIGHT)), ImGuiCond_Always);
    ImGui::Begin("Image View", nullptr, mm);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // go through options
            if (ImGui::MenuItem("New", "CTRL+N")) {}
            if (ImGui::MenuItem("Open", "CTRL+O")) {fileDialog.Open()}
            if (ImGui::BeginMenu("Open Recent"))
            {
                // Iterate through recently opened menus...
                ImGui::MenuItem("placeholder1.png");
                ImGui::MenuItem("pholder2.jpg");
                ImGui::MenuItem("HopeToSupportAnimated.gif");
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            if (ImGui::MenuItem("Save As..")) {}
            if (ImGui::MenuItem("Quit","ALT+F4")) {}

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            // TODO: Add flags for this stuff
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y")) {}
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Options"))
        {
            // TODO: Add flags for this stuff
            if (ImGui::MenuItem("Style")) {}
            if (ImGui::MenuItem("Save Window Layout")) {}
            if (ImGui::MenuItem("Backend")) {}
            if (ImGui::MenuItem("About")) {} // show build version and date
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
}


int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw\n";
        return -1;
    }

    // direct opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *displayWin = glfwCreateWindow(VIEWER_WIDTH, VIEWER_HEIGHT, "main image", NULL, NULL);
    if (!displayWin)
    {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
    }

    glfwSetWindowSizeCallback(displayWin, glfw_resize_cb);
    glfwMakeContextCurrent(displayWin);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwTerminate();
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cerr << "OpenGL version from glad: " << GLVersion.major << "." << GLVersion.minor << "\n";

    // init - imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 3.0f;
    style.WindowRounding = 6.0f;
    style.ChildRounding = 3.0f;
    style.GrabRounding = 6.0f;

    // Imgui - setup platform and renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(displayWin, true);
    ImGui_ImplOpenGL3_Init("#version 150"); //3.2 glsl

    // render loop
    while (!glfwWindowShouldClose(displayWin))
    {
        //poll events
        glfwPollEvents();

        // Start new imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawMainImageWindow();
        ToolMenu();
        DrawSources();

        // Render
        ImGui::Render();

        if (io.KeysDown[256]) // escape key
            glfwSetWindowShouldClose(displayWin, GLFW_TRUE);

        // see if window size changed
        int display_w, display_h;
        glfwGetFramebufferSize(displayWin, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(displayWin);
    }

    // shutdown - imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    
    return 0;
}
