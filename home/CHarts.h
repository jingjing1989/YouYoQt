#pragma execution_character_set("utf-8")
#ifndef CHARTS_H
#define CHARTS_H

#include <QAbstractAxis>
#include <QStandardItem>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QWidget>
#include <QtCharts> //必须这么设置

QT_CHARTS_USE_NAMESPACE //必要要有这个宏

    namespace Ui {
  class CHarts;
}

const int fixedColumnCount = 5; //数据模型的列数
const int iniDataRowCount = 20; //学生个数

enum {
  ColNoName,
  ColNoMath,
  ColNoChinese,
  ColNoEnglish,
  ColNoAverage

};

class CHarts : public QWidget {
  Q_OBJECT

public:
  explicit CHarts(QWidget *parent = nullptr);
  ~CHarts();

private:
  Ui::CHarts *ui;

  QStandardItemModel *stanModel = nullptr;

  void iniData();

  void CalculateData();

  void iniBarChart();

  void buildBarChart();
};

#endif // CHARTS_H
