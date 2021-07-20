#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>

namespace Ui {
class NetWorkWidget;
}

class NetWorkWidget : public QWidget
{
  Q_OBJECT

public:
  explicit NetWorkWidget(QWidget *parent = nullptr);
  ~NetWorkWidget();

private:
  Ui::NetWorkWidget *ui;
};

#endif // NETWORKWIDGET_H
