#include <corgi/image/raster_image.h>
#include <corgi/test/test.h>
#include <windows.h>

#include <vector>

using namespace corgi::image;

raster_image img = raster_image(100, 100, corgi::image::color_format::rgba);

// Callback function for the current win32 window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static std::vector<unsigned char> pixels;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{

    for(int i = 0; i < 16; i++)
    {
        pixels.push_back(255);
        pixels.push_back(0);
        pixels.push_back(0);
    }

    // Nom de la classe de la window
    const char CLASS_NAME[] = "corgi-image tests";

    // Structure de la window
    WNDCLASS wc = {};

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd =
        CreateWindowEx(0,                               // Style
                       CLASS_NAME,                      // Nom de la classe
                       "corgi-image tests",             // Titre
                       WS_OVERLAPPEDWINDOW,             // Style
                       CW_USEDEFAULT, CW_USEDEFAULT,    // Position
                       CW_USEDEFAULT, CW_USEDEFAULT,    // Taille
                       NULL,                            // Handle
                       NULL,                            // Handle du menu
                       hInstance,    // Handle de l'instance de l'application
                       NULL          // param additionnel
        );

    if(hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:

            PAINTSTRUCT ps;

            HDC hdc    = BeginPaint(hwnd, &ps);
            HDC hdcMem = CreateCompatibleDC(hdc);

            BITMAPINFO bminfo;

            RECT rect;
            GetClientRect(hwnd, &rect);

            HBITMAP bm = CreateCompatibleBitmap(hdc, img.width(), img.height());
            HGDIOBJ hOld = SelectObject(hdcMem, bm);

            bminfo.bmiHeader.biSize          = sizeof(bminfo.bmiHeader);
            bminfo.bmiHeader.biWidth         = img.width();
            bminfo.bmiHeader.biHeight        = img.height();
            bminfo.bmiHeader.biPlanes        = 1;    // must always be 1
            bminfo.bmiHeader.biBitCount      = img.bits_per_pixel();
            bminfo.bmiHeader.biCompression   = BI_RGB;
            bminfo.bmiHeader.biSizeImage     = 0;
            bminfo.bmiHeader.biXPelsPerMeter = 1;
            bminfo.bmiHeader.biYPelsPerMeter = 1;
            bminfo.bmiHeader.biClrUsed       = 0;
            bminfo.bmiHeader.biClrImportant  = 0;

            SetDIBits(hdcMem, bm, 0, img.height(), img.data(), &bminfo,
                      DIB_RGB_COLORS);

            BitBlt(hdc, 0, 0, img.width(), img.height(), hdcMem, 0, 0, SRCCOPY);
            DeleteDC(hdcMem);

            // Fin du dessin
            EndPaint(hwnd, &ps);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}