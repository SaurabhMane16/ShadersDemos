// Header Files 
#include <windows.h>
#include <stdio.h> //for file I/O
#include <stdlib.h> // for exit

//OpenGl Related Header files
#include <gl\GL.h>

//Link with OpenGl import library
#pragma comment(lib,"opengl32.lib")

/*

//Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//GLOBAL VARIABLE DECLARATIONS
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL bFullscreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;
FILE* gpFile = NULL;
BOOL bActiveWindow = FALSE;
BOOL bEscapeKeyIsPressed = FALSE;

//Entry-Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    //Function Declarations
    int initialize(void);
    void render(void);
    void DrawPortrait(void);
    void update(void);
    void uninitialize(void);

    // Variable Declarations
    WNDCLASSEX wndclass;
    HWND hwnd = NULL;
    MSG msg;
    TCHAR szAppName[] = TEXT("RTR7_SHS");
    BOOL bDone = FALSE;

    // code
    // Create Log File
    gpFile = fopen("Log.txt", "w");
    if (gpFile == NULL)
    {
        MessageBox(NULL, TEXT("Log File Creation Failed"), TEXT("Error"), MB_OK);
        exit(0);
    }
    else
    {
        fprintf(gpFile, "SHS : Program Started Successfully\n");
    }

    // WNDCLASSEX iNITIALIZATION
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    // Register Above WNDCLASS
    RegisterClassEx(&wndclass);

    //Centering
    int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create The Window
    hwnd = CreateWindowEx(WS_EX_APPWINDOW,
        szAppName,
        TEXT("My Frist RTR7 Program : Saeed Haroon Shaikh"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
        ScreenWidth / 2 - WIN_WIDTH / 2,
        ScreenHeight / 2 - WIN_HEIGHT / 2,
        WIN_WIDTH,
        WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

    //SET GLOBAL WINDOW HANDLE
    ghwnd = hwnd;

    int iResult = initialize();
    if (iResult != 0)
    {
        fprintf(gpFile, "SHS : WinMain() : initialize() Failed");
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    else
    {
        fprintf(gpFile, "SHS : WinMain() : initialize() Succeded");
    }
    // Show Window
    ShowWindow(hwnd, iCmdShow);

    //Update The Window To Point Its Background
    UpdateWindow(hwnd);

    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    // Game Loop
    while (bDone == FALSE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                bDone = TRUE;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (bActiveWindow == TRUE)
            {
                if (bEscapeKeyIsPressed == TRUE)
                    bDone = TRUE;
                //Render
                render();
                //Update
                update();
            }
        }
    }

    //uninitialize
    uninitialize();

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    //FUNCTION DECLARATIONS
    void resize(int, int);
    void toggleFullScreen(void);
    void uninitialize(void);

    // Code
    switch (iMsg)
    {
    case WM_CREATE:
        memset(&wpPrev, 0, sizeof(WINDOWPLACEMENT));
        wpPrev.length = sizeof(WINDOWPLACEMENT);
        break;
    case WM_SETFOCUS:
        bActiveWindow = TRUE;
        break;
    case WM_KILLFOCUS:
        bActiveWindow = FALSE;
        break;
    case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            bEscapeKeyIsPressed = TRUE;
            break;

        default:
            break;
        }
        break;
    case WM_CHAR:
        switch (wParam)
        {
        case 'F':
        case 'f':
            if (bFullscreen == FALSE)
            {
                toggleFullScreen();
                bFullscreen = TRUE;
            }
            else
            {
                toggleFullScreen();
                bFullscreen = FALSE;
            }
            break;
        default:
            break;
        }
        break;

    case WM_CLOSE:
        uninitialize();
        break;

    case WM_DESTROY:
        PostQuitMessage(100);
        break;

    default:
        break;
    }

    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullScreen(void)
{
    //Variable Declarations
    MONITORINFO mi;

    //CODE
    if (bFullscreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            memset(&mi, 0, sizeof(MONITORINFO));
            mi.cbSize = sizeof(MONITORINFO);
            if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }

        ShowCursor(FALSE);
    }
    else
    {
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowCursor(TRUE);
    }


}

int initialize(void)
{
    //Function Declarations
    void resize(int, int);
    void printGLInfo(void);

    //Variable Declarations
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormatIndex;

    //code
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1; //Conventional
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;

    ghdc = GetDC(ghwnd);
    if (ghdc == NULL)
    {
        return -1;
    }

    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd); //Index is 1 based not 0 based

    if (iPixelFormatIndex == 0)
        return -2;

    if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
        return -3;

    ghrc = wglCreateContext(ghdc);
    if (ghrc == NULL)
        return -4;

    if (wglMakeCurrent(ghdc, ghrc) == FALSE)
        return -5;

    //print Opengl Info
    printGLInfo();

    //Choose Screen clearing color as blue
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    //Warmup resize
    resize(WIN_WIDTH, WIN_HEIGHT);

    return(0);
}

void printGLInfo(void)
{
    //Code
    fprintf(gpFile, "OpenGL Vendor : %s\n", glGetString(GL_VENDOR));
    fprintf(gpFile, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
    fprintf(gpFile, "OpenGL	Version : %s\n", glGetString(GL_VERSION));
}

void resize(int width, int height)
{
    if (height <= 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-5.0, 5.0,
        -5.0, 5.0,
        -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void render(void)
{
    //code
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawPortrait();

    //do double buffering
    SwapBuffers(ghdc);

}
*/

void DrawPortrait(void)
{
    glPushMatrix();
	glTranslatef(0.1f, 0.0f, 0.0f);
	glScalef(0.3f, 0.2f, 0.0f);

    glLineWidth(3.0f);

    glBegin(GL_LINES);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.688285f, 3.226030f);
    glVertex2f(0.941392f, 3.112131f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.688285f, 3.226030f);
    glVertex2f(-0.324145f, 3.181736f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.324145f, 3.181736f);
    glVertex2f(-0.473786f, 3.152390f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.473786f, 3.152390f);
    glVertex2f(-0.259327f, 3.415179f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.259327f, 3.415179f);
    glVertex2f(-0.165689f, 3.415179f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.165689f, 3.415179f);
    glVertex2f(0.257189f, 3.397055f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.257189f, 3.397055f);
    glVertex2f(0.347806f, 3.412158f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.347806f, 3.412158f);
    glVertex2f(0.688285f, 3.226030f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.257189f, 3.397055f);
    glVertex2f(-0.324145f, 3.181736f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.324145f, 3.181736f);
    glVertex2f(0.688285f, 3.226030f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.688285f, 3.226030f);
    glVertex2f(0.867342f, 2.956054f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.867342f, 2.956054f);
    glVertex2f(1.021391f, 2.765758f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.021391f, 2.765758f);
    glVertex2f(0.951918f, 2.989280f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.951918f, 2.989280f);
    glVertex2f(0.941392f, 3.112131f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.688285f, 3.226030f);
    glVertex2f(0.941392f, 3.112131f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.941392f, 3.112131f);
    glVertex2f(1.015349f, 3.173534f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.015349f, 3.173534f);
    glVertex2f(1.075761f, 3.279253f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.941392f, 3.112131f);
    glVertex2f(0.825054f, 3.348726f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.825054f, 3.348726f);
    glVertex2f(0.872082f, 3.356076f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.872082f, 3.356076f);
    glVertex2f(1.075761f, 3.279253f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.075761f, 3.279253f);
    glVertex2f(1.127110f, 3.221863f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.127110f, 3.221863f);
    glVertex2f(1.184501f, 2.980218f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.941392f, 3.112131f);
    glVertex2f(1.184501f, 2.980218f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.184501f, 2.980218f);
    glVertex2f(1.112417f, 2.607163f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.021391f, 2.765758f);
    glVertex2f(1.087843f, 2.641915f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.112417f, 2.607163f);
    glVertex2f(1.208665f, 2.448600f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.087843f, 2.641915f);
    glVertex2f(1.112417f, 2.607163f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.112417f, 2.607163f);
    glVertex2f(1.133972f, 2.637956f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.092916f, 2.558922f);
    glVertex2f(1.112417f, 2.607163f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.092916f, 2.558922f);
    glVertex2f(1.048576f, 2.521093f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.138407f, 2.564347f);
    glVertex2f(1.266761f, 2.446486f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.266761f, 2.446486f);
    glVertex2f(1.502970f, 2.154053f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.236151f, 2.333521f);
    glVertex2f(1.274613f, 2.299431f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.274613f, 2.299431f);
    glVertex2f(1.502970f, 2.154053f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.502970f, 2.154053f);
    glVertex2f(1.505187f, 2.360288f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.266761f, 2.446486f);
    glVertex2f(1.505187f, 2.360288f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.505187f, 2.360288f);
    glVertex2f(1.327794f, 2.581939f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.133972f, 2.637956f);
    glVertex2f(1.327794f, 2.581939f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.327794f, 2.581939f);
    glVertex2f(1.493957f, 2.534330f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.493957f, 2.534330f);
    glVertex2f(1.495377f, 2.480492f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.495377f, 2.480492f);
    glVertex2f(1.609403f, 2.361974f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.609403f, 2.361974f);
    glVertex2f(1.505187f, 2.360288f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.609403f, 2.361974f);
    glVertex2f(1.714350f, 2.353465f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.493957f, 2.534330f);
    glVertex2f(1.714350f, 2.353465f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.714350f, 2.353465f);
    glVertex2f(1.735623f, 2.757653f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.493957f, 2.534330f);
    glVertex2f(1.610499f, 2.686550f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.610499f, 2.686550f);
    glVertex2f(1.735623f, 2.757653f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.493957f, 2.534330f);
    glVertex2f(1.392418f, 2.743471f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.392418f, 2.743471f);
    glVertex2f(1.610499f, 2.686550f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.392418f, 2.743471f);
    glVertex2f(1.515801f, 2.639942f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.515801f, 2.639942f);
    glVertex2f(1.610499f, 2.686550f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.515801f, 2.639942f);
    glVertex2f(1.493957f, 2.534330f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.392418f, 2.743471f);
    glVertex2f(1.133972f, 2.637956f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.133972f, 2.637956f);
    glVertex2f(1.137477f, 2.686270f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.137477f, 2.686270f);
    glVertex2f(1.225105f, 2.831868f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.225105f, 2.831868f);
    glVertex2f(1.392418f, 2.743471f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.222409f, 2.852090f);
    glVertex2f(1.225105f, 2.831868f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.222409f, 2.852090f);
    glVertex2f(1.278188f, 2.940642f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.278188f, 2.940642f);
    glVertex2f(1.305048f, 2.951756f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.305048f, 2.951756f);
    glVertex2f(1.324499f, 2.881363f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.324499f, 2.881363f);
    glVertex2f(1.334687f, 2.823937f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.334687f, 2.823937f);
    glVertex2f(1.392418f, 2.743471f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.735623f, 2.757653f);
    glVertex2f(1.451410f, 3.232583f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.451410f, 3.232583f);
    glVertex2f(1.591944f, 2.808914f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.591944f, 2.808914f);
    glVertex2f(1.610499f, 2.686550f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.127110f, 3.221863f);
    glVertex2f(1.610499f, 2.686550f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.305048f, 2.951756f);
    glVertex2f(1.293999f, 2.985679f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.293999f, 2.985679f);
    glVertex2f(1.315691f, 3.002365f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.293999f, 2.985679f);
    glVertex2f(1.236434f, 3.049919f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.236434f, 3.049919f);
    glVertex2f(1.202228f, 3.114993f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.202228f, 3.114993f);
    glVertex2f(1.127110f, 3.221863f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.202228f, 3.114993f);
    glVertex2f(1.315691f, 3.002365f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.610499f, 2.686550f);
    glVertex2f(1.714350f, 2.353465f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.825054f, 3.348726f);
    glVertex2f(0.733264f, 3.525901f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.347806f, 3.412158f);
    glVertex2f(0.733264f, 3.525901f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.733264f, 3.525901f);
    glVertex2f(0.872082f, 3.507026f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.872082f, 3.507026f);
    glVertex2f(1.057274f, 3.418599f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.057274f, 3.418599f);
    glVertex2f(1.075761f, 3.279253f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.057274f, 3.418599f);
    glVertex2f(1.451410f, 3.232583f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.127110f, 3.221863f);
    glVertex2f(1.451410f, 3.232583f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.057274f, 3.418599f);
    glVertex2f(1.263463f, 3.567981f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.263463f, 3.567981f);
    glVertex2f(1.451410f, 3.232583f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(1.057274f, 3.418599f);
    glVertex2f(0.924725f, 3.797313f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.924725f, 3.797313f);
    glVertex2f(1.263463f, 3.567981f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.924725f, 3.797313f);
    glVertex2f(0.601998f, 3.816143f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.601998f, 3.816143f);
    glVertex2f(0.622364f, 3.765227f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.622364f, 3.765227f);
    glVertex2f(1.057274f, 3.418599f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.423792f, 3.874696f);
    glVertex2f(0.622364f, 3.765227f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.423792f, 3.874696f);
    glVertex2f(0.601998f, 3.816143f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.601998f, 3.816143f);
    glVertex2f(0.708921f, 3.976528f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.708921f, 3.976528f);
    glVertex2f(0.924725f, 3.797313f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.423792f, 3.874696f);
    glVertex2f(0.006281f, 3.658304f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.006281f, 3.658304f);
    glVertex2f(0.339781f, 3.640483f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.339781f, 3.640483f);
    glVertex2f(0.733264f, 3.525901f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.006281f, 3.658304f);
    glVertex2f(-0.070093f, 3.915429f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.070093f, 3.915429f);
    glVertex2f(0.423792f, 3.874696f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.423792f, 3.874696f);
    glVertex2f(0.455036f, 4.059151f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.455036f, 4.059151f);
    glVertex2f(0.601998f, 3.816143f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.455036f, 4.059151f);
    glVertex2f(0.708921f, 3.976528f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.455036f, 4.059151f);
    glVertex2f(-0.095782f, 4.140154f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.095782f, 4.140154f);
    glVertex2f(0.423792f, 3.874696f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.095782f, 4.140154f);
    glVertex2f(-0.334161f, 3.957319f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.334161f, 3.957319f);
    glVertex2f(-0.070093f, 3.915429f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.334161f, 3.957319f);
    glVertex2f(-0.702144f, 3.989720f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.702144f, 3.989720f);
    glVertex2f(-0.095782f, 4.140154f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.334161f, 3.957319f);
    glVertex2f(-0.514681f, 3.862430f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.514681f, 3.862430f);
    glVertex2f(-0.584112f, 3.783742f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.584112f, 3.783742f);
    glVertex2f(-0.070093f, 3.915429f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.584112f, 3.783742f);
    glVertex2f(-0.262416f, 3.707368f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.262416f, 3.707368f);
    glVertex2f(0.006281f, 3.658304f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.006281f, 3.658304f);
    glVertex2f(0.347806f, 3.412158f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.006281f, 3.658304f);
    glVertex2f(-0.165689f, 3.415179f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(0.006281f, 3.658304f);
    glVertex2f(-0.412849f, 3.411130f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.412849f, 3.411130f);
    glVertex2f(-0.259327f, 3.415179f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.584112f, 3.783742f);
    glVertex2f(-1.063185f, 3.406501f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.063185f, 3.406501f);
    glVertex2f(-0.635028f, 3.526848f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.635028f, 3.526848f);
    glVertex2f(0.006281f, 3.658304f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.635028f, 3.526848f);
    glVertex2f(-0.734545f, 3.362528f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.734545f, 3.362528f);
    glVertex2f(-0.412849f, 3.411130f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.063185f, 3.406501f);
    glVertex2f(-0.734545f, 3.362528f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.734545f, 3.362528f);
    glVertex2f(-0.871093f, 3.263011f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.734545f, 3.362528f);
    glVertex2f(-0.588741f, 3.353271f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.588741f, 3.353271f);
    glVertex2f(-0.412849f, 3.411130f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.871093f, 3.263011f);
    glVertex2f(-0.743803f, 3.293098f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.743803f, 3.293098f);
    glVertex2f(-0.588741f, 3.353271f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.743803f, 3.293098f);
    glVertex2f(-0.473786f, 3.152390f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.743803f, 3.293098f);
    glVertex2f(-0.915065f, 3.045461f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.915065f, 3.045461f);
    glVertex2f(-0.679001f, 3.073233f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.679001f, 3.073233f);
    glVertex2f(-0.514369f, 3.173538f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.030784f, 2.846426f);
    glVertex2f(-0.679001f, 3.073233f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.915065f, 3.045461f);
    glVertex2f(-1.030784f, 2.846426f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.915065f, 3.045461f);
    glVertex2f(-1.243705f, 2.655029f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.243705f, 2.655029f);
    glVertex2f(-1.118729f, 2.702936f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.118729f, 2.702936f);
    glVertex2f(-1.030784f, 2.846426f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.063185f, 3.406501f);
    glVertex2f(-1.086328f, 3.225981f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.086328f, 3.225981f);
    glVertex2f(-0.782657f, 3.327464f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.086328f, 3.225981f);
    glVertex2f(-1.278420f, 3.013060f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.278420f, 3.013060f);
    glVertex2f(-0.871093f, 3.263011f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.278420f, 3.013060f);
    glVertex2f(-1.063185f, 3.406501f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.063185f, 3.406501f);
    glVertex2f(-0.896551f, 3.769856f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.102529f, 3.630994f);
    glVertex2f(-1.063185f, 3.406501f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.102529f, 3.630994f);
    glVertex2f(-0.896551f, 3.769856f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-0.896551f, 3.769856f);
    glVertex2f(-0.702144f, 3.989720f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.188160f, 3.758284f);
    glVertex2f(-0.896551f, 3.769856f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.188160f, 3.758284f);
    glVertex2f(-0.702144f, 3.989720f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.188160f, 3.758284f);
    glVertex2f(-1.442474f, 3.406393f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.406393f);
    glVertex2f(-1.102529f, 3.630994f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.188160f, 3.758284f);
    glVertex2f(-1.102529f, 3.630994f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.406393f);
    glVertex2f(-1.063185f, 3.406501f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.406393f);
    glVertex2f(-1.278420f, 3.013060f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.406393f);
    glVertex2f(-1.442474f, 3.205127f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.205127f);
    glVertex2f(-1.278420f, 3.013060f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.205127f);
    glVertex2f(-1.509856f, 3.040832f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.509856f, 3.040832f);
    glVertex2f(-1.712131f, 2.749223f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.442474f, 3.406393f);
    glVertex2f(-1.560772f, 3.168122f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.560772f, 3.168122f);
    glVertex2f(-1.602430f, 3.017689f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.602430f, 3.017689f);
    glVertex2f(-1.712131f, 2.749223f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.712131f, 2.749223f);
    glVertex2f(-1.561929f, 2.817960f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.561929f, 2.817960f);
    glVertex2f(-1.278420f, 3.013060f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.278420f, 3.013060f);
    glVertex2f(-1.243705f, 2.655029f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.243705f, 2.655029f);
    glVertex2f(-1.246250f, 2.469185f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.243705f, 2.655029f);
    glVertex2f(-1.340445f, 2.698307f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.340445f, 2.698307f);
    glVertex2f(-1.488101f, 2.759406f);

    glColor3f(0.10f, 0.09f, 0.08f);
    glVertex2f(-1.488101f, 2.759406f);
    glVertex2f(-1.278420f, 3.013060f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.712131f, 2.749223f);
    glVertex2f(-1.488101f, 2.759406f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.488101f, 2.759406f);
    glVertex2f(-1.574658f, 2.509918f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.574658f, 2.509918f);
    glVertex2f(-1.243705f, 2.655029f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.574658f, 2.509918f);
    glVertex2f(-1.393907f, 2.278251f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.393907f, 2.278251f);
    glVertex2f(-1.243705f, 2.655029f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.393907f, 2.278251f);
    glVertex2f(-1.284437f, 2.382628f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.284437f, 2.382628f);
    glVertex2f(-1.246250f, 2.469185f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.284437f, 2.382628f);
    glVertex2f(-1.174968f, 2.471731f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.174968f, 2.471731f);
    glVertex2f(-1.140576f, 2.601330f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.140576f, 2.601330f);
    glVertex2f(-1.118729f, 2.702936f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.030784f, 2.846426f);
    glVertex2f(-1.140576f, 2.349748f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.174968f, 2.471731f);
    glVertex2f(-1.140576f, 2.349748f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.140576f, 2.349748f);
    glVertex2f(-1.195335f, 2.186602f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.393907f, 2.278251f);
    glVertex2f(-1.195335f, 2.186602f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.393907f, 2.278251f);
    glVertex2f(-1.392158f, 2.098166f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.392158f, 2.098166f);
    glVertex2f(-1.195335f, 2.186602f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.712131f, 2.749223f);
    glVertex2f(-1.574658f, 2.509918f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.712131f, 2.749223f);
    glVertex2f(-1.679036f, 2.395357f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.679036f, 2.395357f);
    glVertex2f(-1.628120f, 1.988030f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.628120f, 1.988030f);
    glVertex2f(-1.518651f, 1.578157f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.628120f, 1.988030f);
    glVertex2f(-1.579750f, 2.122957f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.579750f, 2.122957f);
    glVertex2f(-1.564475f, 2.324075f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.564475f, 2.324075f);
    glVertex2f(-1.597570f, 2.413178f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.597570f, 2.413178f);
    glVertex2f(-1.574658f, 2.509918f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.631282f, 2.608486f);
    glVertex2f(-1.597570f, 2.413178f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.597570f, 2.413178f);
    glVertex2f(-1.628120f, 1.988030f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.628120f, 1.988030f);
    glVertex2f(-1.554292f, 1.893835f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.554292f, 1.893835f);
    glVertex2f(-1.575987f, 1.792835f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.575987f, 1.792835f);
    glVertex2f(-1.505922f, 1.690172f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.505922f, 1.690172f);
    glVertex2f(-1.518651f, 1.578157f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.505922f, 1.690172f);
    glVertex2f(-1.457552f, 1.842920f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.575987f, 1.792835f);
    glVertex2f(-1.457552f, 1.842920f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.457552f, 1.842920f);
    glVertex2f(-1.485555f, 1.972755f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.628120f, 1.988030f);
    glVertex2f(-1.485555f, 1.972755f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.485555f, 1.972755f);
    glVertex2f(-1.392158f, 2.098166f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.628120f, 1.988030f);
    glVertex2f(-1.574726f, 1.982309f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.574726f, 1.982309f);
    glVertex2f(-1.392158f, 2.098166f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.579750f, 2.122957f);
    glVertex2f(-1.392158f, 2.098166f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.579750f, 2.122957f);
    glVertex2f(-1.472826f, 2.265522f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.472826f, 2.265522f);
    glVertex2f(-1.464907f, 2.369252f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.472826f, 2.265522f);
    glVertex2f(-1.437185f, 2.240064f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.437185f, 2.240064f);
    glVertex2f(-1.393907f, 2.278251f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.437185f, 2.240064f);
    glVertex2f(-1.393907f, 2.278251f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.393907f, 2.278251f);
    glVertex2f(-1.340898f, 2.175318f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.340898f, 2.175318f);
    glVertex2f(-1.392442f, 2.127404f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.429176f, 1.960956f);
    glVertex2f(-1.457552f, 1.842920f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.429176f, 1.960956f);
    glVertex2f(-1.217264f, 2.167192f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.217264f, 2.167192f);
    glVertex2f(-1.317544f, 1.906086f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.341841f, 1.997533f);
    glVertex2f(-1.317544f, 1.906086f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.341841f, 1.997533f);
    glVertex2f(-1.217264f, 2.167192f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.341841f, 1.997533f);
    glVertex2f(-1.457552f, 1.842920f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.457552f, 1.842920f);
    glVertex2f(-1.330789f, 1.873921f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.330789f, 1.873921f);
    glVertex2f(-1.328896f, 1.660117f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.370479f, 1.783949f);
    glVertex2f(-1.328896f, 1.660117f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.370479f, 1.783949f);
    glVertex2f(-1.330789f, 1.873921f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.457552f, 1.842920f);
    glVertex2f(-1.395109f, 1.706937f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.395109f, 1.706937f);
    glVertex2f(-1.327518f, 1.596132f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.327518f, 1.596132f);
    glVertex2f(-1.328896f, 1.660117f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.457552f, 1.842920f);
    glVertex2f(-1.424247f, 1.522613f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.505922f, 1.690172f);
    glVertex2f(-1.424247f, 1.522613f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.424247f, 1.522613f);
    glVertex2f(-1.327518f, 1.596132f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.328896f, 1.660117f);
    glVertex2f(-1.174215f, 1.746613f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.174215f, 1.746613f);
    glVertex2f(-1.062106f, 1.901697f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.062106f, 1.901697f);
    glVertex2f(-0.912627f, 2.045571f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.327518f, 1.596132f);
    glVertex2f(-1.316451f, 1.422516f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.424247f, 1.522613f);
    glVertex2f(-1.316451f, 1.422516f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.373956f, 1.475914f);
    glVertex2f(-1.347250f, 1.530312f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.347250f, 1.530312f);
    glVertex2f(-1.327518f, 1.596132f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.373956f, 1.475914f);
    glVertex2f(-1.371449f, 1.433516f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.371449f, 1.433516f);
    glVertex2f(-1.394548f, 1.433516f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.424247f, 1.522613f);
    glVertex2f(-1.394548f, 1.433516f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.394548f, 1.433516f);
    glVertex2f(-1.341841f, 1.192470f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.316451f, 1.422516f);
    glVertex2f(-1.224746f, 1.083447f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.341841f, 1.192470f);
    glVertex2f(-1.290034f, 1.138534f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.316451f, 1.422516f);
    glVertex2f(-1.290034f, 1.138534f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.174215f, 1.746613f);
    glVertex2f(-1.224746f, 1.083447f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.518651f, 1.578157f);
    glVertex2f(-1.612390f, 1.444568f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.612390f, 1.444568f);
    glVertex2f(-1.530781f, 1.440487f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.530781f, 1.440487f);
    glVertex2f(-1.442474f, 1.393736f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.442474f, 1.393736f);
    glVertex2f(-1.341841f, 1.192470f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.442474f, 1.393736f);
    glVertex2f(-1.522620f, 1.050804f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.612390f, 1.444568f);
    glVertex2f(-1.522620f, 1.050804f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.522620f, 1.050804f);
    glVertex2f(-1.341386f, 1.137235f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.341386f, 1.137235f);
    glVertex2f(-1.341841f, 1.192470f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.341386f, 1.137235f);
    glVertex2f(-1.387455f, 0.984288f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.387455f, 0.984288f);
    glVertex2f(-1.427995f, 0.800015f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.522620f, 1.050804f);
    glVertex2f(-1.427995f, 0.800015f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.387455f, 0.984288f);
    glVertex2f(-1.219920f, 0.808769f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.427995f, 0.800015f);
    glVertex2f(-1.322108f, 0.743435f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.322108f, 0.743435f);
    glVertex2f(-1.219920f, 0.808769f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.387455f, 0.984288f);
    glVertex2f(-1.320433f, 0.845624f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.320433f, 0.845624f);
    glVertex2f(-1.219920f, 0.808769f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.427995f, 0.800015f);
    glVertex2f(-1.384091f, 0.616119f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.384091f, 0.616119f);
    glVertex2f(-1.219920f, 0.808769f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.322108f, 0.743435f);
    glVertex2f(-1.316082f, 0.695925f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.384091f, 0.616119f);
    glVertex2f(-1.149561f, 0.475401f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.219920f, 0.808769f);
    glVertex2f(-1.149561f, 0.475401f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.290034f, 1.138534f);
    glVertex2f(-1.219920f, 0.808769f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.224746f, 1.083447f);
    glVertex2f(-1.057424f, 0.567538f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.057424f, 0.567538f);
    glVertex2f(-1.085903f, 0.460324f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.149561f, 0.475401f);
    glVertex2f(-1.085903f, 0.460324f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.149561f, 0.475401f);
    glVertex2f(-0.945642f, 0.047294f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.057424f, 0.567538f);
    glVertex2f(-0.945642f, 0.047294f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.224746f, 1.083447f);
    glVertex2f(-0.797017f, 0.747264f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.057424f, 0.567538f);
    glVertex2f(-0.797017f, 0.747264f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.797017f, 0.747264f);
    glVertex2f(-0.837634f, 0.289399f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.057424f, 0.567538f);
    glVertex2f(-0.837634f, 0.289399f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.837634f, 0.289399f);
    glVertex2f(-0.856096f, 0.119546f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.856096f, 0.119546f);
    glVertex2f(-0.945642f, 0.047294f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.856096f, 0.119546f);
    glVertex2f(-0.675166f, 0.071545f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.837634f, 0.289399f);
    glVertex2f(-0.675166f, 0.071545f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.837634f, 0.289399f);
    glVertex2f(-0.531160f, 0.156471f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.797017f, 0.747264f);
    glVertex2f(-0.531160f, 0.156471f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.531160f, 0.156471f);
    glVertex2f(-0.257918f, -0.164773f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.675166f, 0.071545f);
    glVertex2f(-0.497928f, -0.120463f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.497928f, -0.120463f);
    glVertex2f(-0.257918f, -0.164773f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.675166f, 0.071545f);
    glVertex2f(-0.464991f, 0.078678f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.464991f, 0.078678f);
    glVertex2f(-0.456644f, -0.024566f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.456644f, -0.024566f);
    glVertex2f(-0.416651f, -0.067521f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.416651f, -0.067521f);
    glVertex2f(-0.497928f, -0.120463f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.856096f, 0.119546f);
    glVertex2f(-0.665889f, -0.121871f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.945642f, 0.047294f);
    glVertex2f(-0.665889f, -0.121871f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.611490f, -0.121871f);
    glVertex2f(-0.497928f, -0.120463f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.665889f, -0.121871f);
    glVertex2f(-0.659845f, -0.248801f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.945642f, 0.047294f);
    glVertex2f(-0.659845f, -0.248801f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.659845f, -0.248801f);
    glVertex2f(-0.229130f, -0.464861f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.257918f, -0.164773f);
    glVertex2f(-0.229130f, -0.464861f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.659845f, -0.248801f);
    glVertex2f(-0.451316f, -0.306222f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.451316f, -0.306222f);
    glVertex2f(-0.229130f, -0.464861f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.451316f, -0.306222f);
    glVertex2f(-0.245979f, -0.289221f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.497928f, -0.120463f);
    glVertex2f(-0.451316f, -0.306222f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.659845f, -0.248801f);
    glVertex2f(-0.497928f, -0.120463f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.257918f, -0.164773f);
    glVertex2f(0.494616f, -0.124893f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.494616f, -0.124893f);
    glVertex2f(0.509727f, -0.378754f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.245979f, -0.289221f);
    glVertex2f(0.062449f, -0.418042f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.055152f, -0.154027f);
    glVertex2f(0.062449f, -0.418042f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.055152f, -0.154027f);
    glVertex2f(-0.137454f, -0.334549f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.531160f, 0.156471f);
    glVertex2f(-0.100747f, 0.283097f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.100747f, 0.283097f);
    glVertex2f(0.035249f, 0.198477f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.035249f, 0.198477f);
    glVertex2f(-0.257918f, -0.164773f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.035249f, 0.198477f);
    glVertex2f(0.494616f, -0.124893f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.062449f, -0.418042f);
    glVertex2f(0.189116f, -0.141083f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.189116f, -0.141083f);
    glVertex2f(0.313287f, -0.399909f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.313287f, -0.399909f);
    glVertex2f(0.494616f, -0.124893f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.062449f, -0.418042f);
    glVertex2f(0.313287f, -0.399909f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.313287f, -0.399909f);
    glVertex2f(0.509727f, -0.378754f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.245979f, -0.289221f);
    glVertex2f(-0.115858f, -0.460352f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.229130f, -0.464861f);
    glVertex2f(-0.115858f, -0.460352f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.115858f, -0.460352f);
    glVertex2f(0.062449f, -0.418042f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.062449f, -0.418042f);
    glVertex2f(-0.058437f, -0.538928f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.062449f, -0.418042f);
    glVertex2f(0.252844f, -0.557061f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.252844f, -0.557061f);
    glVertex2f(0.313287f, -0.399909f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.252844f, -0.557061f);
    glVertex2f(0.509727f, -0.378754f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.509727f, -0.378754f);
    glVertex2f(0.588303f, -0.484529f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.252844f, -0.557061f);
    glVertex2f(0.588303f, -0.484529f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.229130f, -0.464861f);
    glVertex2f(-0.058437f, -0.538928f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.115858f, -0.460352f);
    glVertex2f(-0.058437f, -0.538928f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.659845f, -0.248801f);
    glVertex2f(-0.103769f, -0.862298f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.257918f, -0.164773f);
    glVertex2f(-0.137454f, -0.334549f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.494616f, -0.124893f);
    glVertex2f(0.706166f, 0.301230f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.100747f, 0.283097f);
    glVertex2f(0.174268f, 0.337495f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.174268f, 0.337495f);
    glVertex2f(0.706166f, 0.301230f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.494616f, -0.124893f);
    glVertex2f(0.808919f, -0.130938f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.808919f, -0.130938f);
    glVertex2f(0.941894f, 0.289141f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.706166f, 0.301230f);
    glVertex2f(0.941894f, 0.289141f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.941894f, 0.289141f);
    glVertex2f(0.494616f, -0.124893f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.808919f, -0.130938f);
    glVertex2f(0.688034f, -0.266934f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.688034f, -0.266934f);
    glVertex2f(0.509727f, -0.378754f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.494616f, -0.124893f);
    glVertex2f(0.688034f, -0.266934f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.688034f, -0.266934f);
    glVertex2f(0.821008f, -0.342488f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.509727f, -0.378754f);
    glVertex2f(0.821008f, -0.342488f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.821008f, -0.342488f);
    glVertex2f(0.588303f, -0.484529f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.821008f, -0.342488f);
    glVertex2f(0.966071f, -0.185336f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.808919f, -0.130938f);
    glVertex2f(0.966071f, -0.185336f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.941894f, 0.289141f);
    glVertex2f(0.995170f, 0.034352f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.995170f, 0.034352f);
    glVertex2f(0.912748f, -0.061807f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.912748f, -0.061807f);
    glVertex2f(0.808919f, -0.130938f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.995170f, 0.034352f);
    glVertex2f(0.966071f, -0.185336f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.966071f, -0.185336f);
    glVertex2f(1.123664f, -0.166073f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.821008f, -0.342488f);
    glVertex2f(1.123664f, -0.166073f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.123664f, -0.166073f);
    glVertex2f(1.291891f, 0.270629f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.291891f, 0.270629f);
    glVertex2f(0.995170f, 0.034352f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.941894f, 0.289141f);
    glVertex2f(1.291891f, 0.270629f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.291891f, 0.270629f);
    glVertex2f(1.280901f, 0.075563f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.280901f, 0.075563f);
    glVertex2f(1.123664f, -0.166073f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.280901f, 0.075563f);
    glVertex2f(1.511683f, 0.427231f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.291891f, 0.270629f);
    glVertex2f(1.511683f, 0.427231f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.797357f, 0.619550f);
    glVertex2f(0.706166f, 0.301230f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.797357f, 0.619550f);
    glVertex2f(0.941894f, 0.289141f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.941894f, 0.289141f);
    glVertex2f(1.006160f, 0.611308f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.797357f, 0.619550f);
    glVertex2f(1.003413f, 0.957481f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(1.003413f, 0.957481f);
    glVertex2f(1.006160f, 0.611308f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.003413f, 0.957481f);
    glVertex2f(1.357828f, 0.734941f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357828f, 0.734941f);
    glVertex2f(0.941894f, 0.289141f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357828f, 0.734941f);
    glVertex2f(1.291891f, 0.270629f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357828f, 0.734941f);
    glVertex2f(1.511683f, 0.427231f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357828f, 0.734941f);
    glVertex2f(1.561136f, 0.800879f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.561136f, 0.800879f);
    glVertex2f(1.511683f, 0.427231f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.003413f, 0.957481f);
    glVertex2f(1.424126f, 1.362449f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.424126f, 1.362449f);
    glVertex2f(1.357828f, 0.734941f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.545128f, 1.263192f);
    glVertex2f(1.357828f, 0.734941f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.545128f, 1.263192f);
    glVertex2f(1.561136f, 0.800879f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.424126f, 1.362449f);
    glVertex2f(1.481647f, 1.853594f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.481647f, 1.853594f);
    glVertex2f(1.545128f, 1.263192f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.702895f, 0.946525f);
    glVertex2f(1.003413f, 0.957481f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.685196f, 1.225282f);
    glVertex2f(1.003413f, 0.957481f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.406438f, 1.216433f);
    glVertex2f(0.685196f, 1.225282f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.406438f, 1.216433f);
    glVertex2f(0.702895f, 0.946525f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.123256f, 1.645632f);
    glVertex2f(0.406438f, 1.216433f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.123256f, 1.645632f);
    glVertex2f(0.114406f, 1.265105f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.114406f, 1.265105f);
    glVertex2f(0.260422f, 1.269530f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.260422f, 1.269530f);
    glVertex2f(0.406438f, 1.216433f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.368917f, 1.595001f);
    glVertex2f(0.685196f, 1.225282f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.368917f, 1.595001f);
    glVertex2f(0.694046f, 1.601384f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.694046f, 1.601384f);
    glVertex2f(1.087846f, 1.734126f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(1.087846f, 1.734126f);
    glVertex2f(0.866610f, 1.512890f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.866610f, 1.512890f);
    glVertex2f(0.541361f, 1.393421f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.087846f, 1.734126f);
    glVertex2f(1.424126f, 1.362449f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.291384f, 1.942088f);
    glVertex2f(1.424126f, 1.362449f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.291384f, 1.942088f);
    glVertex2f(1.481647f, 1.853594f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.291384f, 1.942088f);
    glVertex2f(1.087846f, 1.734126f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.074572f, 2.035008f);
    glVertex2f(1.291384f, 1.942088f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.797017f, 0.747264f);
    glVertex2f(-0.447534f, 1.220858f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.447534f, 1.220858f);
    glVertex2f(-0.425411f, 1.004046f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.425411f, 1.004046f);
    glVertex2f(-0.513905f, 0.804933f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.797017f, 0.747264f);
    glVertex2f(-0.513905f, 0.804933f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.224746f, 1.083447f);
    glVertex2f(-0.881158f, 1.304928f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.881158f, 1.304928f);
    glVertex2f(-0.522755f, 1.335901f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.522755f, 1.335901f);
    glVertex2f(-0.416561f, 1.543863f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.969652f, 1.384573f);
    glVertex2f(-0.881158f, 1.304928f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.969652f, 1.384573f);
    glVertex2f(-0.713018f, 1.450944f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.713018f, 1.450944f);
    glVertex2f(-0.416561f, 1.543863f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.361036f, 1.668383f);
    glVertex2f(-0.416561f, 1.543863f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.361036f, 1.668383f);
    glVertex2f(-0.540150f, 1.505126f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.042956f, 1.543785f);
    glVertex2f(-0.967187f, 1.521896f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.967187f, 1.521896f);
    glVertex2f(-0.713018f, 1.450944f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.967187f, 1.521896f);
    glVertex2f(-0.808915f, 1.521896f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.808915f, 1.521896f);
    glVertex2f(-0.438596f, 1.597690f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.042956f, 1.543785f);
    glVertex2f(-1.058693f, 1.483733f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.058693f, 1.483733f);
    glVertex2f(-1.042677f, 1.428822f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.042677f, 1.428822f);
    glVertex2f(-0.969652f, 1.384573f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.168516f, 1.456277f);
    glVertex2f(-1.042956f, 1.543785f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.168516f, 1.456277f);
    glVertex2f(-1.058693f, 1.483733f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.168516f, 1.456277f);
    glVertex2f(-1.042677f, 1.428822f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.174215f, 1.746613f);
    glVertex2f(-0.987874f, 1.695833f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.987874f, 1.695833f);
    glVertex2f(-1.042956f, 1.543785f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.987874f, 1.695833f);
    glVertex2f(-0.863074f, 1.788938f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.863074f, 1.788938f);
    glVertex2f(-0.609513f, 1.854309f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.609513f, 1.854309f);
    glVertex2f(-0.456980f, 1.790919f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.456980f, 1.790919f);
    glVertex2f(-0.361036f, 1.668383f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.609513f, 1.854309f);
    glVertex2f(-0.575837f, 1.775071f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.575837f, 1.775071f);
    glVertex2f(-0.361036f, 1.668383f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.042956f, 1.543785f);
    glVertex2f(-0.902693f, 1.691871f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.902693f, 1.691871f);
    glVertex2f(-0.837322f, 1.737433f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.837322f, 1.737433f);
    glVertex2f(-0.575837f, 1.775071f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.042956f, 1.543785f);
    glVertex2f(-0.975912f, 1.588229f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.975912f, 1.588229f);
    glVertex2f(-0.878661f, 1.659817f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.878661f, 1.659817f);
    glVertex2f(-0.782893f, 1.719837f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.782893f, 1.719837f);
    glVertex2f(-0.699956f, 1.740740f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.699956f, 1.740740f);
    glVertex2f(-0.600161f, 1.745629f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.600161f, 1.745629f);
    glVertex2f(-0.533404f, 1.726411f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.533404f, 1.726411f);
    glVertex2f(-0.456531f, 1.693032f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.456531f, 1.693032f);
    glVertex2f(-0.361036f, 1.668383f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.456531f, 1.693032f);
    glVertex2f(-0.479289f, 1.645998f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.943078f, 1.612399f);
    glVertex2f(-0.925230f, 1.577776f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.925230f, 1.577776f);
    glVertex2f(-0.778802f, 1.575280f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.778802f, 1.575280f);
    glVertex2f(-0.625718f, 1.601071f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.625718f, 1.601071f);
    glVertex2f(-0.479289f, 1.645998f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.600161f, 1.745629f);
    glVertex2f(-0.582682f, 1.714825f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.582682f, 1.714825f);
    glVertex2f(-0.582682f, 1.662638f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.582682f, 1.662638f);
    glVertex2f(-0.611423f, 1.626333f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.611423f, 1.626333f);
    glVertex2f(-0.625718f, 1.601071f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.807651f, 1.704321f);
    glVertex2f(-0.807316f, 1.662638f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.807316f, 1.662638f);
    glVertex2f(-0.795214f, 1.627846f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.795214f, 1.627846f);
    glVertex2f(-0.761935f, 1.602130f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.761935f, 1.602130f);
    glVertex2f(-0.727508f, 1.583922f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.912627f, 2.045571f);
    glVertex2f(-0.927227f, 1.924353f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.927227f, 1.924353f);
    glVertex2f(-1.174215f, 1.746613f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.912627f, 2.045571f);
    glVertex2f(-0.561091f, 2.004714f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.561091f, 2.004714f);
    glVertex2f(-0.436312f, 2.024607f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.436312f, 2.024607f);
    glVertex2f(-0.398336f, 1.914295f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.927227f, 1.924353f);
    glVertex2f(-0.712997f, 1.912486f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.712997f, 1.912486f);
    glVertex2f(-0.539391f, 1.917911f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.539391f, 1.917911f);
    glVertex2f(-0.510456f, 1.894402f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.510456f, 1.894402f);
    glVertex2f(-0.398336f, 1.914295f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.174215f, 1.746613f);
    glVertex2f(-1.002340f, 1.832917f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-1.002340f, 1.832917f);
    glVertex2f(-0.919154f, 1.861851f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.919154f, 1.861851f);
    glVertex2f(-0.637411f, 1.896900f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.637411f, 1.896900f);
    glVertex2f(-0.609513f, 1.854309f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.912627f, 2.045571f);
    glVertex2f(-0.754640f, 1.975038f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.754640f, 1.975038f);
    glVertex2f(-0.598205f, 1.983271f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.600949f, 2.009347f);
    glVertex2f(-0.598205f, 1.983271f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.598205f, 1.983271f);
    glVertex2f(-0.524104f, 1.983271f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.524104f, 1.983271f);
    glVertex2f(-0.445081f, 1.906001f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.427961f, 2.000350f);
    glVertex2f(-0.445081f, 1.906001f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.361036f, 1.668383f);
    glVertex2f(-0.287468f, 1.734714f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.456980f, 1.790919f);
    glVertex2f(-0.287468f, 1.734714f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.445081f, 1.906001f);
    glVertex2f(-0.398379f, 1.841989f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.398379f, 1.841989f);
    glVertex2f(-0.287468f, 1.734714f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.445081f, 1.906001f);
    glVertex2f(-0.398336f, 1.914295f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.398336f, 1.914295f);
    glVertex2f(-0.287468f, 1.734714f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.287468f, 1.734714f);
    glVertex2f(-0.134247f, 1.896900f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.333405f, 1.693296f);
    glVertex2f(-0.290256f, 1.664390f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.287468f, 1.734714f);
    glVertex2f(-0.290256f, 1.664390f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.290256f, 1.664390f);
    glVertex2f(-0.338751f, 1.444202f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.338751f, 1.444202f);
    glVertex2f(-0.447534f, 1.220858f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.290256f, 1.664390f);
    glVertex2f(-0.215237f, 1.246949f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.440803f, 1.154895f);
    glVertex2f(-0.335064f, 1.224827f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.335064f, 1.224827f);
    glVertex2f(-0.259481f, 1.274601f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.259481f, 1.274601f);
    glVertex2f(-0.215237f, 1.246949f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.215237f, 1.246949f);
    glVertex2f(-0.193306f, 1.109175f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.425411f, 1.004046f);
    glVertex2f(-0.321755f, 0.942190f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.321755f, 0.942190f);
    glVertex2f(-0.311479f, 1.021829f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.311479f, 1.021829f);
    glVertex2f(-0.193306f, 1.109175f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.406438f, 1.216433f);
    glVertex2f(0.402700f, 1.096330f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.402700f, 1.096330f);
    glVertex2f(0.305079f, 0.993570f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.258837f, 1.065502f);
    glVertex2f(0.305079f, 0.993570f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.135525f, 1.140002f);
    glVertex2f(0.258837f, 1.065502f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.311479f, 1.021829f);
    glVertex2f(-0.175323f, 1.011553f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.175323f, 1.011553f);
    glVertex2f(-0.077701f, 0.947328f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.193306f, 1.109175f);
    glVertex2f(-0.077701f, 0.947328f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.194378f, 1.104446f);
    glVertex2f(0.117542f, 1.042381f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.117542f, 1.042381f);
    glVertex2f(0.027628f, 0.960173f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.258837f, 1.065502f);
    glVertex2f(0.117542f, 1.042381f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.077701f, 0.947328f);
    glVertex2f(0.027628f, 0.960173f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.134247f, 1.896900f);
    glVertex2f(0.002884f, 1.906099f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.912627f, 2.045571f);
    glVertex2f(-0.608098f, 2.206938f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.608098f, 2.206938f);
    glVertex2f(-0.427961f, 2.000350f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.608098f, 2.206938f);
    glVertex2f(-0.134247f, 1.896900f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.427961f, 2.000350f);
    glVertex2f(-0.134247f, 1.896900f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.002884f, 1.906099f);
    glVertex2f(0.133144f, 1.738621f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.133144f, 1.738621f);
    glVertex2f(0.261201f, 1.708483f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.236862f, 1.959737f);
    glVertex2f(0.261201f, 1.708483f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.002884f, 1.906099f);
    glVertex2f(0.236862f, 1.959737f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.002884f, 1.906099f);
    glVertex2f(0.133014f, 2.255305f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.133014f, 2.255305f);
    glVertex2f(0.238193f, 2.146131f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.238193f, 2.146131f);
    glVertex2f(0.002884f, 1.906099f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.236862f, 1.959737f);
    glVertex2f(0.298106f, 1.983702f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.298106f, 1.983702f);
    glVertex2f(0.331391f, 2.026306f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.133014f, 2.255305f);
    glVertex2f(0.710836f, 2.304567f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.710836f, 2.304567f);
    glVertex2f(0.938503f, 2.188736f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.938503f, 2.188736f);
    glVertex2f(1.074572f, 2.035008f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.238193f, 2.146131f);
    glVertex2f(0.504471f, 2.176753f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.504471f, 2.176753f);
    glVertex2f(0.736132f, 2.184742f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.736132f, 2.184742f);
    glVertex2f(1.074572f, 2.035008f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.238193f, 2.146131f);
    glVertex2f(0.472518f, 2.042283f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.472518f, 2.042283f);
    glVertex2f(0.780068f, 2.115509f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.780068f, 2.115509f);
    glVertex2f(1.074572f, 2.035008f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.472518f, 2.042283f);
    glVertex2f(0.489826f, 1.987696f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.298106f, 1.983702f);
    glVertex2f(0.489826f, 1.987696f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.489826f, 1.987696f);
    glVertex2f(0.809359f, 1.985033f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.809359f, 1.985033f);
    glVertex2f(0.915870f, 1.942429f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.915870f, 1.942429f);
    glVertex2f(0.952855f, 1.963560f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.952855f, 1.963560f);
    glVertex2f(0.991041f, 1.965642f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.991041f, 1.965642f);
    glVertex2f(1.074572f, 2.035008f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.915870f, 1.942429f);
    glVertex2f(1.063256f, 1.816573f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.063256f, 1.816573f);
    glVertex2f(1.087846f, 1.734126f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.489826f, 1.987696f);
    glVertex2f(0.354444f, 1.870362f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.354444f, 1.870362f);
    glVertex2f(0.259168f, 1.729466f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.489826f, 1.987696f);
    glVertex2f(0.444091f, 1.861995f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.489826f, 1.987696f);
    glVertex2f(0.543301f, 1.930127f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.323366f, 1.750832f);
    glVertex2f(0.444091f, 1.861995f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.444091f, 1.861995f);
    glVertex2f(0.543301f, 1.930127f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.323366f, 1.750832f);
    glVertex2f(0.397474f, 1.724535f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.397474f, 1.724535f);
    glVertex2f(0.530153f, 1.694653f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.530153f, 1.694653f);
    glVertex2f(0.805072f, 1.714973f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.805072f, 1.714973f);
    glVertex2f(0.970023f, 1.810597f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.543301f, 1.930127f);
    glVertex2f(0.772799f, 1.936103f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.772799f, 1.936103f);
    glVertex2f(0.889938f, 1.876338f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.889938f, 1.876338f);
    glVertex2f(0.940141f, 1.811792f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.940141f, 1.811792f);
    glVertex2f(0.970023f, 1.810597f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.889938f, 1.876338f);
    glVertex2f(0.978149f, 1.827565f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.978149f, 1.827565f);
    glVertex2f(0.970023f, 1.810597f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.889938f, 1.876338f);
    glVertex2f(0.872061f, 1.858408f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.872061f, 1.858408f);
    glVertex2f(0.886195f, 1.809220f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.886195f, 1.809220f);
    glVertex2f(0.817219f, 1.775297f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.817219f, 1.775297f);
    glVertex2f(0.716349f, 1.761140f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.716349f, 1.761140f);
    glVertex2f(0.582742f, 1.749637f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.582742f, 1.749637f);
    glVertex2f(0.430553f, 1.752292f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.430553f, 1.752292f);
    glVertex2f(0.411087f, 1.798303f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.411087f, 1.798303f);
    glVertex2f(0.488066f, 1.859355f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.488066f, 1.859355f);
    glVertex2f(0.559736f, 1.902711f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.559736f, 1.902711f);
    glVertex2f(0.765014f, 1.906250f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.765014f, 1.906250f);
    glVertex2f(0.872061f, 1.858408f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.559736f, 1.902711f);
    glVertex2f(0.539386f, 1.873617f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.539386f, 1.873617f);
    glVertex2f(0.539767f, 1.822107f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.539767f, 1.822107f);
    glVertex2f(0.583368f, 1.762873f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.583368f, 1.762873f);
    glVertex2f(0.622339f, 1.753047f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.622339f, 1.753047f);
    glVertex2f(0.716349f, 1.761140f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.716349f, 1.761140f);
    glVertex2f(0.746871f, 1.797131f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.746871f, 1.797131f);
    glVertex2f(0.761404f, 1.829831f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.761404f, 1.829831f);
    glVertex2f(0.763481f, 1.869280f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.763481f, 1.869280f);
    glVertex2f(0.765014f, 1.906250f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.259168f, 1.729466f);
    glVertex2f(0.368917f, 1.595001f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.133144f, 1.738621f);
    glVertex2f(0.123256f, 1.645632f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.862381f, 2.555147f);
    glVertex2f(-0.608098f, 2.206938f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.217264f, 2.167192f);
    glVertex2f(-0.862381f, 2.555147f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.862381f, 2.555147f);
    glVertex2f(-0.093766f, 2.772364f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.093766f, 2.772364f);
    glVertex2f(0.468770f, 2.883758f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.468770f, 2.883758f);
    glVertex2f(0.133014f, 2.255305f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.468770f, 2.883758f);
    glVertex2f(1.104922f, 2.588622f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.048576f, 2.521093f);
    glVertex2f(0.710836f, 2.304567f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357278f, 2.165761f);
    glVertex2f(1.291384f, 1.942088f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357278f, 2.165761f);
    glVertex2f(1.481647f, 1.853594f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.236151f, 2.333521f);
    glVertex2f(1.357278f, 2.165761f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357278f, 2.165761f);
    glVertex2f(1.412702f, 2.157363f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.412702f, 2.157363f);
    glVertex2f(1.475879f, 1.997533f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.475879f, 1.997533f);
    glVertex2f(1.481647f, 1.853594f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.475879f, 1.997533f);
    glVertex2f(1.572255f, 1.826501f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.475879f, 1.997533f);
    glVertex2f(1.502970f, 2.154053f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.502970f, 2.154053f);
    glVertex2f(1.693179f, 2.007887f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.502970f, 2.154053f);
    glVertex2f(1.714350f, 2.353465f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.714350f, 2.353465f);
    glVertex2f(1.763719f, 2.090183f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.763719f, 2.090183f);
    glVertex2f(1.693179f, 2.007887f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.693179f, 2.007887f);
    glVertex2f(1.609204f, 1.824821f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.572255f, 1.826501f);
    glVertex2f(1.609204f, 1.824821f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.609204f, 1.824821f);
    glVertex2f(1.607653f, 1.976814f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.607653f, 1.976814f);
    glVertex2f(1.693179f, 2.007887f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.513489f, 2.134274f);
    glVertex2f(1.607653f, 1.976814f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.572255f, 1.826501f);
    glVertex2f(1.609204f, 1.824821f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.513489f, 2.134274f);
    glVertex2f(1.526565f, 2.003514f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.526565f, 2.003514f);
    glVertex2f(1.572255f, 1.826501f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.481647f, 1.853594f);
    glVertex2f(1.591015f, 1.825648f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.591015f, 1.825648f);
    glVertex2f(1.535410f, 1.694141f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.481647f, 1.853594f);
    glVertex2f(1.535410f, 1.694141f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.763719f, 2.090183f);
    glVertex2f(1.905568f, 1.976004f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.905568f, 1.976004f);
    glVertex2f(1.929339f, 1.604149f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.905568f, 1.976004f);
    glVertex2f(1.777777f, 1.896900f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.777777f, 1.896900f);
    glVertex2f(1.703509f, 1.773946f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.703509f, 1.773946f);
    glVertex2f(1.698416f, 1.733194f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.698416f, 1.733194f);
    glVertex2f(1.610121f, 1.575283f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.610121f, 1.575283f);
    glVertex2f(1.596537f, 1.451331f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.511637f, 1.574674f);
    glVertex2f(1.545598f, 1.558303f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.545598f, 1.558303f);
    glVertex2f(1.596537f, 1.451331f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.545598f, 1.558303f);
    glVertex2f(1.610121f, 1.575283f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.610121f, 1.575283f);
    glVertex2f(1.632014f, 1.614438f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.632014f, 1.614438f);
    glVertex2f(1.929339f, 1.604149f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.777777f, 1.896900f);
    glVertex2f(1.849842f, 1.720285f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.849842f, 1.720285f);
    glVertex2f(1.854770f, 1.671007f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.854770f, 1.671007f);
    glVertex2f(1.929339f, 1.604149f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.929339f, 1.604149f);
    glVertex2f(1.787515f, 1.261845f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.929339f, 1.604149f);
    glVertex2f(1.829259f, 0.949436f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.709412f, 1.094868f);
    glVertex2f(1.829259f, 0.949436f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.709412f, 1.094868f);
    glVertex2f(1.787515f, 1.261845f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.610121f, 1.575283f);
    glVertex2f(1.787515f, 1.261845f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.610121f, 1.575283f);
    glVertex2f(1.660935f, 1.405931f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.660935f, 1.405931f);
    glVertex2f(1.677144f, 1.293103f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.677144f, 1.293103f);
    glVertex2f(1.669015f, 1.218755f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.669015f, 1.218755f);
    glVertex2f(1.787515f, 1.261845f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.677144f, 1.293103f);
    glVertex2f(1.787515f, 1.261845f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.553208f, 1.128533f);
    glVertex2f(1.669015f, 1.218755f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.545128f, 1.263192f);
    glVertex2f(1.553208f, 1.128533f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.596537f, 1.451331f);
    glVertex2f(1.605725f, 1.267232f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.605725f, 1.267232f);
    glVertex2f(1.553208f, 1.128533f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.553208f, 1.128533f);
    glVertex2f(1.559941f, 1.093522f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.559941f, 1.093522f);
    glVertex2f(1.687867f, 0.952130f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.687867f, 0.952130f);
    glVertex2f(1.829259f, 0.949436f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.687867f, 0.952130f);
    glVertex2f(1.665191f, 0.808911f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.561136f, 0.800879f);
    glVertex2f(1.665191f, 0.808911f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.665191f, 0.808911f);
    glVertex2f(1.829259f, 0.949436f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.866610f, 1.512890f);
    glVertex2f(1.424126f, 1.362449f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.694046f, 1.601384f);
    glVertex2f(0.866610f, 1.512890f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.710836f, 2.304567f);
    glVertex2f(0.736132f, 2.184742f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.763217f, 2.172759f);
    glVertex2f(0.856188f, 2.175553f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.856188f, 2.175553f);
    glVertex2f(0.934870f, 2.142213f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.934870f, 2.142213f);
    glVertex2f(0.973510f, 2.149186f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.259168f, 1.729466f);
    glVertex2f(0.572987f, 1.599008f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.321755f, 0.942190f);
    glVertex2f(-0.148177f, 0.911281f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.148177f, 0.911281f);
    glVertex2f(-0.077701f, 0.947328f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.148177f, 0.911281f);
    glVertex2f(-0.306821f, 0.855974f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.306821f, 0.855974f);
    glVertex2f(-0.350485f, 0.810855f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.513905f, 0.804933f);
    glVertex2f(-0.350485f, 0.810855f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.513905f, 0.804933f);
    glVertex2f(-0.651763f, 0.691508f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.651763f, 0.691508f);
    glVertex2f(-0.700602f, 0.533009f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.027628f, 0.960173f);
    glVertex2f(0.138547f, 0.940391f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.138547f, 0.940391f);
    glVertex2f(0.268284f, 0.890571f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.268284f, 0.890571f);
    glVertex2f(0.445648f, 0.851608f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.445648f, 0.851608f);
    glVertex2f(0.614481f, 0.861796f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.614481f, 0.861796f);
    glVertex2f(0.711996f, 0.786113f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.711996f, 0.786113f);
    glVertex2f(0.797357f, 0.619550f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.702895f, 0.946525f);
    glVertex2f(0.790590f, 0.799212f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.790590f, 0.799212f);
    glVertex2f(0.797357f, 0.619550f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.700602f, 0.533009f);
    glVertex2f(-0.571713f, 0.557606f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.571713f, 0.557606f);
    glVertex2f(-0.474198f, 0.611458f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.474198f, 0.611458f);
    glVertex2f(-0.328653f, 0.672587f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.328653f, 0.672587f);
    glVertex2f(-0.146721f, 0.736627f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.146721f, 0.736627f);
    glVertex2f(0.000279f, 0.720617f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.000279f, 0.720617f);
    glVertex2f(0.141458f, 0.771558f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.141458f, 0.771558f);
    glVertex2f(0.301558f, 0.749726f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.301558f, 0.749726f);
    glVertex2f(0.445648f, 0.723528f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.445648f, 0.723528f);
    glVertex2f(0.585371f, 0.698785f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.585371f, 0.698785f);
    glVertex2f(0.691620f, 0.669676f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.711996f, 0.786113f);
    glVertex2f(0.719296f, 0.697238f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.719296f, 0.697238f);
    glVertex2f(0.691620f, 0.669676f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.585371f, 0.698785f);
    glVertex2f(0.566908f, 0.627638f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.571713f, 0.557606f);
    glVertex2f(-0.511984f, 0.528877f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.511984f, 0.528877f);
    glVertex2f(-0.402748f, 0.543841f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.402748f, 0.543841f);
    glVertex2f(-0.163327f, 0.629135f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.163327f, 0.629135f);
    glVertex2f(0.004268f, 0.627638f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.004268f, 0.627638f);
    glVertex2f(0.161388f, 0.665048f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(0.161388f, 0.665048f);
    glVertex2f(0.566908f, 0.627638f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.402748f, 0.543841f);
    glVertex2f(-0.016681f, 0.555812f);

    glColor3f(0.42f, 0.39f, 0.35f);
    glVertex2f(-0.016681f, 0.555812f);
    glVertex2f(0.504454f, 0.633400f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.511984f, 0.528877f);
    glVertex2f(-0.109457f, 0.380735f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.109457f, 0.380735f);
    glVertex2f(0.177849f, 0.401684f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.177849f, 0.401684f);
    glVertex2f(0.566908f, 0.627638f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.035249f, 0.198477f);
    glVertex2f(0.174268f, 0.337495f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.945642f, 0.047294f);
    glVertex2f(-0.831459f, -0.472551f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.831459f, -0.472551f);
    glVertex2f(-1.259497f, -0.857016f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.857090f, -0.282881f);
    glVertex2f(-1.259497f, -0.857016f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.857090f, -0.282881f);
    glVertex2f(-0.659845f, -0.248801f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.831459f, -0.472551f);
    glVertex2f(-0.813517f, -0.582764f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.813517f, -0.582764f);
    glVertex2f(-0.103769f, -0.862298f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.229130f, -0.464861f);
    glVertex2f(-0.103769f, -0.862298f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.063064f, -0.552007f);
    glVertex2f(0.063064f, -0.944162f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.058437f, -0.538928f);
    glVertex2f(0.063064f, -0.552007f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.063064f, -0.552007f);
    glVertex2f(0.252844f, -0.557061f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.103769f, -0.862298f);
    glVertex2f(0.063064f, -0.944162f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.063064f, -0.944162f);
    glVertex2f(0.527765f, -0.497618f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.527765f, -0.497618f);
    glVertex2f(0.406520f, -0.995424f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.063064f, -0.944162f);
    glVertex2f(0.406520f, -0.995424f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.123664f, -0.166073f);
    glVertex2f(0.996034f, -0.323891f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.996034f, -0.323891f);
    glVertex2f(0.406520f, -0.995424f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.813517f, -0.582764f);
    glVertex2f(-1.085206f, -1.038997f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.259497f, -0.857016f);
    glVertex2f(-1.085206f, -1.038997f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.813517f, -0.582764f);
    glVertex2f(-0.526450f, -1.008239f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.526450f, -1.008239f);
    glVertex2f(-0.651131f, -1.186089f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.813517f, -0.582764f);
    glVertex2f(-0.651131f, -1.186089f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.813517f, -0.582764f);
    glVertex2f(-0.734061f, -1.274802f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.103769f, -0.862298f);
    glVertex2f(-0.033614f, -1.021453f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.033614f, -1.021453f);
    glVertex2f(0.100854f, -1.588560f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.526450f, -1.008239f);
    glVertex2f(0.100854f, -1.588560f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.100854f, -1.588560f);
    glVertex2f(0.406520f, -0.995424f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.406520f, -0.995424f);
    glVertex2f(0.721506f, -1.647871f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.100854f, -1.588560f);
    glVertex2f(0.721506f, -1.647871f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.651131f, -1.186089f);
    glVertex2f(-0.613002f, -1.344959f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.651131f, -1.186089f);
    glVertex2f(-0.678669f, -1.270820f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.734061f, -1.274802f);
    glVertex2f(-0.678669f, -1.270820f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.678669f, -1.270820f);
    glVertex2f(-0.613002f, -1.344959f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-1.085206f, -1.038997f);
    glVertex2f(-0.734061f, -1.274802f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.734061f, -1.274802f);
    glVertex2f(-0.517680f, -1.743193f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.613002f, -1.344959f);
    glVertex2f(0.100854f, -1.588560f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.613002f, -1.344959f);
    glVertex2f(-0.127919f, -1.851225f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.259497f, -0.857016f);
    glVertex2f(-1.589550f, -1.027213f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.589550f, -1.027213f);
    glVertex2f(-1.735091f, -1.103449f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.735091f, -1.103449f);
    glVertex2f(-2.442004f, -1.446509f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.442004f, -1.446509f);
    glVertex2f(-1.610342f, -1.935111f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.326392f, -1.390403f);
    glVertex2f(-1.392158f, -1.172402f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.259497f, -0.857016f);
    glVertex2f(-1.392158f, -1.172402f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.085206f, -1.038997f);
    glVertex2f(-1.610342f, -1.935111f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.610342f, -1.935111f);
    glVertex2f(-1.579358f, -1.882239f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.579358f, -1.882239f);
    glVertex2f(-0.738044f, -1.323351f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.610342f, -1.935111f);
    glVertex2f(-0.517680f, -1.743193f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.517680f, -1.743193f);
    glVertex2f(-0.440678f, -1.696439f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.440678f, -1.696439f);
    glVertex2f(-0.127919f, -1.851225f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.442004f, -1.446509f);
    glVertex2f(-3.313747f, -2.009327f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.313747f, -2.009327f);
    glVertex2f(-3.687093f, -2.488684f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.687093f, -2.488684f);
    glVertex2f(-4.015037f, -3.017975f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-4.015037f, -3.017975f);
    glVertex2f(-3.647413f, -2.869511f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.647413f, -2.869511f);
    glVertex2f(-3.313747f, -2.009327f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.647413f, -2.869511f);
    glVertex2f(-3.025281f, -2.148404f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.313747f, -2.009327f);
    glVertex2f(-3.025281f, -2.148404f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.025281f, -2.148404f);
    glVertex2f(-2.442004f, -1.446509f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.442004f, -1.446509f);
    glVertex2f(-2.466777f, -2.402913f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.025281f, -2.148404f);
    glVertex2f(-2.466777f, -2.402913f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.025281f, -2.148404f);
    glVertex2f(-2.735424f, -3.138159f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.735424f, -3.138159f);
    glVertex2f(-2.466777f, -2.402913f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-3.647413f, -2.869511f);
    glVertex2f(-2.735424f, -3.138159f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-4.015037f, -3.017975f);
    glVertex2f(-2.735424f, -3.138159f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.735424f, -3.138159f);
    glVertex2f(-1.293210f, -3.032114f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.293210f, -3.032114f);
    glVertex2f(-0.932656f, -3.314901f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.466777f, -2.402913f);
    glVertex2f(-1.293210f, -3.032114f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-2.466777f, -2.402913f);
    glVertex2f(-1.116468f, -2.805884f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.610342f, -1.935111f);
    glVertex2f(-1.116468f, -2.805884f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.610342f, -1.935111f);
    glVertex2f(-2.466777f, -2.402913f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.610342f, -1.935111f);
    glVertex2f(-0.624222f, -2.509476f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.624222f, -2.509476f);
    glVertex2f(-0.517680f, -1.743193f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.517680f, -1.743193f);
    glVertex2f(-0.505999f, -1.808383f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.505999f, -1.808383f);
    glVertex2f(0.241834f, -2.245535f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.241834f, -2.245535f);
    glVertex2f(0.376553f, -2.253783f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.505999f, -1.808383f);
    glVertex2f(0.094251f, -2.730080f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.624222f, -2.509476f);
    glVertex2f(0.094251f, -2.730080f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.624222f, -2.509476f);
    glVertex2f(-1.116468f, -2.805884f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.094251f, -2.730080f);
    glVertex2f(0.098683f, -2.812440f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.098683f, -2.812440f);
    glVertex2f(-0.134247f, -3.185059f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.624222f, -2.509476f);
    glVertex2f(-0.134247f, -3.185059f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.116468f, -2.805884f);
    glVertex2f(-0.134247f, -3.185059f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-1.116468f, -2.805884f);
    glVertex2f(-0.932656f, -3.314901f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.932656f, -3.314901f);
    glVertex2f(-0.134247f, -3.185059f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.134247f, -3.185059f);
    glVertex2f(0.188892f, -3.456794f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.098683f, -2.812440f);
    glVertex2f(0.188892f, -3.456794f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.932656f, -3.314901f);
    glVertex2f(0.188892f, -3.456794f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.188892f, -3.456794f);
    glVertex2f(0.284482f, -3.462801f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.296197f, -2.431835f);
    glVertex2f(0.284482f, -3.462801f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.296197f, -2.431835f);
    glVertex2f(0.468025f, -2.302964f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.468025f, -2.302964f);
    glVertex2f(0.557844f, -2.509938f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.557844f, -2.509938f);
    glVertex2f(0.581275f, -3.415939f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.284482f, -3.462801f);
    glVertex2f(0.581275f, -3.415939f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.560774f, -2.623213f);
    glVertex2f(0.659379f, -2.650524f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.659379f, -2.650524f);
    glVertex2f(0.581275f, -3.415939f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.659379f, -2.650524f);
    glVertex2f(1.241250f, -3.201154f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.581275f, -3.415939f);
    glVertex2f(1.241250f, -3.201154f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.241250f, -3.201154f);
    glVertex2f(1.975423f, -3.298784f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.581275f, -3.415939f);
    glVertex2f(1.975423f, -3.298784f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.241250f, -3.201154f);
    glVertex2f(1.659104f, -2.138946f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.659379f, -2.650524f);
    glVertex2f(1.659104f, -2.138946f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.659379f, -2.650524f);
    glVertex2f(1.249060f, -1.818722f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.249060f, -1.818722f);
    glVertex2f(1.659104f, -2.138946f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.249060f, -1.818722f);
    glVertex2f(0.468025f, -2.302964f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.100854f, -1.588560f);
    glVertex2f(0.376553f, -2.253783f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(-0.127919f, -1.851225f);
    glVertex2f(0.376553f, -2.253783f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.721506f, -1.647871f);
    glVertex2f(0.376553f, -2.253783f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(0.376553f, -2.253783f);
    glVertex2f(0.960077f, -1.842153f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.406520f, -0.995424f);
    glVertex2f(1.357291f, -0.573395f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.357291f, -0.573395f);
    glVertex2f(0.964618f, -1.298331f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.964618f, -1.298331f);
    glVertex2f(0.721506f, -1.647871f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.721506f, -1.647871f);
    glVertex2f(1.342189f, -1.242954f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.342189f, -1.242954f);
    glVertex2f(1.357291f, -0.573395f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.511683f, 0.427231f);
    glVertex2f(1.280901f, 0.075563f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.418488f, 0.285220f);
    glVertex2f(1.463011f, -0.220996f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.463011f, -0.220996f);
    glVertex2f(1.357291f, -0.573395f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.463011f, -0.220996f);
    glVertex2f(1.494568f, -0.483245f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.494568f, -0.483245f);
    glVertex2f(1.469815f, -0.884791f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.469815f, -0.884791f);
    glVertex2f(1.387088f, -1.256628f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.342189f, -1.242954f);
    glVertex2f(1.387088f, -1.256628f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.387088f, -1.256628f);
    glVertex2f(1.677144f, -0.820187f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.463011f, -0.220996f);
    glVertex2f(1.677144f, -0.820187f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.677144f, -0.820187f);
    glVertex2f(1.942385f, -0.686376f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.677144f, -0.820187f);
    glVertex2f(1.979043f, -1.524617f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.942385f, -0.686376f);
    glVertex2f(1.979043f, -1.524617f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.387088f, -1.256628f);
    glVertex2f(1.979043f, -1.524617f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(1.387088f, -1.256628f);
    glVertex2f(0.960077f, -1.842153f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.960077f, -1.842153f);
    glVertex2f(1.159844f, -1.754797f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.159844f, -1.754797f);
    glVertex2f(1.979043f, -1.524617f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.979043f, -1.524617f);
    glVertex2f(1.659104f, -2.138946f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.979043f, -1.524617f);
    glVertex2f(2.884739f, -1.927148f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.659104f, -2.138946f);
    glVertex2f(2.884739f, -1.927148f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.979043f, -1.524617f);
    glVertex2f(2.678225f, -1.267416f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.678225f, -1.267416f);
    glVertex2f(2.884739f, -1.927148f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.942385f, -0.686376f);
    glVertex2f(2.303316f, -0.967488f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.303316f, -0.967488f);
    glVertex2f(2.678225f, -1.267416f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.678225f, -1.267416f);
    glVertex2f(3.556136f, -1.807909f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.678225f, -1.267416f);
    glVertex2f(3.324942f, -1.920382f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(3.324942f, -1.920382f);
    glVertex2f(3.556136f, -1.807909f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.884739f, -1.927148f);
    glVertex2f(3.324942f, -1.920382f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(3.324942f, -1.920382f);
    glVertex2f(3.682066f, -2.705672f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(3.556136f, -1.807909f);
    glVertex2f(3.682066f, -2.705672f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.884739f, -1.927148f);
    glVertex2f(3.682066f, -2.705672f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.659104f, -2.138946f);
    glVertex2f(2.320075f, -2.772117f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.241250f, -3.201154f);
    glVertex2f(2.320075f, -2.772117f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.320075f, -2.772117f);
    glVertex2f(2.884739f, -1.927148f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.884739f, -1.927148f);
    glVertex2f(2.942667f, -3.193564f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.942667f, -3.193564f);
    glVertex2f(3.684385f, -2.714949f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(3.682066f, -2.705672f);
    glVertex2f(3.684385f, -2.714949f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(3.684385f, -2.714949f);
    glVertex2f(3.940510f, -3.003161f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(3.556136f, -1.807909f);
    glVertex2f(3.940510f, -3.003161f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.975423f, -3.298784f);
    glVertex2f(2.320075f, -2.772117f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(1.975423f, -3.298784f);
    glVertex2f(2.942667f, -3.193564f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.320075f, -2.772117f);
    glVertex2f(2.942667f, -3.193564f);

    glColor3f(0.08f, 0.29f, 0.50f);
    glVertex2f(2.942667f, -3.193564f);
    glVertex2f(3.940510f, -3.003161f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.193306f, 1.109175f);
    glVertex2f(0.135525f, 1.140002f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.135525f, 1.140002f);
    glVertex2f(0.027628f, 0.960173f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(0.114406f, 1.265105f);
    glVertex2f(0.135525f, 1.140002f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.287468f, 1.734714f);
    glVertex2f(-0.095349f, 1.438959f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.095349f, 1.438959f);
    glVertex2f(0.114406f, 1.265105f);

    glColor3f(0.63f, 0.40f, 0.27f);
    glVertex2f(-0.095349f, 1.438959f);
    glVertex2f(-0.190022f, 1.244631f);

    glEnd();

    glPopMatrix();
}

/*
void update(void)
{
    //code
}

void uninitialize(void)
{
    //code
    // if exiting in full screen first restore and then proceed
    if (bFullscreen == TRUE)
    {
        toggleFullScreen();
        bFullscreen = FALSE;
    }

    //first check the current contex and if it is then unmake it
    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);

    }

    //Destroy the rendering contex
    if (ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    //release the device contex
    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }

    //destroy window
    if (ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;

    }

    //Close Log File
    if (gpFile)
    {
        fprintf(gpFile, "SHS : Program Terminated Successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }
   
}
 */