// GT_HelloWorldWin32.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "ONP.h"
// Global variables

//UWAGA
//wiekszosc rzeczy skopiowana z jakiegos template'a xd

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier
//uchwyty do :
//hEdit - tam wpisujesz wyrazenie
//hOnpOutput - tutaj wypisuje ci ONP
//hResult - tutaj wypisuje wynik
//hButton - jego klikasz
//uchyt to wskaznik
HWND hEdit;
HWND hOnpOutput;
HWND hResult;
HWND hButton;

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Parser matematyczny zrobiony przez XXXYYY");
//instancja aplikacji?
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	//tutaj pewnie deklaruje wyglad okienka, nie wiem jak to dziala.
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		//wywala blad jesli sie nie uda stworzyc klasy okna
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

					   // The parameters to CreateWindow explained:
					   // szWindowClass: the name of the application
					   // szTitle: the text that appears in the title bar
					   // WS_OVERLAPPEDWINDOW: the type of window to create
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
					   // 500, 100: initial size (width, length)
					   // NULL: the parent of this window
					   // NULL: this application does not have a menu bar
					   // hInstance: the first parameter from WinMain
					   // NULL: not used in this application
	HWND hWnd = CreateWindow( //tworzy okno?
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 150,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"), //nie udalo sie sotwrzyc okna, wywala blad
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) //jest to petla programu. Najlepiej jak ci to wytlumacze xd
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_CREATE: //tylko raz sie to wywluje przy tworzeniu okienka(czy programu, nie wiem :D)
		{
			// Create an edit box
			hEdit=CreateWindowEx(WS_EX_CLIENTEDGE, //tworzy pole do wprowadzania tekstu
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				10,
				10,
				470,
				20,
				hWnd,
				(HMENU)IDC_MAIN_EDIT,
				GetModuleHandle(NULL),
				NULL);
			HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			SendMessage(hEdit,
				WM_SETTEXT,
				NULL,
				(LPARAM)"");

			//tworzy pole do wypisania ONP i wyniku
			hOnpOutput = CreateWindow("STATIC", "Tutaj pojawi sie wyrazenie skonwertowane do ONP", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 40, 470, 20, hWnd, NULL, hInst, NULL);
			hResult = CreateWindow("STATIC", "Tutaj pojawi sie wynik", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 65, 470, 20, hWnd, NULL, hInst, NULL);

			// Create a push button
			 hButton=CreateWindowEx(NULL, //tworzy przycisk
				"BUTTON",
				"Oblicz",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,
				85,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND: //guzik przesyla ten rodzaj komendy
		if ((HWND)lParam == hButton) //sprawdzamy czy to nasz guzik
		{
			try
			{

				int txtlen = GetWindowTextLength(hEdit); //sprawdzamy ile liter ma wprowadzone przez nas wyrazenie
				std::string expr;  //or use wstring for wchar_t //tworzymy string ktory bedzie to przechowywal.
				expr.reserve(txtlen + 1); //zwiekszamy ilosc znakow w tym stringu zeby mogl to przechowac (bedziemy przesylac wskaznik wiec musimy to zrobic)
				GetWindowText(hEdit, const_cast<char*>(expr.c_str()), txtlen + 1); //pobieramy napis

				ONP onp(expr.c_str()); //inicjalizujemy ONP


				std::string value = std::to_string(onp); //pobieramy wynik
				std::string onpExpr = onp.onpExpression; //pobieramy wyrażenie ONP

				SetWindowText(hOnpOutput, onpExpr.c_str()); //pokazujemy wyrazenie w psotaci ONP
				SetWindowText(hResult, value.c_str()); //pokazujemy wynik
			}
			catch (std::exception e) 
			{
				MessageBox(NULL, //pokazuje nam okienko z bledem (moze dzielenie przez 0?
			(e.what()),
			_T("Blad!!!"),
			NULL);
			}
			catch (...) //lapie kazdy inny blad ktory nie jest std::exception
			{
				MessageBox(NULL, //pokazuje nam okienko z bledem (moze dzielenie przez 0?
					("Unexpected error"),
					_T("Blad!!!"),
					NULL);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}