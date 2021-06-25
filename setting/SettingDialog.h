#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QMainWindow>

namespace Ui {
  class SettingDialog;
}

class SettingDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SettingDialog(QWidget *parent = nullptr);
  ~SettingDialog();

  QToolButton* GetToolButton(int index);

private:
  Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
