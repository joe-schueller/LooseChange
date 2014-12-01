#include "LooseChangePresenter.h"
#include "ui_loosechangepresenter.h"

#include<QDebug>

#include <QFileDialog>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <Utility/TransactionType.h>
#include <Utility/Categories.h>
#include <Delegates/DoubleSpinBoxDelegate.h>
#include <Delegates/DateEditDelegate.h>


LooseChangePresenter::LooseChangePresenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LooseChangePresenter)
{
    ///Sets up the UI
    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);

    ///Add Buttons to the toolbar
    ui->mainToolBar->addWidget(ui->toolButtonOpen);
    ui->mainToolBar->addWidget(ui->toolButtonSave);




    /// http://iconsetc.com/icon/bfa_folder-open/?style=simple-black
    //Used to set edit triggers. Ex: signal or double click


    rawView = new RawViewPresenter(ui->tableWidgetRawView, &transactionDAO, &categoryDAO, this);
    connect(&transactionDAO, SIGNAL(DataChanged(bool)), this, SLOT(SaveButtonEnabled(bool)));

    rawView->Load();


}

LooseChangePresenter::~LooseChangePresenter()
{
    delete rawView;
    delete ui;

}

void LooseChangePresenter::on_toolButtonOpen_clicked()
{
    QString fileLocation = QFileDialog::getOpenFileName(this, tr("Open File"), "./",
                                                        tr("LooseChange Files (*.json);;All Files (*.* *"));
    if(fileLocation != "")
    {
        transactionDAO.ReadFile(fileLocation);
        rawView->Load();
        fileLocationTemp = fileLocation;
    }
}

void LooseChangePresenter::on_toolButtonSave_clicked()
{
    QString fileLocation = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        fileLocationTemp,
                                                        tr("LooseChange Files (*.json);;All Files (*.* *"));
    transactionDAO.WriteFile(fileLocation);
    transactionDAO.ReadFile(fileLocation);
    rawView->Load();
}

void LooseChangePresenter::SaveButtonEnabled(bool enabled)
{
    ui->toolButtonSave->setEnabled(enabled);
}









