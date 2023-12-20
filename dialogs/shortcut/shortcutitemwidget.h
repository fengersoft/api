#ifndef SHORTCUTITEMWIDGET_H
#define SHORTCUTITEMWIDGET_H

#include <QWidget>

namespace Ui
{
class ShortCutItemWidget;
}

class ShortCutItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShortCutItemWidget(QWidget* parent = nullptr);
    ~ShortCutItemWidget();

    const QString& caption() const;
    void setCaption(const QString& newCaption);

    QString& shortCut() ;
    void setShortCut(const QString& newShortCut);


private slots:
    void on_btnClear_clicked();

private:
    Ui::ShortCutItemWidget* ui;
    QString m_caption;
    QString m_shortCut;
};

#endif // SHORTCUTITEMWIDGET_H
