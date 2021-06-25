#ifndef COMMONUTILITY_H
#define COMMONUTILITY_H
#include <QString>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QColor>
#include <QPalette>
#include <QWidget>

class CommonUtility
{
public:
  CommonUtility();

  static void setStyleSheet(const QString &strFile,QWidget *pwidget);
};

#endif // COMMONUTILITY_H
