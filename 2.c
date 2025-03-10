//2. Using TCP/IP sockets, write a client-server program to make the client send the file name and to make the server send back the contents of the requested file if present.






//client
#include<stdio.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
int soc,n;
int port=5556;
char buffer[1024],fname[50];
struct sockaddr_in addr;



soc=socket(PF_INET,SOCK_STREAM,0);
printf("Client Socket created");
addr.sin_family=AF_INET;
addr.sin_port=port;
addr.sin_addr.s_addr=inet_addr("127.0.0.1");



while(connect(soc,(struct sockaddr*) &addr,sizeof(addr)));
printf("\n CLIENT IS CONNECTED TO SERVER\n");



printf("Enter the file name");
scanf("%s",fname);
send(soc,fname,sizeof(fname),0);



printf("Recieved response\n");
while((n=recv(soc,buffer,sizeof(buffer),0))>0)
printf("%s",buffer);
return 0;
}









//server
#include<stdio.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
int server_soc,fd,n,client_soc;
int port=5556;



char buffer[1024],fname[50];
struct sockaddr_in addr;



server_soc=socket(PF_INET,SOCK_STREAM,0);
printf("Socket created....\n");



addr.sin_family=AF_INET;
addr.sin_port=port;
addr.sin_addr.s_addr=inet_addr("127.0.0.1");



bind(server_soc,(struct sockaddr*)&addr,sizeof(addr));
printf("bind to th port number %d",port);
printf("\nSERVER IS ONLINE\n");



listen(server_soc,5);
printf("Listining....\n");



client_soc=accept(server_soc,NULL,NULL);
printf("server accepted......\n");



recv(client_soc,fname,50,0);
printf("client Requesting for file %s:",fname);
fd=open(fname,O_RDONLY);
if(fd<0)
send(client_soc,"\nFile not found...",25,0);
else
while((n=read(fd,buffer,sizeof(buffer))) > 0)
send(client_soc,buffer,n,0);
close(fd);
printf("\ndisconnected......");
return 0;


}
