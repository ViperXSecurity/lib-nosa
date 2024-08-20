#include <stdio.h>
#include "nosa.h"

int main() {
    // Powershell [TCP] Server
    /*   
    # Create a TCP listener on port 8888
    $tcpListener = New - Object System.Net.Sockets.TcpListener([System.Net.IPAddress]::Any, 8888)
    $tcpListener.Start()

    Write - Host "TCP Server is running on port 8888..."

    while ($true) {
        # Accept a TCP client connection
            $tcpClient = $tcpListener.AcceptTcpClient()
            $networkStream = $tcpClient.GetStream()

            # Buffer to read the incoming data
            $buffer = New - Object byte[] 1024
            $bytesRead = $networkStream.Read($buffer, 0, $buffer.Length)

            # Convert the received bytes to a string
            $receivedData = [System.Text.Encoding]::UTF8.GetString($buffer, 0, $bytesRead)

            # Get the remote client's IP address and port
            $remoteEndPoint = $tcpClient.Client.RemoteEndPoint
            Write - Host "Received: $receivedData from $remoteEndPoint"

            # Prepare and send the response
            $response = [System.Text.Encoding]::UTF8.GetBytes("0xdeadbeef !!")
            $networkStream.Write($response, 0, $response.Length)

            # Close the client connection
            $networkStream.Close()
            $tcpClient.Close()
    }
    */

    HANDLE hSocket = NULL;
    char* socketType = "TCP";         // Protocol (TCP, UDP, RAW)
    char* host = "cloud.google.com";  // Target Host
    int port = 80;                    // Target port

    unsigned char pktPtr_send[MAX_SENT_BYTES] = { 0 };  // Craft our TCP packet request
    snprintf((char*)pktPtr_send, MAX_SENT_BYTES, "GET / HTTP/1.1\x0d\x0a\x0d\x0a", socketType); // Format the string and store it in pktPtr_send
 
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
    // Send client packets
    nosa_send(&hSocket, pktPtr_send, sizeof(pktPtr_send));
    printf("nosa_send() -> Request:\n");
    hexdump(&pktPtr_send, 0x100);

    // Receive and print TCP packet response
    nosa_recv((HANDLE*)hSocket, &pktPtr_resp);
    printf("nosa_recv() -> Response:\n");
    hexdump(&pktPtr_resp, 0x100);

    // Close target socket
    if (hSocket) // close socket only in case hSocket != 0
    {
        afd_close(hSocket);
    }

    return 0;
}
