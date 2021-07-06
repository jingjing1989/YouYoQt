#ifndef COMMONUTILITY_H
#define COMMONUTILITY_H
#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QPalette>
#include <QString>
#include <QWidget>

class CommonUtility {
public:
  CommonUtility();

  static void setStyleSheet(const QString &strFile, QWidget *pwidget);
  static void globalInit(QApplication *pwidget);
  static void addIconFont();
  static void addDefaultFont();
  static void setGlobalColors();
};

#endif // COMMONUTILITY_H
