/*
 * pp.c
 *
 *  Created on: Feb 18, 2017
 *      Author: vaidehi
 */

/**
 * @vaidehip_assignment1
 * @author  Vaidehi Santu Patil <vaidehip@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <malloc.h>


#include "../include/global.h"
#include "../include/logger.h"

/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */
#define PORT1 "9034"
#define CMD_SIZE 100
#define BUFFER_SIZE 256
#define MSG_SIZE 256
	struct node{
		int list_id;
		char hostname[1025];
		char ip_add[INET_ADDRSTRLEN];
		char port_no[20];
		//struct sockaddr_in clientaddress;
		struct node* next;
	};
	//This part is taken from http://www.geeksforgeeks.org/merge-sort-for-linked-list/
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source,
          struct node** frontRef, struct node** backRef);
void MergeSort(struct node** headRef)
{
  struct node* head = *headRef;
  struct node* a;
  struct node* b;

  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }

  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b);

  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);

  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}
struct node* SortedMerge(struct node* a, struct node* b)
{
  struct node* result = NULL;

  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);

  /* Pick either a or b, and recur */
  if (a->port_no <= b->port_no)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}
void FrontBackSplit(struct node* source,
          struct node** frontRef, struct node** backRef)
{
  struct node* fast;
  struct node* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
//This part is taken from http://www.geeksforgeeks.org/merge-sort-for-linked-list/
//int connect_to_host(char *server_ip, int server_port);
int main(int argc, char **argv)
{
	/*Init. Logger*/
	cse4589_init_log(argv[2]);

	/*Clear LOGFILE*/
	fclose(fopen(LOGFILE, "w"));

	/*Start Here*/
	//char *m="j";
	int n, port, t, fdaccept, sockfd;
	struct sockaddr_in udpserver, res;
	struct hostent *he;
	char ubit_name[8] = "vaidehip";
	char ipstr[100],  service[32];
	socklen_t addr_len;
	//memset(m,0,sizeof m);
	//strncpy(m,argv[1],(sizeof m)-1);
	//*m = argv[1]; /* convert strings to integers */
	port = atoi(argv[2]);
	////printf("M: %s", argv[1]);
	////printf("N: %d", n);
	if(!strcmp(argv[1],"s"))
	{

	struct sockaddr_in server_addr,hints, udpserver, res; /*defining struct*/
	struct sockaddr_storage client_addr;
	int fd=0, rv, ret, selret, sock_index, max_conn,  ud;      /*defining integer*/
	int server_socket, caddr_len;
	socklen_t addr_len;
	int STDIN,i;
	char ipstr[100];
	char *messages[5][10000];
	//char buf[20];	      /*defining character*/

	    fd_set master;    // master file descriptor list
        fd_set watch_list; //temporary file descriptor list for select
        FD_ZERO(&master);
        FD_ZERO(&watch_list);

        /* From creating server socket to listen() taken from Beej Guide to network programming
         *
         * */
		server_socket =socket(AF_INET, SOCK_STREAM, 0); /*creating socket*/
		if(server_socket < 0)
			return -1;
		bzero(&server_addr, sizeof(server_addr));
		//portno = n; /*Converting character to integer value*/
		 memset(&hints, 0, sizeof hints);
   		// hints.ai_family = AF_INET;
   		// hints.ai_socktype = SOCK_STREAM;
   		// hints.ai_flags = AI_PASSIVE;
		 server_addr.sin_family = AF_INET; /* IPv4*/
		server_addr.sin_addr.s_addr =htonl(INADDR_ANY) ;
		server_addr.sin_port = htons(port);	  /*server address*/
		//portno1 = PORT; /*server listening port*/
		//rv = getaddrinfo(NULL, PORT, &hints, &server_addr);
		if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))<0)
					return -1;

		if(listen(server_socket, 4)<0)
					return -1;

//From creating server socket to listen() taken from Beej Guide to network programming

	STDIN = 0;
	FD_SET(server_socket, &master);
	FD_SET(STDIN, &master);
	max_conn=server_socket;

	struct node* head;
	head = (struct node *) malloc( sizeof(struct node) );
	head = NULL;




	while(1)
		{
		watch_list = master;
	////printf("Before select\n");
		selret = select(max_conn+1, &watch_list, NULL, NULL, NULL) ;

		////printf("After select\n");
	if(selret<0)
			{
				////printf("4");
				return -1;
			}

	if(selret>0)
		{
	for(sock_index=0; sock_index<=max_conn; sock_index++)
			{
		if(FD_ISSET(sock_index, &watch_list))
				{
				if(sock_index == STDIN) //Check if this is one of the standard input
					{
					char *cmd = (char*) malloc(sizeof(char)*MSG_SIZE);
							    	memset(cmd, '\0', MSG_SIZE);
									if(fgets(cmd, MSG_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to msg
										exit(-1);
									else
									{


					              {
												int len=strlen(cmd);
												if(cmd[len-1]=='\n'){
													cmd[len-1] = '\0';
												}
					              }
												if(!strncmp(cmd,"AUTHOR", 6))
												{
													cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
													cse4589_print_and_log("I, %s, have read and understood the course academic integrity policy.\n", "vaidehip");
													cse4589_print_and_log("[%s:END]\n", cmd);

//fflush(stdin);
//printf("I, %s, have read and understood the course academic integrity policy.\n", "vaidehip");

												}

												if(!strncmp(cmd,"IP", 2))
												{

													memset(&udpserver,0, sizeof udpserver);
													udpserver.sin_family = AF_INET; /* IPv4*/
													udpserver.sin_addr.s_addr =inet_addr("8.8.8.8") ;
													udpserver.sin_port = htons(port);
													if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
													{
														////printf("Error in creating udp socket");

														cse4589_print_and_log("[%s:ERROR]\n", cmd);
														cse4589_print_and_log("[%s:END]\n", cmd);
													}
													connect(sockfd, (struct sockaddr *)&udpserver, sizeof(udpserver));
													addr_len = sizeof res;
												if(!(getsockname(sockfd,(struct sockaddr *)&res,&addr_len )))
													{
												        inet_ntop(res.sin_family, &res.sin_addr, ipstr, sizeof ipstr);//taken from beej guide
												       //printf("  The IP address is %s\n", ipstr);

													cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
													cse4589_print_and_log("IP:%s\n", ipstr);
													cse4589_print_and_log("[%s:END]\n", cmd);
													}

												}
												 if(!strncmp(cmd,"PORT",4))
												 {
													//printf("Port no is %d",port);
													cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
													cse4589_print_and_log("PORT:%d\n", port);
													cse4589_print_and_log("[%s:END]\n", cmd);
												}
												 if(!strncmp(cmd,"LIST",4))
												 		{
													 int i;
													 i=0;
													 struct node* current;
													 current = (struct node *) malloc( sizeof(struct node) );

												 					 		current = head;
												 					 		cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
												 					 		while(current!=NULL)
												 					 		 {i++;
																				//printf("%-5d%-35s%-20s%-8d\n",i , current->hostname, current->ip_add, atoi(current->port_no));

									 					 			cse4589_print_and_log("%-5d%-35s%-20s%-8d\n",i , current->hostname, current->ip_add, atoi(current->port_no));
									 					 			current = current->next; }
												 					 		cse4589_print_and_log("[%s:END]\n", cmd);
												 					 		}
												 if(!strncmp(cmd,"STATISTICS",10))
														{

															//cse4589_print_and_log("[%s:SUCCESS]\n", cmd);
													 	 	//cse4589_print_and_log("PORT:%d\n", port);
															//cse4589_print_and_log("[%s:END]\n", cmd);
														}
												if(strstr(cmd, "BLOCKED"))
												{
													////printf("HI");
												}
												else
												{
													//
												}
						                      }
					//if()
//						{
//
//						}


					}
				//else()
				else if(sock_index == server_socket){

					////printf("BEFORE accept\n");
                caddr_len = sizeof((struct sockaddr*)&client_addr);
                fdaccept = accept(server_socket, (struct sockaddr *)&client_addr, &caddr_len);
                struct node* newnode =(struct node*)malloc(sizeof(struct node));
                               //inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &(((struct sockaddr_in *)&client_addr)->sin_addr), newnode->ip_add, INET_ADDRSTRLEN);



                struct hostent *he;

                struct in_addr ipv4addr;
                char *cp;

                inet_pton(AF_INET, newnode->ip_add, &ipv4addr);
                char host[1024];
                char service[20];
                //This function getnameinfo is taken from Beej Guide
                getnameinfo((struct sockaddr *)&client_addr, caddr_len, host, sizeof host, service, sizeof service, 0);
                //printf("%s", host);
                //he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
                //unsigned short int p = ((struct sockaddr_in *)&ipv4addr)->sin_port;
               // //printf("Host name: %s\n", he->h_name);
                strcpy( newnode->hostname , host);

                //char *p1;
                //itoa(p,p1,10);
               // //printf("%s",p1);
                //newnode->port_no= p;

                recv(fdaccept, newnode->port_no, BUFFER_SIZE, 0);

                newnode->next = NULL;
                struct node *temp=head;
                if(head==NULL)
                {
                	head = newnode;
                }
                else
                {
                	while(temp->next!=NULL)
                	{
                		temp = temp->next;

                	}
                	temp->next = newnode;

                }
                MergeSort(&head);
                struct node* current;
                current = (struct node *) malloc( sizeof(struct node) );
                current = head;

                 while(current!=NULL)
                	{
                	 char s1[1025], s2[INET_ADDRSTRLEN], s3[20];



                	 strcpy(s1,current->hostname);
                	 strcpy(s2,current->ip_add);
                	 strcpy(s3,current->port_no);
                	 strcat(s1, " ");
                	 strcat(s1, s2);
                	 strcat(s1, " ");
                	 strcat(s1, s3);
                	 //strcat(strcat(s1, " "),strcat(strcat(s2, " "),s3));

//                	 if(send(fdaccept, s1, sizeof s1, 0) == sizeof s1)
//                    { ;
//
//                    }


         //       	 cse4589_print_and_log("message %s",s1);
                	 int z= send(fdaccept, s1, sizeof s1, 0);
         //       	 cse4589_print_and_log("Actual bytes %lu and Sending %d bytes", sizeof (s1), z);
                	current = current->next;
                	}


                ////printf("AFTER accept");

            }
            /* Read from existing clients */
				 else
				 {
					 char *buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);
                 memset(buffer, '\0', BUFFER_SIZE);
   int r;
  // //printf("Before receive");
  r= recv(fdaccept, buffer, BUFFER_SIZE, 0);
  //printf("%d", r);
  //printf("%s",buffer);

if(strstr(buffer, "BROADCAST"))
{
	int x;
	int i, j;
	i=0;
  					                	char *array[3];
  					                	char *token;
  					                	token = strtok(buffer, " ");
  					                	 while (token != NULL )
  	            							 	 {
  					                			array[i] = token;
  					                			token = strtok(NULL, " ");
  					                			i++;
  	            							 	 }
  					                	 //The below part is taken from Beej Guide
  				                        for(j = 0; j <= max_conn; j++) {
  				                            // send to everyone!
  				                            if (FD_ISSET(j, &master)) {
  				                                // except the listener and ourselves
  				                                if (j != server_socket && j != sock_index) {
  				                                    int x = send(j, array[2], sizeof array[2], 0);
  				                                    if(x != sizeof (array[2]))
  				                                    {
  				                                    	strcpy(messages[j][1], array[1]);
  				                                    	strcpy(messages[j][2], array[2]);
  				                                    }

  				                                }

  				                            }
  				                        }//The above part is taken form Beej Guide
  				                      cse4589_print_and_log("[%s:SUCCESS]\n", "RELAYED");
  				                      cse4589_print_and_log("msg from:%s, to:%s\n[msg]:%s\n", array[1], "255.255.255.255");
  				                      cse4589_print_and_log("[%s:END]\n", "RELAYED");
}
if(strstr(buffer, "SEND"))
{
	char *array[3];
	char *token;
	int j;
	token = strtok(buffer, " ");
	  	while (token != NULL )
	  		 {
	  			array[i] = token;
	  			token = strtok(NULL, " ");
	  			i++;
	  			}
	  	for(j = 0; j <= max_conn; j++) {
	  	  	if (FD_ISSET(j, &master)) {
	  	  		// except the listener and ourselves
	  	  		if (j != server_socket && j != sock_index) {
	  	  			int x = send(j, array[2], sizeof array[2], 0);
	  	  				if(x != sizeof (array[2]))
	  	  				  {strcpy(messages[j][8], array[1]);
	  	  				   strcpy(messages[j][9], array[2]);
	  	  				   strcpy(messages[j][10], array[3]);
	  	  				  }

	  	  				  }

	  	  			}
	  		}
	  	cse4589_print_and_log("[%s:SUCCESS]\n", "RELAYED");
	  	cse4589_print_and_log("msg from:%s, to:%s\n[msg]:%s\n", array[1], array[2]);
	  	cse4589_print_and_log("[%s:END]\n", "RELAYED");
	  			////printf("msg from:%s, to:%s\n[msg]:%s\n", from-client-ip, "255.255.255.255", array[1]);
	  			//cse4589_print_and_log("[%s:SUCCESS]\n", "RELAYED");
	  			//cse4589_print_and_log("msg from:%s, to:%s\n[msg]:%s\n", from-client-ip, "255.255.255.255", array[1]);

}

////printf("\nRemote Host connected!\n");
/* Add to watched socket list */

free(buffer);
if( r<= 0)
{
close(sock_index);
// //printf("Remote Host terminated connection!\n");
/* Remove from watched list */
FD_CLR(sock_index, &master);
}				                							////printf("msg from:%s, to:%s\n[msg]:%s\n", from-client-ip, "255.255.255.255", array[1]);


				 }
				}
			}

		}	/*else stdin and connections loop*/

	}	/*while loop*/
	}	/*if server*/
	if(!strcmp(argv[1],"c"))
	{
		int port1= atoi(argv[2]);
		 int fdsocket;
		struct sockaddr_in my;
		struct node{
						int list_id;
						char hostname[1025];
						char ip_add[INET_ADDRSTRLEN];
						char port_no[20];
						//struct sockaddr_in clientaddress;
						struct node* next;
					};
		struct node* current;
		current = (struct node *) malloc( sizeof(struct node) );

			int server;
			int login;
			login =0;
			 struct sockaddr_in sa;
			int p;
			while(1){



				////printf("\n[PA1-Client@//cse489/589]$ ");
				//fflush(stdout);

				char *cmdomsg = (char*) malloc(sizeof(char)*MSG_SIZE);
		    	memset(cmdomsg, '\0', MSG_SIZE);
				if(fgets(cmdomsg, MSG_SIZE-1, stdin) == NULL) //Mind the newline character that will be written to msg
					exit(-1);
				else
				{


              {
							int len=strlen(cmdomsg);
							if(cmdomsg[len-1]=='\n'){
								cmdomsg[len-1] = '\0';
							}
              }


						////printf("%s\n",cmdomsg);
					if(!strncmp(cmdomsg,"AUTHOR", 6))
							{
							cse4589_print_and_log("[%s:SUCCESS]\n", cmdomsg);
							cse4589_print_and_log("I, %s, have read and understood the course academic integrity policy.\n", "vaidehip");
							cse4589_print_and_log("[%s:END]\n", cmdomsg);
							//int x= 4*6;
							////printf("%d",x);
							//printf("I, %s, have read and understood the course academic integrity policy.", ubit_name);
							}

					if(!strncmp(cmdomsg,"IP", 2))
							{

							memset(&udpserver,0, sizeof udpserver);
							udpserver.sin_family = AF_INET; /* IPv4*/
							udpserver.sin_addr.s_addr =inet_addr("8.8.8.8") ;
							udpserver.sin_port = htons(port);
							if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
									{
									////printf("Error in creating udp socket");
									cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
									cse4589_print_and_log("[%s:END]\n", cmdomsg);
									return -1;
									}
							connect(sockfd, (struct sockaddr *)&udpserver, sizeof(udpserver));
							addr_len = sizeof res;
							if(!(getsockname(sockfd,(struct sockaddr *)&res,&addr_len )))
								{
								inet_ntop(res.sin_family, &res.sin_addr, ipstr, sizeof ipstr);//taken from beej guide
							   //printf("  The IP address is %s", ipstr);
								cse4589_print_and_log("[%s:SUCCESS]\n", cmdomsg);
								cse4589_print_and_log("IP:%s\n", ipstr);
								cse4589_print_and_log("[%s:END]\n", cmdomsg);
								}

							}
					 if(!strncmp(cmdomsg,"PORT",4))
							{
								//printf("Port no is %d",port);
								cse4589_print_and_log("[%s:SUCCESS]\n", cmdomsg);
								cse4589_print_and_log("PORT:%d\n", port);
								cse4589_print_and_log("[%s:END]\n", cmdomsg);
							}
					 if(strstr(cmdomsg, "LOGIN"))
					 		{

						 				 fdsocket = socket(AF_INET, SOCK_STREAM, 0);
						 										 	    if(fdsocket < 0)
						 										 	    {

						 										 	    	//return -1;
						 										 	    }
						 //This part is taken from http://fresh2refresh.com/c-programming/c-strings/c-strstr-function/
						 char *array[3], *array1, *array2;
						 						 int i = 0;
						 						 char *token, *token1;
						 						 token = strtok(cmdomsg, " ");
						 						while (token != NULL )
						 							{
						 								array[i] = token;
						 								token = strtok(NULL, " ");
						 								i++;
						 								 }
						 	//printf("%s, %s, %s", array[0], array[1], array[2]);
						 	int len, portno;
						 	    struct sockaddr_in remote_server_addr;


						 	   //struct sockaddr_in sa;
						 	   int p;
						 	   bzero(&remote_server_addr, sizeof(remote_server_addr));
						 	   remote_server_addr.sin_family = AF_INET;
						 	   p = inet_pton(AF_INET, array[1], &remote_server_addr.sin_addr.s_addr);

						 	   if(p!=1)
						 	   {
						 		   //printf("Invalid IP address!");
						 		 cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
						 		 cse4589_print_and_log("[%s:END]\n", cmdomsg);
						 	   }
						 	   else
						 	   {
						 	    portno = atoi(array[2]);
						 	    remote_server_addr.sin_port = htons(portno);
						 	   // //printf("connection");
//						 	   my.sin_family = AF_INET; /* IPv4*/
//						 	   		my.sin_addr.s_addr =htonl(INADDR_ANY) ;
//						 	   		my.sin_port = htons(port1);	  /*server address*/
//						 	   		if(bind(fdsocket, (struct sockaddr*)&my, sizeof(my)) < 0)
//						 	   					return -1;
						 	    if(connect(fdsocket, (struct sockaddr*)&remote_server_addr, sizeof(remote_server_addr)) < 0)
						 	        {
						 	    	cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
						 	    	cse4589_print_and_log("[%s:END]\n", cmdomsg);
						 	    	return -1;
						 	        }
						 	   if(send(fdsocket,argv[2] , strlen(argv[2]), 0)== strlen(argv[2]))
						 	   {
						 		   ;
						 	   }
						 		  ////printf("1\n");
						 	  struct node* current1;
						 	  current1 = (struct node *) malloc( sizeof(struct node) );
						 	  current1 = current;
						 	 ////printf("Current1 %u",current1);
						 	   while(current1!=NULL)
						 	  {
						 		   char buffer[1025];

//						 		   if(recv(fdsocket, buffer, sizeof (buffer), 0) <= 0)
//					 	 		 {
//						 			   return -1;
//						 		 }



						 		   int r= recv(fdsocket, buffer, sizeof (buffer), 0);
					//	 		  cse4589_print_and_log("Received bytes %d", r);
						 		 char *m[3];
						 		  i = 0;
						 		 						 						 char *token1;
						 		 						 						 token1 = strtok(buffer, " ");
						 		 						 						while (token1 != NULL )
						 		 						 							{
						 		 						 								m[i] = token1;
						 		 						 								token1 = strtok(NULL, " ");
						 		 						 								i++;
						 		 						 								 }

						 		  						 		strcpy(current->hostname,m[0]);
						 		  						 		strcpy(current->ip_add,m[1]);
						 		  						 		strcpy(current->port_no,m[2]);
						 		  						 	//cse4589_print_and_log("Token %s", token1);
						 //		  						 cse4589_print_and_log("array1 %s %s", m[0], m[1]);
						 		  current1 = current1->next;
				 		 }

						 	   login =1;
						 	 cse4589_print_and_log("[%s:SUCCESS]\n", cmdomsg);
						 	 					 cse4589_print_and_log("[%s:END]\n", cmdomsg);

						 	   }
					 		}
					 if((!strncmp(cmdomsg,"LIST",4))&&login)
					 					 					 		{
					 						 int i;
					 						 i=0;
					 						 struct node* current1;
					 						 current1 = (struct node *) malloc( sizeof(struct node) );

					 					 					 		current1 = current;
					 					 					 		cse4589_print_and_log("[%s:SUCCESS]\n", cmdomsg);
					 					 					 		while(current1!=NULL)
					 					 					 		 {i++;
					 													//printf("%-5d%-35s%-20s%-8d\n",i , current1->hostname, current1->ip_add, atoi(current1->port_no));

					 		 					 			cse4589_print_and_log("%-5d%-35s%-20s%-8d\n",i , current1->hostname, current1->ip_add, atoi(current1->port_no));
					 		 					 			current1 = current1->next; }
					 					 					 		cse4589_print_and_log("[%s:END]\n", cmdomsg);
					 					 					 		}
					 	 	 	 	 	 if((strstr(cmdomsg, "SEND"))&&login)
					 					 {					 		char *array[4];
					 						 						 int i = 0;
					 						 						 char *token;
					 						 						 token = strtok(cmdomsg, " ");
					 						 						 while (token != NULL )
					 						 						  {
					 						 						 	array[i] = token;
					 						 						 	token = strtok(NULL, " ");
					 						 						    i++;
					 						 						  }
					 						 						 struct sockaddr_in sa;
					 						 						 int p;
					 						 						 p = inet_pton(AF_INET, array[1], &(sa.sin_addr));


					 						 						struct node* current1;
					 						 						current1 = (struct node *) malloc( sizeof(struct node) );
					 						 						current1 = current;
					 						 						i=0;
					 						 						do
					 						 					    {
					 						 							if(!strcmp(array[1],current1->ip_add))
					 						 							{
					 						 							 i=1;
					 						 						    }
					 						 							////printf("%-5d%-35s%-20s%-8d\n",i , current1->hostname, current1->ip_add, current1->port_no);
					 						 						current1 = current1->next;
					 						 						//cse4589_print_and_log("%-5d%-35s%-20s%-8d\n",i , current1->hostname, current1->ip_add, current1->port_no);
					 						 						}while(current1!=NULL);
					 						 							if(p!=1)
					 						 							 {
					 						 					      //   //printf("Invalid IP address!");
					 						 							 cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
					 						 							 cse4589_print_and_log("[%s:END]\n", cmdomsg);
					 						 							 }
					 						 							else if(i!=1)
					 						 							{
					 						 							//printf("Client not in the list!");
					 						 						 cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
					 						 						 cse4589_print_and_log("[%s:END]\n", cmdomsg);
					 						 							 }
					 						 							else
					 						 							{

					 						 								char s1[1025], s2[INET_ADDRSTRLEN], s3[INET_ADDRSTRLEN], s4[256];
					 						 								strcpy(s1,array[0]);
					 						 							    strcpy(s2,ipstr);
					 						 								strcpy(s3,array[1]);
					 						 								strcpy(s4,array[2]);
					 						 								strcat(strcat(s1, " "),strcat(strcat(s2, " "),s3));
					 						 								strcat(s1, " ");
					 						 								strcat(s1, s4);
					 						 								send(fdsocket, s1, sizeof s1, 0);
					 //						 									{
					 //						 							//if(send(client_socket, array[2], strlen(array[2]), 0)== strlen(array[2]))
					 //						 							//printf("SUCCESS!!");
					 						 							cse4589_print_and_log("[%s:SUCCESS]\n", array[0]);
					 						 							cse4589_print_and_log("[%s:END]\n", array[0]);
					 						 									}
					 						 							//fflush(stdout);
					 						 							}
					 					 if((strstr(cmdomsg, "BROADCAST"))&&login)
					 					 					  {					 		char *array[3];
				 						 						 int i = 0;
				 						 						 char *token;
				 						 						 token = strtok(cmdomsg, " ");
				 						 						 while (token != NULL )
				 						 						  {
				 						 						 	array[i] = token;
				 						 						 	token = strtok(NULL, " ");
				 						 						    i++;
				 						 						  }
				 						 						 struct sockaddr_in sa;
				 						 						 int p;
				 						 						 p = inet_pton(AF_INET, array[1], &(sa.sin_addr));


				 						 						struct node* current1;
				 						 						current1 = (struct node *) malloc( sizeof(struct node) );
				 						 						current1 = current;
				 						 						i=0;
				 						 						do
				 						 					    {
				 						 							if(!strcmp(array[1],current1->ip_add))
				 						 							{
				 						 							 i=1;
				 						 						    }
				 						 							////printf("%-5d%-35s%-20s%-8d\n",i , current1->hostname, current1->ip_add, current1->port_no);
				 						 						current1 = current1->next;
				 						 						//cse4589_print_and_log("%-5d%-35s%-20s%-8d\n",i , current1->hostname, current1->ip_add, current1->port_no);
				 						 						}while(current1!=NULL);
				 						 							if(p!=1)
				 						 							 {
				 						 					      //   //printf("Invalid IP address!");
				 						 							 cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
				 						 							 cse4589_print_and_log("[%s:END]\n", cmdomsg);
				 						 							 }
				 						 							else if(i!=1)
				 						 							{
				 						 							//printf("Client not in the list!");
				 						 						 cse4589_print_and_log("[%s:ERROR]\n", cmdomsg);
				 						 						 cse4589_print_and_log("[%s:END]\n", cmdomsg);
				 						 							 }
				 						 							else
				 						 							{

				 						 								char s1[1025], s2[INET_ADDRSTRLEN], s3[INET_ADDRSTRLEN], s4[256];
				 						 								strcpy(s1,array[0]);
				 						 							    strcpy(s2,ipstr);
				 						 								strcpy(s3,array[1]);

				 						 								strcat(strcat(s1, " "),strcat(strcat(s2, " "),s3));
				 						 								send(fdsocket, s1, sizeof s1, 0);
				 //						 									{
				 //						 							//if(send(client_socket, array[2], strlen(array[2]), 0)== strlen(array[2]))
				 //						 							//printf("SUCCESS!!");
				 						 							cse4589_print_and_log("[%s:SUCCESS]\n", array[0]);
				 						 							cse4589_print_and_log("[%s:END]\n", array[0]);
				 						 									}
				 						 							//fflush(stdout);
				 						 							}
					 							 	}
							if((!strncmp(cmdomsg,"LOGOUT",6))&&login)
					 					 					 {
					 					 						shutdown(fdsocket, SHUT_RDWR);
					 					 						login = 0;
					 					 					 }
					 					 					 if(!strncmp(cmdomsg,"EXIT",4))
					 					 					 					 {
					 					 					 						 close(fdsocket);
					 					 					 							 cse4589_print_and_log("[%s:SUCCESS]\n", cmdomsg);
					 					 					 							 cse4589_print_and_log("[%s:END]\n", cmdomsg);
					 					 					 							 return 0;

					 					 					 					 }




						 	  // //printf("After\n");
						 	   //}
					 		}



					 }
	//else()

	return 0;
}

