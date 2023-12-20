#include "richviewimageitem.h"
#include "ui_richviewimageitem.h"

RichViewImageItem::RichViewImageItem(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RichViewImageItem)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    m_srcPix = QPixmap("E:\\C 测试数据\\微信图片_20211221145344.jpg");
    QStringList menuNames;
    menuNames << "粘贴剪贴板图像";
    menuNames << "清除图像";
    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(this);
        if (menuNames[i] == "-")
        {
            act->setSeparator(true);
        }
        else
        {
            act->setText(menuNames[i]);
            connect(act, &QAction::triggered, this, &RichViewImageItem::onTriggered);
        }
        addAction(act);
    }
}

RichViewImageItem::~RichViewImageItem()
{
    delete ui;
}

void RichViewImageItem::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    int d = qApp->devicePixelRatio();
    double f1 = width();
    f1 = f1 / height();
    double f2 = m_srcPix.width();
    f2 = f2 / height();
    painter.begin(this);
    QPixmap tempPix;
    QRect imgRc;
    if (f1 > f2)
    {
        tempPix = m_srcPix.scaledToHeight(height() * d,
                                          Qt::SmoothTransformation);
        imgRc = QRect(0,
                      (height() - tempPix.height() / d) / d, tempPix.width() / d, tempPix.height() / d);

    }
    else
    {
        tempPix = m_srcPix.scaledToWidth(width() * d,
                                         Qt::SmoothTransformation);
        imgRc = QRect((width() - tempPix.width() / d) / d, 0, tempPix.width() / d, tempPix.height() / d);

    }
    m_imageHeight = tempPix.height() + 32;


    painter.drawPixmap(imgRc, tempPix, tempPix.rect());
    painter.end();

}

int RichViewImageItem::imageHeight() const
{
    return m_imageHeight;
}

void RichViewImageItem::setImageHeight(int newImageHeight)
{
    m_imageHeight = newImageHeight;
}

QString RichViewImageItem::filePath() const
{
    return m_filePath;
}

void RichViewImageItem::setFilePath(const QString& newFilePath)
{
    m_filePath = newFilePath;
    update();
}

void RichViewImageItem::onTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "粘贴剪贴板图像")
    {
        if (!qApp->clipboard()->pixmap().isNull())
        {
            m_srcPix = qApp->clipboard()->pixmap();
            update();
        }

    }
    else if (act->text() == "清除图像")
    {
        m_srcPix = QPixmap();
        update();
    }
}
