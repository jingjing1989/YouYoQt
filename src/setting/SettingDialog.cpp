#include "SettingDialog.h"
#include "ui_SettingDialog.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>

enum toolButtonIndex {
  Transaction,
  Account,
  Password,
  Client,
};

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingDialog) {
  ui->setupUi(this);
#if 0
  //横向布局填充控件
  QHBoxLayout *hLayout = new QHBoxLayout;
  hLayout->addWidget(ui->toolButton_Transaction);
  hLayout->addWidget(ui->toolButton_Accout);
  hLayout->addWidget(ui->toolButton_Password);
  hLayout->addWidget(ui->toolButton_Client);
  ui->groupBox->setLayout(hLayout);
#endif

  //网格布局
  QGridLayout *gLayout = new QGridLayout;
  for (int i = 0; i < 4; ++i) {
    gLayout->addWidget(GetToolButton(i), 0, i);
    GetToolButton(i)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    GetToolButton(i)->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    GetToolButton(i)->setIconSize(QSize(100, 100));
  }

  ui->groupBox->setLayout(gLayout);
}

SettingDialog::~SettingDialog() { delete ui; }

QToolButton *SettingDialog::GetToolButton(int index) {
  switch (index) {
  case Transaction:
    return ui->toolButton_Transaction;
  case Account:
    return ui->toolButton_Accout;
  case Password:
    return ui->toolButton_Password;
  case Client:
    return ui->toolButton_Client;
  }
  return 0;
}
