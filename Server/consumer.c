#pragma comment(lib, "ws2_32.lib")

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define ADDR ("127.0.0.1")
#define PORT (5000)
#define SIZE (20)
#define MAX (4)

void printb(char c);
void process(SOCKET sock);

int main(int argc, char *argv[]) {
   WSADATA wsaData;
   struct sockaddr_in consumer, producer;
   SOCKET sock, recvSock;
   size_t producerLen;

   producerLen = sizeof(producer);
   if (WSAStartup(MAKEWORD(2, 0), &wsaData)) {
      printf("failed to load winsock2\n");
      exit(EXIT_FAILURE);
   }
   if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
      printf("failed to create socket\n");
      exit(EXIT_FAILURE);
   }
   memset(&consumer, 0, sizeof(consumer));
   consumer.sin_family = AF_INET;
   consumer.sin_port = htons(PORT);
   consumer.sin_addr.s_addr = htonl(INADDR_ANY);
   bind(sock, (struct sockaddr*)&consumer, sizeof(consumer));
   listen(sock, MAX);
   recvSock = accept(sock, (struct sockaddr*)&producer, &producerLen);
   process(recvSock);
   closesocket(sock);
   WSACleanup();
   exit(EXIT_SUCCESS);
}

void printb(char c) {
   char mask;

   mask = '\1';
   for (int i = 0; i < 8; ++i) {
      printf("%d", (c & mask) ? 1 : 0);
      mask <<= 1u;
   }
}

void process(SOCKET sock) {
   char buf[SIZE], *ptr;
   int bytes, total, col;
   bool flag;

   total = 0;
   col = 0;
   flag = true;
   while (flag && (bytes = recv(sock, buf, SIZE, 0)) > 0) {
      total += bytes;
      if (buf[0] == EOF) {
         flag = false;
      }
      else {
         ptr = buf;
         while (*ptr) {
            printb(*ptr++);
            if (++col == 10) {
               printf("\n");
               col = 0;
            }
         }
      }
   }
   closesocket(sock);
   printf("\ntotal bytes: %d\n", total);
} 
