#ifndef MAINWINDOWHOME_H
#define MAINWINDOWHOME_H

#include <QMainWindow>
#include <QObject>
#include <QByteArray>
#include <QEvent>

#include "home/MyLeftBar.h"

namespace Ui {
  class MainWindowHome;
}

class MainWindowHome : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindowHome(QWidget *parent = nullptr);
  ~MainWindowHome();

private:
  bool eventFilter(QObject *watched,QEvent *event);
  bool nativeEvent(const QByteArray &eventType,void *message,long *result);

#ifdef Q_OS_WIN
  bool winEvent(MSG *message,long *result);
#endif

private:
  Ui::MainWindowHome *ui;

  int padding;

  void initControl();
};

#endif // MAINWINDOWHOME_H
