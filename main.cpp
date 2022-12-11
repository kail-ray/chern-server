#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>  // подключили библиотеку queue
using namespace std;
void errHandler(const char * why, const int exitCode = 1)
{
cerr<<why << endl;
exit(exitCode);
}
int main (int argc, char **argv)
{//подготовка адресной структуры
struct sockaddr_in {
   short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];
};
struct in_addr {
 unsigned long s_addr;
};
sockaddr_in * addr = new (sockaddr_in);
addr->sin_family = AF_INET; // интернет протокол IPv4
addr->sin_port = htons(2220); // порт 44214
addr->sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
//создание сокета
int s = socket(AF_INET, SOCK_STREAM, 0); // TCP
if (s==-1) {
    errHandler("error open socket", 11);
    }
int rc = bind(s,(const sockaddr*) addr,sizeof(sockaddr_in));
    if (rc == -1){
    close(s);
    errHandler("error bind socket with local address", 12);}
//установка сокета в режим ожидния соединения
rc = listen(s, 6);
if (rc == -1){
    close(s);
    errHandler("connection waiting error", 13);} 
    //извлечение клиент из очереди и получение его сокета 
while(true){
  sockaddr_in * client_addr = new sockaddr_in;
  socklen_t len = sizeof (sockaddr_in);
  int work_sock = accept(s, (sockaddr*)(client_addr), &len);
  if (work_sock == -1){
      errHandler("connection waiting error", 14);}
  else cout<<"connect"<<endl;//вывод сообщения при подключении клиента 
char buf[500];//выделение памяти под полученное сообщение 
rc = recv(work_sock, buf, sizeof buf,0);//получение сообщение от клиента
buf[rc]='\0';
string srt;
srt=buf;
cout<<str<<endl;
close(work_sock);// закрытие сокета клиента 
}
}