#include "stdafx.h"

#include "JGN_bmpLoader.h"




void JGN_bmpLoad(char filename[], int A)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	FILE* file;
	file = fopen(filename, "rb");

	if (A != 1 && A != 0)
	{
		std::cout << "Second argument must be JGN_RGB or JGN_RGBA";
	}
	else
	{
		if (file == NULL)
		{
			std::cout << "Cant open bmp";

		}
		else
		{
			fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
			if (bfh.bfType != 0x4D42)
			{
				std::cout << "Not a valid bmp";
			}
			else
			{
				fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);

				if (bih.biSizeImage == 0)
				{
					bih.biSizeImage = bih.biHeight*bih.biWidth * (3 + A);
				}


				JGN_bmpData = (char*)malloc(sizeof(char)*bih.biSizeImage);
				fseek(file, bfh.bfOffBits, SEEK_SET);


				fread(JGN_bmpData, 1, bih.biSizeImage, file);

				JGN_bmpWidth = bih.biWidth;
				JGN_bmpHeight = bih.biHeight;


				char temp;
				for (int i = 0; i < bih.biSizeImage; i += (3 + A))
				{
					temp = JGN_bmpData[i];
					JGN_bmpData[i] = JGN_bmpData[i + 2];
					JGN_bmpData[i + 2] = temp;

				}




				fclose(file);
			}
		}
	}
}