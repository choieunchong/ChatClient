/********************************************************************************
** Form generated from reading UI file 'clientmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTMANAGERFORM_H
#define UI_CLIENTMANAGERFORM_H

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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientManagerForm
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSplitter *splitter;
    QTableView *tableView;
    QToolBox *toolBox;
    QWidget *inputPage;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *clientFormLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *phoneNumberLabel;
    QLineEdit *phoneNumberLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QHBoxLayout *addHorizontalLayout;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QWidget *searchPage;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QTableView *serchTableView;
    QHBoxLayout *horizontalLayout;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;

    void setupUi(QWidget *ClientManagerForm)
    {
        if (ClientManagerForm->objectName().isEmpty())
            ClientManagerForm->setObjectName(QString::fromUtf8("ClientManagerForm"));
        ClientManagerForm->resize(643, 433);
        gridLayout_2 = new QGridLayout(ClientManagerForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(ClientManagerForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\355\234\264\353\250\274\353\221\245\352\267\274\355\227\244\353\223\234\353\235\274\354\235\270")});
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        splitter = new QSplitter(ClientManagerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGridStyle(Qt::SolidLine);
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setCascadingSectionResizes(false);
        tableView->verticalHeader()->setStretchLastSection(false);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        inputPage->setGeometry(QRect(0, 0, 322, 345));
        verticalLayout_2 = new QVBoxLayout(inputPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
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

        nameLineEdit = new QLineEdit(inputPage);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        clientFormLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        phoneNumberLabel = new QLabel(inputPage);
        phoneNumberLabel->setObjectName(QString::fromUtf8("phoneNumberLabel"));

        clientFormLayout->setWidget(2, QFormLayout::LabelRole, phoneNumberLabel);

        phoneNumberLineEdit = new QLineEdit(inputPage);
        phoneNumberLineEdit->setObjectName(QString::fromUtf8("phoneNumberLineEdit"));

        clientFormLayout->setWidget(2, QFormLayout::FieldRole, phoneNumberLineEdit);

        addressLabel = new QLabel(inputPage);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        clientFormLayout->setWidget(3, QFormLayout::LabelRole, addressLabel);

        addressLineEdit = new QLineEdit(inputPage);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));

        clientFormLayout->setWidget(3, QFormLayout::FieldRole, addressLineEdit);


        verticalLayout->addLayout(clientFormLayout);

        addHorizontalLayout = new QHBoxLayout();
        addHorizontalLayout->setObjectName(QString::fromUtf8("addHorizontalLayout"));
        addPushButton = new QPushButton(inputPage);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        addHorizontalLayout->addWidget(addPushButton);

        modifyPushButton = new QPushButton(inputPage);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        addHorizontalLayout->addWidget(modifyPushButton);


        verticalLayout->addLayout(addHorizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        toolBox->addItem(inputPage, QString::fromUtf8("&Input"));
        searchPage = new QWidget();
        searchPage->setObjectName(QString::fromUtf8("searchPage"));
        searchPage->setGeometry(QRect(0, 0, 322, 345));
        verticalLayout_3 = new QVBoxLayout(searchPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        serchTableView = new QTableView(searchPage);
        serchTableView->setObjectName(QString::fromUtf8("serchTableView"));
        serchTableView->horizontalHeader()->setStretchLastSection(true);

        gridLayout_3->addWidget(serchTableView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchComboBox = new QComboBox(searchPage);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));

        horizontalLayout->addWidget(searchComboBox);

        searchLineEdit = new QLineEdit(searchPage);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        horizontalLayout->addWidget(searchLineEdit);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        searchPushButton = new QPushButton(searchPage);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));

        gridLayout_4->addWidget(searchPushButton, 1, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        toolBox->addItem(searchPage, QString::fromUtf8("&Search"));
        splitter->addWidget(toolBox);

        gridLayout->addWidget(splitter, 1, 0, 1, 1);

        gridLayout->setRowStretch(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        idLabel->setBuddy(idLineEdit);
        nameLabel->setBuddy(nameLineEdit);
        phoneNumberLabel->setBuddy(phoneNumberLineEdit);
        addressLabel->setBuddy(addressLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ClientManagerForm);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ClientManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ClientManagerForm)
    {
        ClientManagerForm->setWindowTitle(QCoreApplication::translate("ClientManagerForm", "Client Info", nullptr));
        label->setText(QCoreApplication::translate("ClientManagerForm", "client", nullptr));
        idLabel->setText(QCoreApplication::translate("ClientManagerForm", "I&D", nullptr));
        nameLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Name", nullptr));
        phoneNumberLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Phone Number", nullptr));
        addressLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Address", nullptr));
        addPushButton->setText(QCoreApplication::translate("ClientManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ClientManagerForm", "&Modify", nullptr));
        toolBox->setItemText(toolBox->indexOf(inputPage), QCoreApplication::translate("ClientManagerForm", "&Input", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ClientManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ClientManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ClientManagerForm", "Phone Number", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ClientManagerForm", "Address", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ClientManagerForm", "S&earch", nullptr));
        toolBox->setItemText(toolBox->indexOf(searchPage), QCoreApplication::translate("ClientManagerForm", "&Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientManagerForm: public Ui_ClientManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTMANAGERFORM_H
