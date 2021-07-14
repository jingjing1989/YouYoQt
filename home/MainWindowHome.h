#ifndef MAINWINDOWHOME_H
#define MAINWINDOWHOME_H

#include <QByteArray>
#include <QEvent>
#include <QMainWindow>
#include <QObject>

#include "CHarts.h"
#include "MyLeftBar.h"
#include "MyTableWidget.h"

namespace Ui {
class MainWindowHome;
}

namespace MainWindowHomeSpace {
const int LeftPadding = 4;
}

class MainWindowHome : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindowHome(QWidget *parent = nullptr);
  ~MainWindowHome();

private:
  bool eventFilter(QObject *watched, QEvent *event);
  bool nativeEvent(const QByteArray &eventType, void *message, long *result);

#ifdef Q_OS_WIN
  bool winEvent(MSG *message, long *result);
#endif

private:
  Ui::MainWindowHome *ui;

  // int padding = MainWindowHomeSpace::LeftPadding;

  void initLeftBar();

  //初始化MDI
  void initMDI();
};

#endif // MAINWINDOWHOME_H
