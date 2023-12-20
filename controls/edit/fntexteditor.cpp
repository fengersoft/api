#include "fntexteditor.h"
#include "ui_fntexteditor.h"

FnTextEditor::FnTextEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FnTextEditor)
{
    ui->setupUi(this);
    m_textEdit=new FnPlainTextEdit(ui->wgtInfo);
    addWidgetToPage(ui->wgtInfo,m_textEdit);

    m_lineNumber=new FnLineNumber(ui->wgtLineNumber);
    addWidgetToPage(ui->wgtLineNumber,m_lineNumber);
    m_lineNumber->setTextEdit(m_textEdit);
    connect(m_textEdit,&FnPlainTextEdit::blockCountChanged,this,&FnTextEditor::onBlockCountChanged);
     connect(m_textEdit,&FnPlainTextEdit::updateRequest,this,&FnTextEditor::onUpdateRequest);
     connect(m_textEdit,&FnPlainTextEdit::cursorPositionChanged,this,&FnTextEditor::onCursorPositionChanged);
}

FnTextEditor::~FnTextEditor()
{
    delete ui;
}

void FnTextEditor::onBlockCountChanged(int newBlockCount)
{
    int w=m_textEdit->lineNumberWidth()*5+32;


    ui->wgtLineNumber->setMinimumWidth(w);
    ui->wgtLineNumber->setMaximumWidth(w);
    m_lineNumber->update();


}

void FnTextEditor::onUpdateRequest(const QRect &rect, int dy)
{
    m_lineNumber->update();
}

void FnTextEditor::onCursorPositionChanged()
{
    m_lineNumber->update();

}
