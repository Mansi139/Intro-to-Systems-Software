//Manasi Thakkar
//Project 2
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  if (argc != 2)
    {
      printf ("error!!!\n");
    }
  else
    {

      FILE *file = fopen (argv[1], "r");

      if (file == 0)
	{
	  printf ("Could not open the file\n");
	}
      else
	{

	  fseek (file, 0, SEEK_END);
	  long pos = ftell (file);	//file size
	  fseek (file, 0, SEEK_SET);

	  char *bytes;
	  bytes = (char *) malloc (pos * sizeof (char));
	  fread (bytes, sizeof (char), pos, file);

	  int i, count = 0;
	  for (i = 0; i < pos; i++)
	    {
	      if ((bytes[i] > 31 && bytes[i] < 127) || (bytes[i] == 9))
		{
		  count++;
		  if (count != 0 && count != 1 && count != 2 && count != 3)
		    {
		      if (count == 4)
			{
			  printf ("%c%c%c%c",
				  bytes[i - 3], bytes[i - 2], bytes[i - 1],
				  bytes[i]);

			  if (!isprint (bytes[i + 1]))
			    {
			      if (bytes[i + 1] == 9)
				{
				}
			      else
				{
				  printf ("\n");
				}
			    }
			}
		      if (count > 4)
			{
			  printf ("%c", bytes[i]);

			  if (!isprint (bytes[i + 1]))
			    {
			      if (bytes[i + 1] == 9)
				{
				}
			      else
				{

				  printf ("\n");
				}
			    }
			}
		    }

		}
	      else
		{
		  count = 0;
		}
	    }

	  fclose (file);
	  free (bytes);

	}
    }
  return 0;
}
