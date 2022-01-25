#include "ImGUI.h"
#include <imgui.h>
#include <glad/glad.h>

ImGUI::ImGUI()
{
    is_enable = true;
    tmp_poziom_rekurencji = 0;
    poziom_rekurencji = 0;
    kolor_tla = ImVec4(0.f, 0.f, 0.f, 1.f);
    kolor_fraktala = ImVec4(1.f, 0.f, 0.f, 1.f);
    obrot_fraktala[0] = 0;
    obrot_fraktala[1] = 0;
    obrot_fraktala[2] = 0;
    obrot_fraktala[3] = 0;
    zoom = -4.f;
}

void ImGUI::Draw()
{
    if (is_enable)
    {
        ImGui::Begin("Ustawienia piramidy");
        //ImGui::Text("Ustawienia piramidy");
        //if (ImGui::Button("Wylacz"))
        //    is_enable = false;
        ImGui::SliderInt("Ilosc fraktali", &poziom_rekurencji, 0, 8);
        ImGui::SliderFloat("Zoom", &zoom, -10.f, 0.f);
        ImGui::ColorEdit3("Kolor tla", (float*)&kolor_tla);
        ImGui::ColorEdit3("Kolor fraktala", (float*)&kolor_fraktala);
        ImGui::SliderInt3("Obrot fraktala", obrot_fraktala, -360, 360);
        ImGui::Columns(2);
        if (ImGui::Button("Pokaz siatke"))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        ImGui::SameLine();
        if (ImGui::Button("Pokaz model"))
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        ImGui::NextColumn();
        ImGui::Checkbox("Pokaz teksture", &pokaz_teksture);
        ImGui::End();
    }
    else
    {
        ImGui::Begin("GUI");
        if (ImGui::Button("Wlacz"))
            is_enable = true;
        ImGui::End();
    }
}

void ImGUI::EnableGUI(bool type)
{
    is_enable = type;
}

ImGUI::~ImGUI()
{

}