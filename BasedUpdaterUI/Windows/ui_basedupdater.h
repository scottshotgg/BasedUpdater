/********************************************************************************
** Form generated from reading UI file 'basedupdater.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEDUPDATER_H
#define UI_BASEDUPDATER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasedUpdater
{
public:
    QAction *actionAbout;
    QWidget *centralWidget;
    QLineEdit *filePath_lineEdit;
    QPushButton *pushButton;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BasedUpdater)
    {
        if (BasedUpdater->objectName().isEmpty())
            BasedUpdater->setObjectName(QStringLiteral("BasedUpdater"));
        BasedUpdater->resize(400, 253);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BasedUpdater->sizePolicy().hasHeightForWidth());
        BasedUpdater->setSizePolicy(sizePolicy);
        BasedUpdater->setMaximumSize(QSize(400, 253));
        actionAbout = new QAction(BasedUpdater);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout->setMenuRole(QAction::AboutRole);
        centralWidget = new QWidget(BasedUpdater);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(400, 200));
        centralWidget->setMaximumSize(QSize(401, 201));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        centralWidget->setFont(font);
        filePath_lineEdit = new QLineEdit(centralWidget);
        filePath_lineEdit->setObjectName(QStringLiteral("filePath_lineEdit"));
        filePath_lineEdit->setGeometry(QRect(90, 130, 151, 20));
        filePath_lineEdit->setClearButtonEnabled(true);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 130, 51, 21));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 401, 101));
        QFont font1;
        font1.setFamily(QStringLiteral("Impact"));
        font1.setPointSize(30);
        label->setFont(font1);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        BasedUpdater->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BasedUpdater);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        BasedUpdater->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BasedUpdater);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BasedUpdater->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BasedUpdater);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BasedUpdater->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionAbout);

        retranslateUi(BasedUpdater);

        QMetaObject::connectSlotsByName(BasedUpdater);
    } // setupUi

    void retranslateUi(QMainWindow *BasedUpdater)
    {
        BasedUpdater->setWindowTitle(QApplication::translate("BasedUpdater", "BasedUpdater", 0));
        actionAbout->setText(QApplication::translate("BasedUpdater", "About", 0));
        filePath_lineEdit->setText(QString());
        filePath_lineEdit->setPlaceholderText(QApplication::translate("BasedUpdater", "File Path", 0));
        pushButton->setText(QApplication::translate("BasedUpdater", "Browse", 0));
        label->setText(QApplication::translate("BasedUpdater", "BasedUpdater", 0));
        menuFile->setTitle(QApplication::translate("BasedUpdater", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class BasedUpdater: public Ui_BasedUpdater {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEDUPDATER_H
