#ifndef CACHEDDTOLIST_H
#define CACHEDDTOLIST_H

#include <Data/DTO/TransactionDTO.h>
#include <QObject>

class CachedData : public QObject
{
    Q_OBJECT
public:
    CachedData(QObject *parent = 0);
    CachedData(const CachedData & other);

    ~CachedData();

    CachedData & operator =(const CachedData & other);

    /**
     * @brief ReadFile
     * @param fileLocation
     */
    void ReadFile(QString fileLocation);

    /**
     * @brief WriteFile
     * @param fileLocation
     */
    void WriteFile(QString fileLocation);


    /**
     * @brief GetTransactionList
     * @return
     */
    QList<TransactionDTO> GetTransactionList();

    /**
     * @brief GetCategoryList
     * @return
     */
    QList<CategoryDTO> GetCategoryList();

    /**
     * @brief AddTransaction
     * @param transactionDTO
     */
    void AddTransaction(TransactionDTO inTransactionDTO);

    /**
     * @brief UpdateTransactionAmount
     * @param id
     * @param amount
     * @return
     */
    bool UpdateTransactionAmount(int id, double amount);

    /**
     * @brief UpdateTransactionDate
     * @param id
     * @param date
     * @return
     */
    bool UpdateTransactionDate(int id, QDate date);

    /**
     * @brief UpdateTransactionType
     * @param id
     * @param type
     */
    bool UpdateTransactionType(int id, TransactionType type);

    /**
     * @brief UpdateTransactionComment
     * @param id
     * @param comment
     * @return
     */
    bool UpdateTransactionComment(int id, QString comment);

    /**
     * @brief UpdateTransactionCategory
     * @param id
     * @param categoryId
     * @return
     */
    bool UpdateTransactionCategory(int id, int categoryId);

    /**
     * @brief UpdateCategoryDescription
     * @param categoryId
     * @param categoryDescription
     * @return
     */
    bool UpdateCategoryDescription(int categoryId, QString categoryDescription);

    /**
     * @brief AddCategory
     * @param inCategory
     */
    void AddCategory(CategoryDTO inCategory);

signals:
    void MarkDirty() const;
    void MarkClean() const;

private:
    QList<TransactionDTO>   transactionList;
    QList<CategoryDTO>      categoryList;


};

#endif // CACHEDDTOLIST_H
