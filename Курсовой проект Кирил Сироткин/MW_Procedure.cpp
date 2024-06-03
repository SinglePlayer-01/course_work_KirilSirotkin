#include "MainWindow.h"
#include <stdio.h> 

// Собитійно-орієнтовна функція для створення моделі поведірки ввікна
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        // Реагування на зміну розміра вікна
    case WM_SIZE:
        GetClientRect(m_hwnd, &clientRect);
        rc_platform.left = platform_x_1;
        rc_platform.top = clientRect.bottom - platform_y_1;
        rc_platform.right = platform_x_2;
        rc_platform.bottom = clientRect.bottom;
        return 0;


        // Переміщення платформи при реагуванні на кнопки <- ->
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
        {
            if (platform_x_1 != 0)
            {
                platform_x_1 -= 30;
                platform_x_2 -= 30;
                rc_platform.left = platform_x_1;
                rc_platform.top = clientRect.bottom - platform_y_1;
                rc_platform.right = platform_x_2;
                rc_platform.bottom = clientRect.bottom;
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
        break;
        case VK_RIGHT:
        {
            GetClientRect(m_hwnd, &clientRect);
            if (platform_x_2 != clientRect.right)
            {
                platform_x_1 += 30;
                platform_x_2 += 30;
                rc_platform.left = platform_x_1;
                rc_platform.top = clientRect.bottom - platform_y_1;
                rc_platform.right = platform_x_2;
                rc_platform.bottom = clientRect.bottom;
                InvalidateRect(m_hwnd, NULL, TRUE);
            }
        }
        break;
        }
        return 0;
    }

    case WM_CREATE:
    {
        SetTimer(m_hwnd, 1, 16, NULL); // Таймер для обновления анимации

        // Creating the font we need

        HFONT hFont = CreateFont(50, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");


        hwnd_edit = CreateWindow(L"EDIT", L"0", WS_CHILD | ES_CENTER | ES_READONLY | WS_VISIBLE, 0, 0, 100, 60, m_hwnd, NULL, NULL, NULL, NULL);
        // Set your font
        SendMessage(hwnd_edit, WM_SETFONT, (WPARAM)hFont, TRUE);

        GetClientRect(m_hwnd, &clientRect);
    }
    break;
    case WM_TIMER:
        // Обновление координат шарика
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        
        GetClientRect(m_hwnd, &clientRect);
        if (block_1.left <= ballX - ballRadius && ballX - ballRadius <= block_1.right && (ballY - ballRadius == block_1.bottom || ballY + ballRadius == block_1.top) && block_1_hit == false)
        {
                ballSpeedY = -ballSpeedY;
                block_1_hit = true;
        }
        if (block_2.left <= ballX - ballRadius && ballX - ballRadius <= block_2.right && (ballY - ballRadius == block_2.bottom || ballY + ballRadius == block_2.top) && block_2_hit == false)
        {
                ballSpeedY = -ballSpeedY;
                block_2_hit = true;
        }
        if (block_3.left <= ballX - ballRadius && ballX - ballRadius <= block_3.right && (ballY - ballRadius == block_3.bottom || ballY + ballRadius == block_3.top) && block_3_hit == false)
        {
                ballSpeedY = -ballSpeedY;
                block_3_hit = true;
        }
        if (block_4.left <= ballX - ballRadius && ballX - ballRadius <= block_4.right && (ballY - ballRadius == block_4.bottom || ballY + ballRadius == block_4.top) && block_4_hit == false)
        {
                ballSpeedY = -ballSpeedY;
                block_4_hit = true;
        }
        // Проверка столкновения с границами окна
        if (ballX - ballRadius < 0 || ballX + ballRadius > clientRect.right)
        {
            ballSpeedX = -ballSpeedX;
        }
        if (ballY - ballRadius < 0 || ballY + ballRadius > clientRect.bottom)
        {
            ballSpeedY = -ballSpeedY;
        }

        if (rc_platform.left <= ballX && ballX <= rc_platform.right && ballY + ballRadius > clientRect.bottom - 20)
        {
            score++;
            ballSpeedY = -ballSpeedY;
        }


        // Перерисовка окна
        InvalidateRect(m_hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);


        // Преобразование int to wchar_t
        wchar_t m_reportFileName[100];
        swprintf_s(m_reportFileName, L"%d", score);

        // Рисование шарика
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 5));
        FillRect(hdc, &rc_platform, (HBRUSH)(COLOR_WINDOW + 9));
        if(block_1_hit == false)
        {
            FillRect(hdc, &block_1, (HBRUSH)(COLOR_WINDOW + 13));
        }
        if (block_2_hit == false)
        {
            FillRect(hdc, &block_2, (HBRUSH)(COLOR_WINDOW + 13));
        }
        if (block_3_hit == false)
        {
            FillRect(hdc, &block_3, (HBRUSH)(COLOR_WINDOW + 13));
        }
        if (block_4_hit == false)
        {
            FillRect(hdc, &block_4, (HBRUSH)(COLOR_WINDOW + 13));
        }

        Ellipse(hdc, ballX - ballRadius, ballY - ballRadius, ballX + ballRadius, ballY + ballRadius);
        SetWindowText(hwnd_edit, m_reportFileName);

        EndPaint(m_hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    case WM_CTLCOLORBTN:
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORSTATIC:
        SetTextColor(HDC(wParam), (COLORREF)RGB(0, 255, 0));
        SetBkMode(HDC(wParam), (COLORREF)RGB(200, 0, 0));
        return LRESULT(HBRUSH(GetStockObject(NULL_BRUSH)));


    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return 0;
}