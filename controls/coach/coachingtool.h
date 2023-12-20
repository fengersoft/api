#ifndef COACHINGTOOL_H
#define COACHINGTOOL_H

#include <QWidget>
#include "../api/controls/base/widgethelper.h"

class CoachingTool : public QWidget
{
    Q_OBJECT
public:
    explicit CoachingTool(QWidget* parent = nullptr);

    const QString& caption() const;
    void setCaption(const QString& newCaption);
protected:
    WidgetHelper* m_helper;
signals:


private:
    QString m_caption;

};

#endif // COACHINGTOOL_H
