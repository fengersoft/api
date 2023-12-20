#include "map3dobject.h"

Map3dObject::Map3dObject(QObject* parent) : QObject(parent)
{
    m_selected = false;
    m_color = QColor(254, 254, 254);
    m_height = 300;
    m_objectType = OBJ_OBJECT;
    m_iconIndex = -1;
    m_devId = "";
    m_modelScale = 1;
    m_direction = "front";


}

QJsonObject Map3dObject::toJsonObject()
{
    QJsonObject jobj;

    QJsonArray jpoints;
    for (int i = 0; i < points.count(); i++)
    {
        QJsonObject jpoint;
        jpoint["x"] = points.at(i).x();
        jpoint["y"] = points.at(i).y();
        jpoints.append(jpoint);
    }
    jobj["points"] = jpoints;

    jobj["height"] = m_height;
    jobj["objectType"] = m_objectType;
    jobj["iconIndex"] = m_iconIndex;
    jobj["devId"] = m_devId;
    int r, g, b;
    m_color.getRgb(&r, &g, &b);
    jobj["color"] = QString("0x%1%2%3").arg(r, 2, 16, QLatin1Char('0')).arg(g, 2, 16, QLatin1Char('0')).arg(b, 2, 16, QLatin1Char('0'));
    jobj["modelName"] = m_modelName;
    jobj["modelType"] = m_modelType;
    jobj["modelScale"] = m_modelScale;
    jobj["direction"] = m_direction;

    return jobj;

}

QJsonObject Map3dObject::toExportJsonObject()
{
    QJsonObject jobj;
    QPoint centerPt = centerPoint();

    QJsonArray jpoints;
    for (int i = 0; i < points.count(); i++)
    {
        QJsonObject jpoint;
        jpoint["x"] = points.at(i).x() - centerPt.x();
        jpoint["z"] = points.at(i).y() - centerPt.y();
        jpoints.append(jpoint);
    }
    jobj["points"] = jpoints;
    QJsonObject jcenterPoint;
    jcenterPoint["x"] = m_exportPosition.x();
    jcenterPoint["z"] = m_exportPosition.y();

    jobj["center"] = jcenterPoint;
    jobj["name"] = m_name;
    int r, g, b;
    m_color.getRgb(&r, &g, &b);
    jobj["color"] = QString("0x%1%2%3").arg(r, 2, 16, QLatin1Char('0')).arg(g, 2, 16, QLatin1Char('0')).arg(b, 2, 16, QLatin1Char('0'));
    jobj["height"] = m_height;
    jobj["objectType"] = m_objectType;
    jobj["iconIndex"] = m_iconIndex;
    jobj["devId"] = m_devId;
    jobj["modelName"] = m_modelName;
    jobj["modelType"] = m_modelType;
    jobj["modelScale"] = m_modelScale;
    jobj["direction"] = m_direction;
    return jobj;

}

void Map3dObject::fromJsonObject(QJsonObject& jobj)
{
    QJsonArray jpoints = jobj["points"].toArray();
    for (int i = 0; i < jpoints.count(); i++)
    {
        QJsonObject jpoint = jpoints.at(i).toObject();
        points << QPoint(jpoint["x"].toInt(), jpoint["y"].toInt());
    }
    m_height = jobj["height"].toDouble() ;
    m_objectType = jobj["objectType"].toString();
    m_iconIndex = jobj["iconIndex"].toInt();
    m_color = hexToColor(jobj["color"].toString(), m_color);
    m_devId = jobj["devId"].toString();

}

QPoint Map3dObject::centerPoint()
{
    int l = 1000000;
    int r = -1000000;
    int t = 10000000;
    int b = -1000000;

    if (points.count() == 0)
    {
        return QPoint(0, 0);
    }

    for (int i = 0; i < points.count(); i++)
    {
        QPoint pt = points.at(i);

        if (pt.x() > r)
        {
            r = pt.x();
        }
        if (pt.x() < l)
        {
            l = pt.x();
        }
        if (pt.y() > b)
        {
            b = pt.y();
        }
        if (pt.x() < t)
        {
            t = pt.y();
        }


    }

    return QPoint((l + r) / 2, (t + b) / 2);

}

QPoint Map3dObject::exportPosition() const
{
    return m_exportPosition;
}

void Map3dObject::setExportPosition(QPoint newExportPosition)
{
    m_exportPosition = newExportPosition;
}

QPolygon Map3dObject::polygon()
{
    QPolygon pol;
    for (int i = 0; i < points.count(); i++)
    {
        pol.append(points.at(i));
    }

    return pol;
}

bool Map3dObject::selected() const
{
    return m_selected;
}

void Map3dObject::setSelected(bool newSelected)
{
    m_selected = newSelected;
}

const QColor& Map3dObject::color() const
{
    return m_color;
}

void Map3dObject::setColor(const QColor& newColor)
{
    m_color = newColor;
}

const QString& Map3dObject::name() const
{
    return m_name;
}

void Map3dObject::setName(const QString& newName)
{
    m_name = newName;
}

double Map3dObject::height() const
{
    return m_height;
}

void Map3dObject::setHeight(double newHeight)
{
    m_height = newHeight;
}

const QString& Map3dObject::objectType() const
{
    return m_objectType;
}

void Map3dObject::setObjectType(const QString& newObjectType)
{
    m_objectType = newObjectType;
}

void Map3dObject::moveBy(int x, int y)
{
    for (int i = 0; i < points.count(); i++)
    {
        QPoint pt = points.at(i);
        pt = QPoint(pt.x() + x, pt.y() + y);
        points.replace(i, pt);
    }
}

int Map3dObject::iconIndex() const
{
    return m_iconIndex;
}

void Map3dObject::setIconIndex(int newIconIndex)
{
    m_iconIndex = newIconIndex;
}

int Map3dObject::sizeArea()
{
    if (points.count() == 1)
    {
        return 16;
    }
    else
    {
        QSize sz = polygon().boundingRect().size();
        return sz.width() * sz.height();
    }
}

const QString& Map3dObject::devId() const
{
    return m_devId;
}

void Map3dObject::setDevId(const QString& newDevId)
{
    m_devId = newDevId;
}

QString Map3dObject::modelName() const
{
    return m_modelName;
}

void Map3dObject::setModelName(const QString& newModelName)
{
    m_modelName = newModelName;
}

QString Map3dObject::modelType() const
{
    return m_modelType;
}

void Map3dObject::setModelType(const QString& newModelType)
{
    m_modelType = newModelType;
}

double Map3dObject::modelScale() const
{
    return m_modelScale;
}

void Map3dObject::setModelScale(double newModelScale)
{
    m_modelScale = newModelScale;
}

QString Map3dObject::direction() const
{
    return m_direction;
}

void Map3dObject::setDirection(const QString& newDirection)
{
    m_direction = newDirection;
}