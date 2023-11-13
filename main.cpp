#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "ImGuiFileDialog/ImGuiFileDialog.h"

int main(int, char**) {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(600, 600, " Form", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the GLFW context current
    glfwMakeContextCurrent(window);

    // Initialize ImGuiFileDialog
    ImGuiFileDialog fileDialog;

    bool openFileDialog = false;
    char selectedFilePath[128] = "";

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
    style.ChildRounding = 4.0f;
    style.ItemSpacing.y = 10;
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 5.0f;

    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF("font/Arial.ttf", 14);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Handle input and events
        glfwPollEvents();
        // Start a new frame for ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImVec4 bg_color = ImVec4(0.7450980392156863f, 0.9098039215686274f, 0.7725490196078432f, 1.0f);
        ImVec4 text_color(0.1137f, 0.4784f, 0.1686f, 1.0f);
        ImVec4 input_color(1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, bg_color);
        ImGui::PushStyleColor(ImGuiCol_Text, text_color);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, input_color);
        ImGui::PushStyleColor(ImGuiCol_TitleBg, text_color);
        ImGui::SetNextWindowSize(ImVec2(400, 500));

        // Start the form

        ImGui::Begin("Appeal Application Form", NULL,ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        static char firstName[64] = "";
        static char lastName[64] = "";
        static char studentNumber[64] = "";
        static char requestSummary[64] = "";
        static const char* options[] = { "Yes", "No" };

        // Add styling
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0, 0, 0, 0));

        // Use ImGui InputText with the specified buffer size

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        ImGui::SetWindowFontScale(1.4f);
        ImGui::Text("Appeal Application Form");
        ImGui::PopFont();
        ImGui::SetWindowFontScale(1.0f);

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        ImGui::SetWindowFontScale(1.2f);
        ImGui::Text("Personal Information");
        ImGui::PopFont();
        ImGui::SetWindowFontScale(1.0f);

        ImU32 border_color = ImGui::GetColorU32(ImVec4(0.1137f, 0.4784f, 0.1686f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, border_color);
        ImGui::BeginGroup();
        float width = ImGui::GetContentRegionAvail().x / 2 - 4;
        ImGui::Text("Name");
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 10));
        ImGui::SetNextItemWidth(width);
        ImGui::InputTextWithHint("###FirstName", "First", firstName, sizeof(firstName));
        ImGui::PopStyleVar();

        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 10));
        ImGui::SetNextItemWidth(width);
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.1137f, 0.4784f, 0.1686f, 1.0f));
        ImGui::InputTextWithHint("###LastName", "Last", lastName, sizeof(lastName));
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::EndGroup();

        ImGui::Text("Studen Number");
        ImGui::PushStyleColor(ImGuiCol_Border, border_color);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 10));
        ImGui::SetNextItemWidth(-1);
        ImGui::InputTextWithHint("###StudentNumber", "StudentNumber", studentNumber, sizeof(studentNumber));

        ImGui::BeginGroup();
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        ImGui::SetWindowFontScale(1.2f);
        ImGui::Text("Appeal Information");
        ImGui::PopFont();
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Text("Request Summary");
        ImGui::SetNextItemWidth(500);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        ImGui::InputTextMultiline("###RequestSummary", requestSummary, sizeof(requestSummary), ImVec2(-1, 50));
        ImGui::PopStyleVar();
        ImGui::EndGroup();
        ImGui::PopStyleColor();

        ImGui::Text("Selected File: %s", selectedFilePath);
        ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Border, border_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.588f, 0.376f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.588f, 0.376f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Button, white);
        if (ImGui::Button("Choose File or drag here", ImVec2(-1, 40))) {
            // Open the file dialog when the button is clicked
            openFileDialog = true;
        }
        if (openFileDialog) {
            // Open the file dialog
            if (fileDialog.Display("Choose a File")) {
                // If the user selected a file, get the file path and close the dialog
                if (fileDialog.IsOk()) {
                    strcpy_s(selectedFilePath, fileDialog.GetFilePathName().c_str());
                    openFileDialog = false;
                }
                // Close the dialog
                fileDialog.Close();
            }
        }
        ImGui::PopStyleColor();


        static int selected =0;
        ImVec4 transparent(0.0f, 0.0f, 0.0f, 0.0f);
        ImGui::Text("Do you have supporting documents for your appeal?");
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 10));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, transparent);
        ImGui::PushStyleColor(ImGuiCol_Border, border_color);
        ImGui::SetNextItemWidth(-1);
        if (ImGui::BeginCombo("###Select", options[selected])) {
                ImGui::PushStyleColor(ImGuiCol_Header, white);
            for (int i = 0; i < 2; i++) {
                bool is_selected = (i == selected);
                if (ImGui::Selectable(options[i], is_selected))
                    selected = i;
            }
            ImGui::EndCombo();
                ImGui::PopStyleColor();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        ImGui::End();

        ImGui::PopStyleColor();

        // Render ImGui
        ImGui::Render();

        // Swap buffers
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
    }

    // Cleanup resources
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
