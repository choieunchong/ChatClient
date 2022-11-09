#include "chatserverform.h"
#include "ui_chatserverform.h"
#include "logthread.h"


#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QMenu>
#include <QFile>
#include <QFileInfo>
#include <QProgressDialog>

ChatServerForm::ChatServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatserverForm), totalSize(0), byteReceived(0)
{
    ui->setupUi(this); //ui 만들기
    QList<int> sizes; //사이즈 설정
    sizes << 120 << 500;
    ui->splitter->setSizes(sizes); //스플리터로 마우스로 조정 가능

    chatServer = new QTcpServer(this);
    connect(chatServer, SIGNAL(newConnection( )), SLOT(clientConnect( ))); //connect로 고객연결
    if (!chatServer->listen(QHostAddress::Any, PORT_NUMBER)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(chatServer->errorString( )));
        close( );
        return;
    }

    fileServer = new QTcpServer(this); //파일을 주고 받기 위한 fileServer생성
    connect(fileServer, SIGNAL(newConnection()),SLOT(acceptConnection())); //파일을 연결하기 위한 connect
    if(!fileServer->listen(QHostAddress::Any, PORT_NUMBER+1)){
        QMessageBox::critical(this, tr("chatting Server"),
                              tr("Unable to start the server: %1.").arg(fileServer->errorString()));
        close();
        return;
    }

    qDebug("Start listening ...");

    QAction* inviteAction = new QAction(tr("&Invite")); //초대 액션이 일어났을때
    inviteAction->setObjectName("Invite");
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));

    QAction* removeAction = new QAction(tr("&Kick out")); //강퇴 액션
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));


    QPushButton* connectbutton = new QPushButton(tr("&connectbutton")); // 초대 버튼
    connectbutton->setObjectName("connectbutton");
    connect(connectbutton, SIGNAL(clicked()), SLOT(inviteClient())); //초대 버튼 connet연결


    QPushButton* exitbuton = new QPushButton(tr("&exit")); // 강퇴버튼
    connect(exitbuton, SIGNAL(clicked()), SLOT(kickOut())); // connect로 강퇴버튼 연결

    menu = new QMenu;
    menu->addAction(inviteAction); // 초대 액션
    menu->addAction(removeAction); // 퇴장 액션

    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    progressDialog = new QProgressDialog(0); //file 보낼때 progressDialog 시각화
    progressDialog->setAutoClose(true);
    progressDialog->reset(); //완료 되었다면 reset

    logThread = new LogThread(this);
    logThread->start();

    connect(ui->savebutton, SIGNAL(clicked()), logThread, SLOT(saveData())); // server에 저장된 데이터를 저장하기 위한 connect

    qDebug() << tr("The server is running on port %1.").arg(chatServer->serverPort( ));
}

ChatServerForm::~ChatServerForm()
{
    delete ui;
    logThread->terminate();  //소멸자
    chatServer->close();    // 채팅닫기
    fileServer->close( );   // 파일 닫기
}

void ChatServerForm::message()
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    qDebug("입력중~");
}

void ChatServerForm::acceptConnection() // client를 연결하귀 위한 함수
{
    qDebug("Connected, preparing to receive files!");

    QTcpSocket* receivedSocket = fileServer->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void ChatServerForm::clientConnect( )
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug("new connection is established...");
}

void ChatServerForm::receiveData( )
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( )); //TcpSoket 연결 형변환
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE); //1024데이터를 읽어온다

    Chat_Status type;       // 채팅의 목적
    char data[1020];        // 전송되는 메시지/데이터
    memset(data, 0, 1020);

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);
    in >> type;
    in.readRawData(data, 1020);

    QString ip = clientConnection->peerAddress().toString();
    quint16 port = clientConnection->peerPort();
    QString name = QString::fromStdString(data);

    qDebug() << ip << " : " << type;

    switch(type) {
    case Chat_Login:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(1) != "O") {
                item->setIcon(0, QIcon(":/image/redpoint.png"));     // QList<QTcpSocket*> clientList;
            }
            clientSocketHash[name] = clientConnection;
        }
        break;
    case Chat_In:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(1) != "O") {
                item->setIcon(0, QIcon(":/image/greenpoint.png")); // 아이콘
            }
            clientNameHash[port] = name;
            if(clientSocketHash.contains(name))
                clientSocketHash[name] = clientConnection;
        }
        break;
    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            qDebug() << sock->peerPort();
            if(clientNameHash.contains(sock->peerPort()) && port != sock->peerPort()) {
                QByteArray sendArray;
                sendArray.clear();
                QDataStream out(&sendArray, QIODevice::WriteOnly);
                out << Chat_Talk;
                sendArray.append("<font color=lightsteelblue>");
                sendArray.append(clientNameHash[port].toStdString().data());
                sendArray.append("</font> : ");

                sendArray.append(name.toStdString().data());
                sock->write(sendArray);
                qDebug() << sock->peerPort();
            }
        }

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));
        item->setText(3, clientNameHash[port]);
        item->setText(4, QString(data));
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data));

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        logThread->appendData(item);
    }
        break;
    case Chat_Out:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "-") {
                item->setIcon(0, QIcon(":/image/redpoint.png"));
            }
            clientNameHash.remove(port);
        }
        break;
    case Chat_LogOut:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "X") {
                item->setIcon(0, QIcon(":/image/redpoint.png"));
            }
            clientSocketHash.remove(name);
        }
        break;
    case Chat_Chatting:
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            qDebug() << sock->peerPort();
            if(clientNameHash.contains(sock->peerPort()) && port != sock->peerPort()) {
                QByteArray sendArray;
                sendArray.clear();
                QDataStream out(&sendArray, QIODevice::WriteOnly);
                out << Chat_Chatting;
                sendArray.append(clientNameHash[port].toStdString().data());  
                sock->write(sendArray);
            }
        }break;
    }
}


void ChatServerForm::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    if(clientConnection != nullptr) {
        QString name = clientNameHash[clientConnection->peerPort()];
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            item->setIcon(0, QIcon(":/image/redpoint.png"));
        }
        clientSocketHash.remove(name);
        clientConnection->deleteLater();
    }
}

void ChatServerForm::addClient(int id, QString name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setIcon(0, QIcon(":/image/redpoint.png"));
    item->setText(1, name);
    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->clientTreeWidget->resizeColumnToContents(0);
}


/* 클라이언트 강퇴하기 */
void ChatServerForm::kickOut()
{
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_KickOut;
    out.writeRawData("", 1020);

    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[name];
    sock->write(sendArray);

    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/image/redpoint.png"));
}


/* 클라이언트 초대하기 */
void ChatServerForm::inviteClient()
{
     if(ui->clientTreeWidget->currentItem() !=nullptr){
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_Invite;
    out.writeRawData("", 1020);

    /* 소켓은 현재 선택된 아이템에 표시된 이름과 해쉬로 부터 가져온다. */
    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[name];
     if(sock != nullptr){
    sock->write(sendArray);

    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/image/bluepoint.png"));
     }
     }else{
         return;
     }
}



void ChatServerForm::on_exitbutton_clicked()
{

    if(ui->clientTreeWidget->currentItem() !=nullptr){
        QString name = ui->clientTreeWidget->currentItem()->text(1);
        QTcpSocket* sock = clientSocketHash[name];
        if(sock != nullptr){

            QByteArray sendArray;
            QDataStream out(&sendArray, QIODevice::WriteOnly);
            out << Chat_KickOut;
            out.writeRawData("", 1020);

            sock->write(sendArray);
            ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/image/redpoint.png"));
        }
    }
    else{
        return;
    }
}


void ChatServerForm::on_connectbutton_clicked()
{
    if(ui->clientTreeWidget->currentItem() !=nullptr){

        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << Chat_Invite;
        out.writeRawData("", 1020);

        /* 소켓은 현재 선택된 아이템에 표시된 이름과 해쉬로 부터 가져온다. */
        QString name = ui->clientTreeWidget->currentItem()->text(1);
        QTcpSocket* sock = clientSocketHash[name];
        if(sock != nullptr){
            sock->write(sendArray);

            ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/image/bluepoint.png"));
        }
    }
    else{
        return;
    }
}

void ChatServerForm::on_connectbutton_customContextMenuRequested(const QPoint &pos)
{
    if(ui->clientTreeWidget->currentItem())
    {
        foreach(QAction *action, menu->actions()) {
            if(action->objectName() == "connectbutton"){
                action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) != "O");
                action->setIconText(":/image/greenpoint.png");
            }

            else
            {
                action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "O");
                action->setIconText(":/image/greenpoint.png");
            }

        }
        QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
        menu->exec(globalPos);
    }
    else{
        return;
    }
}

/* 파일 전송 */
void ChatServerForm::readClient()
{
    qDebug("Receiving file ...");
    QTcpSocket* receivedSocket = dynamic_cast<QTcpSocket *>(sender( ));
    QString filename, name;

    if (byteReceived == 0) {        // 파일 전송 시작 : 파일에 대한 정보를 이용해서 QFile 객체 생성
        progressDialog->reset();
        progressDialog->show();

        QString ip = receivedSocket->peerAddress().toString();
        quint16 port = receivedSocket->peerPort();
        qDebug() << ip << " : " << port;

        QDataStream in(receivedSocket);
        in >> totalSize >> byteReceived >> filename >> name;
        progressDialog->setMaximum(totalSize);

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[name]));
        item->setText(3, name);
        item->setText(4, filename);
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, filename);

        /* 컨텐츠의 길이로 QTreeWidget의 헤더의 크기를 고정 */
        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);
        logThread->appendData(item);

        QFileInfo info(filename);
        QString currentFileName = info.fileName();
        file = new QFile(currentFileName);
        file->open(QFile::WriteOnly);
    } else {                    // 파일 데이터를 읽어서 저장
        inBlock = receivedSocket->readAll();

        byteReceived += inBlock.size();
        file->write(inBlock);
        file->flush();
    }

    progressDialog->setValue(byteReceived);

    if (byteReceived == totalSize) {        /* 파일의 다 읽으면 QFile 객체를 닫고 삭제 */
        qDebug() << QString("%1 receive completed").arg(filename);

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        progressDialog->reset();
        progressDialog->hide();

        file->close();
        delete file;
    }
}


void ChatServerForm::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->clientTreeWidget->currentItem()){
        foreach(QAction *action, menu->actions()) {
            if(action->objectName() == "Invite")        // 초대
                action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) != "O");
            else                                        // 강퇴
                action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "O");
        }
        QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
        menu->exec(globalPos);
    }else {
        return;
    }


}

