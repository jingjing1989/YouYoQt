#pragma execution_character_set("utf-8")
#ifndef MYLEFTBAR_H
#define MYLEFTBAR_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
  class MyLeftBar;
}

class MyLeftBar : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(int shrinkTree READ shrinkTree WRITE setshrinkTree)

public:
  explicit MyLeftBar(QWidget *parent = nullptr);
  ~MyLeftBar();

  void setHeaderItem(QTreeWidgetItem* pItem);

  void setExpandsOnDoubleClick(bool isExpand);

  void setExpand(bool isExpand);

private:
  Ui::MyLeftBar *ui;

  void initTreeWIdget();

  bool eventFilter(QObject *watched, QEvent *event);

  //void initControl();


  void setshrinkTree(int height);

  int shrinkTree();
};

#endif // MYLEFTBAR_H
