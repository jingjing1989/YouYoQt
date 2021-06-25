#include "loginDialog.h"
#include "ui_loginDialog.h"
#pragma execution_character_set("utf-8")


#include <QGridLayout>
#include <QFontDatabase>
#include <QDebug>
#include <QChar>
#include <QMessageBox>
#include <QFile>

#include "LineEditLabel.h"

#define ICON_USER  QChar(0xf21b)
#define ICON_PASSWORD  QChar(0xf023)
#define ICON_KEY  QChar(0xf084)
#define ICON_CLOSE  QChar(0xf2d4)
#define ICON_MINI  QChar(0xf2d1)


loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    //为对话框加上最大化最小化按钮
    this->setWindowFlags(this->windowFlags()&Qt::WindowMaximizeButtonHint & Qt::WindowMinimizeButtonHint);


    //设置无边框,点击图标栏可放大缩小  最大化最小化  |Qt::FramelessWindowHint
    setWindowFlags(Qt::Dialog\
                       |Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint|Qt::FramelessWindowHint);

        //设置背景提示
        ui->lineEdit_user->setPlaceholderText("请输入账号");
        ui->lineEdit_Password->setPlaceholderText("请输入密码!!");

        //密码显示黑圆圈
        //ui->lineEdit_PassWord->setEchoMode(QLineEdit::Password);

        //设置样式
        //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
        QFile styleSheet(":/qss/res/qss/defaultstyle/application.qss");

        if (!styleSheet.open(QIODevice::ReadOnly)) {
          qWarning("Unable to open :/qss/res/qss/defaultstyle/application.qss");
          return;
        }
        this->setStyleSheet(styleSheet.readAll());


        //group input layout
//        QGridLayout *layoutIn = new QGridLayout;
//        layoutIn->addWidget(ui->label_user,0,0);
//        layoutIn->addWidget(ui->lineEdit_user,0,1);
//        ui->groupBox_Input->setLayout(layoutIn);
        //setLwEwAhsize(50,50,34);

        //设置label和lineedit位置
        ui->lineEdit_user->setGeometry(111,170,231,41);
        ui->lineEdit_Password->setGeometry(111,240,231,41);
        ui->lineEdit_Key->setGeometry(111,310,231,41);
        //设置样式属性
        ui->label_user->setProperty("style","withframe");
        ui->label_passWord->setProperty("style","withframe");
        ui->label_Key->setProperty("style","withframe");

#if 1
        // 创建字体
        QFont font =SetIconFont();
        //将此字体设为QApplication的默认字体
        font.setPointSize(10);

        ui->label_user->setFont(font);
        ui->label_user->setText(ICON_USER);
        ui->label_passWord->setFont(font);
        ui->label_passWord->setText(ICON_PASSWORD);
        ui->label_Key->setFont(font);
        ui->label_Key->setText(ICON_KEY);

        //最大最小化图标
        font.setPointSize(10);

        ui->pushButton_Close->setFont(font);
        ui->pushButton_Close->setText(ICON_CLOSE);

        ui->pushButton_Mini->setFont(font);
        ui->pushButton_Mini->setText(ICON_MINI);

        //设置全局字体
        SetSourceHanSans();
        //ui->label_test->setStyleSheet("color: rgb(0, 160, 230);");
#endif

        //信号槽
        connect(ui->pushButton_Close, &QPushButton::clicked, this, &loginDialog::close);
        connect(ui->pushButton_Mini, &QPushButton::clicked, this, &loginDialog::minimumSize);

        connect(ui->pushbutton_Log,&QPushButton::clicked,this,&loginDialog::checkLogin);


}

loginDialog::~loginDialog()
{
    delete ui;
}



QFont loginDialog::SetIconFont()
{
  if (QFontDatabase::addApplicationFont(
          ":/iconfont/res/iconFont/fontawesome-webfont.ttf") < 0)
    qWarning() << "FontAwesome cannot be loaded !";

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

QFont loginDialog::SetSourceHanSans()
{
  qDebug()<<"SetSourceHanSans";

  if (QFontDatabase::addApplicationFont(
          ":/iconfont/res/iconFont/SourceHanSansCN-Bold.ttf") < 0)
    qWarning() << "SourceHan cannot be loaded !";

  int fontId = QFontDatabase::addApplicationFont(
      ":/iconfont/res/iconFont/SourceHanSansCN-Bold.ttf");
  QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
  qDebug() << "fontFamilies.size() " << fontFamilies.size();
  qDebug() << "fontFamilies: " << fontFamilies.at(0);

  // 创建字体
  QFont font;
  font.setFamily(fontFamilies.at(0));


  //将此字体设为QApplication的默认字体
  QApplication::setFont(font);

  return font;

}

void loginDialog::minimumSize()
{
   this->showMinimized();
  return;
}

void loginDialog::checkLogin()
{
  qDebug()<<"checkLogin()";
#if 0
  if(ui->lineEdit_user->text().trimmed() =="admin" &&
     linePassword->text().trimmed() =="admin")
    {
      QDialog::accept();
      qDebug()<<"OK  user name:"<<ui->lineEdit_user->text();
      qDebug()<<"key:"<<ui->lineEdit_Key->text();
    }else
    {
      qDebug()<<"user name:"<<ui->lineEdit_user->text();
      qDebug()<<"user name:"<<ui->lineEdit_user->displayText();
      qDebug()<<"key:"<<ui->lineEdit_Key->text();
      QMessageBox::warning(this,"警告","用户名或密码错误！！！",QMessageBox::Yes);

      // 清空内容
      ui->lineEdit_user->clear();
      linePassword->clear();
      //定位光标
      ui->lineEdit_user->setFocus();

    }
#endif
  QDialog::accept();

  return;

}
