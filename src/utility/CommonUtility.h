#ifndef COMMONUTILITY_H
#define COMMONUTILITY_H
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QPushButton>
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
  static void setIconFont(QChar strFile, QPushButton *p, const int &size = 10);
  static void setIconFont(QChar strFile, QLabel *p, const int &size = 10);
};

#endif // COMMONUTILITY_H
