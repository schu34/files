#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

void writePadding(FILE *, int);

int main(int argc, char *argv[])
{
  printf("%i\n", argc);
  if (argc != 4)
  {
    fprintf(stderr, "Usage...\n");
    return 1;
  }


  int factor = atoi(argv[1]);
  printf("%i\n", factor);
  char *infile = argv[2];
  char *outfile = argv[3];
  printf("%i %s %s\n", factor, infile, outfile);

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

  printf("hihi\n");

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

  printf("hi\n");
  LONG inWidth = inbi.biWidth;
  LONG inHeight = abs(inbi.biHeight);

  int inPadding = 4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4;
  int outPadding = 4 - (inWidth * factor * sizeof(RGBTRIPLE)) % 4;

  inbi.biWidth *= factor;
  inbi.biHeight *= factor;

  fwrite(&inbf, sizeof(BITMAPFILEHEADER), 1, outptr);

  fwrite(&inbf, sizeof(BITMAPINFOHEADER), 1, outptr);

  RGBTRIPLE *row = malloc(inbi.biWidth * sizeof(RGBTRIPLE));

  printf("%i %i %i %i\n", inWidth, inHeight, inPadding, outPadding);

  for (int i = 0; i < inHeight; i++)
  {

    for (int j = 0; j < inWidth; j++)
    {
      RGBTRIPLE pixel;
      fread(&pixel, sizeof(RGBTRIPLE), 1, inptr);
      printf("%i, %i, %i   ", pixel.rgbtRed, pixel.rgbtGreen, pixel.rgbtBlue);
      row[j] = pixel;
      row[j + 1] = pixel;
      row[j + 2] = pixel;
    }
    printf("\n");

    fseek(inptr, inPadding, SEEK_CUR);

    for (int k = 0; k < factor; k++)
    {
      fwrite(row, sizeof(RGBTRIPLE) * inbi.biWidth, 1, outptr);
      writePadding(outptr, outPadding);
    }
  }

  free(row);
  fclose(inptr);
  fclose(outptr);
  return 0;
}

void writePadding(FILE *file, int padding)
{
  for (int i = 0; i < padding; i++)
  {
    fputc(0x00, file);
  }
}
