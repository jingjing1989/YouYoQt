
#pragma execution_character_set("utf-8")
#include "SystemSettingMainWindow.h"
#include "ui_SystemSettingMainWindow.h"
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>


enum pushButtonIndex
{
  Transaction,
  Account,
  Password,
  Client,
};

SystemSettingMainWindow::SystemSettingMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SystemSettingMainWindow)
{
  ui->setupUi(this);

  //设置样式
  //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
  QFile styleSheet(":/qss/res/qss/defaultstyle/systemsetting.css");

  if (!styleSheet.open(QIODevice::ReadOnly)) {
    qWarning("Unable to open :/qss/res/qss/defaultstyle/systemsetting.css");
    return;
  }



   this->setStyleSheet(styleSheet.readAll());

  //设置顶部按钮位置
  GetPushButton(Transaction)->setGeometry(0,0,200,100);
  GetPushButton(Account)->setGeometry(200,0,200,100);
  GetPushButton(Password)->setGeometry(400,0,200,100);
  GetPushButton(Client)->setGeometry(600,0,200,100);

  //设置StackWidget 按钮
  ui->pushButton_changepassword->setGeometry(0,0,180,50);
  ui->pushButton_logUpload->setGeometry(0,50,180,50);
  ui->pushButton_clientlock->setGeometry(0,100,180,50);
  ui->pushButton_margintradesetting->setGeometry(0,150,180,50);
  ui->pushButton_about->setGeometry(0,200,180,50);


  //信号槽
//  connect(GetPushButton(Account),QOverload<int>::of(&QPushButton::toggled),this,
//         &SystemSettingMainWindow::PushButtonChanged );

  connect(GetPushButton(Transaction),&QPushButton::clicked,this,[=]()
  {
      GetPushButton(Transaction)->setChecked(true);

    });
  connect(GetPushButton(Account),&QPushButton::clicked,this,[=]()
  {
      GetPushButton(Account)->setChecked(true);

    });
  connect(GetPushButton(Client),&QPushButton::clicked,this,[=]()
  {
      GetPushButton(Client)->setChecked(true);

    });
  connect(GetPushButton(Password),&QPushButton::clicked,this,[=]()
  {
      GetPushButton(Password)->setChecked(true);

    });
  #if 1
  connect(GetPushButton(Transaction),&QPushButton::toggled,this,[=](bool checked)
  {
      if(checked)
        {
            ui->stackedWidget_Menu->setCurrentIndex(Transaction);
        }
      for (int i=0;i<4;++i) {
          if(GetPushButton(i)->isChecked()&& i!=Transaction)
            {
              GetPushButton(i)->setChecked(false);
            }
        }

    });

  connect(GetPushButton(Account),&QPushButton::toggled,this,[=](bool checked)
  {
      if(checked)
        {
            ui->stackedWidget_Menu->setCurrentIndex(Account);
            for (int i=0;i<4;++i) {
                if(GetPushButton(i)->isChecked()&& i!=Account)
                  {
                    GetPushButton(i)->setChecked(false);
                  }
              }
        }

    });

  connect(GetPushButton(Client),&QPushButton::toggled,this,[=](bool checked)
  {
      if(checked)
        {
            ui->stackedWidget_Menu->setCurrentIndex(Client);
        }
      for (int i=0;i<4;++i) {
          if(GetPushButton(i)->isChecked()&& i!=Client)
            {
              GetPushButton(i)->setChecked(false);
            }
        }

    });


  connect(GetPushButton(Password),&QPushButton::toggled,this,[=](bool checked)
  {
      if(checked)
        {
            ui->stackedWidget_Menu->setCurrentIndex(Password);
        }
      for (int i=0;i<4;++i) {
          if(GetPushButton(i)->isChecked()&& i!=Password)
            {
              GetPushButton(i)->setChecked(false);
            }
        }

    });
#endif
  connect(ui->pushButton_changepassword,&QPushButton::clicked,this,[=](){
      ui->stackedWidget_setting->setCurrentIndex(0);
    });
  connect(ui->pushButton_logUpload,&QPushButton::clicked,[=](){
      ui->stackedWidget_setting->setCurrentIndex(1);

    });

  connect(ui->pushButton_changepassword,&QPushButton::toggled,this,[=](bool checked){
      if(checked)
        {
          ui->stackedWidget_setting->setCurrentIndex(0);
        }
      else{
          ui->stackedWidget_setting->setCurrentIndex(1);
        }
    });


}

SystemSettingMainWindow::~SystemSettingMainWindow()
{
  delete ui;
}

//获得对应PushButton控件
QPushButton* SystemSettingMainWindow::GetPushButton(int index)
{
  switch (index) {
    case Transaction:
      return ui->pushButton_trading;
    case Account:
      return ui->pushButton_accounts;
    case Password:
      return ui->pushButton_password;
    case Client:
      return ui->pushButton_client;

    }
  return 0;

}
void SystemSettingMainWindow::PushButtonChanged(bool checked,int index)
{
  if(checked)
    {
        ui->stackedWidget_Menu->setCurrentIndex(index);
        for (int i=0;i<4;++i) {
            if(GetPushButton(i)->isChecked()&& i!=index)
              {
                GetPushButton(i)->setChecked(false);
              }
          }
    }


  return;
}
