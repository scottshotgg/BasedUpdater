        /* INCLUDES */

#include "basedupdater.h"
#include "ui_basedupdater.h"
#include <QFileDialog>
#include <QMessageBox>
#include "aboutdialog.h"
#include <QtGui>
#include <QGridLayout>
#include <winsock2.h>
#include <fstream>
#include <iostream>
#include <io.h>
#include <fcntl.h>

        /* VARIABLES */

WSADATA wsa;
SOCKET s;
struct sockaddr_in server;
char *message, server_reply[2000];
int recv_size;

        /* FUNCTIONS */

void startDownloadProcess();
int receive_file();

BasedUpdater::BasedUpdater(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasedUpdater)
{
    ui->setupUi(this);
}

BasedUpdater::~BasedUpdater()
{
    delete ui;
}

void BasedUpdater::on_pushButton_clicked()
{
   if(ui->pushButton->text() == "Browse")
   {
        QString filePath = QFileDialog::getExistingDirectory(this, tr("Open File"));
        ui->filePath_lineEdit->setText(filePath);
        if(ui->filePath_lineEdit->text() != "")
        {
            ui->pushButton->setText("Get BASED");
            ui->pushButton->adjustSize();
        }
   }
   else
   {
       // do some function to start the download process

       startDownloadProcess();
   }
}

void BasedUpdater::on_actionAbout_triggered()
{
    //QMessageBox::information(this, "title", "Hello");

    AboutDialog about;
    about.setModal(true);
    about.setWindowTitle("About BasedUpdater");
    about.setWindowFlags(Qt::WindowCloseButtonHint);
    about.setMaximumSize(250, 150);
    about.setMinimumSize(250, 150);
    /*QLabel *aboutLabel = new QLabel("Sup");
    aboutLabel->adjustSize();
    aboutLabel->move(0, 0);
    aboutLabel->show();

    QGridLayout *gridLayout = new QGridLayout();

    about.setLayout(gridLayout);*/
    about.exec();
}

void BasedUpdater::on_filePath_lineEdit_textEdited(const QString &arg1)
{
    //if(ui->filePath_lineEdit->text() == "")
    {
        // this should be a check that constantly checks the directory location
        ui->pushButton->setText("Browse");
        ui->pushButton->adjustSize();
    }
}

void startDownloadProcess()
{
        qDebug("\nInitialising Winsock...");

        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            qDebug("Failed. Error Code : %d",WSAGetLastError());
            return;
        }

        qDebug("Initialised.\n");

        //Create a socket
        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            qDebug("Could not create socket : %d" , WSAGetLastError());
        }

        qDebug("Socket created.\n");


        server.sin_addr.s_addr = inet_addr("192.168.1.108");    // Change the IP when the server gets set up
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);

        //Connect to remote server
        if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)     // Uncomment this when the server is set up
        {
            qDebug("connect error");
            return;
        }

        qDebug("Connected");

        //Send some data
        message =  "hello.txt";

        if( send(s , message , strlen(message) , 0) < 0)
        {
            qDebug("Send failed");
            return;
        }

        qDebug("Data Send\n");

        receive_file();

        closesocket(s);
        WSACleanup();
}

int receive_file()
{
    int bytes_read = 0, bytes_written = 0;
    char mybuffer[1000];
    int fd = _open("bfile.txt", _O_RDWR | _O_CREAT, 777);

    while(1)
    {
        bytes_read = recv(s, mybuffer, 1000, 0);
        bytes_written = _write(fd, mybuffer, bytes_read);

        if(bytes_read == 0)
            break;

        qDebug("Bytes read: %d\nBytes written: %d\n", bytes_read, bytes_written);
    }

    close(fd);

    return(0);
}
