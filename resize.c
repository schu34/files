#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    fprintf(stderr, "Usage...\n");
    return 1;
  }

  float factor = atof(argv[1]);
  char *infile = argv[2];
  char *outfile = argv[3];

  FILE *inptr = fopen(infile, "r");

  if (inptr == NULL)
  {
    fprintf(stderr, "couldn't open %s.\n", infile);
    return 2;
  }

  FILE *outptr = fopen(outfile, "w");

  if (outptr == NULL)
  {
    fclose(inptr);
    fprintf(stderr, "couldn't open %s.\n", outfile);
    return 3;
  }


  BITMAPFILEHEADER inbf;
  fread(&inbf, sizeof(BITMAPFILEHEADER), 1, inptr);

  BITMAPINFOHEADER inbi;
  fread(&inbi, sizeof(BITMAPINFOHEADER), 1, inptr);

  if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 ||
      inbi.biBitCount != 24 || inbi.biCompression != 0)
  {
    fclose(outptr);
    fclose(inptr);
    fprintf(stderr, "Unsupported file format.\n");
    return 4;
  }

  LONG inWidth = inbi.biWidth;
  LONG inHeight = abs(inbi.biHeight);

  inbi.biWidth *= factor;
  inbi.biHeight *= factor;

  int inPadding = (4 - (inWidth * sizeof(RGBTRIPLE)) % 4) % 4;
  int outPadding = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


  fwrite(&inbf, sizeof(BITMAPFILEHEADER), 1, outptr);

  fwrite(&inbi, sizeof(BITMAPINFOHEADER), 1, outptr);

  RGBTRIPLE *row = malloc(inbi.biWidth * sizeof(RGBTRIPLE));


  for (int i = 0; i < inHeight; i++)
  {

    for (int j = 0; j < inWidth; j++)
    {
      RGBTRIPLE pixel;
      fread(&pixel, sizeof(RGBTRIPLE), 1, inptr);
      for(int k  = 0; k < factor; k++){
        row[(int)(j*factor)+k] = pixel;
      }
    }

    fseek(inptr, inPadding, SEEK_CUR);

    for (int k = 0; k < factor; k++)
    {
      fwrite(row, sizeof(RGBTRIPLE) * inbi.biWidth + outPadding, 1, outptr);
    }
  }

  free(row);
  fclose(inptr);
  fclose(outptr);
  return 0;
}
