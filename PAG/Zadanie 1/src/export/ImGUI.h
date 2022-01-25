#ifndef __ImGUI_H__
#define __ImGUI_H__

#include <stdio.h>
#include <imgui.h>

class ImGUI
{
private:
	bool is_enable;

public:
	int tmp_poziom_rekurencji, poziom_rekurencji;
	ImVec4 kolor_tla;
	ImVec4 kolor_fraktala;
	int obrot_fraktala[4];
	bool pokaz_teksture;
	float zoom;

public:
	ImGUI();
	~ImGUI();
	void Draw();
	void EnableGUI(bool type);
};

#endif //__ImGUI_H__