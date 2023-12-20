#include "wordtablereader.h"

WordTableReader::WordTableReader(QObject* parent)
    : QObject{parent}
{
    m_app = new QAxWidget("Word.Application");
    m_app->dynamicCall("SetVisible(bool)", false);
    m_documents = m_app->querySubObject("Documents");
}

void WordTableReader::loadfromFile(QString fileName)
{


    m_documents->dynamicCall("Open(QString)", fileName);
    m_doc = m_app->querySubObject("ActiveDocument");
    m_tables = m_doc->querySubObject("Tables"); //获取所有表格
    m_tablesCount = m_tables->dynamicCall("Count").toInt();
    qDebug() << m_tablesCount;


}

void WordTableReader::quit()
{
    m_doc->dynamicCall("Close(boolean)", true);//关闭
    m_app->dynamicCall("Quit()");//退出


}

WordTableReader::~WordTableReader()
{
    delete m_app;
}

QString WordTableReader::tableText(int tableIndex, int col, int row)
{
    QAxObject* table = m_doc->querySubObject("Tables(int)", tableIndex);
    QAxObject* cell = table->querySubObject("Cell(int,int)", row, col);
    QString sp = cell->querySubObject("Range")->property("Text").toString();
    return sp;

}

QString WordTableReader::tableText(QAxObject* table, int col, int row)
{
    QAxObject* cell = table->querySubObject("Cell(int,int)", row, col);
    QString sp = cell->querySubObject("Range")->property("Text").toString();
    return sp;

}

int WordTableReader::tableRowsCount(QAxObject* table)
{
    int row = table->querySubObject("Rows")->dynamicCall("Count").toInt(); //获取行数
    return row;

}

QString WordTableReader::tableTextString(QAxObject* table, int col, int row)
{
    QString ret = tableText(table, col, row);
    ret = ret.replace("\r\u0007", "");
    qDebug() << ret;
    return ret;

}

QAxObject* WordTableReader::table(int index)
{
    return m_doc->querySubObject("Tables(int)", index);

}
