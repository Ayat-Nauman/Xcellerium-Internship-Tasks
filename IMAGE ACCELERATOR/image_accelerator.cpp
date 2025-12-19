#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push,1)
struct BMPHeader
{
    char signature[2];
    int fileSize;
    int reserved;
    int dataOffset;
};

struct DIBHeader
{
    int size;
    int width;
    int height;
    short planes;
    short bitsPerPixel;
    int compression;
    int imageSize;
    int xppm;
    int yppm;
    int colorsUsed;
    int importantColors;
};
#pragma pack(pop)

int main()
{
    ifstream in("input.bmp", ios::binary);
    if(!in)
    {
        cout << "Cannot open input.bmp\n";
        return 0;
    }

    BMPHeader bmp;
    DIBHeader dib;

    in.read((char*)&bmp, sizeof(bmp));
    in.read((char*)&dib, sizeof(dib));

    if(dib.bitsPerPixel != 24)
    {
        cout << "Only 24-bit BMP supported\n";
        return 0;
    }

    int width = dib.width;
    int height = dib.height;
    int rowPadding = (4 - (width * 3) % 4) % 4;

    unsigned char* rgb = new unsigned char[width * height * 3];
    unsigned char* gray = new unsigned char[width * height];
    unsigned char* blur = new unsigned char[width * height];

    in.seekg(bmp.dataOffset);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int idx = ((height - 1 - i) * width + j) * 3;
            in.read((char*)&rgb[idx], 3);
        }
        in.ignore(rowPadding);
    }
    in.close();

    // RGB to Grayscale
    for(int i = 0; i < width * height; i++)
    {
        unsigned char b = rgb[i*3 + 0];
        unsigned char g = rgb[i*3 + 1];
        unsigned char r = rgb[i*3 + 2];

        gray[i] = (unsigned char)(0.299*r + 0.587*g + 0.114*b);
    }

    // 3x3 Blur Convolution
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            int sum = 0;

            for(int y = -1; y <= 1; y++)
                for(int x = -1; x <= 1; x++)
                    sum += gray[(i+y)*width + (j+x)];

            blur[i*width + j] = sum / 9;
        }
    }

    // Grayscale to RGB
    for(int i = 0; i < width * height; i++)
    {
        rgb[i*3 + 0] = blur[i];
        rgb[i*3 + 1] = blur[i];
        rgb[i*3 + 2] = blur[i];
    }

    ofstream out("output.bmp", ios::binary);
    out.write((char*)&bmp, sizeof(bmp));
    out.write((char*)&dib, sizeof(dib));

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int idx = ((height - 1 - i) * width + j) * 3;
            out.write((char*)&rgb[idx], 3);
        }
        for(int p = 0; p < rowPadding; p++)
            out.put(0);
    }

    out.close();

    delete[] rgb;
    delete[] gray;
    delete[] blur;

    cout << "Done. Output saved as output.bmp\n";
    return 0;
}
