#include <fstream>
#include <iostream>
#include <string>
using namespace std;

double const x = 2.0;
double const neg_X = -2.0;
double const y = 2.0;
double const neg_Y = -2.0;

int const dispWidth = 768;
int const dispHeight = 768;

struct complex 
{
    float real;
    float imag;
};

int cal_pixel(complex c)
{
    int count, max_iter;
    complex z;
    float temp, lengthsq;
    max_iter = 10000;
    z.real = 0;
    z.imag = 0;
    count = 0;
    do 
    {
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        lengthsq = z.real * z.real + z.imag * z.imag;
        count++;
    } while ((lengthsq < 4.0) && (count < max_iter));

    return count;
}

int main()
{
    ofstream myFile;

    myFile.open("MandelbrotSetImg.ppm");
    myFile << "P3\n" + to_string(dispWidth) + " " + to_string(dispHeight) + "\n" + to_string(255) + "\n";

    complex z;

    int color;
    float scaleReal = (x - neg_X) / dispWidth;
    float scaleImaginary = (y - neg_Y) / dispHeight;

    for (int i = 0; i < dispHeight; i++)
    {
        for (int j = 0; j < dispWidth; j++)
        {
            z.real = neg_X + ((float)j * scaleReal);
            z.imag = neg_Y + ((float)i * scaleImaginary);
            color = cal_pixel(z);
            myFile << (color * color) % 256 << " " << (color * color) % 256 << " " << (color) % 256 << "   ";
        }
        myFile << "\n";
    }

    myFile.close();

    return 0;
}