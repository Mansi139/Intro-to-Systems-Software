//mat185
//Manasi Thakkar
//Project1 part2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>		//read and open function
#include <math.h>

struct TIFF
{
  short tag;
  short datatype;
  int dataItems;
  int offset;
};

struct header
{
  short start;
  short APP1;
  short length;
  char exif[4];
  short terminator;
  short endianness;
  short versionnum;
  int offset;
};


main (int argc, char **argv)
{

  unsigned short count;
  char buffer[40];

  FILE *fp;
  fp = fopen (argv[1], "r");
  if (fp == NULL)
    {
      printf ("Error\n");
    }
  else
    {
   //   printf ("Filename: %s\n", argv[1]);
    }

  int b;

  struct header h1;
  int c = fread (&h1, 20, 1, fp);

  short a = h1.start;
  //checking for exif and endianness

  if (strcmp (h1.exif, "Exif") != 0)
    {
      perror ("EXIF tag is not in the right place\n");
    }
  if (h1.endianness != 0x4949)
    {
      perror ("dont support MM\n");
    }

  fread (&count, 2, 1, fp);

  //go to 20th bit save count
  //read 12 bytes, see if tag is the one we are looking for

  if (fseek (fp, 20, SEEK_SET) != 0)
    {
      printf ("error\n");
    }				//count, save count
  count = fgetc (fp);

  short x = fgetc (fp);

  int i;
  for (i = 0; i < count; i++)
    {

      unsigned short temp;
      struct TIFF t1;
      fread (&t1, 12, 1, fp);


      if (t1.tag == 0xffff8769 || t1.tag == 0x10f || t1.tag == 0x110)
	{
	  //need to save the curr position so that seek to it later
	  unsigned long position;
	  fflush (fp);
	  position = ftell (fp);

	  char buffer[t1.dataItems];

	  if (fseek (fp, 12 + t1.offset, SEEK_SET) != 0)
	    {
	      printf ("error\n");
	    }

	  //starts        
	  if (t1.tag == 0xffff8769)
	    {
	      unsigned short ch;
	      ch = fgetc (fp);

	      short x1 = fgetc (fp);

	      int k;
	      for (k = 0; k < ch; k++)
		{
		  unsigned short temp1;
		  struct TIFF t2;
		  fread (&t2, 12, 1, fp);

		  if (t2.tag == 0xffff8827)
		    {
		      printf ("ISO:     	      ISO %d\n", t2.offset);
		    }

		  if (t2.tag == 0xffff829d || t2.tag == 0xffff829a
		      || t2.tag == 0xffff920a)
		    {
		      unsigned long position;
		      fflush (fp);
		      position = ftell (fp);
		      char a[200];
		      unsigned int ek, be;

		      //            printf ("offset %d\n", 12 + t2.offset);
		      if (fseek (fp, 12 + t2.offset, SEEK_SET) != 0)
			{
			  printf ("error\n");
			}
		      fread (&ek, 1, 4, fp);
		      fread (&be, 1, 4, fp);

		      if (t2.tag == 0xffff829a)
			{
			  printf ("Exposure Time: 	%d/%d seconds\n", ek, be);
			}
		      if (t2.tag == 0xffff829d)
			{
			  double a = (double) ek / be;
			  printf ("F-stop: 	   f/%.1f second\n", a);
			}
		      if (t2.tag == 0xffff920a)
			{
			  printf ("Focal Length:	 %.1f mm\n",
				  (double) ek / be);
			}
		      fseek (fp, position, SEEK_SET);

		    }

		  if (t2.tag == 0xffff9003)
		    {
		      unsigned long position;
		      fflush (fp);
		      position = ftell (fp);

		      char a[200];
		      fread (&a, 1, 12, fp);
		      if (fseek (fp, 12 + t2.offset, SEEK_SET) != 0)
			{
			  printf ("error\n");
			}
		      fread (a, 1, t2.dataItems, fp);
		      printf ("Date Taken:        %s\n", a);

		      fseek (fp, position, SEEK_SET);
		    }

		  if (t2.tag == 0xffffa002)
		    {
		      printf ("Width: 		%d pixels\n", t2.offset);
		    }
		  if (t2.tag == 0xffffa003)
		    {
		      printf ("Height:		%d pixels\n\n", t2.offset);
		    }

		}
	    }
	  //ends the third block checking

	  fread (buffer, 1, t1.dataItems, fp);
	  if (t1.tag == 0x110)
	    {
	      printf ("Model:         %s\n", buffer);
	    }

	  if (t1.tag == 0x10f)
	    {
	      printf ("\nManufacturer:  %s\n", buffer);
	    }

	  fseek (fp, position, SEEK_SET);

	}
    }
  return 0;
}
