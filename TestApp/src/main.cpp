#include <iostream>

#include <core/Image.h>

using namespace std;

int main()
{
    try
    {
        auto a = ahs::Image::fromFile(R"(C:\Temp\test1.bmp)");
        cout << a.isInitialized() << endl;
        cout << "W = " << a.getWidth() << endl
            << "H = " << a.getHeight() << endl
            << "Stride = " << a.getStride() << endl;
    }
    catch (const exception& exc)
    {
        cout << exc.what() << endl;
    }

    return 0;
}