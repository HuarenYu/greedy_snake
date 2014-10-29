#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include "snake.h"
#include "food.h"

/*������Ϣ������*/
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
/*��ʼ�������ࣨ���ڵ����ԣ�*/
BOOL InitWindowsClass(HINSTANCE hInstance);
/*��ʼ������*/
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
/*����*/
void draw_snake(snake_body *snake,HDC hDC);
/*��ʳ��*/
void draw_food(food *f,HDC hDC);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int nCmdShow)
{
	MSG Message;
	if(!InitWindowsClass(hInstance))
	{
		return FALSE;
	}
	if(!InitWindows(hInstance,nCmdShow)) 
	{
		return FALSE;
	}
	while(GetMessage(&Message,0,0,0)) 
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

/*������Ϣ������*/
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	//��ʼ����
	static snake_body *snake = init_snake(100,100,20);
	//��ʼ��ʳ��
	static food *f = init_food(20);
	//��ť
	static HWND button;
	static int grade=0;
	static int level=1;
	static TCHAR fm[] = TEXT("�ɼ�:%d      �ȼ���%d");
	static TCHAR buffere[50];
	static int game_state = START;
	HDC hDC;//�豸�����ľ��
	HBRUSH hBrush;//��ȡ��ˢ	
	HPEN hPen;//��ȡ����
	PAINTSTRUCT PtStr;
	switch (iMessage)
	{
    case  WM_CREATE:
		button = CreateWindow( 
						TEXT("button"),
						TEXT("��ʼ��Ϸ"),
						WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						10,
						10,
						100,
						30,
						hWnd,
						(HMENU)1,
						((LPCREATESTRUCT)lParam)->hInstance,
						NULL
					); 
        return 0;
	case WM_PAINT:
		hDC = BeginPaint(hWnd,&PtStr);
		SetMapMode(hDC,MM_ANISOTROPIC);
		hPen = CreatePen(NULL,NULL,RGB(255,0,0)); 
		hBrush = CreateSolidBrush(RGB(255,111,111));
		SelectObject(hDC,hPen);
		SelectObject(hDC,hBrush);
		switch (game_state)
		{
		case START:
			break;
		case GAME:
			//����
			draw_snake(snake,hDC);
			//��ʳ��
			draw_food(f,hDC);
			break;
		case OVER:
			//����Ϸ�����Ļ���
			SetTextColor(hDC,RGB(255,0,0));
			SetBkColor(hDC,RGB(111,111,111));
			SelectObject(hDC,hPen);
			SelectObject(hDC,hBrush);
			TextOut(hDC,330,270,TEXT("GAME OVER"),9);
			break;
		}
		//����ʾ��
		hPen = CreatePen(NULL,NULL,RGB(111,111,111)); 
		hBrush = CreateSolidBrush(RGB(111,111,111));
		SelectObject(hDC,hPen);
		SelectObject(hDC,hBrush);
		Rectangle(hDC,0,0,800,50);
		//���ɼ��͵ȼ�
		SetTextColor(hDC,RGB(255,0,0));
		SetBkColor(hDC,RGB(111,111,111));
		SelectObject(hDC,hPen);
		SelectObject(hDC,hBrush);
		TextOut(hDC,150,20,buffere,wsprintf(buffere,fm,grade,level));
		EndPaint(hWnd,&PtStr);
		return 0;
	case WM_TIMER:
		//�ߵ��ƶ�
		move(snake);
		//�ж����Ƿ�Ե�ʳ��
		if(snake->head->l_x == f->l_x && snake->head->l_y == f->l_y) 
		{	
			++grade;
			add_head(snake,snake->direction);
			change_food_position(f);
		}
		//�жϵȼ�
		switch(grade)
		{
		case 1:
			level=2;
			KillTimer(hWnd,1);
			SetTimer(hWnd,1,400,NULL);
			break;
		case 2:
			level=3;
			KillTimer(hWnd,1);
			SetTimer(hWnd,1,300,NULL);
			break;
		case 3:
			level=4;
			KillTimer(hWnd,1);
			SetTimer(hWnd,1,200,NULL);
			break;
		case 4:
			level=4;
			KillTimer(hWnd,1);
			SetTimer(hWnd,1,100,NULL);
			break;
		case 5:
			level=4;
			KillTimer(hWnd,1);
			SetTimer(hWnd,1,50,NULL);
			break;	
		}
		//�ж����Ƿ�ײǽ��
		if(snake->head->l_x>800 || snake->head->l_x<0 || snake->head->l_y>600 || snake->head->l_y<60) 
		{
			KillTimer(hWnd,1);
			game_state = OVER;
		}
		//�ػ�
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_DOWN:
			snake->direction = DOWN;
			break;
		case VK_UP:
			snake->direction = UP;
			break;
		case VK_LEFT:
			snake->direction = LEFT;
			break;
		case VK_RIGHT:
			snake->direction = RIGHT;
			break;
		}
		return 0;
	case WM_COMMAND:
		switch(wParam)
		{
		case 1:
			game_state = GAME;
			level = 1;
			grade = 0;
			if(snake->length>3)
			{
				destroy(snake);
				snake = init_snake(100,100,20);
			}
			SetTimer(hWnd,1,500,NULL);
			break;
		}
		SetFocus (hWnd);
		return 0;
	case WM_DESTROY:
		destroy(snake);
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam) ;


}
/*��ʼ�������ࣨ���ڵ����ԣ�*/
BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS wndclass ;
        
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
        
	wndclass.lpfnWndProc   = WndProc ;
        
    wndclass.cbClsExtra    = 0 ;
        
    wndclass.cbWndExtra    = 0 ;
        
    wndclass.hInstance     = hInstance ;
        
    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
        
	wndclass.hCursor	   = LoadCursor (NULL, IDC_ARROW) ;
        
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
        
	wndclass.lpszMenuName  =  NULL ;
        
    wndclass.lpszClassName =  TEXT("GameWindow");

	return RegisterClass(&wndclass);
}
/*��ʼ������*/
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow)
{
	HWND    hwnd;
	hwnd = CreateWindow(TEXT("GameWindow"),     
        
						TEXT ("Snake"),  
        
						WS_OVERLAPPEDWINDOW, 
        
						100,            // ��ʼ������xλ��
        
						100,            // ��ʼ������yλ��
        
						800,            // initial x size
        
						600,            // initial y size
        
						NULL,           // parent window handle
        
						NULL,            // window menu handle
        
						hInstance,      // program instance handle
        
						NULL);          // creation parameters
        
	if(!hwnd)
	{
		return FALSE;
	}        
    ShowWindow(hwnd, nCmdShow) ;
    UpdateWindow(hwnd);	
	return TRUE;
}
void draw_snake(snake_body *snake,HDC hDC)
{
		//����
	snake_node *tmp;
	tmp=snake->head;
	for (int i=1;i<=snake->length;i++) 
	{
		Rectangle(hDC,tmp->l_x,tmp->l_y,tmp->r_x,tmp->r_y);
		tmp=tmp->next_node;
	}
}
void draw_food(food *f,HDC hDC)
{
	Rectangle(hDC,f->l_x,f->l_y,f->r_x,f->r_y);
}







