#pragma execution_character_set("utf-8")
#include "MyToolButton.h"
#include "ui_MyToolButton.h"

#include <QDebug>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

MyToolButton::MyToolButton(QWidget *parent) : QToolButton(parent), ui(new Ui::MyToolButton) {
  ui->setupUi(this);

  // label->setFixedWidth(120);
  // new一个V布局，若想左右放图片和文本，将QVBoxLayout改为QHBoxLayout即可
  //  QVBoxLayout* myLayout = new QVBoxLayout();
  //  myLayout->addSpacing(0);
  //  myLayout->addWidget(ui->label_Icon);
  //  myLayout->addSpacing(0);
  //  myLayout->addWidget(ui->label_Text);
  //  myLayout->addStretch();
  //  setLayout(myLayout);

  //设置样式
  //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
  QFile styleSheet(":/qss/files/MyToolButton.css");

  if (!styleSheet.open(QIODevice::ReadOnly)) {
    qWarning("Unable to open :/files/blue.qss");
    return;
  }

  this->setStyleSheet(styleSheet.readAll());
  // ui->label_Text->setStyleSheet("file:///:/qss/files/MyToolButton.qss");
  // ui->label_Text->setStyleSheet("QLabel{background-color:rgb(59,183,212);}");

  SetIconTextGeometry(0, 0, 200, 80, 0, 80, 200, 70);

  //创建字体iconfont
  QFont font = SetIconFont();
  font.setPointSize(35);
  ui->label_Icon->setFont(font);
}

MyToolButton::~MyToolButton() { delete ui; }

//设置上方IconFont
void MyToolButton::SetIconFont(QString istr) {
  ui->label_Icon->setText(istr);
  return;
}

//设置下方文本
void MyToolButton::SetText(QString istr) {
  ui->label_Text->setText(istr);
  return;
}

void MyToolButton::SetIconTextGeometry(int iconx, int icony, int iconw, int iconh, int textx, int texty, int textw, int texth) {
  ui->label_Icon->setGeometry(iconx, icony, iconw, iconh);
  ui->label_Text->setGeometry(textx, texty, textw, texth);

  return;
}
QFont MyToolButton::SetIconFont() {
  if (QFontDatabase::addApplicationFont(":/iconfont/res/iconFont/fontawesome-webfont.ttf") < 0)
    qWarning() << "FontAwesome cannot be loaded !";

  int fontId = QFontDatabase::addApplicationFont(":/iconfont/res/iconFont/fontawesome-webfont.ttf");
  QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
  qDebug() << "fontFamilies.size() " << fontFamilies.size();
  qDebug() << "fontFamilies: " << fontFamilies.at(0);

  // 创建字体
  QFont font;
  font.setFamily(fontFamilies.at(0));

  //将此字体设为QApplication的默认字体
  // QApplication::setFont(font);

  return font;
}

// void MyToolButton::paintEvent(QPaintEvent *)
//{
//  QStyleOption opt;
//  opt.init(this);
//  QPainter p(this);
//  style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);

//}
