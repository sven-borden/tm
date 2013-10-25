/*  client side */

#include <winsock2.h> //fonction socket windows
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdio> //pour les Sprintf

#define benchmark //comment this line to disable the benchmark

WSADATA initialisation_win32;

int erreur;
int tempo;
int phrase = 0;
int numberChar;
char buffer[65535]; //tampon contenant les données reçues ou envoyee

SOCKET socketId;
SOCKADDR_IN destInfo;

#ifdef benchmark

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";


int stringLength = sizeof(alphanum) - 1;

char genRandom()  // Random string generator function.
{

    return alphanum[rand() % stringLength];
}

#endif

int main(int argc, char* argv[])
{
    printf("\n Bienvenue, vous etes du cote client \n");

    //Initialisation de Winsock

    erreur = WSAStartup(MAKEWORD(2,2), &initialisation_win32);
    if(erreur != 0)
        printf("\nWSAStartup : [FAIL] : Desole, ne peux pas initialiser Winsock2 : %d %d", erreur, WSAGetLastError());
    else
        printf("\nWSAStartup : [OK]");

    //Ouverture d'une Socket

    socketId = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketId == INVALID_SOCKET)
        printf("\nSocket : [FAIL] : Desole, ne peux pas creer la socket, erreur : %d", WSAGetLastError());
    else
        printf("\nSocket : [OK]");

    //Envois de donnees

    destInfo.sin_family = AF_INET; //IPV4
    destInfo.sin_addr.s_addr = inet_addr("172.16.1.52"); //adresse du serveur
    destInfo.sin_port = htons(888);

#ifdef benchmark


    for(int i = 0; i<1000;i++)
    {
          char Image[1024];

        for(int j = 0; j<1024; j++)
        {
            Image[j] = genRandom();
        }
        strcpy(buffer, Image);
        numberChar = sendto(socketId, buffer, strlen(buffer), 0, (struct sockaddr*)&destInfo, sizeof(destInfo));
        //sendto(int socket, char * buffer, int len, int flags, const struct sock_addr *dest_addr, int sock_len dest_len).
    }

#endif // benchmark

    if(numberChar == SOCKET_ERROR)
        printf("\nSend : [FAIL] : Desole, ne peux pas envoyer les donnees du a l'erreur : %d", WSAGetLastError());
    else
        printf("\nSend : [OK]");

    //fermeture de la socket correspondant a la commande socket()

    erreur = closesocket(socketId);
    if(erreur != 0)
        printf("\nClosesocket : [FAIL] : Desole, ne peux pas liberer la socjet du a l'erreur = %d %d", erreur, WSAGetLastError());
    else
        printf("\nClosesocket : [OK]");

    //quitte proprement le winsock ouvert avec la commande WSAStartup

    erreur = WSACleanup();

    if(erreur != 0)
        printf("\nWSACleanup : [FAIL] : Desole, ne peux pas liberer winsock du a l'erruer : %d %d", erreur, WSAGetLastError());
    else
        printf("\nWSACleanup : [OK]");
}
