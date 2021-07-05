#ifndef MYTOOLBUTTON_H
#define MYTOOLBUTTON_H

#include <QString>
#include <QToolButton>
#include <QWidget>

namespace Ui {
class MyToolButton;
}

class MyToolButton : public QToolButton {
  Q_OBJECT

public:
  explicit MyToolButton(QWidget *parent = nullptr);
  ~MyToolButton();

  void SetIconFont(QString istr);
  void SetText(QString istr);

  QFont SetIconFont();

  void SetIconTextGeometry(int iconx, int icony, int iconw, int iconh, int textx, int texty, int textw, int texth);

private:
  Ui::MyToolButton *ui;

  //重写 paintEvent 函数
  // void paintEvent(QPaintEvent *);
};

#endif // MYTOOLBUTTON_H
