#pragma execution_character_set("utf-8")
#ifndef MyWeatherWidget_H
#define MyWeatherWidget_H

#include "LabelDelegate.h"
#include "weather.h"
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class MyWeatherWidget;
}

class MyWeatherWidget : public QWidget {
  Q_OBJECT

public:
  explicit MyWeatherWidget(QWidget *parent = nullptr);
  ~MyWeatherWidget();

private:
  void GetWeatherInfo();

  //初始化预报表格
  void initTableForecast();

  Ui::MyWeatherWidget *ui;

  weather *weatherInfo = nullptr;

  //自定义代理组件
  LabelDelegate labelDelgate;
};

#endif // MyWeatherWidget_H
