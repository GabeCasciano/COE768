// Gabriel Casciano, 500744076, L4
#include <stdint.h>

/*
 * Server process,
 * 1. Bind server to port
 * 2. Wait for client
 * 3. Recv client files request for the small file
 * 4. Put header together and send
 * 5. Send small file
 * 6. Repeat 3. -> 5. for medium and large files
 * 7. Wait for disconnect request
 * 8. close server
 *
 */
