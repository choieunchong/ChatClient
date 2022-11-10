#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include <QWidget>
#include "clientmanagerform.h"
#include "productmanagerform.h"

class orderitem;
class QMenu;
class QTreeWidgetItem;
class QSqlTableModel;

namespace Ui {
class OrderManagerForm;

}


class OrderManagerForm : public QWidget
{
    Q_OBJECT
public:
    explicit OrderManagerForm(QWidget *parent = nullptr);
    ~OrderManagerForm();
    void loadData();
    ClientManagerForm *client;
    ProductManagerForm *product;

public slots:
    void addClient(int, QString);
    void addProduct(int, QString);
    void getClientInfo( QString, QString, QString);     // 응답
    void getProductInfo( QString, QString, int, int);     // 응답

private slots:
   // void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_searchPushButton_clicked();
    void showContextMenu(const QPoint &);
    void removeItem();
    void total(QString);

    void on_ClientW_itemClicked(QTreeWidgetItem *item, int column);
    void on_ProductW_itemClicked(QTreeWidgetItem *item, int column);
    void on_modifyPushButton_clicked();

    void on_clientcombo_currentIndexChanged(int index);
    void on_productcombo_currentIndexChanged(int index);
    void on_countspin_valueChanged(int arg1);

    void on_addPushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

signals:
    void datasant(QString);
    void getClientInfo(int);            // 요청
    void getProductInfo(int);           // 요청
private:
    Ui::OrderManagerForm* ui;
    QMap<int, orderitem*> OrderList;
    int makeId();
    QMenu* menu;
    QList<int> clientIDList;
    QList<int> productIDList;
    QSqlTableModel* orderModel;

};

#endif // ORDERMANAGERFORM_H
