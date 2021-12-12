#include "UserInterface.h"

UserInterface::UserInterface(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);


    directional_light_enable = true;
    point_light_enable = true;
    point_light_spin = true;
    point_lightSku = 32;
    point_lightWli = 0.03;
    point_lightWkw = 0;
    for(int i=0; i<3; i++)
    {
        directional_light_direction[i] = 0;
        directional_light_color[i] = 1;

        point_light_position[i] = 0;
        point_light_color[i] = 1;
    }

    directional_light_direction[1] = -1;

    spot_light_1_enable = true;
    spot_light_1_range = 0;
    spot_light_1_position[0] = 0;
    spot_light_1_position[1] = 5;
    spot_light_1_position[2] = 0;
    spot_light_1_direction[0] = 0;
    spot_light_1_direction[1] = -1;
    spot_light_1_direction[2] = 0;
    spot_light_1_color[0] = 1;
    spot_light_1_color[1] = 1;
    spot_light_1_color[2] = 1;
    spot_light_1_radius[0] = 12.5;
    spot_light_1_radius[1] = 17.5;

    spot_light_2_enable = true;
    spot_light_2_range = 0;
    spot_light_2_position[0] = 2.5;
    spot_light_2_position[1] = 0.5;
    spot_light_2_position[2] = 0;
    spot_light_2_direction[0] = 1;
    spot_light_2_direction[1] = -0.5;
    spot_light_2_direction[2] = 0;
    spot_light_2_color[0] = 1;
    spot_light_2_color[1] = 1;
    spot_light_2_color[2] = 1;
    spot_light_2_radius[0] = 12.5;
    spot_light_2_radius[1] = 17.5;
}

UserInterface::~UserInterface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::Display()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {
        ImGui::Begin("Hello, world!");

        ImGui::Checkbox("Sw. kierunkowe", &directional_light_enable);
        ImGui::SliderFloat3("Kierunek (sw. kier)", &directional_light_direction[0], -1.f, 1.f);
        ImGui::ColorEdit3("Kolor (sw. kier)", &directional_light_color[0]);

        ImGui::Checkbox("Sw. punktowe", &point_light_enable);
        ImGui::Checkbox("Poruszanie (sw. pkt)", &point_light_spin);
        ImGui::SliderFloat("Skupienie (sw. pkt)", &point_lightSku, 0, 128);
        ImGui::SliderFloat("Wsp. liniowy (sw. pkt)", &point_lightWli, 0, 1);
        ImGui::SliderFloat("Wsp. kwadrawowy (sw. pkt)", &point_lightWkw, 0, 0.5);
        ImGui::SliderFloat3("Pozycja (sw. pkt)", &point_light_position[0], -500, 500);
        ImGui::ColorEdit3("Kolor (sw. pkt)", &point_light_color[0]);

        ImGui::Checkbox("Sw. spotlight 1", &spot_light_1_enable);
        ImGui::SliderFloat3("Pozycja (sw. spot1)", &spot_light_1_position[0], -500, 500);
        ImGui::SliderFloat("Zasieg (sw. spot1)", &spot_light_1_range, 0, 5);
        ImGui::SliderFloat3("Kierunek (sw. spot1)", &spot_light_1_direction[0], -1, 1);
        ImGui::ColorEdit3("Kolor (sw. spot1)", &spot_light_1_color[0]);
        ImGui::SliderFloat2("Promien (sw. spot1)", &spot_light_1_radius[0], 0, 25);

        ImGui::Checkbox("Sw. spotlight 2", &spot_light_2_enable);
        ImGui::SliderFloat3("Pozycja (sw. spot2)", &spot_light_2_position[0], -500, 500);
        ImGui::SliderFloat("Zasieg (sw. spot2)", &spot_light_2_range, 0, 5);
        ImGui::SliderFloat3("Kierunek (sw. spot2)", &spot_light_2_direction[0], -1, 1);
        ImGui::ColorEdit3("Kolor (sw. spot2)", &spot_light_2_color[0]);
        ImGui::SliderFloat2("Promien (sw. spot2)", &spot_light_2_radius[0], 0, 25);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f/ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
