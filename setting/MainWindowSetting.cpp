#include "MainWindowSetting.h"
#include "ui_MainWindowSetting.h"

#include <QFont>
#include <QFontDatabase>
#include <QDebug>


#pragma execution_character_set("utf-8")

#define ICON_USER  QChar(0xf21b)
#define ICON_PASSWORD  QChar(0xf023)
#define ICON_KEY  QChar(0xf084)
#define ICON_CLOSE  QChar(0xf2d4)
#define ICON_MINI  QChar(0xf2d1)

enum toolButtonIndex
{
  Transaction,
  Account,
  Password,
  Client,
};

MainWindowSetting::MainWindowSetting(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindowSetting)
{
  ui->setupUi(this);
  // 创建字体
  //QFont font =SetIconFont();
  //font.setPointSize(10);

  //GetMyToolButton(Transaction)->setFont(font);
  GetMyToolButton(Transaction)->SetIconFont(ICON_USER);
  GetMyToolButton(Transaction)->SetText("交易设置");
  //GetMyToolButton(Account)->setFont(font);
  GetMyToolButton(Account)->SetIconFont(ICON_USER);
  GetMyToolButton(Account)->SetText("账户设置");
  //GetMyToolButton(Password)->setFont(font);
  GetMyToolButton(Password)->SetIconFont(ICON_PASSWORD);
  GetMyToolButton(Password)->SetText("密码设置");
  //GetMyToolButton(Client)->setFont(font);
  GetMyToolButton(Client)->SetIconFont(ICON_KEY);
  GetMyToolButton(Client)->SetText("客户端设置");

  //设置位置
  GetMyToolButton(Transaction)->setGeometry(0,0,200,150);
  GetMyToolButton(Account)->setGeometry(200,0,200,150);
  GetMyToolButton(Password)->setGeometry(400,0,200,150);
  GetMyToolButton(Client)->setGeometry(600,0,200,150);

  MyToolButton *tooTest = new MyToolButton(ui->toolButton_Par);
  tooTest->setGeometry(40,150,200,200);
  tooTest->SetText("AAAAAAAA");


  //setStyleSheet("file:///:/qss/files/MyToolButton.qss");

}

MainWindowSetting::~MainWindowSetting()
{
  delete ui;
}
QFont MainWindowSetting::SetIconFont()
{
  if (QFontDatabase::addApplicationFont(
          ":/iconfont/res/iconFont/fontawesome-webfont.ttf") < 0)
    qWarning()
        << ":/iconfont/res/iconFont/fontawesome-webfont.ttf cannot be loaded !";

  int fontId = QFontDatabase::addApplicationFont(
      ":/iconfont/res/iconFont/fontawesome-webfont.ttf");
  QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
  qDebug() << "fontFamilies.size() " << fontFamilies.size();
  qDebug() << "fontFamilies: " << fontFamilies.at(0);

  // 创建字体
  QFont font;
  font.setFamily(fontFamilies.at(0));

  //将此字体设为QApplication的默认字体
  //QApplication::setFont(font);

  return font;

}

//获得对应ToolButton控件
MyToolButton* MainWindowSetting::GetMyToolButton(int index)
{
  switch (index) {
    case Transaction:
      return ui->toolButton_Transaction;
    case Account:
      return ui->toolButton_Account;
    case Password:
      return ui->toolButton_Password;
    case Client:
      return ui->toolButton_Client;

    }
  return 0;

}
