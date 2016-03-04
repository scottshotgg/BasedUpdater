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
#include <dirent.h>
#include <math.h>
#include <string.h>

// ======= External includes =======

#include <sqlite3.h>
#include <taglib/tag_c.h>   // Need to put the license for that here

#define CREATE_FILES        false  // Used to just create 1000 files to simulate DB files
//#define PRINT_DEBUG

#if CREATE_FILES

void createFiles()
{
    int result = mkdir("./shit_folder", 0777);

    char filename[30], number[4];
    int j, fd, file_count = 0;

    for(j = 0; j < 1000; j++)
    {
        snprintf(number, 4, "%d", j);
        strcpy(filename, "./shit_folder/shit_file_");
        strcat(filename, number);
        fd = open(filename, O_RDWR | O_CREAT, 0400);

        if(fd != -1)
        {
            #ifdef PRINT_DEBUG
            printf("File created: %s\n", filename);
            #endif

            file_count++;
        }
        else
            #ifdef PRINT_DEBUG
            printf("There was an error creating: %s\n", filename);
            #endif

        close(fd);
    }

    printf("%d files created\n", file_count);
}

#endif

sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;
int db_size = 0;
int showDBTable = 0;
int file_count_for_adding_files = 0;

int stringToInt(char* string)
{
    int value = 0, length, k;
    length = strlen(string) - 1;
    //printf("length %d\n", length);

    for(k = 0; k <= length; k++)
    {
        //printf("%f      %d\n", (pow(10, length)), string[k] - 48); // this only works for ascii
        value += (pow(10, length) * (string[k] - 48));
        //printf("%d\n", value);
    }

    //printf("value %d\n", value);
    return value;
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

static int callbackForSize(void *NotUsed, int argc, char **argv, char **azColName)
{
    //if(sizeof(argv) == 4)   // else we need to do something else maybe
    //printf("%s %s %s %s\n", argv[0], argv[1], argv[2], argv[4]);
    db_size = stringToInt(argv[0]);

    printf("Got database size: %d\n", db_size);

    return 0;
}

void executeSQL(char type, char* sqlStatement)
{
    if(type == 'e')
    {
        rc = sqlite3_exec(db, sqlStatement, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);\
            sqlite3_free(zErrMsg);
            //exit(0);
        }
        else
        {
            //fprintf(stdout, "Statement executed successfully\n");
        }
    }
    else if(type == 'o')
    {
        //rc = sqlite3_open_v2("test.db", &db, SQLITE_OPEN_READWRITE, NULL);
        rc = sqlite3_open("test.db", &db);

        if(rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

            /*createDatabase()
            printf("Creating database...");
            
            rc = sqlite3_open_v2("test.db", &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
            */
            //exit(0);
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

void getLastItemForSize()
{
    sql = "SELECT * FROM MUSIC WHERE ID = (SELECT MAX(ID) FROM MUSIC);";

    if(rc = sqlite3_exec(db, sql, callbackForSize, 0, &zErrMsg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);\
        sqlite3_free(zErrMsg);

        // We didn't find a table so create it

        //  We may want to add stuff like bitrate and composer shit
        sql =   "CREATE TABLE MUSIC(" \
                "ID INT PRIMARY KEY     NOT NULL," \
                "FILEPATH       TEXT    NOT NULL," \
                "FILENAME       TEXT    NOT NULL," \
                "TITLE          TEXT    NOT NULL," \
                "ARTIST         TEXT    NOT NULL," \
                "ALBUM          TEXT    NOT NULL," \
                "TRACKNUMBER    INT     NOT NULL);";

        executeSQL('e', sql);
    }
    else
    {
        //fprintf(stdout, "Statement executed successfully\n");
    }
}

void insertSqlItem(int ID, char* filepath, char* filename, char* title, char* artist, char* album, int trackNumber)
{
    sqlite3_stmt* stmt;
    sql = "INSERT INTO MUSIC VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);

    sqlite3_bind_int(stmt, 1, ID);
    sqlite3_bind_text(stmt, 2, filepath, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, filename, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, title, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, artist, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, album, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, trackNumber);

    sqlite3_step(stmt); // Need some error checking
}

void getTrackInfo(char* dir, char* filename)    // this should put the data in the struct
{
    // int i, seconds, minutes; // might not need this
    char filepath[strlen(dir) + strlen(filename)];

    strcpy(filepath, dir);
    strcat(filepath, filename);

    TagLib_File *file  = taglib_file_new(filepath);
    TagLib_Tag *tag = taglib_file_tag(file);
    const TagLib_AudioProperties *properties = taglib_file_audioproperties(file);

    taglib_set_strings_unicode(0);

    if(file == NULL)
      return;

   /* if(tag != NULL)
    {
        printf("-- TAG --\n");
        printf("title   - \"%s\"\n", taglib_tag_title(tag));
        printf("artist  - \"%s\"\n", taglib_tag_artist(tag));
        printf("album   - \"%s\"\n", taglib_tag_album(tag));
        printf("year    - \"%i\"\n", taglib_tag_year(tag));
        printf("comment - \"%s\"\n", taglib_tag_comment(tag));
        printf("track   - \"%i\"\n", taglib_tag_track(tag));
        printf("genre   - \"%s\"\n", taglib_tag_genre(tag));
    }

    if(properties != NULL) 
    {
        seconds = taglib_audioproperties_length(properties) % 60;
        minutes = (taglib_audioproperties_length(properties) - seconds) / 60;

        printf("-- AUDIO --\n");
        printf("bitrate     - %i\n", taglib_audioproperties_bitrate(properties));
        printf("sample rate - %i\n", taglib_audioproperties_samplerate(properties));
        printf("channels    - %i\n", taglib_audioproperties_channels(properties));
        printf("length      - %i:%02i\n", minutes, seconds);
    } */
    insertSqlItem(++file_count_for_adding_files, filepath, filename, taglib_tag_title(tag), taglib_tag_artist(tag), taglib_tag_album(tag), taglib_tag_track(tag));

    taglib_tag_free_strings();
    taglib_file_free(file);
}

void constructDatabase()
{
    struct dirent *dp;
    DIR *base_directory;
    //char* dir = "./shit_folder/";
    char* dir = "music/";

    if ((base_directory = opendir(dir)) == NULL) 
    {
        fprintf(stderr, "listdir: can't open %s\n", ".");
        return;
    }

    int trackNumber = 0; // dont leave this here you lazy noob

    executeSQL('o', sql);

    getLastItemForSize();

    executeSQL('e', "BEGIN TRANSACTION");

    while ((dp = readdir(base_directory)) != NULL) 
    {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;    /* skip self and parent */
            getTrackInfo(dir, dp->d_name);
        //printf("Found file: %s\n", dp->d_name); // found shitl
        // There are warning coming from here, I don't think it likes the string literal

        #ifdef PRINT_DEBUG
        printf("%4d: %s was added to the data base\n", file_count_for_adding_files, dp->d_name);
        #endif
    }
    closedir(base_directory);

    executeSQL('e', "END");

    printf("Number of files: %d\n", file_count_for_adding_files);

    // Here is where you would get the file count in creation to know how big the table is

    if(showDBTable)
    {
        executeSQL('e', "SELECT * from MUSIC");
    }

    sqlite3_close(db);

     printf("Database built!\n");
}

// old insertion function from when I didn't know about prepare and bind
// lol injection top kek

/*
void insertSqlItem(int ID, char* title, char* artist, char* album, int trackNumber)
{
    //executeSQL('o', sql);

    //sql =   "INSERT INTO MUSIC (ID,TITLE,ALBUM,TRACKNUMBER,ARTIST)" \
    //        "VALUES (1 , 'I Own Swag', 'Lil B', 'Example Album', 9)";
    //executeSQL('e', sql);

    char* exampleTitle = title;
    int exampleID = ID;
    char* exampleArtist = artist;
    int lengthOfNumber = log10(exampleID) + 2;
    char somrhinngIMade[lengthOfNumber];

    snprintf(somrhinngIMade, lengthOfNumber, "%d", exampleID);

    //printf("%d\n", lengthOfNumber);

    sql =   "INSERT INTO MUSIC (ID,TITLE,ARTIST,ALBUM,TRACKNUMBER)" \
            "VALUES ('";

    char sqlModified[200];
    strcpy(sqlModified, sql);
    // printf("%s\n", sqlModified);
    strcat(sqlModified, somrhinngIMade);
    //printf("%s\n", sqlModified);
    strcat(sqlModified, "','");
    //printf("%s\n", sqlModified);
    strcat(sqlModified, exampleTitle);
    //printf("%s\n", sqlModified);
    strcat(sqlModified, "','");
    //printf("%s\n", sqlModified);
    strcat(sqlModified, exampleArtist);
    //printf("%s\n", sqlModified);
    strcat(sqlModified, "','");
    //printf("%s\n", sqlModified);
    strcat(sqlModified, "Example Album");
    //printf("%s\n", sqlModified);
    strcat(sqlModified, "',");
    //printf("%s\n", sqlModified);
    strcat(sqlModified, "9");
    //printf("%s\n", sqlModified);
    strcat(sqlModified, ");");
    //printf("%s\n", sqlModified);
    sql = sqlModified;
    //printf("%s\n", sql);

    executeSQL('e', sql); // originally used the string passing to modify the static sql string
 
    //sqlite3_close(db); 
}
*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void doServerStuff(char argc, char *argv[])
{
    printf("Starting server on port %d\n", atoi(argv[1]));
    int mybuffer[10000];
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc < 2) 
    {
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

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
          error("ERROR on binding");

    //while(1)
    {
        listen(sockfd, 5);

        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        // Bound to 0 because I wanted to take out the fork
        pid_t process = 0;

        //if((process = fork()) >= 0)
        {
            if(process != 0)        // I am the parent of the fork
            {
                // I am going to do nothing because I am the parent and I need to go back to listerning for another client
                close(newsockfd);
                close(sockfd);
                printf("%s\n", "I am the parent");
                return;
                //continue;
            }
            else if(process == 0)                  // I am the child of the fork
            {
                if (newsockfd < 0) 
                    error("ERROR on accept");

                printf("server: got connection from %s port %d\n", 
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

               //while(1)
                int l = 1;
                for(l; l <= file_count_for_adding_files; l++)
                {

                    printf("%d and %d \n", file_count_for_adding_files, l);

                    printf("Waiting for some input from the client: \n");
                    bzero(buffer, 256); // increase this later





                    sqlite3_stmt* filename;
                    sql = "SELECT FILENAME FROM MUSIC WHERE ID=?;";
                    sqlite3_prepare_v2(db, sql, strlen(sql), &filename, NULL);
                    sqlite3_bind_int(filename, 1, l);
                    //sqlite3_bind_int(filename, 1, 1);
                    sqlite3_step(filename);

                    n = read(newsockfd, buffer, 255);
                    const char* filenamestring = sqlite3_column_text(filename, 0);
                    printf("%s\n", filenamestring);
                    n = write(newsockfd, filenamestring, strlen(filenamestring));
                    n = read(newsockfd, buffer, 255);





                    sqlite3_stmt* filepath;
                    sql = "SELECT FILEPATH FROM MUSIC WHERE ID=?;";
                    sqlite3_prepare_v2(db, sql, strlen(sql), &filepath, NULL);
                    sqlite3_bind_int(filepath, 1, l);
                    //sqlite3_bind_int(stmt, 1, 1);
                    sqlite3_step(filepath);

                    /*if(sqlite3_step(stmt) == SQLITE_ROW)
                    {
                        // Add in varialble checking to see what is going on and check for errors
                        // For now just make it hardcoded
                        const char* result_of_call = sqlite3_column_text(stmt, 0);
                        printf("This is the row that I have returned2: %s\n\n", result_of_call);                      
                    }*/

                    const char* filepathstring = sqlite3_column_text(filepath, 0);
                    printf("This is the row that I have returned: %s\n\n", filepathstring);
                    /*char filepath[100];
                    strcpy(filepath, "music/");
                    strcat(filepath, result_of_call);*/

                    int fd = open(filepathstring, O_RDWR);

                    //printf("this is the file descriptor that i got %d\n", fd);

                    //int c = getchar();

                    int bytes_read, bytes_written;

                    while(1)
                    {
                        bytes_read = read(fd, mybuffer, sizeof(mybuffer));

                        if(bytes_read <= 0) 
                            break;

                        printf("Bytes read: %d\n", bytes_read);
                        // another if goes here to check for errors if they have occured; I have not done this as our program is mostly predictable, being this small
                        // also I'm lazy :D

                        void *p = mybuffer;
                        while(bytes_read > 0)
                        {
                            bytes_written = write(newsockfd, p, bytes_read);
                            printf("Bytes written: %d\n", bytes_written);
                            // handle errors here like we did before at the read section

                            bytes_read -= bytes_written;
                            p += bytes_written;
                        }
                    }

                    close(fd);
                    //close(newsockfd);

                    getchar();
                    char endbuffer[1000];
                    int k = 0;
                    for(k; k < 1000; k++)
                        endbuffer[k] = 'e';
                    
                    n = write(newsockfd, endbuffer, sizeof(endbuffer));
                    printf("File transfer completerino");
                }

                close(newsockfd);
                close(sockfd);
            }
        }
        /*else
        {
            printf("ERROR: Fork failed");
            close(newsockfd);
            close(sockfd);
            return;
        }*/
    }
}

int main(int argc, char *argv[])
{
    #if CREATE_FILES
        createFiles();
    #endif

    constructDatabase();

    doServerStuff(argc, argv);    // Make more arguments here and source them from command line
   
    return 0;
}