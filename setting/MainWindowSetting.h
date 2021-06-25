#ifndef MAINWINDOWSETTING_H
#define MAINWINDOWSETTING_H

#include <QMainWindow>

#include "login\MyToolButton.h"

namespace Ui {
  class MainWindowSetting;
}

class MainWindowSetting : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindowSetting(QWidget *parent = nullptr);
  ~MainWindowSetting();

  QFont SetIconFont();

  //获得对应ToolButton控件
  MyToolButton* GetMyToolButton(int index);

private:
  Ui::MainWindowSetting *ui;
};

#endif // MAINWINDOWSETTING_H
