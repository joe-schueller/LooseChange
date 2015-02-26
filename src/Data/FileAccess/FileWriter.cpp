//#include "FileWriter.h"

//#include <QFile>
//#include <QFileDialog>
//#include <QTextStream>
//#include <QMessageBox>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>


//FileWriter::FileWriter()
//{
//}

//bool FileWriter::WriteFile(QList<TransactionDTO> transactionList, QList<CategoryDTO> categoryList, QString fileLocation)
//{
//    QFile file(fileLocation);
//    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        //Add Transactions
//        QJsonArray transactionJSONArray;
//        foreach (TransactionDTO transaction, transactionList)
//        {
//            //Write to individual Transaction
//            QJsonObject transactionJSON;
//            transactionJSON["ID"] = QString(transaction.id);
//            transactionJSON["DATE"] = transaction.date.toString("yyyyMMdd");
//            transactionJSON["AMOUNT"] = transaction.amount;
//            transactionJSON["TRANSACTION_TYPE"] = TransactionTypeHelper::ToString(transaction.transactionType);
//            transactionJSON["CATEGORY_ID"] = QString(transaction.categoryId);
//            transactionJSON["COMMENT"] = QString(transaction.comment);

//            transactionJSONArray.append(transactionJSON);
//        }

//        //Add Categories
//        QJsonArray categoryJSONArray;
//        foreach(CategoryDTO category, categoryList)
//        {
//            QJsonObject categoryJSON;
//            categoryJSON["ID"] = QString(category.id);
//            categoryJSON["DESCRIPTION"] = QString(category.description);

//            categoryJSONArray.append(categoryJSON);
//        }




//        //Write Section for all transactions
//        QJsonObject mainJsonObj;
//        mainJsonObj["TRANSACTIONS"] = transactionJSONArray;
//        mainJsonObj["CATEGORIES"] = categoryJSONArray;

//        //Write to the file
//        QJsonDocument doc(mainJsonObj);
//        if(file.write(doc.toJson()) < 0) //file.write(doc.toJson()) returns -1 if error
//        {
//            return false;
//        }
//        else
//        {
//            return true;
//        }
//    }
//    else
//    {
//        return false;
//    }
//}
