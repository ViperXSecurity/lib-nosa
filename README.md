# lib-nosa ( No Socket API )

**lib-nosa** is a minimalist C library designed to facilitate socket connections through AFD driver IOCTL operations on Windows. By bypassing the traditional `winsock2.h -> (ws2_dll.dll)`  header, **lib-nosa** directly interacts with the internal socket APIs of the AFD (Ancillary Function Driver for WinSock), offering developers a lightweight and low-level alternative for network programming.

## Features

- Establishes (TCP, UDP, RAW) connections directly through AFD driver IOCTL calls, **bypassing** the standard Winsock2 interface.
- Focuses on simplicity and performance, with a small footprint and no unnecessary dependencies.
- Provides direct access to internal socket APIs, giving developers fine-grained control over network operations.
- Avoids the overhead and abstraction of the Winsock2 API, making it ideal for performance-critical applications.

## Getting Started

### Prerequisites

- Windows operating system (x64 Only) -> Windows Vista+ ~ Windows 10/11
- C compiler (e.g., GCC, MSVC)

### Installation

To use **lib-nosa** in your project, clone the repository and include the library files in your build process.

```bash
git clone https://github.com/ViperXSecurity/lib-nosa

[linux]

  sudo apt-get install gcc-mingw-w64-x86-64
  x86_64-w64-mingw32-gcc  -o nosa-example.exe nosa-example.c

[Windows]

  Install https://sourceforge.net/projects/mingw/
  x86_64-w64-mingw32-gcc.exe -o nosa-example.exe nosa-example.c
or
  Create a new project on Visual Studio 2019+
```

### APIs
```C
NTSTATUS nosa_dns_lookup(HANDLE hSocket, const char* domain_name, DOMAIN_INFO* outBuffer)
NTSTATUS nosa_connect(HANDLE* hSocket, char* host, int port, char* socketType)
NTSTATUS nosa_send(HANDLE* hSocket, LPVOID packet_data, int packet_data_sz)
NTSTATUS nosa_recv(HANDLE hSocket, LPVOID packet_data_received)
```

### Key definitions (nosa.h)
```C
//#define CURRENT_LOG_LEVEL 0 // uncomment to hide log informations
#ifndef CURRENT_LOG_LEVEL < 1
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif
<...>
#define DNS_SERVER "8.8.8.8"
#define DNS_PORT 53
<...>
#define MAX_RECV_BYTES 0x1000
#define MAX_SENT_BYTES 0x1000
```

### TODO
- x86 AFD.sys driver connection.

- ### (For bind connections)
- nosa_listen()
- nosa_accept()
