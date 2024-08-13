#include <stdio.h>
#include <windows.h>

#ifndef LOG_H
#define LOG_H

// Logging levels
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERROR 3

// Set the current log level
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

// Macro to get the current time as a string
#define GET_CURRENT_TIME_STR(buffer, size) \
    do { \
        SYSTEMTIME st; \
        GetSystemTime(&st); \
        snprintf(buffer, size, "%02d:%02d:%02d", \
                 st.wHour, st.wMinute, st.wSecond); \
    } while (0)

// Base logging macro, used by other macros
#define LOG(level, level_str, format, ...) \
    do { \
        if (level >= CURRENT_LOG_LEVEL) { \
            char time_str[16]; \
            char *filename = strrchr(__FILE__, '\\'); \
            GET_CURRENT_TIME_STR(time_str, sizeof(time_str)); \
            fprintf(stderr, "[%s] %s:%s:%d: " format "\n\n", \
                    time_str, level_str, filename, __LINE__, ##__VA_ARGS__); \
        } \
    } while (0)

// Log macros for different levels
#define LOG_DEBUG(format, ...) LOG(LOG_LEVEL_DEBUG, "DEBUG", format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)  LOG(LOG_LEVEL_INFO,  "INFO",  format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  LOG(LOG_LEVEL_WARN,  "WARN",  format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG(LOG_LEVEL_ERROR, "ERROR", format, ##__VA_ARGS__)

#endif // LOG_H

#define Initializeobject_attributes(p, n, a, r, s) { \
    (p)->Length = sizeof(OBJECT_ATTRIBUTES);        \
    (p)->RootDirectory = r;                         \
    (p)->Attributes = a;                            \
    (p)->ObjectName = n;                            \
    (p)->SecurityDescriptor = s;                    \
    (p)->SecurityQualityOfService = NULL;           \
}

#pragma push(pack, 1)
#pragma warning(push)
#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

struct buffer_data_t
{
    uint32_t Size;
    char _4[4];
    int64_t VirtualAddress;
    int32_t pad;
    int32_t pad1;
};

struct userbuf_t
{
    struct buffer_data_t* buffer_data;
    int32_t num_buffers;
    int32_t field_c;
    uint32_t length;
    char _14[1];
    uint8_t field_15;
    char _16[2];
};

#pragma push(pop)

const GUID GUID_NULL = { 
    0x00000000, 0x0000, 0x0000, 
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

#define SystemHandleInformation		    0x10
#define SystemHandleInformationSize	    0x400000

#define FILE_SUPERSEDE		            0x0
#define FILE_OPEN			    0x1
#define FILE_CREATE		            0x2
#define FILE_OPEN_IF		            0x3
#define FILE_OVERWRITE			    0x4
#define FILE_OVERWRITE_IF	            0x5
#define FILE_MAXIMUM_DISPOSITION            0x5

#define OBJ_INHERIT                         0x2L
#define OBJ_PERMANENT                       0x10L
#define OBJ_EXCLUSIVE                       0x20L
#define OBJ_CASE_INSENSITIVE                0x40L
#define OBJ_OPENIF                          0x80L
#define OBJ_OPENLINK                        0x100L
#define OBJ_KERNEL_HANDLE                   0x200L
#define OBJ_FORCE_ACCESS_CHECK              0x400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP   0x800L
#define OBJ_DONT_REPARSE                    0x1000L
#define OBJ_VALID_ATTRIBUTES                0x1FF2L


#define AFD_ENDPOINT_CONNECTIONLESS	    0x1
#define AFD_ENDPOINT_MESSAGE_ORIENTED	    0x10
#define AFD_ENDPOINT_RAW		    0x100
#define AFD_ENDPOINT_MULTIPOINT	            0x1000
#define AFD_ENDPOINT_C_ROOT		    0x10000
#define AFD_ENDPOINT_D_ROOT		    0x100000

#define TDI_RECEIVE_BROADCAST		    0x4
#define TDI_RECEIVE_MULTICAST		    0x8
#define TDI_RECEIVE_PARTIAL		    0x10
#define TDI_RECEIVE_NORMAL		    0x20
#define TDI_RECEIVE_EXPEDITED		    0x40
#define TDI_RECEIVE_PEEK		    0x80
#define TDI_RECEIVE_NO_RESPONSE_EXP         0x100
#define TDI_RECEIVE_COPY_LOOKAHEAD	    0x200
#define TDI_RECEIVE_ENTIRE_MESSAGE	    0x400
#define TDI_RECEIVE_AT_DISPATCH_LEVEL	    0x800
#define TDI_RECEIVE_CONTROL_INFO	    0x1000
#define TDI_RECEIVE_FORCE_INDICATION	    0x2000
#define TDI_RECEIVE_NO_PUSH		    0x4000

#define MAX_PROTOCOL_CHAIN                  7
#define WSAPROTOCOL_LEN                     255

#define IOCTL_AFD_BIND			    0x12003
#define IOCTL_AFD_DOCONNECT		    0x12007
#define IOCTL_AFD_DOCONNECT_EX	            0x120c7
#define IOCTL_AFD_RECV			    0x12017
#define IOCTL_AFD_SEND			    0x1201F

#define IOCTL_AFD_SET_CONTEXT               0x12047
#define IOCTL_AFD_GET_CONTEXT               0x12043

#define SOCK_CONTEXT_BUF_SIZE ( sizeof(SOCK_SHARED_INFO) + \
                                sizeof(GUID)+ \
                                sizeof(PVOID) + 8 + \
                                (2 * sizeof(SOCKADDR_STORAGE)))

#define SOCK_CONTEXT_ADDR_SIZE (sizeof(SOCKADDR_STORAGE))

#define INADDR_ANY                          0x00000000
#define INADDR_LOOPBACK                     0x7f000001
#define INADDR_BROADCAST                    0xffffffff
#define INADDR_NONE                         0xffffffff

#define DNS_SERVER "8.8.8.8"
#define DNS_PORT 53

#define MAX_RECV_BYTES 0x1000
#define MAX_SENT_BYTES 0x1000

#pragma comment(lib, "ntdll.lib")

typedef struct _WSAPROTOCOLCHAIN
{
    int ChainLen;                  /* the length of the chain,     */
    /* length = 0 means layered protocol, */
    /* length = 1 means base protocol, */
    /* length > 1 means protocol chain */
    DWORD ChainEntries[MAX_PROTOCOL_CHAIN]; /* a list of dwCatalogEntryIds */
} WSAPROTOCOLCHAIN, * LPWSAPROTOCOLCHAIN;

typedef struct _WSAPROTOCOL_INFOW
{
    DWORD dwServiceFlags1;
    DWORD dwServiceFlags2;
    DWORD dwServiceFlags3;
    DWORD dwServiceFlags4;
    DWORD dwProviderFlags;
    GUID ProviderId;
    DWORD dwCatalogEntryId;
    WSAPROTOCOLCHAIN ProtocolChain;
    int iVersion;
    int iAddressFamily;
    int iMaxSockAddr;
    int iMinSockAddr;
    int iSocketType;
    int iProtocol;
    int iProtocolMaxOffset;
    int iNetworkByteOrder;
    int iSecurityScheme;
    DWORD dwMessageSize;
    DWORD dwProviderReserved;
    WCHAR szProtocol[WSAPROTOCOL_LEN + 1];
} WSAPROTOCOL_INFOW, * LPWSAPROTOCOL_INFOW;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
    USHORT UniqueProcessId;
    USHORT CreatorBackTraceIndex;
    UCHAR ObjectTypeIndex;
    UCHAR HandleAttributes;
    USHORT HandleValue;
    PVOID Object;
    ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, * PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
    ULONG NumberOfHandles;
    SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef enum _EVENT_TYPE
{
    NotificationEvent,
    SynchronizationEvent
} EVENT_TYPE;

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;       // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService; // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef struct _INITIAL_TEB
{
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackAllocationBase;
} INITIAL_TEB, * PINITIAL_TEB;

typedef VOID(NTAPI* PIO_APC_ROUTINE)(
    PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    ULONG Reserved
    );

// Define the AFD_CREATE_PACKET structure with proper packing
#pragma pack(push, 1)

/**
 * Structure representing an AFD_CREATE_PACKET.
 *
 * This structure contains information related to creating an AFD packet.
 * It includes fields for various parameters such as NextEntryOffset, Flags, EaNameLength, EaValueLength, EaName,
 * EndpointFlags, GroupID, AddressFamily, SocketType, Protocol, SizeOfTransportName, and TransportName.
 */
typedef struct _AFD_CREATE_PACKET
{
    uint32_t NextEntryOffset;
    uint8_t Flags;
    uint8_t EaNameLength;
    uint16_t EaValueLength;
    char EaName[16];
    uint32_t EndpointFlags;
    uint32_t GroupID;
    uint32_t AddressFamily;
    uint32_t SocketType;
    uint32_t Protocol;
    uint64_t SizeOfTransportName;
    char TransportName[5]; // 2 wchar_t characters
} AFD_CREATE_PACKET;
#pragma pack(pop)

/**
 * Structure representing AFD bind data.
 */
typedef struct _AFD_BIND_DATA
{
    ULONG ShareType;
    SOCKADDR_IN addr;
} AFD_BIND_DATA, * PAFD_BIND_DATA;

/**
 * Structure representing AFD listen data.
 */
typedef struct _AFD_LISTEN_DATA {
    BOOLEAN				UseSAN;
    ULONG				Backlog;
    BOOLEAN				UseDelayedAcceptance;
} AFD_LISTEN_DATA, * PAFD_LISTEN_DATA;

/**
 * Structure representing data for accepting connections in the AFD (Ancillary Function Driver).
 */
typedef struct _AFD_ACCEPT_DATA {
    BOOLEAN				UseSAN;
    ULONG				SequenceNumber;
    HANDLE				ListenHandle;
} AFD_ACCEPT_DATA, * PAFD_ACCEPT_DATA;

// SOCKADDR_STORAGE structure definition
typedef struct _SOCKADDR_STORAGE {
    short ss_family;          // Address family
    char __ss_pad1[6];        // Padding to ensure alignment
    __int64 __ss_align;       // Force alignment to 64-bit boundary
    char __ss_pad2[112];      // Additional padding to bring the size to 128 bytes
} SOCKADDR_STORAGE;

/**
 * Structure representing AFD (Ancillary Function Driver) actual socket state.
 */
typedef enum _SOCKET_STATE
{
    SocketUndefined = -1,
    SocketOpen,
    SocketBound,
    SocketBoundUdp,
    SocketConnected,
    SocketClosed
} SOCKET_STATE, * PSOCKET_STATE;

/**
 * Structure representing AFD (Ancillary Function Driver) shared informations.
 */
typedef struct _SOCK_SHARED_INFO {
    SOCKET_STATE                State;
    INT                            AddressFamily;
    INT                            SocketType;
    INT                            Protocol;
    INT                            SizeOfLocalAddress;
    INT                            SizeOfRemoteAddress;
    struct linger                LingerData;
    ULONG                        SendTimeout;
    ULONG                        RecvTimeout;
    ULONG                        SizeOfRecvBuffer;
    ULONG                        SizeOfSendBuffer;
    struct {
        BOOLEAN                    Listening : 1;
        BOOLEAN                    Broadcast : 1;
        BOOLEAN                    Debug : 1;
        BOOLEAN                    OobInline : 1;
        BOOLEAN                    ReuseAddresses : 1;
        BOOLEAN                    ExclusiveAddressUse : 1;
        BOOLEAN                    NonBlocking : 1;
        BOOLEAN                    DontUseWildcard : 1;
        BOOLEAN                    ReceiveShutdown : 1;
        BOOLEAN                    SendShutdown : 1;
        BOOLEAN                    UseDelayedAcceptance : 1;
        BOOLEAN                    UseSAN : 1;
        BOOLEAN                    HasGUID : 1;
    } Flags;
    DWORD                        CreateFlags;
    DWORD                        CatalogEntryId;
    DWORD                        ServiceFlags1;
    DWORD                        ProviderFlags;
    DWORD                        GroupID;
    DWORD                        GroupType;
    INT                            GroupPriority;
    INT                            SocketLastError;
    HWND                        hWnd;
#ifndef _WIN64
    LONG                        Padding;
#endif
    DWORD                        SequenceNumber;
    UINT                        wMsg;
    LONG                        AsyncEvents;
    LONG                        AsyncDisabledEvents;
} SOCK_SHARED_INFO, * PSOCK_SHARED_INFO;

/**
 * Structure representing AFD (Ancillary Function Driver) current socket-context informations.
 */
typedef struct _SOCKET_CONTEXT {
    SOCK_SHARED_INFO SharedData;
    GUID Guid;
    ULONG SizeOfHelperData;
    ULONG Padding;
    SOCKADDR LocalAddress;
    SOCKADDR RemoteAddress;
    PVOID Helper;
} SOCKET_CONTEXT, * PSOCKET_CONTEXT;

/**
 * Structure representing AFD (Ancillary Function Driver) connection information.
 */
typedef struct _AFD_CONNECT_INFO
{
    uint64_t UseSAN;
    uint64_t Root;
    uint64_t Unknown;
    SOCKADDR_IN Bind;
} AFD_CONNECT_INFO, * PAFD_CONNECT_INFO;

/**
 * Structure representing a buffer and its length for Winsock operations.
 */
typedef struct _AFD_WSABUF
{
    ULONG_PTR len;
    PVOID buf;
} AFD_WSABUF, * PAFD_WSABUF;

/**
 * Structure representing information for AFD receive operation.
 */
typedef struct _AFD_RECV_INFO
{
    PAFD_WSABUF BufferArray;
    DWORD BufferCount;
    DWORD AfdFlags;
    DWORD TdiFlags;
} AFD_RECV_INFO, * PAFD_RECV_INFO;

/**
 * Structure representing information for UDP receive operation in AFD.
 */
typedef struct _AFD_RECV_INFO_UDP {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
    ULONG				TdiFlags;
    PVOID				Address;
    PINT				AddressLength;
} AFD_RECV_INFO_UDP, * PAFD_RECV_INFO_UDP;

/**
 * Structure representing information for sending data using AFD.
 */
typedef struct  _AFD_SEND_INFO {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
    ULONG				TdiFlags;
} AFD_SEND_INFO, * PAFD_SEND_INFO;

/**
 * Structure representing information for sending data over UDP using AFD.
 */
typedef struct _AFD_SEND_INFO_UDP {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
#if 1 /* timurrrr: based on XP+win7 observation: i#418 */
    ULONG				UnknownGap[9];
    ULONG				SizeOfRemoteAddress;
    PVOID				RemoteAddress;
#else
    TDI_REQUEST_SEND_DATAGRAM		TdiRequest;
    TDI_CONNECTION_INFORMATION		TdiConnection;
#endif
} AFD_SEND_INFO_UDP, * PAFD_SEND_INFO_UDP;

/**
 * Structure representing information for further DNS query lookup.
 */
typedef struct _DOMAIN_INFO
{
    uint32_t hex_ip_address;
    unsigned char ip_address_str[16];
}DOMAIN_INFO;


typedef NTSTATUS(NTAPI* NtClose_t)(HANDLE Handle);
typedef NTSTATUS(NTAPI* NtCreateEvent_t)(PHANDLE EventHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES object_attributes, EVENT_TYPE EventType,
    BOOLEAN InitialState);
typedef NTSTATUS(NTAPI* NtDeviceIoControlFile_t)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock, ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength,
    PVOID OutputBuffer, ULONG OutputBufferLength);
typedef NTSTATUS(NTAPI* NtWaitForSingleObject_t)(HANDLE Handle, BOOLEAN Alertable, PLARGE_INTEGER Timeout);
typedef NTSTATUS(NTAPI* NtCreateFile_t)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);

// Function pointers
NtClose_t NtClose;
NtCreateEvent_t NtCreateEvent;
NtCreateFile_t NtCreateFile;
NtDeviceIoControlFile_t NtDeviceIoControlFile;
NtWaitForSingleObject_t NtWaitForSingleObject;



NTSTATUS nosa_dns_lookup(HANDLE hSocket, const char* host, DOMAIN_INFO* outBuffer);

/**
 * Check if a character is a digit.
 *
 * @param ch The character to be checked.
 *
 * @returns 1 if the character is a digit, 0 otherwise.
 */
int is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

/**
 * Checks if a character is a hexadecimal digit.
 *
 * @param ch The character to be checked.
 *
 * @returns 1 if the character is a hexadecimal digit, 0 otherwise.
 */
int is_hex_digit(char ch)
{
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

// Function to check if a string is an IPv4 address
int is_ipv4_address(const char* host)
{
    int dots = 0;
    int digits = 0;
    const char* ptr = host;

    while (*ptr) {
        if (*ptr == '.') {
            if (digits == 0) return 0; // No digits before the dot
            dots++;
            digits = 0; // Reset digit count for the next block
        }
        else if (is_digit(*ptr)) {
            digits++;
            if (digits > 3) return 0; // Too many digits in one block
        }
        else {
            return 0; // Invalid character for an IPv4 address
        }
        ptr++;
    }

    // There should be exactly 3 dots and at least one digit after the last dot
    return (dots == 3 && digits > 0) ? 1 : 0;
}

/**
 * Checks if the given string is a valid IPv6 address.
 *
 * @param host The string representing the IPv6 address.
 *
 * @returns 1 if the string is a valid IPv6 address, 0 otherwise.
 */
int is_ipv6_address(const char* host)
{
    int colons = 0;
    int double_colon = 0;
    int hex_digits = 0;
    const char* ptr = host;

    while (*ptr) {
        if (*ptr == ':') {
            if (hex_digits == 0 && colons > 0 && *(ptr - 1) != ':') return 0; // No hex digits between colons
            if (*(ptr + 1) == ':') {
                if (double_colon) return 0; // Only one double colon allowed
                double_colon = 1;
                ptr++; // Skip the second colon of the double colon
            }
            colons++;
            hex_digits = 0; // Reset hex digit count for the next block
        }
        else if (is_hex_digit(*ptr)) {
            hex_digits++;
            if (hex_digits > 4) return 0; // Each block in IPv6 should not exceed 4 hex digits
        }
        else {
            return 0; // Invalid character for an IPv6 address
        }
        ptr++;
    }

    // Valid IPv6 addresses have between 2 and 7 colons, or a single double colon
    return (colons >= 2 && colons <= 7) || (double_colon && colons < 7);
}

/**
 * Checks if the given input is a valid domain name.
 *
 * @param host The input string to be checked.
 *
 * @returns 1 if the input is a valid domain name, 0 otherwise.
 */
int is_domain_name(const char* host)
{
    const char* ptr = host;
    int has_dot = 0;

    // First, check if the string is an IP address
    if (is_ipv4_address(host)) {
        return 0; // It's an IP address, not a domain name
    }

    // Check if the string contains valid domain name characters
    while (*ptr) {
        if (*ptr == '.') {
            has_dot = 1;
        }
        else if (!((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || is_digit(*ptr) || *ptr == '-')) {
            return 0; // Invalid character for a domain name
        }
        ptr++;
    }

    // A valid domain name should have at least one dot and should not start or end with a dot
    return has_dot && host[0] != '.' && host[ptr - host - 1] != '.' ? 1 : 0;
}

/**
 * Converts a 32-bit unsigned long integer from host byte order to network byte order.
 *
 * @param hostlong The value to be converted from host byte order to network byte order.
 *
 * @returns The converted value in network byte order.
 */
ULONG htonl(ULONG hostlong)
{
    return ((hostlong & 0xFF000000L) >> 24) |
        ((hostlong & 0x00FF0000L) >> 8) |
        ((hostlong & 0x0000FF00L) << 8) |
        ((hostlong & 0x000000FFL) << 24);
}

/**
 * Converts a 16-bit number from host to network byte order.
 *
 * @param netshort The 16-bit number in host byte order.
 *
 * @returns The 16-bit number in network byte order.
 */
USHORT htons(USHORT netshort)
{
    return (netshort << 8) | (UCHAR)((((ULONG_PTR)netshort) >> 8) & 0xff);
    //or
    //return _byteswap_ushort(netshort);
}

/**
 * Converts a 16-bit number from network byte order to host byte order.
 *
 * @param netshort The 16-bit number in network byte order.
 *
 * @returns The 16-bit number in host byte order.
 */
USHORT ntohs(USHORT netshort)
{
    return (netshort >> 8) | ((netshort & 0x00FF) << 8);
}

/**
 * Converts a string containing an IPv4 address in dotted-decimal notation
 * to a ULONG value in network byte order.
 *
 * @param cp A pointer to a null-terminated string representing the IPv4 address.
 *
 * @returns The ULONG value representing the IPv4 address in network byte order.
 */
ULONG inet_addr(PCSTR cp)
{
    ULONG val, base, n;
    UCHAR c;
    ULONG parts[4], * pp = parts;
    if (!cp) return INADDR_ANY;
    if (!isdigit(*cp)) return INADDR_NONE;

again:
    /*
     * Collect number up to ``.''.
     * Values are specified as for C:
     * 0x=hex, 0=octal, other=decimal.
     */
    val = 0;
    base = 10;
    if (*cp == '0')
    {
        if (*++cp == 'x' || *cp == 'X')
            base = 16, cp++;
        else
            base = 8;
    }
    while ((c = *cp))
    {
        if (isdigit(c))
        {
            val = (val * base) + (c - '0');
            cp++;
            continue;
        }
        if (base == 16 && isxdigit(c))
        {
            val = (val << 4) + (c + 10 - (islower(c) ? 'a' : 'A'));
            cp++;
            continue;
        }
        break;
    }
    if (*cp == '.')
    {
        /*
         * Internet format:
         *    a.b.c.d
         *    a.b.c    (with c treated as 16-bits)
         *    a.b    (with b treated as 24 bits)
         */
        if (pp >= parts + 4) return (INADDR_NONE);
        *pp++ = val;
        cp++;
        goto again;
    }
    //Check for trailing characters.
    if (*cp && !isspace((UCHAR)*cp)) return (INADDR_NONE);

    *pp++ = val;
    /*
     * Concoct the address according to
     * the number of parts specified.
     */
    n = (ULONG)(pp - parts);
    switch (n)
    {
    case 1: /* a -- 32 bits */
        val = parts[0];
        break;

    case 2: /* a.b -- 8.24 bits */
        val = (parts[0] << 24) | (parts[1] & 0xffffff);
        break;

    case 3: /* a.b.c -- 8.8.16 bits */
        val = (parts[0] << 24) | ((parts[1] & 0xff) << 16) | (parts[2] & 0xffff);
        break;

    case 4: /* a.b.c.d -- 8.8.8.8 bits */
        val = (parts[0] << 24) | ((parts[1] & 0xff) << 16) | ((parts[2] & 0xff) << 8) | (parts[3] & 0xff);
        break;

    default:
        return (INADDR_NONE);
    }
    val = htonl(val);
    return (val);
}

/**
 * Converts an IP address from string format to network byte order (big-endian).
 *
 * @param ip_address The IP address in string format.
 *
 * @returns The IP address in network byte order.
 */
ULONG convert_ip_to_htonl(PCSTR ip_address)
{
    ULONG parts[4] = { 0 };  // Array to store the four parts of the IP address
    ULONG result = 0;
    int part_index = 0;
    int part_value = 0;

    // Loop through each character in the string
    while (*ip_address) {
        if (isdigit(*ip_address)) {
            // Build the current part by shifting the previous value by 10 and adding the new digit
            part_value = part_value * 10 + (*ip_address - '0');
        }
        else if (*ip_address == '.') {
            // Store the current part in the parts array
            parts[part_index++] = part_value;
            part_value = 0;
        }
        ip_address++;
    }
    // Store the last part
    parts[part_index] = part_value;

    // Combine the four parts into a single 32-bit integer
    result = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3];

    // Convert to network byte order
    return result;
}

/**
 * Converts a 32-bit network-order IP address to a human-readable IP address format.
 *
 * @param network_order_ip The 32-bit network-order IP address to convert.
 *
 * @returns A pointer to a static character array containing the human-readable IP address.
 */
char* convert_htonl_to_ip_address(unsigned long network_order_ip) {
    static char ip_address[16];  // Buffer to hold the printable IP address

    unsigned char bytes[4];
    bytes[0] = (network_order_ip >> 24) & 0xFF;
    bytes[1] = (network_order_ip >> 16) & 0xFF;
    bytes[2] = (network_order_ip >> 8) & 0xFF;
    bytes[3] = network_order_ip & 0xFF;

    // Format the bytes into a string
    snprintf(ip_address, sizeof(ip_address), "%u.%u.%u.%u", bytes[0], bytes[1], bytes[2], bytes[3]);

    return ip_address;
}
/**
 * Builds a DNS query for the given domain.
 *
 * @param domain The domain name to query.
 * @param query_len Pointer to store the length of the query.
 *
 * @returns A pointer to the constructed DNS query.
 */
unsigned char* build_dns_query(const char* domain, int* query_len) {
    static unsigned char query[512];  // DNS query buffer
    unsigned char* qname;
    int i, len;

    // DNS Header
    unsigned short transaction_id = htons(0x2);
    unsigned short flags = htons(0x0100);
    unsigned short questions = htons(1);
    unsigned short answer_rrs = htons(0);
    unsigned short authority_rrs = htons(0);
    unsigned short additional_rrs = htons(0);

    // Build header
    memcpy(query, &transaction_id, 2);
    memcpy(query + 2, &flags, 2);
    memcpy(query + 4, &questions, 2);
    memcpy(query + 6, &answer_rrs, 2);
    memcpy(query + 8, &authority_rrs, 2);
    memcpy(query + 10, &additional_rrs, 2);

    // Build question
    qname = query + 12;
    const char* dot_pos = strchr(domain, '.');
    int subdomain_detected = (dot_pos != NULL && strchr(dot_pos + 1, '.') != NULL);

    while (dot_pos) {
        len = dot_pos - domain;
        *qname++ = len;
        memcpy(qname, domain, len);
        qname += len;
        domain = dot_pos + 1;
        dot_pos = strchr(domain, '.');
    }
    len = strlen(domain);
    *qname++ = len;
    memcpy(qname, domain, len);
    qname += len;
    *qname++ = 0x00;

    // Type and Class
    unsigned short qtype = htons(1);  // Type A for IPv4 addresses
    unsigned short qclass = htons(1); // Class IN
    memcpy(qname, &qtype, 2);
    memcpy(qname + 2, &qclass, 2);

    *query_len = qname + 4 - query;

    // Debug or logging purposes
    if (subdomain_detected) {
        printf("Subdomain detected.\n");
    }
    else {
        printf("No subdomain detected.\n");
    }

    return query;
}

/**
 * Parses a DNS response to extract the IP address.
 *
 * @param response The DNS response buffer.
 * @param response_len The length of the DNS response buffer.
 *
 * @returns The extracted IP address as an unsigned integer.
 */
unsigned int parse_dns_response(unsigned char* response, int response_len)
{
    // Skip the DNS header and question section
    unsigned char* answer_section = response + 12;
    while (*answer_section != 0) answer_section++;
    answer_section += 5; // Skip the null byte and QTYPE, QCLASS

    // Parse the answer section
    unsigned short answer_type;
    unsigned short answer_data_len;

    while (answer_section - response < response_len)
    {
        answer_section += 2; // Skip the NAME field
        answer_type = ntohs(*(unsigned short*)(answer_section));
        answer_section += 8; // Skip TYPE, CLASS, TTL
        answer_data_len = ntohs(*(unsigned short*)(answer_section));
        answer_section += 2;

        if (answer_type == 1 && answer_data_len == 4) // A record
        {
            unsigned int ip_address = *(unsigned int*)(answer_section);
            return ip_address;
        }

        answer_section += answer_data_len;
    }

    return 0; // No IP address found
}

/**
 * Displays a hex dump of the given buffer.
 *
 * @param buffer Pointer to the buffer to be dumped.
 * @param size Size of the buffer in bytes.
 *
 * @returns None
 */
void hexdump(const void* buffer, size_t size) {
    const unsigned char* data = (const unsigned char*)buffer;
    size_t i, j;

    for (i = 0; i < size; i += 16) {
        // Print the offset
        printf("%08zx  ", i);

        // Print the hex bytes
        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                printf("%02x ", data[i + j]);
            }
            else {
                printf("   "); // Fill in the blank for alignment
            }
        }

        // Print the ASCII representation
        printf(" |");
        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                unsigned char c = data[i + j];
                printf("%c", isprint(c) ? c : '.');
            }
            else {
                printf(" ");
            }
        }
        printf("|\n");
    }

    printf("\n");
}

/**
 * Retrieves the number of functions from ntdll.dll that are required for the application.
 *
 * @return The number of functions retrieved from ntdll.dll. \
 * Returns -1 if loading ntdll.dll fails or if any of the required functions are not found.
 */
int get_nt_functions(void)
{
    HMODULE hNtdll = LoadLibraryA("ntdll.dll");

    if (!hNtdll)
    {
        LOG_ERROR("Failed to load ntdll.dll");
        return -1;
    }

    // Load function addresses
    NtClose = (NtClose_t)GetProcAddress(hNtdll, "NtClose");
    NtCreateFile = (NtCreateFile_t)GetProcAddress(hNtdll, "NtCreateFile");
    NtCreateEvent = (NtCreateEvent_t)GetProcAddress(hNtdll, "NtCreateEvent");
    NtDeviceIoControlFile = (NtDeviceIoControlFile_t)GetProcAddress(hNtdll, "NtDeviceIoControlFile");
    NtWaitForSingleObject = (NtWaitForSingleObject_t)GetProcAddress(hNtdll, "NtWaitForSingleObject");

    // Check if any function failed to load
    if (!NtClose || !NtCreateEvent || !NtDeviceIoControlFile || !NtWaitForSingleObject || !NtCreateFile)
    {
        LOG_ERROR("Failed to get one or more functions from ntdll.dll");
        FreeLibrary(hNtdll);
        return -1;
    }

    return 1;
}

/**
 * Retrieves the IP address corresponding to a given domain name.
 *
 * This function lookups the domain name to an IP address using DNS resolution.
 *
 * @param host The domain name to lookup.
 * @param ip_string The buffer to store the resulting IP address string.
 *
 * @return The status of the IP address retrieval operation.
 */
NTSTATUS get_ip_from_domain(
    const char* host,
    char* ip_string
) {
    NTSTATUS Status = NULL;
    DOMAIN_INFO outBuffer = { 0 };
    HANDLE hSocket_dns_lookup = NULL;

    Status = nosa_dns_lookup(&hSocket_dns_lookup, host, &outBuffer);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("nosa_dns_lookup() failed!: [ 0x%x ]", Status);
        return Status;
    }

    LOG_INFO("Host -> [ %s -> 0x%08x -> %s ]",
        host, outBuffer.hex_ip_address, outBuffer.ip_address_str);

    // Copy the lookupd IP address into the provided buffer
    strncpy_s(ip_string, 16, outBuffer.ip_address_str, _TRUNCATE);

    NtClose(hSocket_dns_lookup);

    Sleep(10); // wait a little to prevent bugs

    return Status;
}

/**
 * Initializes a socket context structure with the specified address family and stores it in the provided output buffer.
 *
 * @param addr_family - The address family (e.g., AF_INET for IPv4) to be used for the socket context.
 * @param socket_type The type of the socket to be created.
 * @param socket_protocol The protocol of the socket to be created.
 * @param out_buf - A pointer to the buffer where the socket context will be stored.
 * @returns NTSTATUS - The status code of the operation. Currently, it always returns STATUS_SUCCESS.
 */
NTSTATUS create_context(
    DWORD addr_family,
    DWORD socket_type,
    DWORD socket_protocol,
    LPVOID out_buf
) {
    NTSTATUS status = NULL;
    ULONG len;
    BYTE buffer[SOCK_CONTEXT_BUF_SIZE];
    PSOCKET_CONTEXT sockctx;
    SOCKET sock = INVALID_SOCKET;

    sockctx = (PSOCKET_CONTEXT)&buffer[0];
    WSAPROTOCOL_INFOW wsapi;
    ULONG sockaddr_paddsize, sockaddr_2paddsize;
    ULONG ctxsize;

    // Initialize wsapi structure with relevant data
    memset(&wsapi, 0, sizeof(wsapi));
    wsapi.iAddressFamily = addr_family; // Example initialization, actual values may differ
    wsapi.iSocketType = socket_type;    // Example socket type
    wsapi.iProtocol = socket_protocol;      // Example protocol
    wsapi.iMaxSockAddr = sizeof(SOCKADDR_IN); // Example address size
    wsapi.dwCatalogEntryId = 1;         // Example catalog entry ID
    wsapi.dwServiceFlags1 = 0;          // Example service flags
    wsapi.dwProviderFlags = 0;          // Example provider flags
    wsapi.ProviderId = GUID_NULL;       // Example GUID, use actual GUID if needed

    memset(&sockctx->SharedData, 0, sizeof(SOCK_SHARED_INFO));
    sockctx->SharedData.AddressFamily = wsapi.iAddressFamily;
    sockctx->SharedData.SocketType = wsapi.iSocketType;
    sockctx->SharedData.Protocol = wsapi.iProtocol;
    sockctx->SharedData.SizeOfLocalAddress = wsapi.iMaxSockAddr;
    sockctx->SharedData.SizeOfRemoteAddress = wsapi.iMaxSockAddr;
    sockctx->SharedData.SizeOfRecvBuffer = (1 << 16);
    sockctx->SharedData.SizeOfSendBuffer = (1 << 16);
    sockctx->SharedData.CreateFlags = 1;
    sockctx->SharedData.CatalogEntryId = wsapi.dwCatalogEntryId;
    sockctx->SharedData.ServiceFlags1 = wsapi.dwServiceFlags1;
    sockctx->SharedData.ProviderFlags = wsapi.dwProviderFlags;
    sockctx->Guid = wsapi.ProviderId;
    sockctx->SizeOfHelperData = sizeof(PVOID);

    sockaddr_paddsize = (wsapi.iMaxSockAddr & 0xF0) + (((wsapi.iMaxSockAddr & 0xF) > 0) << 4);
    if (sockaddr_paddsize < sizeof(SOCKADDR)) {
        sockaddr_paddsize = sizeof(SOCKADDR);
    }

    sockaddr_2paddsize = sockaddr_paddsize * 2;
    ctxsize = sizeof(SOCK_SHARED_INFO) + 8 + sizeof(PVOID) + sockaddr_2paddsize;

    sockctx->SharedData.Flags.HasGUID = 1;
    memset(&sockctx->LocalAddress, 0, sockaddr_2paddsize);
    *(int*)(((char*)&sockctx->LocalAddress) + sockaddr_2paddsize) = addr_family;
    ctxsize += sizeof(GUID);

    // Copy the contents of the sockctx buffer to out_buf
    memcpy(out_buf, sockctx, ctxsize);

    return status;
}

/**
 * Creates an AFD socket with the specified socket type.
 *
 * @param socket_handle Pointer to a handle that will receive the socket handle.
 * @param SocketType The type of the socket to be created.
 * @param socketProtocol The protocol of the socket to be created.
 * @returns The status of the AFD socket creation operation.
 */
NTSTATUS afd_create(
    PHANDLE socket_handle,
    DWORD SocketType,
    DWORD socketProtocol
) {
    HANDLE hEvent = NULL;
    HANDLE hSocket = socket_handle;
    DWORD dwStatus = 0;

    IO_STATUS_BLOCK IoStatusBlock = { 0 };
    OBJECT_ATTRIBUTES object_attributes = { 0 };
    UNICODE_STRING object_file_path = { 0 };

    // Initialize the AFD_CREATE_PACKET structure
    AFD_CREATE_PACKET packet =
    {
        .NextEntryOffset = 0x00000000,
        .Flags = 0x00,
        .EaValueLength = 0x001E,
        .EaName = "AfdOpenPacketXX\0",
        .EaNameLength = (sizeof(packet.EaName) - 1),
        .EndpointFlags = 0x00000000,
        .GroupID = 0x00000000,
        .AddressFamily = AF_INET,
        .SocketType = SocketType,
        .Protocol = socketProtocol,
        .SizeOfTransportName = 0x0,
        .TransportName = "\x60\xEF\x3D\x47\xFE"
        //.TransportName = "\x41\x41\x41\x41" // whatever
    };

    // set afd endpoint path
    memset((void*)&object_file_path, 0, sizeof(object_file_path));
    object_file_path.Buffer = L"\\Device\\Afd\\Endpoint";
    object_file_path.Length = wcslen(object_file_path.Buffer) * sizeof(wchar_t);
    object_file_path.MaximumLength = object_file_path.Length;

    // initialise object attributes
    memset((void*)&object_attributes, 0, sizeof(object_attributes));
    object_attributes.Length = sizeof(object_attributes);
    object_attributes.ObjectName = &object_file_path;
    object_attributes.Attributes = 0x40;

    // create socket handle
    IoStatusBlock.Status = 0;
    IoStatusBlock.Information = NULL;

    // FILE_NO_EA_KNOWLEDGE = 0x00000200
    dwStatus = NtCreateFile(&hSocket,
        FILE_GENERIC_READ | FILE_GENERIC_WRITE | FILE_GENERIC_EXECUTE,
        &object_attributes, &IoStatusBlock, NULL, 0, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        FILE_OPEN_IF, 0x00000200, &packet, sizeof(packet));

    *(HANDLE*)socket_handle = hSocket;

    return dwStatus;
}

/**
 * Binds a socket handle using the AFD (Ancillary Function Driver) interface.
 *
 * @param socket_handle Pointer to the socket handle to bind.
 *
 * @return NTSTATUS The status of the AFD bind operation.
 */
NTSTATUS afd_bind(
    HANDLE* socket_handle
) {
    // bind a high port to futher TCP conversation
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;

    Status = NtCreateEvent(&Event, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("Failed to create event!");
        return Status;
    }

    BYTE* dummy[0x777] = { 0 };
    memset(dummy, 'A', sizeof(dummy));

    union
    {
        AFD_BIND_DATA binddata;
        SOCKADDR_IN sockaddr;
    } u;

    memset(&u.binddata, 0, sizeof(u.binddata));
    u.binddata.ShareType = 0x2;
    u.binddata.addr.sin_family = AF_INET;
    u.binddata.addr.sin_addr.s_addr = INADDR_ANY;
    u.binddata.addr.sin_port = 0;

    Status = NtDeviceIoControlFile(
        socket_handle,
        Event,
        NULL,
        NULL,
        &IoStatus,
        IOCTL_AFD_BIND,
        (BYTE*)&u,
        sizeof(u),
        &dummy,
        sizeof(dummy)
    );

    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatus.Status;
    }

    NtClose(Event);

    return Status;
}

/**
 * Sets the context for a given socket using the AFD (Ancillary Function Driver) subsystem.
 *
 * @param socket_handle - The handle to the socket for which the context is to be set.
 * @param input_buf - A pointer to the buffer containing the context data to be set.
 *
 * @returns NTSTATUS - The status code of the operation. If successful, the status will indicate success;
 *                     otherwise, it will provide an error code.
 */
NTSTATUS afd_set_context(
    HANDLE socket_handle,
    LPVOID input_buf
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;

    Status = NtCreateEvent(&Event, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("Failed to create event!");
        return Status;
    }

    Status = NtDeviceIoControlFile(
        socket_handle,
        Event,
        NULL,
        NULL,
        &IoStatus,
        IOCTL_AFD_SET_CONTEXT,
        input_buf,
        SOCK_CONTEXT_BUF_SIZE,
        0,
        NULL
    );

    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatus.Status;
    }

    NtClose(Event);

    return Status;
}

/**
 * Retrieves the context for a given socket using the AFD (Ancillary Function Driver) subsystem.
 *
 * @param socket_handle - The handle to the socket for which the context is to be retrieved.
 * @param out_buf - A pointer to the buffer where the retrieved context data will be stored.
 *
 * @returns NTSTATUS - The status code of the operation. If successful, the status will indicate success;
 *                     otherwise, it will provide an error code.
 */
NTSTATUS afd_get_context(
    HANDLE socket_handle,
    LPVOID out_buf
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;

    Status = NtCreateEvent(&Event, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("Failed to create event!");
        return Status;
    }

    Status = NtDeviceIoControlFile(
        socket_handle,
        Event,
        NULL,
        NULL,
        &IoStatus,
        IOCTL_AFD_GET_CONTEXT,
        NULL,
        0,
        out_buf,
        SOCK_CONTEXT_BUF_SIZE
    );

    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatus.Status;
    }

    NtClose(Event);

    return Status;
}

/**
 * Establishes a connection to a specified address and port using AFD (Ancillary Function Driver).
 *
 * @param socket_handle Pointer to the socket handle.
 * @param Address The address to connect to.
 * @param Port The port number to connect to.
 *
 * @returns The status of the connection attempt.
 */
NTSTATUS afd_connect(
    HANDLE* socket_handle,
    char* Address,
    int Port
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    AFD_CONNECT_INFO conn_struct = { 0 };
    HANDLE Event = NULL;

    Status = NtCreateEvent(&Event, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("Failed to create event!");
        return Status;
    }

    uint32_t htonl_ip = convert_ip_to_htonl(Address);

    memset(&conn_struct, '0', sizeof(conn_struct));

    conn_struct.UseSAN = 0;
    conn_struct.Root = 0;
    conn_struct.Unknown = 0;
    conn_struct.Bind.sin_family = AF_INET;
    conn_struct.Bind.sin_addr.s_addr = htonl(htonl_ip);
    conn_struct.Bind.sin_port = htons(Port);

    Status = NtDeviceIoControlFile(
        socket_handle,
        Event,
        NULL,
        NULL,
        &IoStatus,
        IOCTL_AFD_DOCONNECT,
        &conn_struct,
        sizeof(conn_struct),
        NULL,
        0
    );

    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatus.Status;
    }

    NtClose(Event);

    return Status;
}

/**
 * Sends a buffer over a specified socket handle using the AFD (Ancillary Function Driver) interface.
 *
 * @param socket_handle The handle to the socket for sending the data.
 * @param buf The buffer containing the data to be sent.
 * @param query_len The length of the data buffer.
 * @param is_dns_query A boolean flag indicating if the data is a DNS query.
 *
 * @returns The NTSTATUS of the send operation.
 */
NTSTATUS afd_send(
    HANDLE socket_handle,
    LPVOID buf,
    int query_len,
    BOOL is_dns_query
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;

    Status = NtCreateEvent(&Event, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("Failed to create event!");
        return Status;
    }

    AFD_SEND_INFO fb = { 0 };
    int finalSz = 0;

    // DNS query length must to be the final payload + 2
    if ((is_dns_query) > 0)
    {
        finalSz = query_len + 2;
    }
    else
    {
        finalSz = query_len;
    }

    buf = (unsigned char*)buf;

    AFD_WSABUF wsa_buffers[] =
    {
        {
            .len = finalSz,
            .buf = buf
        }
    };

    fb.BufferArray = wsa_buffers;
    fb.BufferCount = 1;
    fb.AfdFlags = 0;
    fb.TdiFlags = query_len;

    Status = NtDeviceIoControlFile(
        socket_handle,
        Event,
        NULL,
        NULL,
        &IoStatus,
        IOCTL_AFD_SEND,
        &fb,
        sizeof(fb),
        NULL,
        0
    );

    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatus.Status;
    }

    NtClose(Event);

    return Status;
}

/**
 * Receives data from a socket using the Windows AFD API.
 *
 * @param socket_handle A pointer to the handle of the socket.
 * @param wsa_buffer A pointer to the buffer to store the received data.
 *
 * @returns The status of the operation.
 */
NTSTATUS afd_recv(
    HANDLE* socket_handle,
    LPVOID wsa_buffer
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;

    Status = NtCreateEvent(&Event, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("Failed to create event!");
        return Status;
    }

    AFD_RECV_INFO recvInfo;
    AFD_WSABUF FAKE_BUF = { 0 };

    BYTE wsa_recv_buffer[MAX_RECV_BYTES] = { 0 };

    FAKE_BUF.buf = (LPVOID)wsa_recv_buffer;
    FAKE_BUF.len = (uint32_t)sizeof(wsa_recv_buffer);

    recvInfo.BufferArray = &FAKE_BUF;
    recvInfo.BufferCount = 1;
    recvInfo.TdiFlags = TDI_RECEIVE_NORMAL;
    recvInfo.AfdFlags = 0;

    Status = NtDeviceIoControlFile(
        socket_handle,
        Event,
        NULL,
        NULL,
        &IoStatus,
        IOCTL_AFD_RECV,
        &recvInfo,
        sizeof(recvInfo),
        NULL,
        0
    );

    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatus.Status;
    }

    memcpy(wsa_buffer, &wsa_recv_buffer, MAX_RECV_BYTES);

    NtClose(Event);

    return Status;
}

/**
 * Closes an AFD handle.
 *
 * @param Handle The handle to be closed.
 *
 * @return NTSTATUS indicating the result of the close operation.
 */
NTSTATUS afd_close(
    HANDLE Handle
) {
    return NtClose(Handle);
}

/**
 * lookups a domain name to an IP address using the specified socket handle.
 *
 * @param hSocket The handle to the socket for DNS resolution.
 * @param domain_name The domain name to lookup.
 * @param outBuffer Pointer to a DOMAIN_INFO structure to store the lookupd IP address.
 *
 * @return NTSTATUS The status of the domain resolution operation.
 */
NTSTATUS nosa_dns_lookup(
    HANDLE hSocket,
    const char* domain_name,
    DOMAIN_INFO* outBuffer
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;
    unsigned char out_buffer_ptr = { 0 };
    int query_len = 0;
    unsigned char buf[1024] = { 0 };
    unsigned char wsa_buffer[MAX_RECV_BYTES] = { 0 };
    memset(wsa_buffer, 0, sizeof(wsa_buffer));

    Status = afd_create(&hSocket, SOCK_STREAM, IPPROTO_TCP);

    if (hSocket)
    {
        LOG_INFO("Socket created successfully! HANDLE: [ 0x%x ]", hSocket);
    }
    else
    {
        LOG_ERROR("Failed to create socket.");
    }

    Status = afd_bind(hSocket);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("nosa_dns_lookup -> afd_bind() failed!  [ 0x%x ]", Status);
        return Status;
    }
    else
    {
        LOG_INFO("nosa_dns_lookup -> afd_bind() OK");
    }

    Status = afd_connect(hSocket, DNS_SERVER, DNS_PORT);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("nosa_dns_lookup -> afd_connect() failed! [ 0x%x ]", Status);
        return Status;
    }
    else
    {
        LOG_INFO("nosa_dns_lookup -> afd_connect() OK");
    }

    LOG_INFO("lookuping IP address by using [ %s ] DNS SERVER.", DNS_SERVER);

    unsigned char* query = build_dns_query(domain_name, &query_len);

    // Send the query length and the query itself
    unsigned short net_query_len = htons(query_len);
    memcpy(buf, &net_query_len, 2);
    memcpy(buf + 2, query, query_len);

    //    ifconfig.me -> example query pkt
    //
    //    0x12, 0x34, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0,
    //    0x0, 0x0, 0x0, 0x8, 0x69, 0x66, 0x63, 0x6f, 0x6e,
    //    0x66, 0x69, 0x67, 0x2, 0x6d, 0x65, 0x0, 0x0, 0x1,
    //    0x0, 0x1

    // Print the DNS query bytes for verification
    if (LOG_LEVEL_DEBUG)
    {
        LOG_INFO("DNS Query:");
        hexdump(query, query_len);
    }

    // We assume that socket_handle are created with create() -> bind() -> connect()
    Status = afd_send(hSocket, buf, query_len, 1);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("afd_send() failed! [ 0x%x ]", Status);
        return Status;
    }

    Status = afd_recv(hSocket, &wsa_buffer);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("afd_recv() failed! [ 0x%x ]", Status);
        return Status;
    }

    // Print the DNS response bytes for verification
    if (LOG_LEVEL_DEBUG)
    {
        LOG_INFO("afd_recv() Response:");
        hexdump(wsa_buffer, 0x100);
    }

    if (wsa_buffer)
    {
        unsigned int ip_address = parse_dns_response(wsa_buffer + 2, sizeof(wsa_buffer)); // Skip the length prefix

        if (ip_address != 0)
        {
            outBuffer->hex_ip_address = htonl(ip_address);                          // 0x22a06f91 
            strncpy_s(outBuffer->ip_address_str, sizeof(outBuffer->ip_address_str), // 34.160.111.145
                convert_htonl_to_ip_address(outBuffer->hex_ip_address), _TRUNCATE);
        }
        else
        {
            LOG_ERROR("No IP address found in the DNS response.");
        }
    }
    else
    {
        LOG_ERROR("[-] No response received.");
    }

    return Status;
}

/**
 * Establishes a connection using nosa with the specified parameters.
 *
 * @param hSocket Pointer to the socket handle.
 * @param host The host to connect to.
 * @param port The port number to connect to.
 * @param socketType The type of socket to use (e.g., "TCP").
 *
 * @returns NTSTATUS indicating the status of the connection attempt.
 */
NTSTATUS nosa_connect(
    HANDLE* hSocket,
    char* host,
    int port,
    const char* socketType
) {
    NTSTATUS Status = NULL;
    DWORD sType = NULL;
    DWORD socketProtocol = NULL;
    char ip_string[16] = { 0 };  // Allocate enough space for an IPv4 address in dotted notation

    if (get_nt_functions())  // load ntdll libraries
    {
        if (is_domain_name(host))   // lookup the IP address of a given domain name 
        {
            Status = get_ip_from_domain(host, ip_string);

            if (!NT_SUCCESS(Status))
            {
                LOG_ERROR("get_ip_from_domain() failed: [ 0x%x ]", Status);
                return Status;
            }
        }
        else
        {
            // Directly copy the IP address if `host` is an IP address string
            strncpy_s(ip_string, 16, host, _TRUNCATE);
            LOG_INFO("ip_string: %s", ip_string);
        }

        if (socketType == "TCP")
        {
            sType = SOCK_STREAM;
        }

        if (socketType == "UDP") // #TODO -> Not working -> afd_connect() send back an invalid NTSTATUS 0xC0000002
        {                        // idk how it can be implemented since afd_connect() Datagram doesn't help 
            sType = SOCK_DGRAM;
        }

        // Switch case to handle different socket types
        switch (sType) {
        case SOCK_STREAM:
            socketProtocol = IPPROTO_TCP; // TCP
            break;

        case SOCK_DGRAM:
            socketProtocol = IPPROTO_UDP; // UDP -> TODO
            break;

        default:
            LOG_ERROR("Unsupported socket type");
            return -1; // Return an error code
        }

        // Pass the pointer to the HANDLE, allowing the function to modify the original hSocket variable
        Status = afd_create(hSocket, sType, socketProtocol);

        if (*hSocket)
        {
            LOG_INFO("Socket created successfully. HANDLE: [ 0x%x ]", *hSocket);
        }
        else
        {
            LOG_ERROR("Failed to create socket.");
            return Status;
        }

        Status = afd_bind(*hSocket);

        if (!NT_SUCCESS(Status))
        {
            LOG_ERROR("nosa_connect() -> afd_bind() failed! [ 0x%x ]", Status);
            return Status;
        }
        else
        {
            LOG_INFO("nosa_connect() -> afd_bind() OK");
        }

        // generate a context for our created socket
        BYTE* sockctx_input_buffer[SOCK_CONTEXT_BUF_SIZE] = { 0 };
        memset(sockctx_input_buffer, 0, sizeof(sockctx_input_buffer)); // clear our created vm alloc

        int sockctxSz = create_context(AF_INET, sType, socketProtocol, &sockctx_input_buffer);

        // bp afdsetcontext ".if (@rdi == 0xcafe0000) { .echo 'Breakpoint hit!'; } .else { gc; }"
        Status = afd_set_context(*hSocket, sockctx_input_buffer);     // implement current socket context

        if (!NT_SUCCESS(Status))
        {
            LOG_ERROR("nosa_connect() -> afd_set_context() failed! [ 0x%x ]", Status);
            return Status;
        }
        else
        {
            LOG_INFO("nosa_connect() -> afd_set_context() OK");
        }

        // Receive and print TCP packet response
        BYTE* sockctx_out_buffer[SOCK_CONTEXT_BUF_SIZE] = { 0 };
        memset(sockctx_out_buffer, 0, sizeof(sockctx_out_buffer)); // clear

        Status = afd_get_context(*hSocket, sockctx_out_buffer);

        if (!NT_SUCCESS(Status))
        {
            LOG_ERROR("nosa_connect() -> nosa_getcontext() failed! [ 0x%x ]", Status);
            return Status;
        }
        else
        {
            LOG_INFO("nosa_connect() -> nosa_getcontext() OK");
            hexdump(sockctx_out_buffer, 0x100);
        }

        Status = afd_connect(*hSocket, ip_string, port);

        if (!NT_SUCCESS(Status))
        {
            LOG_ERROR("nosa_connect() -> afd_connect() failed! [ 0x%x ]", Status);
            return Status;
        }
        else
        {
            LOG_INFO("nosa_connect() -> afd_connect() OK");
        }

        Sleep(10); // wait a little bit

        return Status;
    }
    else
    {
        LOG_ERROR("Failed to start NTDLL functions");
    }
}

/**
 * Sends a packet of data using the Windows Socket API-less method.
 *
 * @param hSocket A pointer to the socket handle.
 * @param packet_data A pointer to the data packet to be sent.
 * @param packet_data_sz The size of the data packet.
 *
 * @returns The status of the send operation.
 */
NTSTATUS nosa_send(
    HANDLE* hSocket,
    LPVOID packet_data,
    int packet_data_sz
) {
    NTSTATUS Status = NULL;

    Status = afd_send(*hSocket, packet_data, packet_data_sz, 0); // Note: query_len + 2 includes the length prefix

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("afd_send() failed!: [ 0x%x ]", Status);
    }

    Sleep(10); // wait a little bit

    return Status;
}

/**
 * Receives data from a socket using the Windows Socketless API.
 *
 * @param hSocket The handle to the socket from which to receive data.
 * @param packet_data_received Pointer to the buffer where the received data will be stored.
 *
 * @return NTSTATUS The status of the operation.
 */
NTSTATUS nosa_recv(
    HANDLE hSocket,
    LPVOID packet_data_received
) {
    NTSTATUS Status = NULL;
    IO_STATUS_BLOCK IoStatus = { 0 };
    HANDLE Event = NULL;
    unsigned char out_buffer_ptr = { 0 };
    int query_len = 0;
    unsigned char buf[MAX_RECV_BYTES] = { 0 };

    Status = afd_recv(hSocket, packet_data_received);

    if (!NT_SUCCESS(Status))
    {
        LOG_ERROR("afd_recv() failed!: [ 0x%x ]", Status);
        return Status;
    }

    return Status;
}

/* References
- https://github.com/R41N3RZUF477/NtSock
- https://www.x86matthew.com/view_post?id=ntsockets
*/
