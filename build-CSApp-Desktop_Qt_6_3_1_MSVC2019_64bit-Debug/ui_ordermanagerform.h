/********************************************************************************
** Form generated from reading UI file 'ordermanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMANAGERFORM_H
#define UI_ORDERMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderManagerForm
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSplitter *splitter;
    QTableView *tableView;
    QToolBox *toolBox;
    QWidget *inputPage;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *ClientW;
    QTreeWidget *ProductW;
    QFormLayout *clientFormLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QComboBox *clientcombo;
    QComboBox *productcombo;
    QLabel *PriceLabel;
    QLineEdit *PriceLineEdit;
    QLabel *CountLabel;
    QSpinBox *countspin;
    QLabel *TotalLabel;
    QLineEdit *TotalLineEdit;
    QLabel *productNameLabel;
    QHBoxLayout *addHorizontalLayout;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QWidget *searchPage;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTableView *serchTableView;
    QHBoxLayout *horizontalLayout;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;

    void setupUi(QWidget *OrderManagerForm)
    {
        if (OrderManagerForm->objectName().isEmpty())
            OrderManagerForm->setObjectName(QString::fromUtf8("OrderManagerForm"));
        OrderManagerForm->resize(652, 443);
        gridLayout = new QGridLayout(OrderManagerForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_2 = new QSplitter(OrderManagerForm);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\355\234\264\353\250\274\353\221\245\352\267\274\355\227\244\353\223\234\353\235\274\354\235\270")});
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        splitter_2->addWidget(layoutWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setStretchLastSection(true);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        inputPage->setGeometry(QRect(0, 0, 326, 354));
        verticalLayout_4 = new QVBoxLayout(inputPage);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout_4->addLayout(verticalLayout_2);

        ClientW = new QTreeWidget(inputPage);
        ClientW->setObjectName(QString::fromUtf8("ClientW"));

        verticalLayout_4->addWidget(ClientW);

        ProductW = new QTreeWidget(inputPage);
        ProductW->setObjectName(QString::fromUtf8("ProductW"));

        verticalLayout_4->addWidget(ProductW);

        clientFormLayout = new QFormLayout();
        clientFormLayout->setObjectName(QString::fromUtf8("clientFormLayout"));
        idLabel = new QLabel(inputPage);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        clientFormLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(inputPage);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setReadOnly(true);

        clientFormLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(inputPage);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        clientFormLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        clientcombo = new QComboBox(inputPage);
        clientcombo->setObjectName(QString::fromUtf8("clientcombo"));

        clientFormLayout->setWidget(1, QFormLayout::FieldRole, clientcombo);

        productcombo = new QComboBox(inputPage);
        productcombo->setObjectName(QString::fromUtf8("productcombo"));

        clientFormLayout->setWidget(2, QFormLayout::FieldRole, productcombo);

        PriceLabel = new QLabel(inputPage);
        PriceLabel->setObjectName(QString::fromUtf8("PriceLabel"));

        clientFormLayout->setWidget(3, QFormLayout::LabelRole, PriceLabel);

        PriceLineEdit = new QLineEdit(inputPage);
        PriceLineEdit->setObjectName(QString::fromUtf8("PriceLineEdit"));

        clientFormLayout->setWidget(3, QFormLayout::FieldRole, PriceLineEdit);

        CountLabel = new QLabel(inputPage);
        CountLabel->setObjectName(QString::fromUtf8("CountLabel"));

        clientFormLayout->setWidget(4, QFormLayout::LabelRole, CountLabel);

        countspin = new QSpinBox(inputPage);
        countspin->setObjectName(QString::fromUtf8("countspin"));

        clientFormLayout->setWidget(4, QFormLayout::FieldRole, countspin);

        TotalLabel = new QLabel(inputPage);
        TotalLabel->setObjectName(QString::fromUtf8("TotalLabel"));

        clientFormLayout->setWidget(6, QFormLayout::LabelRole, TotalLabel);

        TotalLineEdit = new QLineEdit(inputPage);
        TotalLineEdit->setObjectName(QString::fromUtf8("TotalLineEdit"));

        clientFormLayout->setWidget(6, QFormLayout::FieldRole, TotalLineEdit);

        productNameLabel = new QLabel(inputPage);
        productNameLabel->setObjectName(QString::fromUtf8("productNameLabel"));

        clientFormLayout->setWidget(2, QFormLayout::LabelRole, productNameLabel);


        verticalLayout_4->addLayout(clientFormLayout);

        addHorizontalLayout = new QHBoxLayout();
        addHorizontalLayout->setObjectName(QString::fromUtf8("addHorizontalLayout"));
        addPushButton = new QPushButton(inputPage);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        addHorizontalLayout->addWidget(addPushButton);

        modifyPushButton = new QPushButton(inputPage);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        addHorizontalLayout->addWidget(modifyPushButton);


        verticalLayout_4->addLayout(addHorizontalLayout);

        toolBox->addItem(inputPage, QString::fromUtf8("&Input"));
        searchPage = new QWidget();
        searchPage->setObjectName(QString::fromUtf8("searchPage"));
        searchPage->setGeometry(QRect(0, 0, 326, 354));
        verticalLayout_5 = new QVBoxLayout(searchPage);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        serchTableView = new QTableView(searchPage);
        serchTableView->setObjectName(QString::fromUtf8("serchTableView"));
        serchTableView->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(serchTableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchComboBox = new QComboBox(searchPage);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));

        horizontalLayout->addWidget(searchComboBox);

        searchLineEdit = new QLineEdit(searchPage);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        horizontalLayout->addWidget(searchLineEdit);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);

        searchPushButton = new QPushButton(searchPage);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));

        verticalLayout_3->addWidget(searchPushButton);


        verticalLayout_5->addLayout(verticalLayout_3);

        toolBox->addItem(searchPage, QString::fromUtf8("&Search"));
        splitter->addWidget(toolBox);
        splitter_2->addWidget(splitter);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        idLabel->setBuddy(idLineEdit);
        PriceLabel->setBuddy(PriceLineEdit);
        CountLabel->setBuddy(PriceLineEdit);
        TotalLabel->setBuddy(PriceLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(OrderManagerForm);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(OrderManagerForm);
    } // setupUi

    void retranslateUi(QWidget *OrderManagerForm)
    {
        OrderManagerForm->setWindowTitle(QCoreApplication::translate("OrderManagerForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("OrderManagerForm", "Order", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = ClientW->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("OrderManagerForm", "PhoneNumber", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("OrderManagerForm", "ClientName", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("OrderManagerForm", "ID", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = ProductW->headerItem();
        ___qtreewidgetitem1->setText(4, QCoreApplication::translate("OrderManagerForm", "Stock", nullptr));
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("OrderManagerForm", "Type", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("OrderManagerForm", "ProductName", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("OrderManagerForm", "ID", nullptr));
        idLabel->setText(QCoreApplication::translate("OrderManagerForm", "I&D", nullptr));
        nameLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Name", nullptr));
        PriceLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Price", nullptr));
        CountLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Count", nullptr));
        TotalLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Total", nullptr));
        productNameLabel->setText(QCoreApplication::translate("OrderManagerForm", "&ProductName", nullptr));
        addPushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Modify", nullptr));
        toolBox->setItemText(toolBox->indexOf(inputPage), QCoreApplication::translate("OrderManagerForm", "&Input", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "ProductName", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        searchComboBox->setItemText(4, QCoreApplication::translate("OrderManagerForm", "Count", nullptr));

        searchPushButton->setText(QCoreApplication::translate("OrderManagerForm", "S&earch", nullptr));
        toolBox->setItemText(toolBox->indexOf(searchPage), QCoreApplication::translate("OrderManagerForm", "&Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderManagerForm: public Ui_OrderManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMANAGERFORM_H
