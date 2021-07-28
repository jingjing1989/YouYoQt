#include "MyLeftBar.h"
#include "ui_MyLeftBar.h"
#include "utility/CommonUtility.h"

#include <QIcon>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtDebug>

MyLeftBar::MyLeftBar(QWidget *parent) : QWidget(parent), ui(new Ui::MyLeftBar) {
  ui->setupUi(this);
  initTreeWIdget();
}

MyLeftBar::~MyLeftBar() {
  delete ui;
}

void MyLeftBar::setOneTreeWidgetItem(QTreeWidgetItem *treeItem, QChar icon, QString menuName) {
  QLabel *label = new QLabel(ui->treeWidget);
  label->setProperty("class", "icon");
  CommonUtility::setIconFont(icon, label, 12);
  ui->treeWidget->setItemWidget(treeItem, 0, label);
  treeItem->setText(1, menuName);
  treeItem->setFont(2, QFont("FontAwesome", 12));
  treeItem->setText(2, QChar(0xf101));
}

//初始化树状widget
void MyLeftBar::initTreeWIdget() {
  ui->treeWidget->clear();
  ui->treeWidget->setRootIsDecorated(false);      //隐藏根节点前面的小箭头
  ui->treeWidget->setFrameStyle(QFrame::NoFrame); //去掉边框
  ui->treeWidget->setColumnCount(3);              //第二列用于设置箭头
  ui->treeWidget->setColumnWidth(0, 40);          //设置列宽
  ui->treeWidget->setColumnWidth(1, 86);
  ui->treeWidget->setColumnWidth(2, 24);
  // 1 收藏
  QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
  this->setOneTreeWidgetItem(group1, QChar(0xf005), "我的收藏");
  QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
  subItem11->setText(1, "子元素1");

  // 2 我的首页
  QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
  this->setOneTreeWidgetItem(group2, QChar(0xf015), "我的首页");
  QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
  subItem21->setText(1, "我的首页");

  // 3 基础交易
  QTreeWidgetItem *group3 = new QTreeWidgetItem(ui->treeWidget);
  this->setOneTreeWidgetItem(group3, QChar(0xf1cc), "基础交易");
  QTreeWidgetItem *subItem31 = new QTreeWidgetItem(group3);
  subItem31->setText(1, "普通交易");
  QTreeWidgetItem *subItem32 = new QTreeWidgetItem(group3);
  subItem32->setText(1, "信用交易");
  QTreeWidgetItem *subItem33 = new QTreeWidgetItem(group3);
  subItem33->setText(1, "一件申购");
  QTreeWidgetItem *subItem34 = new QTreeWidgetItem(group3);
  subItem34->setText(1, "增强交易");

  // 4 特色交易
  QTreeWidgetItem *group4 = new QTreeWidgetItem(ui->treeWidget);
  this->setOneTreeWidgetItem(group4, QChar(0xf184), "特色交易");
  QTreeWidgetItem *subItem41 = new QTreeWidgetItem(group4);
  subItem41->setText(1, "组合交易");
  QTreeWidgetItem *subItem42 = new QTreeWidgetItem(group4);
  subItem42->setText(1, "无忧减持");
  QTreeWidgetItem *subItem43 = new QTreeWidgetItem(group4);
  subItem43->setText(1, "逆回购助手");

  // 5 算法交易
  QTreeWidgetItem *group5 = new QTreeWidgetItem(ui->treeWidget);
  this->setOneTreeWidgetItem(group5, QChar(0xf11b), "算法交易");
  QTreeWidgetItem *subItem51 = new QTreeWidgetItem(group5);
  subItem51->setText(1, "算法交易New");
  QTreeWidgetItem *subItem52 = new QTreeWidgetItem(group5);
  subItem52->setText(1, "策略交易");

  return;
}

void MyLeftBar::setHeaderItem(QTreeWidgetItem *pItem) {
  ui->treeWidget->header()->setVisible(false); //隐藏表头
}

bool MyLeftBar::eventFilter(QObject *watched, QEvent *event) {
  if (watched == ui->treeWidget) {
    if (event->type() == QEvent::HoverEnter) {
      qDebug() << event;
      return true;
    }
  }
  return QWidget::eventFilter(watched, event); //?
}

void MyLeftBar::setshrinkTree(int height) {
  this->setFixedWidth(height);
}

int MyLeftBar::shrinkTree() {
  return this->width();
}

void MyLeftBar::setExpandsOnDoubleClick(bool isExpand) {
  ui->treeWidget->setExpandsOnDoubleClick(isExpand);
}

void MyLeftBar::setExpand(bool isExpand) {
  ui->treeWidget->setItemsExpandable(isExpand);
}

QTreeWidget *MyLeftBar::GetTreeWidget() {
  return ui->treeWidget;
}
