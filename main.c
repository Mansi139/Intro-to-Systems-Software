#include <stdio.h>
#include <dlfcn.h>

int
main ()
{
  void *handle;
  void (*my_str_copy) (char *, char *);
  void (*my_strcat) (char *, char *);
  char *error;

  handle = dlopen ("mystr.so", RTLD_LAZY);
  if (!handle)
    {
      printf ("%s\n", dlerror ());
      exit (1);

    }
  dlerror ();

  my_str_copy = dlsym (handle, "my_strcpy");
  my_strcat = dlsym (handle, "my_strcat");

  if ((error = dlerror ()) != NULL)
    {
      printf ("%s\n", error);
      exit (1);
    }

  char dest[100];
  char src[] = "hello world!";

  my_str_copy (dest, src);

  printf ("%s\n", dest);

  my_strcat (dest, src);
  printf ("%s\n", dest);

  dlclose (handle);
  return 0;
}
