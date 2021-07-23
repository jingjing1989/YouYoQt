#include "MyWeatherWidget.h"
#include "ui_MyWeatherWidget.h"

const int FixedRowCount = 6;
const int FixedColumnCount = 4;
MyWeatherWidget::MyWeatherWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MyWeatherWidget) {
  ui->setupUi(this);

  QString strCity = QString::fromUtf8("上海");
  weatherInfo = new weather(strCity);

  //关联信号槽
  connect(weatherInfo, &weather::getDataFinisedSignal, this,
          &MyWeatherWidget::GetWeatherInfo);
}

MyWeatherWidget::~MyWeatherWidget() { delete ui; }

void MyWeatherWidget::GetWeatherInfo() {
  qDebug() << __FUNCTION__;
  ui->label_City->setText(weatherInfo->getCityName());
  ui->label_Type->setText(weatherInfo->getWeatherType());
  ui->label_Wind->setText(weatherInfo->getWind());
  ui->label_Temprature->setText(weatherInfo->getCurrentTemprature());
  ui->label_Range->setText(weatherInfo->getTempratureRange());
  ui->label_Date->setText(weatherInfo->getCurrentDate());
  ui->label_tips->setText(weatherInfo->getColdInfo());

  initTableForecast();
}

void MyWeatherWidget::initTableForecast() {
  qDebug() << __FUNCTION__;
  //创建数据模型代理
  QStandardItemModel *model =
      new QStandardItemModel(FixedRowCount, FixedColumnCount, this);

  //选择模型
  QItemSelectionModel *selectionModel = new QItemSelectionModel(model);

  //设置数据模型

  ui->tableView->setSelectionModel(selectionModel);
  //为各列设置自定义代理组件
  ui->tableView->setItemDelegate(&labelDelgate); //??

  ui->tableView->setModel(model);
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //设置表格数据
  QVector<QMap<QString, QString>> data = weatherInfo->getAllDataMap();
  qDebug() << "data size:" << data.size();
  QStandardItem *aItem = nullptr;
  for (int col = 0; col < FixedColumnCount; col++) {
    if (col > data.size() - 1)
      continue;

    // ui->tableView->setRowHeight(1, 500);

    QMap<QString, QString> mapValue = data.at(col);
    qDebug() << "mapValue date:" << mapValue["date"];
    aItem = new QStandardItem(mapValue["date"]);
    //居中
    aItem->setTextAlignment(Qt::AlignCenter);
    //设置鼠标不可选
    aItem->setSelectable(false);
    model->setItem(0, col, aItem);

    aItem = new QStandardItem(mapValue["type"]);
    // aItem->setSizeHint(QSize(500, 100));
    //居中
    aItem->setTextAlignment(Qt::AlignCenter);
    //设置鼠标不可选
    aItem->setSelectable(false);
    model->setItem(1, col, aItem);

    aItem = new QStandardItem(mapValue["low"]);
    //居中
    aItem->setTextAlignment(Qt::AlignCenter);
    //设置鼠标不可选
    aItem->setSelectable(false);
    model->setItem(2, col, aItem);

    aItem = new QStandardItem(mapValue["high"]);
    //居中
    aItem->setTextAlignment(Qt::AlignCenter);
    //设置鼠标不可选
    aItem->setSelectable(false);
    model->setItem(3, col, aItem);

    aItem = new QStandardItem(mapValue["type"]);
    //居中
    aItem->setTextAlignment(Qt::AlignCenter);
    //设置鼠标不可选
    aItem->setSelectable(false);
    model->setItem(4, col, aItem);

    aItem = new QStandardItem(mapValue["wind"]);
    //居中
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setSelectable(false);
    model->setItem(5, col, aItem);
  }
}
