/********************************************************************************
** Form generated from reading UI file 'chatserverform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATSERVERFORM_H
#define UI_CHATSERVERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatserverForm
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *clientTreeWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *exitbutton;
    QPushButton *connectbutton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *messageTreeWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *deletebutton;
    QPushButton *savebutton;

    void setupUi(QWidget *chatserverForm)
    {
        if (chatserverForm->objectName().isEmpty())
            chatserverForm->setObjectName(QString::fromUtf8("chatserverForm"));
        chatserverForm->resize(532, 500);
        verticalLayout_4 = new QVBoxLayout(chatserverForm);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label = new QLabel(chatserverForm);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("\355\234\264\353\250\274\353\221\245\352\267\274\355\227\244\353\223\234\353\235\274\354\235\270")});
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        splitter = new QSplitter(chatserverForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        clientTreeWidget = new QTreeWidget(layoutWidget);
        clientTreeWidget->setObjectName(QString::fromUtf8("clientTreeWidget"));
        clientTreeWidget->setFocusPolicy(Qt::ClickFocus);
        clientTreeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

        verticalLayout->addWidget(clientTreeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        exitbutton = new QPushButton(layoutWidget);
        exitbutton->setObjectName(QString::fromUtf8("exitbutton"));

        horizontalLayout->addWidget(exitbutton);

        connectbutton = new QPushButton(layoutWidget);
        connectbutton->setObjectName(QString::fromUtf8("connectbutton"));

        horizontalLayout->addWidget(connectbutton);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        messageTreeWidget = new QTreeWidget(layoutWidget1);
        messageTreeWidget->setObjectName(QString::fromUtf8("messageTreeWidget"));
        messageTreeWidget->setColumnCount(6);

        verticalLayout_2->addWidget(messageTreeWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        deletebutton = new QPushButton(layoutWidget1);
        deletebutton->setObjectName(QString::fromUtf8("deletebutton"));

        horizontalLayout_2->addWidget(deletebutton);

        savebutton = new QPushButton(layoutWidget1);
        savebutton->setObjectName(QString::fromUtf8("savebutton"));

        horizontalLayout_2->addWidget(savebutton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        splitter->addWidget(layoutWidget1);

        verticalLayout_3->addWidget(splitter);

        verticalLayout_3->setStretch(1, 1);

        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(chatserverForm);
        QObject::connect(deletebutton, &QPushButton::clicked, messageTreeWidget, qOverload<>(&QTreeWidget::clear));

        QMetaObject::connectSlotsByName(chatserverForm);
    } // setupUi

    void retranslateUi(QWidget *chatserverForm)
    {
        chatserverForm->setWindowTitle(QCoreApplication::translate("chatserverForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("chatserverForm", "Server", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = clientTreeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("chatserverForm", "name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("chatserverForm", "connect", nullptr));
        exitbutton->setText(QCoreApplication::translate("chatserverForm", "exit", nullptr));
        connectbutton->setText(QCoreApplication::translate("chatserverForm", "connect", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = messageTreeWidget->headerItem();
        ___qtreewidgetitem1->setText(5, QCoreApplication::translate("chatserverForm", "Time", nullptr));
        ___qtreewidgetitem1->setText(4, QCoreApplication::translate("chatserverForm", "message", nullptr));
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("chatserverForm", "name", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("chatserverForm", "ID", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("chatserverForm", "Port", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("chatserverForm", "IP", nullptr));
        deletebutton->setText(QCoreApplication::translate("chatserverForm", "delete", nullptr));
        savebutton->setText(QCoreApplication::translate("chatserverForm", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatserverForm: public Ui_chatserverForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATSERVERFORM_H
