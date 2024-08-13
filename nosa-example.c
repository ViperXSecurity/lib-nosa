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
    HANDLE hSocket = NULL;
    NTSTATUS Status = NULL;
    char ip_string[16] = { 0 };      // Allocate enough space for an IPv4 address in dotted notation

    char* socketType = "TCP";  // #TODO UDP -> not working.
                                     // Sadly, afd!AfdConnect() call [ExFreeToLookasideListEx] with a null value when it got a UDP conn
   
    char* host = "google.com"; // #TODO -> subdomain queries not working for while.
    int port = 80;

    // 
    // You can reuse the existing handle to perform iterative operations [request -> response].
    // After the handle is created for the first time, you can follow the follow steps:
    // '-> while (1) { nosa_connect(); nosa_send(); nosa_recv(); } 
    //

    // Connect into remote host
    nosa_connect(&hSocket, host, port, socketType);

    // Craft our send TCP packet request
    unsigned char pktPtr[MAX_SENT_BYTES] = "GET / HTTP/1.1\x0d\x0a\x0d\x0a";

    // print wsa_recv_buffer byte array
    LOG_INFO("nosa_send() Request:");

    hexdump(pktPtr, 0x100);

    // Send client packets
    nosa_send(&hSocket, pktPtr, sizeof(pktPtr));

    // Receive and print TCP packet response
    LPVOID packet_data_received = VirtualAlloc(0, MAX_RECV_BYTES, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    memset(packet_data_received, 0, MAX_RECV_BYTES); // clear our created vm alloc

    nosa_recv((HANDLE*)hSocket, packet_data_received);

    BYTE* bytePtr = packet_data_received;

    // print wsa_recv_buffer byte array
    LOG_INFO("nosa_recv() Response:");
    hexdump(packet_data_received, 0x100);

    if (hSocket) // close socket only in case hSocket != 0
    {
        afd_close(hSocket);
    }

    return 0;
}
