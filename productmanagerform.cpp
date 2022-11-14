#include "productmanagerform.h"
#include "ui_productmanagerform.h"

#include <QMenu>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QStandardItemModel>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 640 << 300;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    searchModel = new QStandardItemModel(0, 4);
    searchModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    searchModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    searchModel->setHeaderData(2, Qt::Horizontal, tr("Type"));
    searchModel->setHeaderData(3, Qt::Horizontal, tr("Price"));
    searchModel->setHeaderData(4, Qt::Horizontal, tr("Stock"));
    ui->serchtableView->setModel(searchModel);
     ui->tableView->resizeColumnsToContents();
}

void ProductManagerForm::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","productConnection");
    db.setDatabaseName("product.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS product(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, "
                   "type VARCHAR(20) NOT NULL, price number(20), stock number(20));");

        productModel = new QSqlTableModel(this, db);
        productModel->setTable("product");
        productModel->select();
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("type"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("price"));
        productModel->setHeaderData(4, Qt::Horizontal, tr("stock"));

        ui->tableView->setModel(productModel);
        ui->tableView->resizeColumnsToContents();
    }

    for(int i = 0; i < productModel->rowCount(); i++) {
        int id = productModel->data(productModel->index(i, 0)).toInt();
        QString name = productModel->data(productModel->index(i, 1)).toString();
        QString type = productModel ->data(productModel->index(i,2)).toString();
        int price = productModel ->data(productModel->index(i,3)).toInt();
        int stock = productModel ->data(productModel->index(i,4)).toInt();
        emit productAdded(id, name, type, price, stock);
    }
}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("productConnection");
    if(db.isOpen()) {
        productModel->submitAll();
        delete productModel;
        db.close();
    }
}

int ProductManagerForm::makeId( )
{
    if(productModel->rowCount() == 0) {
        return 100;
    } else {
        auto id = productModel->data(productModel->index(productModel->rowCount()-1, 0)).toInt();
        return ++id;
    }
}

void ProductManagerForm::removeItem()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        //clientList.remove(clientModel->data(index.siblingAtColumn(0)).toInt());
        productModel->removeRow(index.row());
        productModel->select();
        ui->tableView->resizeColumnsToContents();
    }else {
        QMessageBox::warning(this, tr("Product Manager"), tr("No Item is selected"));
    }
     emit productRemove(index.row());
}

void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->tableView->mapToGlobal(pos);
    if(ui->tableView->indexAt(pos).isValid())
        menu->exec(globalPos);
}

void ProductManagerForm::on_searchPushButton_clicked()
{
    searchModel->clear();
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = productModel->match(productModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) {
        int id = productModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString name = productModel->data(ix.siblingAtColumn(1)).toString();
        QString type = productModel->data(ix.siblingAtColumn(2)).toString();
        QString price = productModel->data(ix.siblingAtColumn(3)).toString();
        QString stock =  productModel->data(ix.siblingAtColumn(4)).toString();
        QStringList strings;
        strings << QString::number(id) << name << type << price<< stock;

        QList<QStandardItem *> items;
        for (int i = 0; i < 4; ++i) {
            items.append(new QStandardItem(strings.at(i)));
        }
        searchModel->appendRow(items); 
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("type"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("price"));
        productModel->setHeaderData(4, Qt::Horizontal, tr("stock"));
        ui->serchtableView->resizeColumnsToContents();
    }

}


void ProductManagerForm::on_addPushButton_clicked()
{
    QString name, type;
    int    price, stock;
    int id = makeId( );
    name = ui->ProductNameLineEdit->text();
    type = ui->typeLineEdit->text();
    price = ui->PriceLineEdit->text().toInt();
    stock = ui-> stockspinBox->text().toInt();

    QSqlDatabase db = QSqlDatabase::database("productConnection");

    if(name.length()) {
        QSqlQuery query(productModel->database());
        query.prepare("INSERT INTO product VALUES (:id, :name, :type, :price, :stock)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":type", type);
        query.bindValue(":price", price);
        query.bindValue(":stock", stock);
        query.exec();
        productModel->select();
        ui->tableView->resizeColumnsToContents();
        emit productAdded(id, name, type, price, stock);
    }
}


void ProductManagerForm::on_modifyPushButton_clicked()
{
    QModelIndex index  = ui->tableView->currentIndex(); //tableview에 index담기
    if(index.isValid()) {
        //        int id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString name, type;
        int id ;
        int price, stock;
        id = ui->idLineEdit->text().toInt();
        name = ui->ProductNameLineEdit->text();
        type = ui->typeLineEdit->text();
        price = ui->PriceLineEdit->text().toInt();
        stock = ui->stockspinBox->text().toInt();

        productModel->setData(index.siblingAtColumn(0), id);
        productModel->setData(index.siblingAtColumn(1), name);
        productModel->setData(index.siblingAtColumn(2), type);
        productModel->setData(index.siblingAtColumn(3), price);
        productModel->setData(index.siblingAtColumn(4), stock);
        productModel->submit();

        ui->tableView->resizeColumnsToContents();
        emit productRemove(index.row());
         emit productAdded(id, name, type, price, stock);
    }
}

void ProductManagerForm::acceptProductInfo(int key)
{
    QModelIndexList indexes = productModel->match(productModel->index(0, 0), Qt::EditRole, key, -1, Qt::MatchFlags(Qt::MatchCaseSensitive));

    foreach(auto index, indexes) {
        //    QModelIndex index = clientList[key];
        QString name = productModel->data(index.siblingAtColumn(1)).toString();
        QString type = productModel->data(index.siblingAtColumn(2)).toString();
        int price = productModel->data(index.siblingAtColumn(3)).toInt();
        int stock = productModel->data(index.siblingAtColumn(4)).toInt();
        emit sendProductInfo(name, type, price, stock);
    }
}


void ProductManagerForm::on_tableView_clicked(const QModelIndex &index)
{
    int id = productModel->data(index.siblingAtColumn(0)).toInt();
    QString name = productModel->data(index.siblingAtColumn(1)).toString();
    QString type = productModel->data(index.siblingAtColumn(2)).toString();
    int price = productModel->data(index.siblingAtColumn(3)).toInt();
    int stock = productModel->data(index.siblingAtColumn(4)).toInt();

    ui->idLineEdit->setText(QString::number(id));
    ui->ProductNameLineEdit->setText(name);
    ui->typeLineEdit->setText(type);
    ui->PriceLineEdit->setText(QString::number(price));
    ui->stockspinBox->setValue(stock);
    ui->toolBox->setCurrentIndex(0);
}

