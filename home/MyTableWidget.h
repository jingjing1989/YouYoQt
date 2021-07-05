#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class MyTableWidget;
}

class MyTableWidget : public QWidget {
  Q_OBJECT

public:
  explicit MyTableWidget(QWidget *parent = nullptr);
  ~MyTableWidget();

private:
  Ui::MyTableWidget *ui;

  void pushButtonAddClick();

  void pushButtonDelClick();

  void searchTextChanged(const QString &str);

  //设置表头
  void SetHeaders();

  //设置模糊搜索匹配
  void SetCompleter(QStringList word_list);
};

#endif // MYTABLEWIDGET_H
