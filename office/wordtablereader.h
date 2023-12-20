#ifndef WORDTABLEREADER_H
#define WORDTABLEREADER_H

#include <QObject>
#include <QAxWidget>
#include <QAxObject>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

class WordTableReader : public QObject
{
    Q_OBJECT
public:
    explicit WordTableReader(QObject* parent = nullptr);
    void loadfromFile(QString fileName);
    void quit();
    ~WordTableReader();
    QString tableText(int tableIndex, int col, int row);
    QString tableText(QAxObject* table, int col, int row);
    int tableRowsCount(QAxObject* table);
    QString tableTextString(QAxObject* table, int col, int row);
    QAxObject* table(int index);

signals:
private:
    QAxWidget* m_app;
    QAxObject* m_documents;
    QAxObject* m_doc;
    QAxObject* m_tables;

    int m_tablesCount;



};

#endif // WORDTABLEREADER_H
