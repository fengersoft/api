#ifndef MODELHELPER_H
#define MODELHELPER_H

#include <QObject>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QListView>

void itemMoveUp(QTableView* lvData, QStandardItemModel* model);
void itemMoveDown(QTableView* lvData, QStandardItemModel* model);
void itemMoveUp(QListView* lvData, QStandardItemModel* model);
void itemMoveDown(QListView* lvData, QStandardItemModel* model);
void itemClickNext(QTableView* lvData, QStandardItemModel* model);
void itemClickPre(QTableView* lvData, QStandardItemModel* model);
#endif // MODELHELPER_H
