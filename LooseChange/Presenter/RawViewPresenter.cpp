#include "RawViewPresenter.h"
#include <Delegates/DateEditDelegate.h>
#include <Delegates/DoubleSpinBoxDelegate.h>
#include <Delegates/TransactionTypeComboBoxDelegate.h>
#include <Delegates/CategoryComboBoxDelegate.h>
#include <Delegates/CommentLineEditDelegate.h>
#include <QInputDialog>

RawViewPresenter::RawViewPresenter()
{
}

RawViewPresenter::RawViewPresenter(QTableWidget *tableWidget, CachedData *inCachedDataPointer, QWidget *parent) :
    QObject(parent)
{
    table = tableWidget;
    //cachedDataPointer = inCachedDataPointer;
    transactionDAO = new TransactionDAO(inCachedDataPointer);
    categoryDAO = new CategoryDAO(inCachedDataPointer);

    table->setEditTriggers(QAbstractItemView::AllEditTriggers);//CurrentChanged);//::AllEditTriggers
}

RawViewPresenter::~RawViewPresenter()
{
    delete transactionDAO;
    delete categoryDAO;
}


void RawViewPresenter::Load()
{
    QList<TransactionDTO> transactionList = transactionDAO->GetTransactionList();
    QList<CategoryDTO> categoryList = categoryDAO->GetCategories();
    int count = transactionList.count();

    table->clear();
    table->setColumnCount(6);
    table->setRowCount(count);

    DateEditDelegate *dateEdit = new DateEditDelegate(this);
    DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
    TransactionTypeComboBoxDelegate *transactionTypeComboBox = new TransactionTypeComboBoxDelegate(this);
    CategoryComboBoxDelegate *categoryComboBox = new CategoryComboBoxDelegate(categoryList, this);
    CommentLineEditDelegate *commentLineEdit = new CommentLineEditDelegate(this);


    QObject::connect(dateEdit, SIGNAL(ValueChanged(QModelIndex,QDate)), this, SLOT(ChangeDate(QModelIndex,QDate)));
    QObject::connect(doubleSpinBox, SIGNAL(ValueChanged(QModelIndex,double)), this, SLOT(ChangeAmount(QModelIndex,double)));
    QObject::connect(transactionTypeComboBox, SIGNAL(ValueChanged(QModelIndex,TransactionType)), this, SLOT(ChangeTransactionType(QModelIndex,TransactionType)));
    //QObject::connect(categoryComboBox, SIGNAL(ValueChanged(CategoryDTO,QModelIndex)), this, SLOT(ChangeCategory(CategoryDTO,QModelIndex)));
    //QObject::connect(categoryComboBox, SIGNAL(AddCategoryRequested(QModelIndex)), this, SLOT(AddCategory(QModelIndex)));
    QObject::connect(commentLineEdit, SIGNAL(ValueChanged(QModelIndex,QString)), this, SLOT(ChangeComment(QModelIndex,QString)));

    table->setItemDelegateForColumn(1, dateEdit);
    table->setItemDelegateForColumn(2, doubleSpinBox);
    table->setItemDelegateForColumn(3, transactionTypeComboBox);
    table->setItemDelegateForColumn(4, categoryComboBox);
    table->setItemDelegateForColumn(5, commentLineEdit);


    ///ui->tableWidgetRawView->verticalHeaderItem(i)->setText(QString::number(dto.id));
    for(int i = 0; i < count; i++)
    {
        TransactionDTO dto = transactionList.at(i);
        QModelIndex index;
        /// Column 0 - ID
        table->setItem(i,0,new QTableWidgetItem(QString::number(dto.id)));

        /// Column 1 - DATE
        index = table->model()->index(i, 1, QModelIndex());
        table->model()->setData(index, QVariant(dto.date));

        /// Column 2 - AMOUNT
        index = table->model()->index(i, 2, QModelIndex());
        table->model()->setData(index, QVariant(dto.amount));

        /// Column 3 - TRANSACTION TYPE
        index = table->model()->index(i, 3, QModelIndex());
        table->model()->setData(index, QVariant(TransactionTypeHelper::ToString(dto.transactionType)));

        /// Column 4 - CATEGORY
        index = table->model()->index(i, 4, QModelIndex());
        table->model()->setData(index, QVariant(dto.category.category));

        /// Column 5 - COMMENT
        index = table->model()->index(i, 5, QModelIndex());
        table->model()->setData(index, QVariant(dto.comment));
    }
    //table->hideColumn(0);
    //table->sortItems(1);
}

int RawViewPresenter::GetIdFromModelIndex(QModelIndex index) const
{
   return table->model()->data(table->model()->index(index.row(),0)).toInt();
}

void RawViewPresenter::ChangeAmount(QModelIndex index, double amount)
{ 
    transactionDAO->UpdateAmount(GetIdFromModelIndex(index), amount);
}

void RawViewPresenter::ChangeDate(QModelIndex index, QDate date)
{
    transactionDAO->UpdateDate(GetIdFromModelIndex(index), date);
}

void RawViewPresenter::ChangeTransactionType(QModelIndex index, TransactionType type)
{
    transactionDAO->UpdateType(GetIdFromModelIndex(index), type);
}

void RawViewPresenter::ChangeComment(QModelIndex index, QString comment)
{
    transactionDAO->UpdateComment(GetIdFromModelIndex(index), comment);
}
