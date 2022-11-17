#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
//#include "clientitem.h"

#include <QFile>
#include <QMenu>
#include <QSqlTableModel>
#include<QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStandardItemModel>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400; //client의 sizes 값
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove")); //client의 삭제액션
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem())); //client의 삭제액션을 누를때 clientItem삭제

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint))); //tableview에 보여주기 위한 connet
    connect(ui->searchLineEdit, SIGNAL(returnPressed()), // 검색버튼과 연결하기 위한 connet
            this, SLOT(on_searchPushButton_clicked()));

    searchModel = new QStandardItemModel(0, 4); //model에 client정보를 저장한다.
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
    ui->serchTableView->setModel(searchModel);

}

void ClientManagerForm::loadData() //clientItem의 db파일을 불러오기 위한 함수
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","clientConnection"); //sqlLite에 저장하기 위해 Qt에 내장된 sqlLite에 접근한다.
    db.setDatabaseName("client.db");
    if(db.open()){
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS client(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, "
                   "phoneNumber VARCHAR(20) NOT NULL, address VARCHAR(50));");

        clientModel = new QSqlTableModel(this, db);
        clientModel->setTable("client");
        clientModel->select();
        clientModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        clientModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        clientModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Phone Number"));
        clientModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Address"));

        ui->tableView->setModel(clientModel);
        ui->tableView->resizeColumnsToContents();
    }

    for(int i = 0; i < clientModel->rowCount(); i++) { //clientmoel의 row를 돌며 data를 가져온다.
        int id = clientModel->data(clientModel->index(i, 0)).toInt();
        QString name = clientModel->data(clientModel->index(i, 1)).toString();
        QString number = clientModel->data(clientModel->index(i, 2)).toString();
        QString address = clientModel->data(clientModel->index(i, 3)).toString();
        emit clientAdded(id,name, number, address);
    }

}

ClientManagerForm::~ClientManagerForm() // 소멸자
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("clientConnection"); //clientConnection에 접근한다.
    if(db.isOpen()) {
        clientModel->submitAll();
        db.close();
        QSqlDatabase::removeDatabase("clientConnection");
    }
}


int ClientManagerForm::makeId( ) //아이디 만듬
{
    if(clientModel->rowCount() == 0) {
        return 100;
    } else {
        auto id = clientModel->data(clientModel->index(clientModel->rowCount()-1, 0)).toInt();
        return ++id;
    }
}

void ClientManagerForm::removeItem() //삭제
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        clientModel->removeRow(index.row());
        clientModel->select();
        ui->tableView->resizeColumnsToContents();
        emit clientRemove(index.row());
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->tableView->mapToGlobal(pos);
    if(ui->tableView->indexAt(pos).isValid())
        menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked() //검색 버튼을 눌렀을 때
{
    searchModel->clear();
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = clientModel->match(clientModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) { //client model indexe에 접근한다.
        int id = clientModel->data(ix.siblingAtColumn(0)).toInt(); //c->id(); row에 해당하는 data에 접근한다.
        QString name = clientModel->data(ix.siblingAtColumn(1)).toString();
        QString number = clientModel->data(ix.siblingAtColumn(2)).toString();
        QString address = clientModel->data(ix.siblingAtColumn(3)).toString();
        QStringList strings;
        strings << QString::number(id) << name << number << address;

        QList<QStandardItem *> items; //item을 돌며 item을 보낸다.
        for (int i = 0; i < 4; ++i) {
            items.append(new QStandardItem(strings.at(i)));
        }
        searchModel->appendRow(items);
        searchModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        searchModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        searchModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Phone Number"));
        searchModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Address"));

        ui->serchTableView->resizeColumnsToContents();
    }

}

void ClientManagerForm::on_modifyPushButton_clicked() // 수정 클릭
{
    QModelIndex index = ui->tableView->currentIndex();// 해당하는 index접근한다.
    if(index.isValid()) {
        //      int id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString  name, number, address;
        int id ;
        id = ui->idLineEdit->text().toInt();
        name = ui->nameLineEdit->text();
        number = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();

        clientModel->setData(index.siblingAtColumn(0), id); //client model에 해당하는 row에 접근한다.
        clientModel->setData(index.siblingAtColumn(1), name);
        clientModel->setData(index.siblingAtColumn(2), number);
        clientModel->setData(index.siblingAtColumn(3), address);
        clientModel->submit();

        //        clientModel->select();
        ui->tableView->resizeColumnsToContents();
        emit clientRemove(index.row());
        emit clientAdded(id, name, number, address);
    }
}

void ClientManagerForm::on_addPushButton_clicked() //addPushbutton을 눌렀을때 name, number, address를 추가한다.
{
    QString name, number, address;
    int id = makeId( );
    ui->idLineEdit->setText(QString::number(id));
    name = ui->nameLineEdit->text();
    number = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();

    QSqlDatabase db = QSqlDatabase::database("clientConnection");

    if(db.isOpen()&&name.length()) { //db 연결 예외처리
        QSqlQuery query(clientModel->database()); //query를 생성한후 database에 저장한다.
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?)"); //db query 접근
        query.bindValue(0, id);
        query.bindValue(1, name);
        query.bindValue(2, number);
        query.bindValue(3, address);
        query.exec();
        clientModel->select();
        ui->tableView->resizeColumnsToContents();
        emit clientAdded(id, name, number, address);
    }
}

void ClientManagerForm::acceptClientInfo(int key) //client의 정보를 connect할 함수
{
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 0), Qt::EditRole, key, -1, Qt::MatchFlags(Qt::MatchCaseSensitive));

    foreach(auto index, indexes) {
        //    QModelIndex index = clientList[key];
        QString name = clientModel->data(index.siblingAtColumn(1)).toString();
        QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
        QString address = clientModel->data(index.siblingAtColumn(3)).toString();
        emit sendClientInfo(name, phoneNumber, address);
    }
}

void ClientManagerForm::on_tableView_clicked(const QModelIndex &index) //model에 저장된 정보를 tableview에 보여주며 tableview를 clicked할때 액션을 주기위한 함수
{
    QString id = clientModel->data(index.siblingAtColumn(0)).toString();
    QString name = clientModel->data(index.siblingAtColumn(1)).toString();
    QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
    QString address = clientModel->data(index.siblingAtColumn(3)).toString();

    ui->idLineEdit->setText(id);
    ui->nameLineEdit->setText(name);
    ui->phoneNumberLineEdit->setText(phoneNumber);
    ui->addressLineEdit->setText(address);
    ui->toolBox->setCurrentIndex(0);
}

