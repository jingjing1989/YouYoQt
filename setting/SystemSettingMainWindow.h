#ifndef SYSTEMSETTINGMAINWINDOW_H
#define SYSTEMSETTINGMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
  class SystemSettingMainWindow;
}

class SystemSettingMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SystemSettingMainWindow(QWidget *parent = nullptr);
  ~SystemSettingMainWindow();

  QPushButton* GetPushButton(int index);

private:
  Ui::SystemSettingMainWindow *ui;



  void PushButtonChanged(bool checked,int index);
};

#endif // SYSTEMSETTINGMAINWINDOW_H
