//Manasi Thakkar
//mat 185
//Project 1 part1

#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  int high = 11, i = 0;
  int low = 1;
  int value[4];
  char input[10];

  printf ("Welcome to blackJack!!!\n");

  //generate random num
  srand ((unsigned int) time (NULL));

  for (i = 0; i < 4; i++)
    {
      value[i] = rand () % (high - low + 1) + low;
//              printf("random num: %d\n",value[i]);
    }

      printf ("The dealer: \n");
      printf ("? + %d\n\n", value[1]);

      printf ("You: \n");
      printf ("%d + %d = %d\n\n", value[2], value[3], value[2] + value[3]);

      printf ("Would you like to \"hit\" or \"stand\"?");
      scanf ("%s", input);

      int dealerTotal = value[0] + value[1];
      int userTotal = value[2] + value[3];

      while ((strcmp (input, "hit") == 0) || (strcmp (input, "stand") == 0))
	{
//	  printf ("12");
	  if ((strcmp (input, "hit") == 0))
	    {
	      int temp;
	      printf ("The dealer: \n");
	      printf ("? + %d\n\n", value[1]);

	      temp = rand () % (high - low + 1) + low;

	      printf ("You: \n");
	      printf ("%d + %d = %d\n\n", userTotal, temp, userTotal + temp);

	      userTotal = userTotal + temp;

	      if (value[2] + value[3] > 10 && temp == 11)
		{
		  printf ("something %d \n", userTotal);
		  userTotal = userTotal + 1;
		}

	      if (userTotal == 21)
		{
		  printf ("WONN!\n\n");
		  exit (0);
		}

	      else if (userTotal > 21)
		{
		  //printf("WONN!\n\n");
		  printf ("You busted, Dealer wins\n\n");
		  exit (0);
		}
	      printf ("Would you like to \"hit\" or \"stand\"?");
	      scanf ("%s", input);
	    }
	  if (strcmp (input, "stand") == 0)
	    {
	      //printf("String stad\n");
	      while (dealerTotal < 17)
		{
		  printf ("Dealer's total: %d\n", dealerTotal);
		  int temp = rand () % (high - low + 1) + low;
		  //printf ("Added card\n");

			//ace would count as 1 at this time
		  if (value[0] + value[1] > 10 && temp == 11)
		    {
		    //  printf ("something");
		      dealerTotal = value[0] + value[1] + 1;
		    }
		  else
		    {
		      dealerTotal = dealerTotal + temp;
		      printf ("Added card! Total: %d\n", dealerTotal);
		    }

		}

	      if (userTotal > 21)
		{
		  printf ("User BUSTED!!! Dealer wins\n\n");
		  exit (0);
		}
	      else if (dealerTotal > 21)
		{
		  printf ("Dealer BUSTED!! USer wins\n\n");
		  exit (0);
		}
	      else if (dealerTotal == 21)
		{
		  printf ("Dealer winss!!!\n\n");
		  exit (0);
		}
	
	      //needto make sure what to do when user want to stand
	      //dealers card totoal is 17 and higher
	      //see the diff and whoeve close wins!
	      if (dealerTotal >= 17 && (strcmp (input, "stand") == 0))
		{
		  if ((userTotal - 21) > (dealerTotal - 21))
		    {
		      printf ("Uer WINSSSS!!!!\n\n");
		    }
		  else if ((userTotal - 21) < (dealerTotal - 21))
		    {
		      printf ("Dealer WINSSSS!!!\n\n");
		    }
		  exit (0);
		}

	      printf ("Would you like to \"hit\" or \"stand\"?");
	      scanf ("%s", input);
	    }
	  printf ("..");
	}

      return 0;
    }

