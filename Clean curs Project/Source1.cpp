#include <windows.h>;
#include <time.h>;
#include <tchar.h>;
#include <stdlib.h>;
#include <string>;
#include <vector>;
#include "resource.h"; // підключення бібліотеки з функціями API
// Глобальні змінні:
HINSTANCE hInst; //Дескриптор програми
LPCTSTR szWindowClass = "Curs Project";
LPCTSTR szTitle = "Curs Project";
// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//Мої функції і змінні
void Win(HWND[], HWND);
void ShowMas(HWND[], int[]);
void Zap(HWND);
void CloseWindows(bool);
int CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM); 
int CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK DlgTable(HWND, UINT, WPARAM, LPARAM);
TCHAR str[256] = "";
HWND hBut[16];
int mas[16], textNumb, j;
bool iswin = false;
int mass_test_win[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0 ,15 };
std::string stri,nik, path, zmist, table, Table;
int stepFoWin = 0;
HWND EditControl;

HANDLE hFile, mfile, object;
DWORD dwBytesRead, dwBytesWritten, dwPos;
LPDWORD hz;
WIN32_FIND_DATA data;


struct tableWin {
	std::string name;
	int countPoint;
};
struct CONTROLS
{
	HWND hControl;
	int id;
};
CONTROLS myControls[5];
std::vector<tableWin> winers;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	// Реєстрація класу вікна
	MyRegisterClass(hInstance);
	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; //стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; //віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; //дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_ASTERISK); //визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //визначення курсору
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //визначення меню
	wcex.lpszClassName = szWindowClass; //ім’я класу
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); //реєстрація класу вікна
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, // ім’я класу вікна
		szTitle, // назва програми
		WS_OVERLAPPEDWINDOW, // стиль вікна
		CW_USEDEFAULT, // положення по Х
		CW_USEDEFAULT, // положення по Y
		500, // розмір по Х
		500, // розмір по Y
		NULL, // дескриптор батьківського вікна
		NULL, // дескриптор меню вікна
		hInstance, // дескриптор програми
		NULL); // параметри створення.
	if (!hWnd) //Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow); //Показати вікно
	UpdateWindow(hWnd); //Оновити вікно
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static int sx, sy;
	int i;
	time_t t;
	bool win = true;
	switch (message)
	{
	case WM_CREATE:
		for (int i = 0; i < 5; ++i)
		{
			myControls[i].id = i;
		}
		srand((unsigned)time(&t));
		for (i = 0; i < 16; i++)
			hBut[i] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, 0, hInst, 0);
		Zap(hWnd);

		ShowMas(hBut, mas);
		break;
	case WM_SIZE:
		sx = LOWORD(lParam) / 4;
		sy = HIWORD(lParam) / 4;
		break;

	case WM_COMMAND:

		for (i = 0; i < 16; i++) {

			if (HWND(lParam) == hBut[i])
			{
				if (mas[i - 4] == 0 && i >= 4)
				{
					GetWindowText(hBut[i], str, 256);
					SetWindowText(hBut[i - 4], str);
					SetWindowText(hBut[i], " ");
					mas[i] = 0;
					wchar_t* end_ptr;

					mas[i - 4] = std::stol(str);

					stepFoWin++;
				}
				if ((mas[i - 1] == 0 && i >= 1) && ((i) % 4) != 0)
				{
					GetWindowText(hBut[i], str, 256);
					SetWindowText(hBut[i - 1], str);
					SetWindowText(hBut[i], " ");
					mas[i] = 0;
					wchar_t* end_ptr;
					mas[i - 1] = std::stol(str);

					stepFoWin++;
				}
				if ((mas[i + 1] == 0 && i <= 14) && ((i + 1) % 4) != 0)
				{
					GetWindowText(hBut[i], str, 256);
					SetWindowText(hBut[i + 1], str);
					SetWindowText(hBut[i], " ");
					mas[i] = 0;
					wchar_t* end_ptr;
					mas[i + 1] = std::stol(str);

					stepFoWin++;
				}
				if (mas[i + 4] == 0 && i <= 11)
				{
					GetWindowText(hBut[i], str, 256);
					SetWindowText(hBut[i + 4], str);
					SetWindowText(hBut[i], " ");
					mas[i] = 0;
					wchar_t* end_ptr;
					mas[i + 4] = std::stol(str);

					stepFoWin++;
				}

			}
		}

		Win(hBut, hWnd); //Проверка на победу игрока (цикл прохожит все ячейки)

		switch (LOWORD(wParam))
		{
		case ID_GAME_NEW:
			iswin = false;
			CloseWindows(true);
			Zap(hWnd);
			ShowMas(hBut, mas);
			stepFoWin = 0;
			break;
		case ID_GAME_EXIT:
			PostQuitMessage(0);
			break;
		case ID_INFORMATION_ABOUTGAME:
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_DIALOG1),
				hWnd,
				DlgProc
			);
			break;
		case ID_INFORMATION_PROMPT:
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_DIALOG3),
				hWnd,
				DlgProc
			);
			break;
		case ID_INFORMATION_ABOUTPROGRAMM:
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_DIALOG2),
				hWnd,
				DlgProc
			);
			break; 
		case ID_INFORMATION_WINERS:
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_DIALOG5),
				hWnd,
				DlgTable
			);
			break;
		}

		break;


	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 16; i++)
			MoveWindow(hBut[i], (i % 4) * sx, (i / 4) * sy, sx, sy, 1);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: //Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void ShowMas(HWND h[], int m[])
{
	TCHAR s[256] = " ";
	for (int i = 0; i < 16; i++)
		if (m[i] != 0)
		{
			//swprintf(s, "%d", m[i]);
			stri = std::to_string(m[i]);
			SetWindowText(h[i], stri.c_str());
		}
		else
			SetWindowText(h[i], " ");
}

void Win(HWND hButt[], HWND hwnd) {
	bool win = true;
	int buff;
	GetWindowText(hButt[15], str, 256);
	if (str[0] == ' ' && !iswin)
	{
		for (int i = 0; i < 15; i++)
		{
			GetWindowText(hButt[i], str, 256);
			buff = str[0] - '0';
			if (i >= 9) {
				buff *= 10;
				buff += str[1] - '0';
			}
			if (buff != i + 1)
			{
				TCHAR hhh = str[0];
				int ii = i;
				win = false;
			}
		}
		if (win)
		{
			CloseWindows(false);
			DialogBox(hInst,
				MAKEINTRESOURCE(IDD_DIALOG4),
				hwnd,
				WinProc
			);
			iswin = true;
		}
	}

}

void Zap(HWND hwnd) {
	int index;
	bool valid;


	for (int i = 0; i < 16; i++)
	{
		valid = false;
		do
		{
			index = rand() % 16;
			if (mass_test_win[index] < 16) {
				mas[i] = mass_test_win[index];
				mass_test_win[index] += 100;
				valid = true;
			}
		} while (!valid);
		//mas[i] = mass_test_win[i];
	}
	for (int i = 0; i < 16; i++)
	{
		mass_test_win[i] -= 100;
	}
}

void CloseWindows(bool state) {
	for (int i = 0; i < 16; i++)
	{
		EnableWindow(hBut[i], state);
	}
}
int CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:

			EndDialog(hDlg, NULL);
			break;
		}

		break;
	}
	return FALSE;
}

int CALLBACK WinProc(HWND hWin, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	RECT rt;
	HDC hdc;
	char buffer[30];
	char text[10];
	char buff[10];
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			
		case 1:
			hdc = GetDC(hWin);
			TextOut(hdc, 125, 235, "Введіть ваше ім'я", 18);
			myControls[0].hControl = CreateWindow(
				"EDIT",
				"",
				WS_CHILD | WS_VISIBLE,
				140,
				260,
				100,
				20,
				hWin,
				(HMENU)myControls[0].id,
				hInst,
				NULL);

			myControls[3].hControl = CreateWindow(
				"button",
				"Записати",
				WS_CHILD | WS_VISIBLE,
				150,
				285,
				75,
				20,
				hWin,
				(HMENU)myControls[3].id,
				hInst,
				NULL);

			ReleaseDC(hWin, hdc);
			break;
		case 2:

			EndDialog(hWin, NULL);
			break;
		case 4:

			EndDialog(hWin, NULL);
			break;
		case 3:
			hdc = GetDC(hWin);
			GetWindowText(myControls[0].hControl,text,10);
			nik = text;

			TextOut(hdc, 90, 315, "Вітаємо, ваш рекорд записано", 28);
			path = "Table\\" + nik + ".txt";


			//mfile = CreateFile(TEXT(path.c_str()), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			
				DeleteFile(path.c_str());
			object = CreateFile(
				path.c_str(), //имя файла
				GENERIC_WRITE | GENERIC_READ, //способ доступа
				FILE_SHARE_WRITE | FILE_SHARE_READ, //совместный доступ
				NULL, //атрибуты доступа
				CREATE_NEW, //проверка существования
				FILE_ATTRIBUTE_NORMAL, //атрибуты файла
				NULL); //дескриптор временного файла

			zmist = std::to_string(stepFoWin);
			//TextOut(hdc, 90, 330, zmist.c_str(), zmist.length());

			WriteFile(object, zmist.c_str(), zmist.length(), hz, 0);

			myControls[4].hControl = CreateWindow(
				"button",
				"Дякую",
				WS_CHILD | WS_VISIBLE,
				150,
				340,
				75,
				20,
				hWin,
				(HMENU)myControls[4].id,
				hInst,
				NULL);

			CloseHandle(object);
			ReleaseDC(hWin, hdc);
			break;
		case IDC_BUTTON1:
			hdc = GetDC(hWin);

			TextOut(hdc, 100, 150, "Ви впорались за : ", 18); 
			TextOut(hdc, 225, 150, buffer, wsprintf(buffer, "%d", stepFoWin));
			TextOut(hdc, 260, 150, "кроків", 7);
			TextOut(hdc, 75, 175, "Ви бажаєте записати результат ?", 31);
			
			myControls[1].hControl = CreateWindow(
				"button",
				"Так",
				WS_CHILD | WS_VISIBLE,
				125,
				200,
				50,
				20,
				hWin,
				(HMENU)myControls[1].id,
				hInst,
				NULL);
			myControls[2].hControl = CreateWindow(
				"button",
				"Ні",
				WS_CHILD | WS_VISIBLE,
				200,
				200,
				50,
				20,
				hWin,
				(HMENU)myControls[2].id,
				hInst,
				NULL);

			ReleaseDC(hWin, hdc);
			break;
		}

		break;
		
	}
	return FALSE;
}
int CALLBACK DlgTable(HWND hTable, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	bool isTable;
	char buff[5] = {0};
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:

			EndDialog(hTable, NULL);
			break;
		}

		break;
	case WM_PAINT: //Перемалювати вікно
		hdc = BeginPaint(hTable, &ps); //Почати графічний вивід
		GetClientRect(hTable, &rt); //Область вікна для малювання
		textNumb = 0;
		tableWin obj;
		isTable = false;
		//DrawText(hdc, "Hello world!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
		object = FindFirstFile("Table\\*.*", &data);
		if (object != INVALID_HANDLE_VALUE) {
			do
			{
				j = 0;
				if (strlen(data.cFileName) > 4)
				{
					Table = data.cFileName;
					for (int i = 0; i < Table.length(); i++)
					{
						if (i + 4 >= Table.length())
						{
							table += Table[i];
						}
					}
					if (table == ".txt")
					{
						Table = "Table\\";
						Table = Table + data.cFileName;
						mfile = CreateFile(TEXT(Table.c_str()), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						
						if (ReadFile(mfile, buff, 4, &dwBytesRead, NULL))
						{
							isTable = true;
							Table = std::to_string(textNumb + 1);
							table = data.cFileName;
							zmist = buff;

							table.erase(table.length()-4, 4);
							obj.countPoint = std::atoi(zmist.c_str());
							obj.name = table;
							
							for (int i = 0; i < 5; i++)
							{
								buff[i] = '\0';
							}
							winers.push_back(obj);
						}
						CloseHandle(mfile);
					}
				}
				table.clear();
			} while (FindNextFile(object, &data));
			FindClose(object);
		}

		if (isTable)
		{           
			Table = "Місце";
			TextOut(hdc, 25, 30, Table.c_str(), Table.length());
			Table = "Ім'я";
			TextOut(hdc, 125, 30, Table.c_str(), Table.length());
			Table = "Кількість кроків";
			TextOut(hdc, 225, 30, Table.c_str(), Table.length());
			for (int i = 0; i < winers.size() - 1; i++) {
				for (int j = 0; j < winers.size() - i - 1; j++) {
					if (winers[j].countPoint < winers[j + 1].countPoint) {
						obj = winers[j];
						winers[j] = winers[j + 1];
						winers[j + 1] = obj;
					}
				}
			}
			if (winers.size() < 11)textNumb = winers.size();
			else textNumb = 10;
			for (int i = 0; i < textNumb; i++)
			{
				Table = std::to_string(i + 1);
				TextOut(hdc, 40, 30 * (i + 2), Table.c_str(), Table.length());
				Table = winers[i].name;
				TextOut(hdc, 125, 30 * (i + 2), Table.c_str(), Table.length());
				Table = std::to_string(winers[i].countPoint);
				TextOut(hdc, 275, 30 * (i + 2), Table.c_str(), Table.length());
			}
		}
		else
		{
			DrawText(hdc, "У базі відсутні дані ", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		EndPaint(hTable, &ps); //Закінчити графічний вивід
		break;
	}
	return FALSE;
}