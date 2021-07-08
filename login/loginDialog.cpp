#pragma execution_character_set("utf-8")
#include "loginDialog.h"
#include "ui_loginDialog.h"
#include "utility/CommonUtility.h"
#include <QChar>
#include <QDebug>
#include <QFile>
#include <QFontDatabase>
#include <QGridLayout>
#include <QMessageBox>
#include <QPainter>

#define ICON_USER QChar(0xf007)
#define ICON_PASSWORD QChar(0xf023)
#define ICON_KEY QChar(0xf14c)
#define ICON_CLOSE QChar(0xf2d3)
#define ICON_MINI QChar(0xf2d1)

loginDialog::loginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::loginDialog) {
  ui->setupUi(this);
  //为对话框加上最大化最小化按钮
  this->setWindowFlags(this->windowFlags() & Qt::WindowMaximizeButtonHint & Qt::WindowMinimizeButtonHint);
  this->setAttribute(Qt::WA_TranslucentBackground);
  //设置无边框,点击图标栏可放大缩小  最大化最小化  |Qt::FramelessWindowHint
  setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::FramelessWindowHint);
  //密码显示黑圆圈
  ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
  //设置样式
  CommonUtility::setStyleSheet(":/qss/res/qss/defaultstyle/login.css", this);
  // 创建字体
  QFont iconfont("FontAwesome", 10);
  ui->label_user->setFont(iconfont);
  ui->label_user->setText(ICON_USER);
  ui->label_password->setFont(iconfont);
  ui->label_password->setText(ICON_PASSWORD);
  ui->label_key->setFont(iconfont);
  ui->label_key->setText(ICON_KEY);

  //最大最小化图标
  ui->pushButton_Close->setFont(iconfont);
  ui->pushButton_Close->setText(ICON_CLOSE);
  ui->pushButton_Mini->setFont(iconfont);
  ui->pushButton_Mini->setText(ICON_MINI);

  //信号槽
  connect(ui->pushButton_Close, &QPushButton::clicked, this, &loginDialog::close);
  connect(ui->pushButton_Mini, &QPushButton::clicked, this, &loginDialog::minimumSize);
  connect(ui->pushbutton_Log, &QPushButton::clicked, this, &loginDialog::checkLogin);
}

loginDialog::~loginDialog() { delete ui; }

void loginDialog::minimumSize() {
  this->showMinimized();
  return;
}

void loginDialog::checkLogin() {
  qDebug() << "checkLogin()";
  QDialog::accept();

  return;
}
/**重写绘制算法加上圆角
 * @brief loginDialog::paintEvent
 * @param event
 */
void loginDialog::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  //拿默认背景的刷子
  painter.setBrush(QPalette().window());
  painter.setPen(Qt::transparent);

  QRect rect = this->rect();
  rect.setWidth(rect.width() - 1);
  rect.setHeight(rect.height() - 1);
  painter.drawRoundedRect(rect, 15, 15);
  QWidget::paintEvent(event);
}
