#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cups/backend.h>
#include <cups/http.h>


int
main (int argn, char *argv [])
{
  //  const char *resolved_uri;
  const char *cups_serverbin;
  char filename [2048];
  http_t *connection;

  if (argn < 6)
    {
      fprintf (stderr, "Usage: %s job user title copies options [filename]\n",
	       argv [0]);
      return (CUPS_BACKEND_FAILED);
    }
  
  connection = httpConnectEncrypt ("c530-e27b83", 80, HTTP_ENCRYPT_NEVER);
  httpGet (connection, "http://c530-e27b83");
  httpClose (connection);

  if ((cups_serverbin = getenv ("CUPS_SERVERBIN")) == NULL)
    {
      cups_serverbin = "/usr/libexec/cups";
    }
  
  snprintf (filename, sizeof (filename), "%s/backend/dnssd", cups_serverbin);
  
  execv (filename, argv);

  fprintf(stderr, "ERROR: Unable to execute backend \"%s\": %s\n", filename,
          strerror(errno));
  exit (CUPS_BACKEND_STOP);
}
