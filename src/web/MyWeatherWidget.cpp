#include "MyWeatherWidget.h"
#include "ui_MyWeatherWidget.h"

const int FixedRowCount = 6;
const int FixedColumnCount = 4;
const QString ICONSUUNYCLOUDY = ":/images/res/images/weather/sunnycloudy.png";
const QString ICONCLOUDY = ":/images/res/images/weather/cloudy.png";
const QString ICONHEAVYRAIN = ":/images/res/images/weather/heavyrain.png";
const QString ICONLIGHTRAIN = ":/images/res/images/weather/lightrain.png";
const QString ICONSUNNY = ":/images/res/images/weather/sunny.png";
const QString ICONTHUNDERSHOWER =
    ":/images/res/images/weather/thunder shower.png";

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
  // QItemSelectionModel *selectionModel = new QItemSelectionModel(model);

  ui->tableView->setModel(model);
  //设置选择模型
  // ui->tableView->setSelectionModel(selectionModel); //设置选择模型
  // ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
  // ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

  //为各列设置自定义代理组件
  /*  labelDelgate = new LabelDelegate(this);
    ui->tableView->setItemDelegateForRow(1, labelDelgate); *///??
                                                         //设置数据模型

  ui->tableView->setItemDelegate(new RowDelegate);

  //行列自适应模式
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  // ui->tableView->setRowHeight(1, 200);
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
    //设置平均分不可选择  仅仅不可选择,可编辑
    // aItem->setFlags(aItem->flags() & (~Qt::ItemIsSelectable));
    //无设置属性 显示灰色不可选择 不可编辑
    // aItem->setFlags(Qt::NoItemFlags);
    //    aItem->setFlags(aItem->flags() & ~Qt::ItemIsEnabled &
    //                    ~Qt::ItemIsSelectable);
    model->setItem(0, col, aItem);

    aItem = new QStandardItem("");
    aItem->setSelectable(false);
    model->setItem(1, col, aItem);
    QLabel *label = new QLabel();
    // 图片不重复，可设置缩放比例，不可动态缩放
    QImage *img = new QImage;
    QString strICon = getWeatherIcon(mapValue["type"]);
    img->load(strICon);
    QImage scaledimg;
    scaledimg =
        img->scaled(label->width(), label->height(), Qt::KeepAspectRatio);
    label->setPixmap(QPixmap::fromImage(scaledimg));
    label->setScaledContents(true);
    ui->tableView->setIndexWidget(model->index(1, col), label);
#if 0
    aItem->setFlags(Qt ::ItemIsEnabled);
    // aItem->setFlags(Qt ::ItemIsEditable);
#endif

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

//设置天气类型图标
QString MyWeatherWidget::getWeatherIcon(QString weaType) {
  qDebug() << __FUNCTION__;
  qDebug() << weaType;
  if (weaType.contains("晴") && weaType.contains("多云")) {
    qDebug() << "ICONSUUNYCLOUDY";
    return ICONSUUNYCLOUDY;

  } else if (weaType.contains("晴")) {
    qDebug() << "ICONSUUNYCLOUDY";
    return ICONSUNNY;

  } else if (weaType.contains("多云")) {
    return ICONCLOUDY;
    // qDebug() << "ICONCLOUDY";
  } else if (weaType.contains("大雨") || weaType.contains("中雨")) {
    qDebug() << "ICONHEAVYRAIN";
    return ICONHEAVYRAIN;

  } else if (weaType.contains("小雨")) {
    qDebug() << "ICONLIGHTRAIN";
    return ICONLIGHTRAIN;

  } else if (weaType.contains("雷")) {
    qDebug() << "ICONTHUNDERSHOWER";
    return ICONTHUNDERSHOWER;
  }
  return "";
}
