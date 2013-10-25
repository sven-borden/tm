/*  Server side */


#include <winsock2.h> // pour les fonctions socket
#include <stdlib.h>
#include <stdio.h>
#include <cstdio> // Pour les Sprintf

//#pragma comment(lib,"ws2_32.lib")

WSADATA initialisation_win32;
int erreur;
int tempo;
int numberChar; // Indique le nombre de caractères qui a été reçu ou envoyé
char buffer[65535]; // Tampon contenant les données reçues ou envoyées
SOCKET socketId; // Identifiant de la socket
SOCKADDR_IN sourceInfo; // Déclaration de la structure des informations lié à l'écoute

int main (int argc, char* argv[])
{
	printf("\nBonjour, vous etes du cote serveur\n");


	erreur = WSAStartup(MAKEWORD(2,2),&initialisation_win32);
	if (erreur!=0)
		printf("\nDesole, je ne peux pas initialiser Winsock du a l'erreur : %d %d", erreur, WSAGetLastError());
	else
		printf("\nWSAStartup  : [OK]");

	// Ouverture d'une Socket

	socketId = socket(AF_INET,SOCK_DGRAM,0);
	if (socketId == INVALID_SOCKET)
		printf("\nDesole, ne peux pas creer la socket du a l'erreur : %d",WSAGetLastError());
	else
		printf("\nsocket      : [OK]");

	// Lie la socket à une ip et un port d'écoute

	sourceInfo.sin_family = AF_INET;
	sourceInfo.sin_addr.s_addr = INADDR_ANY; // Ecoute sur toutes les IP locales
	sourceInfo.sin_port = htons(888); // Ecoute sur le port 33333

	erreur = bind(socketId,(struct sockaddr*)&sourceInfo,sizeof(sourceInfo));
	if (erreur!=0)
		printf("\nDesole, je ne peux pas ecouter ce port : %d %d",erreur,WSAGetLastError());
	else
		printf("\nbind        : [OK]");



	// Reception des données en boucle
    while(true)
    {
        tempo = sizeof(sourceInfo); // Passe par une variable afin d'utiliser un pointeur
        numberChar = recvfrom(socketId,buffer,1515,0,(struct sockaddr*)&sourceInfo,&tempo);
        //recvfrom(int socket, char *data, int maxnumbytes, int flags, sosckaddr *source, int source_len)
        buffer[numberChar] = 0;
        // la ligne du dessus permet de fermer le tableau apres le contenu des data, car la fonction recvfrom ne le fait pas
        printf("\nVoici les donnees : %s",buffer);
    }

	// Fermeture de la socket correspondante à la commande socket()

	erreur=closesocket(socketId);
	if (erreur != 0)
		printf("\nDesole, je ne peux pas liberer la socket du a l'erreur : %d %d",erreur,WSAGetLastError());
	else
		printf("\nclosesocket : [OK]");

	// Quitte proprement le winsock ouvert avec la commande WSAStartup

	erreur=WSACleanup(); // A appeler autant de fois qu'il a été ouvert.
	if (erreur !=0 )
		printf("\nDesole, je ne peux pas liberer winsock du a l'erreur : %d %d",erreur,WSAGetLastError());
	else
		printf("\nWSACleanup  : [OK]");

}

/*#endif // defined WINDOWS 64 bits

#if defined(__gnu_linux__)

#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <cstdio>
using namespace std;

void error( char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    int sockfd;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv,client;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(53000);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[256];
    socklen_t l = sizeof(client);
    //socklen_t m = client;
    printf("\ngoing to recv\n");
    int rc= recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&l);
    if(rc<0)
    {
        printf("ERROR READING FROM SOCKET");
    }
    printf("\n the message received is : %s\n", buffer);
    int rp= sendto(sockfd,"hi",2,0,(struct sockaddr *)&client,l);

    if(rp<0)
    {
        printf("ERROR writing to SOCKET");
    }
}


#endif // defined gnu_linux
*/
