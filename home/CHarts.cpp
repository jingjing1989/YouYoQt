#include "CHarts.h"
#include "ui_CHarts.h"

CHarts::CHarts(QWidget *parent) : QWidget(parent), ui(new Ui::CHarts) {
  ui->setupUi(this);
  stanModel = new QStandardItemModel(iniDataRowCount, fixedColumnCount, this); //数据模型

  // test 设置splitter 内控件比例
  //  ui->splitter->setStretchFactor(0, 2);
  //  ui->splitter->setStretchFactor(1, 4);
  //  ui->splitter->setStretchFactor(2, 4);
  //初始化数据
  iniData();

  ui->tableView->setModel(stanModel); //设置数据模型

  iniBarChart();
}

CHarts::~CHarts() { delete ui; }

//数据初始化
void CHarts::iniData() {

  QStringList headerList;
  headerList << "姓名"
             << "数学"
             << "语文"
             << "英语"
             << "平均分";
  //设置表头文字
  stanModel->setHorizontalHeaderLabels(headerList);

  //设置随机数
  qsrand(QTime::currentTime().second());
  for (int i = 0; i < stanModel->rowCount(); i++) {
    QString stuName = QString("学生%2").arg(i + 1);
    //创建item
    QStandardItem *sItem = new QStandardItem(stuName);
    sItem->setTextAlignment(Qt::AlignHCenter);
    stanModel->setItem(i, ColNoName, sItem);

    qreal aveScore = 0;
    for (int j = ColNoMath; j <= ColNoEnglish; j++) {
      qreal score = 50 + (qrand() % 50); //随机数
      aveScore += score;
      // sItem = new QStandardItem(QString::asprintf("%0.f", score));
      QString strScore = QString::number(score, 10, 1);
      sItem = new QStandardItem(strScore);
      sItem->setTextAlignment(Qt::AlignHCenter);
      stanModel->setItem(i, j, sItem);
    }
    aveScore = aveScore / 3;
    // sItem = new QStandardItem(QString("%1").arg(aveScore));
    QString strAverage = QString::number(aveScore, 10, 2);
    sItem = new QStandardItem(strAverage);
    sItem->setTextAlignment(Qt::AlignHCenter);
    //设置平均分不许编辑
    //需要执行反操作
    sItem->setFlags(sItem->flags() & (~Qt::ItemIsEditable)); //用msvc !编译不通过,~mingw和msvc都可以
    stanModel->setItem(i, ColNoAverage, sItem);
  }
}
//统计数据 计算各个分数段数据
void CHarts::CalculateData() {
  //  int cnt50, cnt60, cnt70, cnt80, cnt90;
  //  qreal sumV, minV, maxV;
  //  qreal val;
  //  QTreeWidgetItem *treItem = nullptr;

  //  int i, j;
  //  for (i = ColNoMath; i <= ColNoAverage; i++) {
  //    sumV = 0;
  //    cnt50 = 0;
  //    cnt60 = 0;
  //    cnt70 = 0;
  //    cnt80 = 0;
  //    cnt90 = 0;
  //    for (j=0;j<stanModel->rowCount();j++) {
  //      val=stanModel->item(j,i)->text().toDouble();
  //      if()
  //    }

  //  }
}
//柱状图初始化
void CHarts::iniBarChart() {
  QChart *chart = new QChart(); //创建chart
  chart->setTitle("Barchart演示");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  ui->graphicsView_Bar->setChart(chart); //为ChartView设置chart
  ui->graphicsView_Bar->setRenderHint(QPainter::Antialiasing);

  buildBarChart();
}

//构造柱状图
void CHarts::buildBarChart() {
  QChart *chart = ui->graphicsView_Bar->chart(); //获取ChartView关联的chart
  chart->removeAllSeries();                      //删除所有序列

  chart->removeAxis(chart->axisX()); //删除坐标轴
  chart->removeAxis(chart->axisY()); //删除坐标轴

  //创建三个QBarSet数据集,从数据模型的表头获取Name
  QBarSet *setMath = new QBarSet(stanModel->horizontalHeaderItem(ColNoMath)->text());
  QBarSet *setChinese = new QBarSet(stanModel->horizontalHeaderItem(ColNoChinese)->text());
  QBarSet *setEnglish = new QBarSet(stanModel->horizontalHeaderItem(ColNoEnglish)->text());

  QLineSeries *Line = new QLineSeries(); //创建一个QLineSeries序列用于显示平均分
  Line->setName(stanModel->horizontalHeaderItem(ColNoAverage)->text());
  QPen pen;
  pen.setColor(Qt::red);
  pen.setWidth(2);
  Line->setPen(pen);
  //    lineseries->setPointLabelsVisible(true);
  //    lineseries->setPointLabelsFormat("@yPoint");

  for (int i = 0; i < stanModel->rowCount(); i++) {                                //从数据模型获取数据
    setMath->append(stanModel->item(i, ColNoMath)->text().toDouble());             //数学
    setChinese->append(stanModel->item(i, ColNoChinese)->text().toDouble());       //语文
    setEnglish->append(stanModel->item(i, ColNoEnglish)->text().toDouble());       //英语
    Line->append(QPointF(i, stanModel->item(i, ColNoAverage)->text().toDouble())); //平均分
  }

  //创建一个柱状图序列 QBarSeries, 并添加三个数据集
  QBarSeries *series = new QBarSeries();
  series->append(setMath);
  series->append(setChinese);
  series->append(setEnglish);
  //    series->setLabelsVisible(true);
  //    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);// LabelsCenter
  //    series->setLabelsPosition(QAbstractBarSeries::LabelsCenter);// LabelsCenter

  //    lineseries->setPointLabelsVisible(true);
  //    lineseries->setPointLabelsFormat("@yPoint");

  chart->addSeries(series); //添加柱状图序列
  chart->addSeries(Line);   //添加折线图序列

  //用于横坐标在字符串列表,即学生姓名
  QStringList categories;
  for (int i = 0; i < stanModel->rowCount(); i++) {

    categories << stanModel->item(i, ColNoName)->text();
    qDebug() << stanModel->item(i, ColNoName)->text();
  }

  //用于柱状图的坐标轴
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories); //添加横坐标文字列表
  //    chart->createDefaultAxes();

  chart->setAxisX(axisX, series);                                           //设置横坐标
  chart->setAxisX(axisX, Line);                                             //设置横坐标
  axisX->setRange(categories.at(0), categories.at(categories.count() - 1)); //这只坐标轴范围

  //数值型坐标作为纵轴
  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(0, 100);
  axisY->setTitleText("分数");
  axisY->setTickCount(6);        // 11
  axisY->setLabelFormat("%.0f"); //标签格式
  //    axisY->setGridLineVisible(false);
  //    axisY->setMinorTickCount(4);
  chart->setAxisY(axisY, series); //为
  chart->setAxisY(axisY, Line);

  //    lineseries->setPointLabelsVisible(true);
  //    lineseries->setPointLabelsFormat("@yPoint");

  chart->legend()->setVisible(true);              //显示图例
  chart->legend()->setAlignment(Qt::AlignBottom); //图例显示在下方
}
