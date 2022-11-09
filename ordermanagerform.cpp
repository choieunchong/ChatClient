#include "ordermanagerform.h"
#include "orderitem.h"
#include "ui_ordermanagerform.h"

#include <QMenu>
#include <QFile>
#include <QString>
#include <QSqlTableModel>
#include<QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>

OrderManagerForm::OrderManagerForm(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
    connect(ui->addPushButton, SIGNAL(pressed()), this, SLOT(on_addButton_Clicked()));
    connect(ui->countspin, SIGNAL(textChanged(QString)),this, SLOT(total(QString)));
}

void OrderManagerForm::addProduct(int id, QString name)
{
    productIDList << id;
    ui->productcombo->addItem(name);
}

void OrderManagerForm::addClient(int id, QString name)
{
    clientIDList << id;
    ui->clientcombo->addItem(name);
}

void OrderManagerForm::total(QString total)
{
    int b= ui->PriceLineEdit->text().toInt() * ui->countspin->text().toInt();
    ui->TotalLineEdit->setText(QString::number(b));
}

void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->tableView->mapToGlobal(pos);
    menu->exec(globalPos);
}

void OrderManagerForm::on_addButton_Clicked()
{
    //  QString ClientName,ProductName, Price, Count, Total;//= ;;
    int id = makeId();
    int cid,pid, Price, Count, Total;;
    cid = clientIDList[ui->clientcombo->currentIndex()];
    pid = productIDList[ui->productcombo->currentIndex()];
    Price = ui->PriceLineEdit->text().toInt();
    Count = ui->countspin->text().toInt();
    Total = ui->TotalLineEdit->text().toInt();
    QString cname = ui->clientcombo->itemText(clientIDList.indexOf(cid));
    QString pname = ui->productcombo->itemText(productIDList.indexOf(pid));

    if(cname.length()) {
        QSqlQuery query(orderModel->database());
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?)");
        query.bindValue(0, id);
        query.bindValue(1, cname);
        query.bindValue(2, pname);
        query.bindValue(3, Price);
        query.bindValue(4, Count);
        query.bindValue(5, Total);
        query.exec();
        orderModel->select();
        ui->tableView->resizeColumnsToContents();

    }
}

int OrderManagerForm::makeId() //주문정보의 아이디 생성후 증가 방법
{
    if(OrderList.size( ) == 0) {
        return 100;
    } else {
        auto id = OrderList.lastKey();
        return ++id;
    }
}

void OrderManagerForm::loadData() //주문정보에 txt파일로 저장하기 위한 함수
{
    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("orderlist.db");
    if (db.open( )) {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS client(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, phoneNumber VARCHAR(20) NOT NULL, address VARCHAR(50));");
        orderModel = new QSqlTableModel();
        orderModel->setTable("order");
        orderModel->select();
        orderModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        orderModel->setHeaderData(1, Qt::Horizontal, tr("cName"));
        orderModel->setHeaderData(2, Qt::Horizontal, tr("pname"));
        orderModel->setHeaderData(3, Qt::Horizontal, tr("price"));
        orderModel->setHeaderData(3, Qt::Horizontal, tr("count"));
        orderModel->setHeaderData(3, Qt::Horizontal, tr("total"));

        ui->tableView->setModel(orderModel);
        ui->tableView->resizeColumnsToContents();
    }

    for(int i = 0; i < orderModel->rowCount(); i++) {
        int id = orderModel->data(orderModel->index(i, 0)).toInt();
        QString name = orderModel->data(orderModel->index(i, 1)).toString();

    }
}

OrderManagerForm::~OrderManagerForm() //소멸자 종료될때 order.txt파일에 orderlist가 저장된다.
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("orderConnection");
    if(db.isOpen()) {
        orderModel->submitAll();
        db.close();
        QSqlDatabase::removeDatabase("orderConnection");
    }
}


void OrderManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column) //treeWidget에 item이 클릭이 될때 럼 위치에 아이디,
{                                                                                   // client이름, product이름, 가격, 개수를 불러온다.
    Q_UNUSED(column);
    emit getClientInfo(clientIDList[ui->clientcombo->findText(item->text(1))]);
    emit getProductInfo(productIDList[ui->productcombo->findText(item->text(2))]);
    ui->idLineEdit->setText(item->text(0));
    ui->clientcombo->setCurrentText(item->text(1));
    ui->productcombo->setCurrentText(item->text(2));
    ui->PriceLineEdit->setText(item->text(3));
    ui->countspin->setValue(item->text(4).toInt());
    ui->toolBox->setCurrentIndex(0);
}

void OrderManagerForm::removeItem() // 우 클릭을 할때 제거 액션 함수
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid() ) {
        orderModel->removeRow(index.row());
        orderModel->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void OrderManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
    //    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = orderModel->match(orderModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));


    foreach(auto ix, indexes) {
        int id = orderModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString cname = orderModel->data(ix.siblingAtColumn(1)).toString();
        QString pname = orderModel->data(ix.siblingAtColumn(2)).toString();
        QString price = orderModel->data(ix.siblingAtColumn(3)).toString();
        QString count = orderModel->data(ix.siblingAtColumn(4)).toString();
        QString total = orderModel->data(ix.siblingAtColumn(5)).toString();
        QStringList strings;
        strings << QString::number(id) << cname << pname << price << count << total;
        new QTreeWidgetItem(ui->searchTreeWidget, strings);
        for(int i = 0; i < ui->searchTreeWidget->columnCount(); i++)
            ui->searchTreeWidget->resizeColumnToContents(i);

    }
}

void OrderManagerForm::on_ClientW_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->clientcombo->setCurrentText(item->text(1));
}


void OrderManagerForm::on_ProductW_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->productcombo->setCurrentText(item->text(2));
    ui->PriceLineEdit->setText(item->text(3));
}


void OrderManagerForm::on_modifyPushButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        //      int key = item->text(0).toInt();
        // orderitem* o = OrderList[key];
        QString Clientname, Productname;
        int price,count;
        Clientname = ui->clientcombo->currentText();
        Productname = ui->productcombo->currentText();
        price = ui->PriceLineEdit->text().toInt();
        count = ui->countspin->text().toInt();
        orderModel->setData(index.siblingAtColumn(1), Clientname);
        orderModel->setData(index.siblingAtColumn(2), Productname);
        orderModel->setData(index.siblingAtColumn(3), price);
        orderModel->setData(index.siblingAtColumn(4), count);
        orderModel->submit();

        orderModel->select();
        ui->tableView->resizeColumnsToContents();
    }
}


void OrderManagerForm::on_clientcombo_currentIndexChanged(int index)
{
    emit getClientInfo(clientIDList[index]);
}




void OrderManagerForm::on_productcombo_currentIndexChanged(int index)
{
    emit getProductInfo(productIDList[index]);
}


void OrderManagerForm::on_countspin_valueChanged(int arg1)
{
    ui->TotalLineEdit->setText(QString::number(arg1 * ui->PriceLineEdit->text().toInt()));
}

