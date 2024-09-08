#include "nosa.h"

int main() {
    // Powershell [UDP] Server
    /*
    $udpClient = New-Object System.Net.Sockets.UdpClient(8888)

    while ($true) {
        $remoteEndPoint = New-Object System.Net.IPEndPoint([System.Net.IPAddress]::Any, 0)
        $receivedBytes = $udpClient.Receive([ref]$remoteEndPoint)
        $receivedData = [System.Text.Encoding]::UTF8.GetString($receivedBytes)

        Write-Host "Received: $receivedData from $($remoteEndPoint.Address):$($remoteEndPoint.Port)"

        $response = [System.Text.Encoding]::UTF8.GetBytes("0xdeadbeef !!")
        $udpClient.Send($response, $response.Length, $remoteEndPoint)
    }
    */

    HANDLE hSocket = NULL;
    char* socketType = "UDP";   // Protocol (TCP, UDP, RAW)
    char* host = "127.0.0.1";   // Target Host
    int port = 8888;            // Target port

    unsigned char pktPtr_send[MAX_SENT_BYTES] = { 0 };  // Craft our TCP packet request
    snprintf((char*)pktPtr_send, MAX_SENT_BYTES, "HELLO FROM [%s]!", socketType); // Format the string and store it in pktPtr_send
 
    // Craft our send TCP packet request
    unsigned char pktPtr_resp[MAX_RECV_BYTES] = { 0 };

    /*
        You can reuse the existing handle to perform iterative operations [request -> response].
        After the handle is created for the first time, you can follow this steps:
        nosa_connect();
        '-> while (1) {  nosa_send(); nosa_recv(); } 
    */

    // Connect into remote host
    nosa_connect(&hSocket, host, port, socketType);

    while (1)
    {
        // Send client packets
        nosa_send(&hSocket, pktPtr_send, sizeof(pktPtr_send));
        printf("nosa_send() -> Request:\n");
        hexdump(&pktPtr_send, 0x100);

        // Receive and print TCP packet response
        nosa_recv((HANDLE*)hSocket, pktPtr_resp);
        printf("nosa_recv() -> Response:\n");
        hexdump(&pktPtr_resp, 0x100);
        Sleep(1000);
        
    }

    // Close target socket
    if (hSocket) // close socket only in case hSocket != 0
    {
        afd_close(hSocket);
    }

    return 0;
}
