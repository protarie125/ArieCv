#include <iostream>

#include <core/Image.h>

using namespace std;

int main()
{
    try
    {
        auto a = ahs::Image::fromFile(R"(C:\Temp\test1.bmp)");
        if (a.isInitialized())
        {
            cout << "W = " << a.getWidth() << endl
                << "H = " << a.getHeight() << endl
                << "Stride = " << a.countChannels() << endl;

            a.write(R"(C:\Temp\write_test.bmp)");
        }
    }
    catch (const exception& exc)
    {
        cout << exc.what() << endl;
    }

    return 0;
}