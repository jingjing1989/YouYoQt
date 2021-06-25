#include "MyLeftBar.h"
#include "ui_MyLeftBar.h"
#include "utility/CommonUtility.h"

#include <QTreeWidget>
#include <QtDebug>
#include <QTreeWidgetItem>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QPropertyAnimation>


#define ICONARROW ":/image/files/images/leftbar/arrow/right.png"

MyLeftBar::MyLeftBar(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MyLeftBar)
{
  ui->setupUi(this);
  initTreeWIdget();

  //initControl();

//  ui->treeWidget->setAttribute(Qt::WA_Hover, true); //开启悬停事件
//  ui->treeWidget->installEventFilter(this); //安装事件过滤器
}

MyLeftBar::~MyLeftBar()
{
  delete ui;
}

//初始化树状widget
void MyLeftBar::initTreeWIdget()
{
  ui->treeWidget->clear();
  ui->treeWidget->header()->setVisible(false); //隐藏表头
  ui->treeWidget->setRootIsDecorated(false);//隐藏根节点前面的小箭头
  ui->treeWidget->setFrameStyle(QFrame::NoFrame);//去掉边框



  #if 0
  this ->setStyleSheet("QTreeView::branch:has-children:!has-siblings:closed,\
  QTreeView::branch:closed:has-children:has-siblings{border-image: none; image: url(:/image/files/images/leftbar/collect.png);}\
  QTreeView::branch:hover:has-children:!has-siblings,\
  QTreeView::branch:hover:has-children:has-siblings{border-image: none; image: url(:/image/files/images/leftbar/collect_sle.png);}");


  QIcon icon;
  icon.addPixmap(QPixmap(":/image/files/images/leftbar/collect_sle.png"), QIcon::Selected);
  icon.addPixmap(QPixmap(":/image/files/images/leftbar/collect.png"), QIcon::Normal);


  group1->setIcon(0,icon);
#endif

//ui->treeWidget->setLayoutDirection(Qt::RightToLeft);//设置右到左排列
  ui->treeWidget->setColumnCount(2);//第二列用于设置箭头
  //ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//鼠标点击哪个列会有这个列的虚线框

  ui->treeWidget->setColumnWidth(0, 180);  //设置列宽
  ui->treeWidget->setColumnWidth(1, 30);
  //1 收藏
  QTreeWidgetItem * group1 = new QTreeWidgetItem(ui->treeWidget);
  group1->setText(0,"我的收藏");
  //group1->setFlags(Qt::NoItemFlags);

  //group1->setIcon(0,QIcon(":/image/files/images/leftbar/collect.png"));
  group1->setIcon(1,QIcon(ICONARROW));

  //QIcon mode 设置无效？？
  QIcon icon;
#if 0
  icon.addPixmap(QPixmap(":/image/files/images/leftbar/collect_sle.png.png"), QIcon::Active);
  icon.addPixmap(QPixmap(":/image/files/images/leftbar/collect_sle.png.png"), QIcon::Selected);
  icon.addPixmap(QPixmap(":/image/files/images/leftbar/collect_sle.png.png"), QIcon::Selected);
#endif
  icon.addPixmap(QPixmap(":/images/res/images/leftbar/collect.png"),
                 QIcon::Normal);
  group1->setIcon(0, icon);



  //group1->setTextAlignment(1,Qt::AlignRight);

  //group1->setTextAlignment(0,Qt::AlignRight);//必要,这个也要往右排列，因为前面设置了setLayoutDirection


  QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
  //subItem11->setFlags(Qt::NoItemFlags);
  subItem11->setText(0, "子元素1");



  //2 我的首页
  QTreeWidgetItem * group2 = new QTreeWidgetItem(ui->treeWidget);
  group2->setText(0,"我的首页");
  group2->setIcon(0, QIcon(":/images/res/images/leftbar/homepage.png"));

  group2->setIcon(1,QIcon(ICONARROW));

  QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
  subItem21->setText(0, "我的首页");

  //3 基础交易
  QTreeWidgetItem * group3 = new QTreeWidgetItem(ui->treeWidget);
  group3->setText(0,"基础交易");
  //group3->setFlags(Qt::NoItemFlags);
  group3->setIcon(0, QIcon(":/images/res/images/leftbar/otc.png"));
  group3->setIcon(1,QIcon(ICONARROW));

  QTreeWidgetItem *subItem31 = new QTreeWidgetItem(group3);
  subItem31->setText(0, "普通交易");

  QTreeWidgetItem *subItem32 = new QTreeWidgetItem(group3);
  subItem32->setText(0, "信用交易");

  QTreeWidgetItem *subItem33 = new QTreeWidgetItem(group3);
  subItem33->setText(0, "一件申购");

  QTreeWidgetItem *subItem34 = new QTreeWidgetItem(group3);
  subItem34->setText(0, "增强交易");

  //4 特色交易
  QTreeWidgetItem * group4 = new QTreeWidgetItem(ui->treeWidget);
  group4->setText(0,"特色交易");
  group4->setIcon(0, QIcon(":/images/res/images/leftbar/arbitrage.png"));
  group4->setIcon(1,QIcon(ICONARROW));

  QTreeWidgetItem *subItem41 = new QTreeWidgetItem(group4);
  subItem41->setText(0, "组合交易");

  QTreeWidgetItem *subItem42 = new QTreeWidgetItem(group4);
  subItem42->setText(0, "无忧减持");

  QTreeWidgetItem *subItem43 = new QTreeWidgetItem(group4);
  subItem43->setText(0, "逆回购助手");

  //5 算法交易
  QTreeWidgetItem * group5 = new QTreeWidgetItem(ui->treeWidget);
  group5->setText(0,"算法交易");
  group5->setIcon(0, QIcon(":/images/res/images/leftbar/algorithm.png"));
  group5->setIcon(1,QIcon(ICONARROW));

  QTreeWidgetItem *subItem51 = new QTreeWidgetItem(group5);
  subItem51->setText(0, "算法交易New");

  QTreeWidgetItem *subItem52 = new QTreeWidgetItem(group5);
  subItem52->setText(0, "策略交易");


  return;
}

void MyLeftBar::setHeaderItem(QTreeWidgetItem* pItem)
{
  ui->treeWidget->header()->setVisible(false); //隐藏表头

}

bool MyLeftBar::eventFilter(QObject *watched, QEvent *event)
{
  if(watched == ui->treeWidget) {
      if(event->type() == QEvent::HoverEnter) {
          qDebug() << event;
          return true;
      }
  }


  return QWidget::eventFilter(watched, event);//?

}



void MyLeftBar::setshrinkTree(int height)
{
    this->setFixedWidth(height);
}

int MyLeftBar::shrinkTree()
{
    return this->width();
}

void MyLeftBar::setExpandsOnDoubleClick(bool isExpand)
{
  ui->treeWidget->setExpandsOnDoubleClick(isExpand);  //屏蔽双击事件对树节点展开的影响

}

void MyLeftBar::setExpand(bool isExpand)
{
  ui->treeWidget->setItemsExpandable(isExpand);
}
