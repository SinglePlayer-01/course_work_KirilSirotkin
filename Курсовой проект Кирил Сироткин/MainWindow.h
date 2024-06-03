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

	// Создаём уничтожаемые блоки
	
	RECT block_1
	{
		block_1.left = 40,
		block_1.top = 40,
		block_1.right = 80,
		block_1.bottom = 80
	};
	RECT block_2
	{
		block_2.left = 85,
		block_2.top = 40,
		block_2.right = 120,
		block_2.bottom = 80
	};
	RECT block_3
	{
		block_3.left = 125,
		block_3.top = 40,
		block_3.right = 160,
		block_3.bottom = 80
	};
	RECT block_4
	{
		block_4.left = 165,
		block_4.top = 40,
		block_4.right = 200,
		block_4.bottom = 80
	};
	bool block_1_hit = false;
	bool block_2_hit = false;
	bool block_3_hit = false;
	bool block_4_hit = false;

	// Создание счётчика 

	int score = 0;
	wchar_t m_reportFileName[100];
	HFONT hFont;
	HWND hwnd_edit;

public:
	PCWSTR ClassName() const { return L"MainWindow class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

