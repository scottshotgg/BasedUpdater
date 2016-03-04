/* The port number is passed as an argument */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include <dirent.h>
#include <math.h>
// http://id3lib.sourceforge.net/api/index.html

sqlite3 *db;
char *zErrMsg = 0;
int rc;
char sql[] = "hi";

void constructDatabase()
{
    struct dirent *dp;
    DIR *base_directory;
    int file_count = 0;

    char dir[] = ".";

    if ((base_directory = opendir(dir)) == NULL) 
    {
        fprintf(stderr, "listdir: can't open %s\n", ".");
        return;
    }
    while ((dp = readdir(base_directory)) != NULL) 
    {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;    /* skip self and parent */
        file_count++;
        printf("Found file: %s\n", dp->d_name); // found shit
    }
    closedir(base_directory);
    printf("Number of files: %d\n", file_count);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void executeSQL(char type)
{
    if(type == 'e')
    {
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);\
            sqlite3_free(zErrMsg);
        }
        else
        {
            fprintf(stdout, "Table created successfully\n");
        }
    }
    else if(type == 'o')
    {
        rc = sqlite3_open("test.db", &db);

        if(rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Opened database successfully\n");
        }
    }
    else
    {
        printf("ERROR: This is not a valid identifier\n");
        exit(0);
    }
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    constructDatabase();

    printf("Starting server on port %d\n", atoi(argv[1]));
    int mybuffer[1000];
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
     fprintf(stderr,"ERROR, no port provided\n");
     exit(1);
    }

    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = INADDR_ANY;  
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
          sizeof(serv_addr)) < 0) 
          error("ERROR on binding");

    /*DIR *base_directory; = opendir("/");
    struct dirent* entry;
    int file_count = 0;

    while ((entry = readdir(base_directory)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;    /* skip self and parent 
        printf("%s/%s\n", dir, entry->d_name);
    }
    closedir(base_directory);

    printf("Amount of files: %d\n", file_count);*/

    //while(1)
    {
        listen(sockfd, 5);

        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, &clilen);

        // Bound to 0 because I wanted to take out the fork
        pid_t process = 0;

        //if((process = fork()) >= 0)
        {
            if(process != 0)        // I am the parent of the fork
            {
                // I am going to do nothing because I am the parent and I need to go back to listerning for another client
                close(newsockfd);
                //continue;
            }
            else                    // I am the child of the fork
            {
                if (newsockfd < 0) 
                    error("ERROR on accept");

                printf("server: got connection from %s port %d\n", 
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

               // while(1)
                {
                    bzero(buffer,256);

                    n = read(newsockfd,buffer,255);

                    int fd = open("afile.txt", O_RDWR);

                    int bytes_read, bytes_written;

                    while(1)
                    {
                        bytes_read = read(fd, mybuffer, sizeof(mybuffer));

                        if(bytes_read == 0) 
                            break;

                        printf("Bytes read: %d\n", bytes_read);
                        // another if goes here to check for errors if they have occured; I have not done this as our program is mostly predictable, being this small
                        // also I'm lazy :D

                        void p* = mybuffer;
                        while(bytes_read > 0)
                        {
                            bytes_written = write(newsockfd, p, bytes_read);
                            printf("Bytes written: %d\n", bytes_written);
                            // handle errors here like we did before at the read section

                            bytes_read -= bytes_written;
                            p += bytes_written;
                        }
                    }

                    close(newsockfd);
                    close(sockfd);
                    close(fd);
                    printf("File transfer completerino");
                }
            }
        }
        /*else
        {
            printf("ERROR: Fork failed");
            close(newsockfd);
            close(sockfd);
            return 1;
        }*/
    }

    // Create SQL statement

    /*sql = "CREATE TABLE COMPANY("   \
            "ID INT PRIMARY KEY     NOT NULL,"  \
            "NAME       TEXT    NOT NULL,"  \
            "AGE        INT     NOT NULL,"  \
            "ADDRESS    CHAR(50),"  \
            "SALARY     REAL);";

    // Execute SQL statement

    executeSQL('e');

    sql =   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (1, 'Paul', 32, 'California', 20000.00);" \
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (2, 'Allen', 25, 'Texas', 15000.00);"   \
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (3, 'Teddy', 23, 'Norway', 20000.00);"  \
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (4, 'Allen', 25, 'Richmond', 65000.00);";

    executeSQL('e');

    sql = "SELECT * from COMPANY";

    executeSQL('e');

    sql =   "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
            "SELECT * from COMPANY";

    executeSQL('e');

    sql =   "DELETE from COMPANY where ID=2; "  \
            "SELECT * from COMPANY";

    executeSQL('e');*/

    //executeSQL('o');

    /*sql = "CREATE TABLE COMPANY("   \
            "ID INT PRIMARY KEY     NOT NULL,"  \
            "NAME       TEXT    NOT NULL,"  \
            "AGE        INT     NOT NULL,"  \
            "ADDRESS    CHAR(50),"  \
            "SALARY     REAL);";
*/
    //  We may want to add stuff like bitrate and composer shit
    sql =   "CREATE TABLE MUSIC(" \
            "ID INT PRIMARY KEY     NOT NULL," \
            "TITLE          TEXT    NOT NULL," \
            "ARTIST         TEXT    NOT NULL," \
            "ALBUM          TEXT    NOT NULL," \
            "TRACKNUMBER    REAL    NOT NULL);";
    //executeSQL('e');

    sql =   "INSERT INTO MUSIC (ID,TITLE,ALBUM,TRACKNUMBER,ARTIST)" \
            "VALUES (1 , 'I Own Swag', 'Lil B', 'Example Album', 9)";
    //executeSQL('e');

    char exampleTitle[] = "tokerino";
    int exampleID = 420;
    char exampleArtist[] = "snoop doggy dog";
    int lengthOfNumber = log10(exampleID) + 2;
    char somrhinngIMade[lengthOfNumber];

    snprintf(somrhinngIMade, lengthOfNumber, "%d", exampleID);

    printf("%d\n", lengthOfNumber);

    sql =   "INSERT INTO MUSIC (ID,TITLE,ALBUM,TRACKNUMBER,ARTIST)" \
            "VALUES ('";
    printf("%s\n", sql);
    strcat(sql, somrhinngIMade);
    printf("%s\n", sql);
    strcat(sql, "','");
    printf("%s\n", sql);
    strcat(sql, exampleTitle);
    printf("%s\n", sql);
    strcat(sql, "','");
    printf("%s\n", sql);
    strcat(sql, exampleArtist);
    printf("%s\n", sql);
    strcat(sql, "','");
    printf("%s\n", sql);
    strcat(sql, "Example Album");
    printf("%s\n", sql);
    strcat(sql, "',");
    printf("%s\n", sql);
    strcat(sql, "9");
    printf("%s\n", sql);
    strcat(sql, ")");
    printf("%s\n", sql);
    //executeSQL('e');

    sql = "SELECT * from MUSIC";
    //executeSQL('e');
 
    sqlite3_close(db); 

    return 0;
}