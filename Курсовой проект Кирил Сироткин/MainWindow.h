#pragma once

#include<Windows.h>
#include"BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{

public:
	PCWSTR ClassName() const { return L"MainWindow class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

