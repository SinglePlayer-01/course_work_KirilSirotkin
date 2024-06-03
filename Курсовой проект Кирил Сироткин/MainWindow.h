#include<Windows.h>
#include"BaseWindow.h"

// Основні властивості вікна
class MainWindow : public BaseWindow<MainWindow>
{
private:
	// розміри вікна
	RECT clientRect;
	// Параметри кулі
	int ballRadius = 20;
	int ballX = 100;
	int ballY = 100;
	int ballSpeedX = 5;
	int ballSpeedY = 5;

	// Параметри платформи
	int platform_x_1 = 0;
	int platform_x_2 = 100;
	int platform_y_1 = 20;
	int platform_y_2 = 0;
	RECT rc_platform;

	// Создание счётчика 

	int score = 0;
	wchar_t m_reportFileName[100];
	HFONT hFont;
	HWND hwnd_edit;

public:
	PCWSTR ClassName() const { return L"MainWindow class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

