#pragma comment(lib, "ws2_32.lib")

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define ADDR   ("127.0.0.1")
#define PORT   (5000)
#define SIZE   (20)
#define CHARS  (128)

typedef struct Node {
   int val;
   char c, *bits;
} Node;

void heapify(Node **table, int pos) {
char **encode(const char *name, int *count);
char *compress(const char *name);
void process(SOCKET sock, char *bits);

int main(int argc, char *argv[]) {
   WSADATA wsaData;
   struct sockaddr_in consumer;
   SOCKET sock;
   
   if (WSAStartup(MAKEWORD(2, 0), &wsaData)) {
      printf("failed to load winsock2\n");
      exit(EXIT_FAILURE);
   }
   if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
      printf("failed to open socket\n");
      exit(EXIT_FAILURE);
   }
   memset(&consumer, 0, sizeof(consumer));
   consumer.sin_family = AF_INET;
   consumer.sin_port = htons(PORT);
   consumer.sin_addr.s_addr = inet_addr(ADDR);
   if (connect(sock, (struct sockaddr*)&consumer, sizeof(consumer)) < 0) {
      printf("failed to connect\n");
      exit(EXIT_FAILURE);
   }
   process(sock, compress("alice.txt"));
   closesocket(sock);
   WSACleanup();
   exit(EXIT_SUCCESS);
}

void heapify(Node **table, int pos) {
   int small, left, right;

   small = pos;
   left = 2 * pos + 1;
   right = 2 * pos + 2;
   if (left 
} 

char **encode(const char *name, int *count) {
   FILE *in;
   Node **table;

   table = malloc(sizeof(Node*) * CHARS);
   for (int i = 0; i < CHARS; ++i) {
      table[i] = malloc(sizeof(Node));
      table[i]->val = count[i];
      table[i]->c = i;
      table[i]->bits = NULL;
   }
   for (int i = (CHARS - 1) / 2; i >= 0; --i) {
      heapify(table, i);
   }
   return table;
}

char *compress(const char *name) {
   FILE *in;
   int count[CHARS], len;
   char c, *bits;
 
   len = 0;
   memset(count, 0, sizeof(int) * CHARS); 
   if ((in = fopen(name, "r")) == NULL) {
      printf("failed to open file\n");
      exit(EXIT_FAILURE);
   } 
   while ((c = getc(in)) != EOF) {
      assert(0 < c && c < CHARS);
      ++count[c];
      ++len;
   }
   fclose(in);
   assert(len > 0);
   bits = malloc(len + 1);
   in = fopen(name, "r");
   for (int i = 0; i < len; ++i) {
      bits[i] = getc(in);
   }
   bits[len] = '\0';
   return bits;
}

void process(SOCKET sock, char *bits) {
   char buf[SIZE];
   int pos;
   bool flag;

   flag = true;
   while (flag) {
      pos = 0;
      while (pos < SIZE - 1 && (buf[pos++] = *bits++));
      if (buf[pos - 1]) {
         buf[pos] = '\0';
      }
      else {
         flag = false;
      }
      if (send(sock, buf, pos, 0) != pos) {
         printf("failed to send\n");
         exit(EXIT_FAILURE);
      }
   }
   buf[0] = EOF;
   if (send(sock, buf, 1, 0) != 1) {
         printf("failed to send EOF\n");
         exit(EXIT_FAILURE);
   }
}
 
