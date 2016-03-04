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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasedUpdater
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BasedUpdater)
    {
        if (BasedUpdater->objectName().isEmpty())
            BasedUpdater->setObjectName(QStringLiteral("BasedUpdater"));
        BasedUpdater->resize(400, 300);
        menuBar = new QMenuBar(BasedUpdater);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BasedUpdater->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BasedUpdater);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BasedUpdater->addToolBar(mainToolBar);
        centralWidget = new QWidget(BasedUpdater);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BasedUpdater->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BasedUpdater);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BasedUpdater->setStatusBar(statusBar);

        retranslateUi(BasedUpdater);

        QMetaObject::connectSlotsByName(BasedUpdater);
    } // setupUi

    void retranslateUi(QMainWindow *BasedUpdater)
    {
        BasedUpdater->setWindowTitle(QApplication::translate("BasedUpdater", "BasedUpdater", 0));
    } // retranslateUi

};

namespace Ui {
    class BasedUpdater: public Ui_BasedUpdater {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEDUPDATER_H
