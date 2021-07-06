#pragma execution_character_set("utf-8")
#ifndef CHARTS_H
#define CHARTS_H

#include <QAbstractAxis>
#include <QPieSeries>
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
  //柱状图初始化
  void iniBarChart();

  //构建柱状图
  void buildBarChart();

  //饼图初始化
  void initPieChart();

  //构建饼图
  void buildPieChart();

  //初始化堆叠柱状图
  void initStackedBarChart();

  //构建堆叠柱状图
  void buildStackedBarChart();

  //初始化百分比柱状图
  void initPercentBarCHart();

  //构建百分比柱状图
  void buildPercentBarChart();

  //初始化散点图
  void initScatterChart();

  //构建散点图
  void buildScatterChart();
};

#endif // CHARTS_H
