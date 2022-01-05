#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

LONG WINAPI MainWindowProcedure(HWND,UINT,WPARAM,LPARAM);
BOOL bSetupPixelFormat(HDC hdc);
GLvoid drawScene(GLvoid);

HWND  hWnd;
const CHAR appName[] = "hello openGL";
HDC   ghDC;
HGLRC ghRC;


#define BLACK_INDEX     0
#define RED_INDEX       13
#define GREEN_INDEX     14
#define BLUE_INDEX      16
#define WIDTH           700
#define HEIGHT          450

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow){
		WNDCLASS windowClass;
		MSG Msg;

		windowClass.style=0;
    	windowClass.lpfnWndProc   = (WNDPROC)MainWindowProcedure;
    	windowClass.cbClsExtra    = 0;
    	windowClass.cbWndExtra    = 0;
    	windowClass.hInstance     = hInstance;
    	windowClass.hIcon         = LoadIcon (hInstance, "hello openGL");
    	windowClass.hCursor       = LoadCursor (NULL,IDC_ARROW);
    	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    	windowClass.lpszMenuName  = appName;
    	windowClass.lpszClassName = appName;

		if (!RegisterClass (&windowClass) ){
		MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
    	return FALSE;
		}
 		hWnd = CreateWindow (appName,
                          appName,
                          WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          WIDTH,
                          HEIGHT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
		if (!hWnd){
			MessageBox(NULL, "Window could not be created!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
  		 
		}

  		ShowWindow (hWnd, nCmdShow);
   		UpdateWindow (hWnd);
	
		while(GetMessage(&Msg, NULL, 0, 0) > 0)
    	{
    	    TranslateMessage(&Msg);
    	    DispatchMessage(&Msg);
    	}
    	return Msg.wParam;
	}

LONG WINAPI MainWindowProcedure(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam){

	RECT rect;
    PAINTSTRUCT    ps;

	 switch(uMsg)
    {
		 case WM_CREATE:
            ghDC = GetDC(hWnd);
            if (!bSetupPixelFormat(ghDC)){
            PostQuitMessage (0);
				}
            
            ghRC = wglCreateContext(ghDC);
            wglMakeCurrent(ghDC, ghRC);
            GetClientRect(hWnd, &rect);
            break;
 		case WM_PAINT:
            BeginPaint(hWnd, &ps);
			drawScene();
            EndPaint(hWnd, &ps);
        break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
	}

BOOL bSetupPixelFormat(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;
    
    ppfd = &pfd;
    
    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;
    
    pixelformat = ChoosePixelFormat(hdc, ppfd);
    
    if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 ) {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }
    
    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }
    
    return TRUE;
}


GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f,0.13f,0.17f,1.0f);
    glClear( GL_COLOR_BUFFER_BIT );
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(0, 1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(-1, -1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(1, -1);
	glEnd();
    SwapBuffers(ghDC);
}

