#include "CHarts.h"
#include "ui_CHarts.h"

CHarts::CHarts(QWidget *parent) : QWidget(parent), ui(new Ui::CHarts) {

  ui->setupUi(this);

  stanModel = new QStandardItemModel(iniDataRowCount, fixedColumnCount, this); //数据模型

  //初始化数据
  iniData();
  //统计数据
  CalculateData();

  //数据模块的 itemChanged信号与自定义的槽函数关联，用于自动计算平均分
  connect(stanModel, &QStandardItemModel::itemChanged, this, &CHarts::on_itemChanged);

  // comboBox_Style 下拉框改变 修改饼图主题
  void (QComboBox::*funSinglePara)(int) = &QComboBox::currentIndexChanged;
  connect(ui->comboBox_Style, funSinglePara, this, [=](int index) { ui->graphicsView_Pie->chart()->setTheme(QChart::ChartTheme(index)); });
  // connect(ui->comboBox_Style, &QComboBox::currentIndexChanged(int), this, &CHarts::on_cBoxTheme_currentIndexChanged(int));

  connect(ui->comboBox_Catagory, funSinglePara, this, [=]() { buildPieChart(); });

  void (QDoubleSpinBox::*funSingleParaSpinBox)(double) = &QDoubleSpinBox::valueChanged;
  connect(ui->doubleSpinBox_Hole, funSingleParaSpinBox, [=](double value) {
    QPieSeries *series;
    series = static_cast<QPieSeries *>(ui->graphicsView_Pie->chart()->series().at(0));
    series->setHoleSize(value);
  });

  connect(ui->doubleSpinBox_Pie, funSingleParaSpinBox, [=](double value) {
    QPieSeries *series;
    series = static_cast<QPieSeries *>(ui->graphicsView_Pie->chart()->series().at(0));
    series->setPieSize(value);
  });

  iniBarChart();

  initPieChart();

  initStackedBarChart();

  initPercentBarCHart();

  initScatterChart();

  // test 设置splitter 内控件比例 可是还是不行啊
  //  ui->splitter->setStretchFactor(0, 1 / 3);
  //  ui->splitter->setStretchFactor(1, 1 / 3);
  //  ui->splitter->setStretchFactor(2, 1 / 3);
}

CHarts::~CHarts() { delete ui; }

//数据初始化
void CHarts::iniData() {

  //设置了这种缩放方式之后，表头就不能再被拉伸完全失去响应。
  //  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  //  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  //  ui->tableView->horizontalHeader()->setMinimumSectionSize(10);
  //  ui->tableView->verticalHeader()->setMinimumSectionSize(10);

  //表头
  QStringList headerList;
  headerList << "姓名"
             << "数学"
             << "语文"
             << "英语"
             << "平均分";
  //设置表头文字
  stanModel->setHorizontalHeaderLabels(headerList);
  //设置列数
  stanModel->setColumnCount(headerList.size());

  //设置随机数
  qsrand(QTime::currentTime().second());
  for (int i = 0; i < stanModel->rowCount(); i++) {
    QString stuName = QString("学生%2").arg(i + 1);
    //创建item
    QStandardItem *sItem = new QStandardItem(stuName);
    sItem->setTextAlignment(Qt::AlignCenter);
    stanModel->setItem(i, ColNoName, sItem);

    qreal aveScore = 0;
    for (int j = ColNoMath; j <= ColNoEnglish; j++) {
      qreal score = 50 + (qrand() % 50); //随机数
      aveScore += score;
      // sItem = new QStandardItem(QString::asprintf("%0.f", score));
      QString strScore = QString::number(score, 10, 1);
      sItem = new QStandardItem(strScore);
      sItem->setTextAlignment(Qt::AlignCenter);
      stanModel->setItem(i, j, sItem);
    }
    //平均分
    aveScore = aveScore / 3;
    // sItem = new QStandardItem(QString("%1").arg(aveScore));
    QString strAverage = QString::number(aveScore, 10, 2);
    sItem = new QStandardItem(strAverage);
    sItem->setTextAlignment(Qt::AlignCenter);
    //设置平均分不许编辑 正常颜色
    // sItem->setFlags(sItem->flags() & (!Qt::ItemIsEditable));
    //需要执行反操作  &按位与:两位同时为“1”，结果才为“1”，否则为0
    // sItem->setFlags(sItem->flags() & (~Qt::ItemIsEditable)); //用msvc !编译不通过,~mingw和msvc都可以
    //无设置属性 显示灰色不可选择 不可编辑
    sItem->setFlags(Qt::NoItemFlags);
    //设置平均分不可选择  仅仅不可选择,可编辑
    // sItem->setFlags(sItem->flags() & (~Qt::ItemIsSelectable));
    stanModel->setItem(i, ColNoAverage, sItem);
  }
  //设置数据模型
  ui->tableView->setModel(stanModel);

  //根据内容来确定列宽度 要放在SetModel之后才有作用
  ui->tableView->resizeColumnsToContents();
  qDebug() << "stanModel->columnCount():  " << stanModel->columnCount();
  qDebug() << "ui->tableView->horizontalHeader()->count():  " << ui->tableView->horizontalHeader()->count();

  //每列设置宽度 要放在SetModel之后才有作用  setColumnWidth后还可以左右拉单元格
  for (int i = 0; i < ui->tableView->horizontalHeader()->count(); i++) {
    ui->tableView->setColumnWidth(i, ui->tableView->columnWidth(i) + 20); //多一些空余控件，不然每列内容很挤
    qDebug() << "ui->tableView->columnWidth(i) + 50:" << ui->tableView->columnWidth(i) + 50;
  }
  // m_tableView->horizontalHeader()->setStretchLastSection(true);        //最后一列补全所有空白位置
}
//统计数据 计算各个分数段数据
void CHarts::CalculateData() {
  int cnt50, cnt60, cnt70, cnt80, cnt90;
  qreal sumV, minV, maxV;
  qreal val;
  //树节点
  QTreeWidgetItem *treeItem = nullptr;

  int i, j;
  for (i = ColNoMath; i <= ColNoAverage; i++) {
    sumV = 0;
    cnt50 = 0;
    cnt60 = 0;
    cnt70 = 0;
    cnt80 = 0;
    cnt90 = 0;
    for (j = 0; j < stanModel->rowCount(); j++) {
      val = stanModel->item(j, i)->text().toDouble();
      //获得最大值最小值
      if (j == 0) {
        minV = val;
        maxV = val;
      }
      if (val < minV) {
        minV = val;
      }
      if (val > maxV) {
        maxV = val;
      }

      sumV += val;

      //统计分数段
      if (val < 60) {
        cnt50++;
      } else if (val >= 60 && val < 70) {
        cnt60++;
      } else if (val >= 70 && val < 80) {
        cnt70++;
      } else if (val >= 80 && val < 90) {
        cnt80++;
      } else {
        cnt90++;
      }
    }
    //数据写入widget
    //<60
    treeItem = ui->treeWidget_Data->topLevelItem(0);
    treeItem->setText(i, QString::number(cnt50));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
    //设置为红色
    treeItem->setForeground(i, QBrush(QColor(255, 0, 0)));
    // 60 - 70
    treeItem = ui->treeWidget_Data->topLevelItem(1);
    treeItem->setText(i, QString::number(cnt60));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
    // 70 - 80
    treeItem = ui->treeWidget_Data->topLevelItem(2);
    treeItem->setText(i, QString::number(cnt70));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
    // 80 -90
    treeItem = ui->treeWidget_Data->topLevelItem(3);
    treeItem->setText(i, QString::number(cnt80));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
    // 90
    treeItem = ui->treeWidget_Data->topLevelItem(4);
    treeItem->setText(i, QString::number(cnt90));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
    //
    qreal aveScore = sumV / stanModel->rowCount();
    treeItem = ui->treeWidget_Data->topLevelItem(5);
    treeItem->setText(i, QString::number(aveScore, 10, 2));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);

    // max
    treeItem = ui->treeWidget_Data->topLevelItem(6);
    treeItem->setText(i, QString::number(maxV));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
    // min
    treeItem = ui->treeWidget_Data->topLevelItem(7);
    treeItem->setText(i, QString::number(minV));
    treeItem->setTextAlignment(i, Qt::AlignHCenter);
  }
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

  //删除所有坐标轴
  QList<QAbstractAxis *> axisListV = chart->axes(Qt::Vertical);
  for (int i = 0; i < axisListV.size(); ++i)
    chart->removeAxis(axisListV.at(i));

  QList<QAbstractAxis *> axisListH = chart->axes(Qt::Horizontal);
  for (int i = 0; i < axisListH.size(); ++i)
    chart->removeAxis(axisListH.at(i));

  //  chart->removeAxis(chart->axisX()); //删除坐标轴 已废弃
  //  chart->removeAxis(chart->axisY()); //删除坐标轴  已废弃

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

  // chart->setAxisX(axisX, series);   //已废弃                                        //设置横坐标
  // chart->setAxisX(axisX, Line);     //已废弃                                      //设置横坐标
  axisX->setRange(categories.at(0), categories.at(categories.count() - 1)); //这只坐标轴范围

  //数值型坐标作为纵轴
  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(0, 100);
  axisY->setTitleText("分数");
  axisY->setTickCount(6);        // 11
  axisY->setLabelFormat("%.0f"); //标签格式
  //    axisY->setGridLineVisible(false);
  //    axisY->setMinorTickCount(4);

  //  chart->setAxisY(axisY, series); //为
  //  chart->setAxisY(axisY, Line);

  chart->addAxis(axisX, Qt::AlignBottom); //坐标轴添加到图表，并指定方向
  chart->addAxis(axisY, Qt::AlignLeft);

  series->attachAxis(axisX); //序列 series 附加坐标轴
  series->attachAxis(axisY);

  Line->attachAxis(axisX); //序列 Line 附加坐标轴
  Line->attachAxis(axisY);

  //    lineseries->setPointLabelsVisible(true);
  //    lineseries->setPointLabelsFormat("@yPoint");

  chart->legend()->setVisible(true);              //显示图例
  chart->legend()->setAlignment(Qt::AlignBottom); //图例显示在下方
}

//初始化饼图
void CHarts::initPieChart() {
  QChart *chart = new QChart(); //创建chart
  chart->setTitle("Piechart演示");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  ui->graphicsView_Pie->setChart(chart); //为ChartView设置chart
  ui->graphicsView_Pie->setRenderHint(QPainter::Antialiasing);

  buildPieChart();
}

//构建饼图
void CHarts::buildPieChart() {
  //获取ChartView关联的chart
  QChart *chart = ui->graphicsView_Pie->chart();
  chart->removeAllSeries(); //删除所有序列

  //获得要统计的列 数学 英语 语文 平均分
  int colIndex = ui->comboBox_Catagory->currentIndex() + 1;

  //创建饼图序列
  QPieSeries *pieSeries = new QPieSeries();
  //设置饼图中间孔大小
  pieSeries->setHoleSize(ui->doubleSpinBox_Hole->value());

  //饼图序列添加分块数据
  for (int i = 0; i <= 4; i++) {
    QTreeWidgetItem *item = ui->treeWidget_Data->topLevelItem(i);
    pieSeries->append(item->text(0), item->text(colIndex).toDouble());
  }

  //饼图分块
  QPieSlice *pieSlice = nullptr;
  for (int i = 0; i <= 4; i++) {
    //获取某块
    pieSlice = pieSeries->slices().at(i);
    QString strPer = QString::number(pieSlice->percentage() * 100, 10, 1) + "%";
    pieSlice->setLabel(pieSlice->label() + QString(":%1人").arg(pieSlice->value()) + strPer);

    //信号槽 鼠标落在某个分块上 此块弹出
    //带参数的信号槽
    //定义函数指针
    void (QPieSlice::*funSinglePara)(bool) = &QPieSlice::hovered;

    connect(pieSlice, funSinglePara, this, [=](bool isshow) {
      // QPieSlice *pSlice = (QPieSlice *)sender();
      pieSlice->setExploded(isshow);
    });

    //最后一个设置
    pieSeries->slices().at(4)->setExploded(true);
    pieSeries->setLabelsVisible(true); //只影响当前的slices，必须添加完slice之后再设置???

    //添加饼图序列
    chart->addSeries(pieSeries);
    chart->setTitle("Pie Chart--" + ui->comboBox_Catagory->currentText());

    //图例
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
  }
}

//初始化堆叠柱状图
void CHarts::initStackedBarChart() {
  //获取chart对象
  QChart *chart = ui->graphicsView_Stacked->chart();
  chart->setTitle("StackedBar 演示");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  //为ChartView设置chart
  ui->graphicsView_Stacked->setChart(chart);
  //启用抗锯齿属性,反走样
  ui->graphicsView_Stacked->setRenderHint(QPainter::Antialiasing);

  buildStackedBarChart();
}

//构建堆叠柱状图
void CHarts::buildStackedBarChart() {
  //获取chart对象
  QChart *chart = ui->graphicsView_Stacked->chart();
  //删除所有序列
  chart->removeAllSeries();
  //删除所有坐标轴
  QList<QAbstractAxis *> axisListV = chart->axes(Qt::Vertical);
  for (int i = 0; i < axisListV.size(); ++i)
    chart->removeAxis(axisListV.at(i));

  QList<QAbstractAxis *> axisListH = chart->axes(Qt::Horizontal);
  for (int i = 0; i < axisListH.size(); ++i)
    chart->removeAxis(axisListH.at(i));

  //创建3门课程的数据集
  QBarSet *setMath = new QBarSet(stanModel->horizontalHeaderItem(ColNoMath)->text());

  QBarSet *setChinese = new QBarSet(stanModel->horizontalHeaderItem(ColNoChinese)->text());

  QBarSet *setEnglish = new QBarSet(stanModel->horizontalHeaderItem(ColNoEnglish)->text());

  for (int i = 0; i < stanModel->rowCount(); i++) {
    setMath->append(stanModel->item(i, ColNoMath)->text().toDouble());
    setChinese->append(stanModel->item(i, ColNoChinese)->text().toDouble());
    setEnglish->append(stanModel->item(i, ColNoEnglish)->text().toDouble());
  }

  //创建并添加数据
  QStackedBarSeries *series = new QStackedBarSeries();
  series->append(setMath);
  series->append(setChinese);
  series->append(setEnglish);
  //显示每段的标签
  series->setLabelsVisible(true);

  chart->addSeries(series);

  QStringList categoriesLst;
  for (int i = 0; i < stanModel->rowCount(); i++) {
    categoriesLst << stanModel->item(i, ColNoName)->text();
  }

  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categoriesLst);
  axisX->setRange(categoriesLst.at(0), categoriesLst.at(categoriesLst.count() - 1));

  //数值坐标轴，作为纵轴
  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(0, 300);
  axisY->setTitleText("总分");
  axisY->setTickCount(6);
  axisY->setLabelFormat("%.0f");

  chart->addAxis(axisX, Qt::AlignBottom); //坐标轴添加到图表，并指定方向
  chart->addAxis(axisY, Qt::AlignLeft);

  series->attachAxis(axisX); //序列 series 附加坐标轴
  series->attachAxis(axisY);

  //序列 series 附加坐标轴
  series->attachAxis(axisX);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);
}

//初始化百分比柱状图
void CHarts::initPercentBarCHart() {
  QChart *chart = ui->graphicsView_Percent->chart();
  chart->setTitle("Percent Bar 演示");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  ui->graphicsView_Percent->setChart(chart);
  ui->graphicsView_Percent->setRenderHint(QPainter::Antialiasing);

  buildPercentBarChart();
}

//构建百分比柱状图
void CHarts::buildPercentBarChart() {
  //获取chart对象
  QChart *chart = ui->graphicsView_Percent->chart();
  //删除所有序列
  chart->removeAllSeries();
  //删除所有坐标轴
  QList<QAbstractAxis *> axisListV = chart->axes(Qt::Vertical);
  for (int i = 0; i < axisListV.size(); ++i) {
    chart->removeAxis(axisListV.at(i));
  }

  QList<QAbstractAxis *> axisListH = chart->axes(Qt::Horizontal);
  for (int i = 0; i < axisListH.size(); ++i) {
    chart->removeAxis(axisListH.at(i));
  }

  //创建数据集
  QBarSet *barSetMath = new QBarSet(stanModel->horizontalHeaderItem(ColNoMath)->text());
  QBarSet *barSetCHinese = new QBarSet(stanModel->horizontalHeaderItem(ColNoChinese)->text());
  QBarSet *barSetEnglish = new QBarSet(stanModel->horizontalHeaderItem(ColNoEnglish)->text());

  //
  QTreeWidgetItem *item = nullptr;

  QStringList categories;
  //从分数段统计数据表里获取数据，添加到数据集
  for (int i = 0; i <= 4; i++) {
    item = ui->treeWidget_Data->topLevelItem(i);
    categories << item->text(ColNoName);
    barSetMath->append(item->text(ColNoMath).toDouble());
    barSetCHinese->append(item->text(ColNoChinese).toDouble());
    barSetEnglish->append(item->text(ColNoEnglish).toDouble());
  }

  QPercentBarSeries *series = new QPercentBarSeries();
  series->append(barSetMath);
  series->append(barSetCHinese);
  series->append(barSetEnglish);
  series->setLabelsVisible(true);

  chart->addSeries(series);

  //横坐标
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories);
  axisX->setRange(categories.at(0), categories.at(categories.count() - 1));

  //纵坐标
  QValueAxis *axisY = new QValueAxis();
  axisY->setRange(0, 100);
  axisY->setTitleText("百分比");
  axisY->setTickCount(6);
  axisY->setLabelsVisible(true);
  axisY->setLabelFormat("%.1f");

  //坐标轴添加到图表，并指定方向
  //横坐标 底部
  chart->addAxis(axisX, Qt::AlignBottom);
  //纵坐标 右侧
  chart->addAxis(axisY, Qt::AlignLeft);

  //序列 series 附加坐标轴
  series->attachAxis(axisX);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignRight);
}

void CHarts::initScatterChart() {
  QChart *chart = new QChart();
  chart->setTitle("QScatter QSplineSeries演示");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  ui->graphicsView_Scatter->setChart(chart);
  ui->graphicsView_Scatter->setRenderHint(QPainter::Antialiasing);
  buildScatterChart();
}

void CHarts::buildScatterChart() {
  QChart *chart = ui->graphicsView_Scatter->chart();
  //删除序列
  chart->removeAllSeries();

  //删除所有坐标轴
  QList<QAbstractAxis *> axisListV = chart->axes(Qt::Vertical);
  for (int i = 0; i < axisListV.size(); ++i)
    chart->removeAxis(axisListV.at(i));

  QList<QAbstractAxis *> axisListH = chart->axes(Qt::Horizontal);
  for (int i = 0; i < axisListH.size(); ++i)
    chart->removeAxis(axisListH.at(i));

  //曲线序列
  QSplineSeries *splineSeries = new QSplineSeries();
  splineSeries->setName("曲线:" + stanModel->horizontalHeaderItem(ColNoAverage)->text());
  QPen pen;
  pen.setColor(Qt::green);
  pen.setWidth(3);
  splineSeries->setPen(pen);

  //散点序列
  QScatterSeries *scatterSeries = new QScatterSeries();
  scatterSeries->setName("散点:" + stanModel->horizontalHeaderItem(ColNoAverage)->text());
  scatterSeries->setMarkerSize(10);
  scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
  scatterSeries->setBorderColor(Qt::black);
  scatterSeries->setBrush(QBrush(Qt::blue));

  chart->addSeries(scatterSeries);
  chart->addSeries(splineSeries);

  //横坐标文字
  QStringList categoriesLst;
  for (int i = 0; i < 5; i++) {
    categoriesLst << ui->treeWidget_Data->topLevelItem(i)->text(0);

    splineSeries->append(QPointF(i, ui->treeWidget_Data->topLevelItem(i)->text(ColNoAverage).toDouble()));
    scatterSeries->append(QPointF(i, ui->treeWidget_Data->topLevelItem(i)->text(ColNoAverage).toDouble()));
  }
  //用于柱状图的坐标轴
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categoriesLst); //添加横坐标文字列表                                   //设置横坐标
  axisX->setRange(categoriesLst.at(0), categoriesLst.at(categoriesLst.count() - 1)); //这只坐标轴范围

  //数值型坐标作为纵轴
  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(0, iniDataRowCount);
  axisY->setTitleText("人数");
  axisY->setTickCount(6);        // 11
  axisY->setLabelFormat("%.0f"); //标签格式

  chart->addAxis(axisX, Qt::AlignBottom); //坐标轴添加到图表，并指定方向
  chart->addAxis(axisY, Qt::AlignLeft);

  scatterSeries->attachAxis(axisX); //序列 series 附加坐标轴
  scatterSeries->attachAxis(axisY);

  splineSeries->attachAxis(axisX); //序列 Line 附加坐标轴
  splineSeries->attachAxis(axisY);

  //    lineseries->setPointLabelsVisible(true);
  //    lineseries->setPointLabelsFormat("@yPoint");

  chart->legend()->setVisible(true);             //显示图例
  chart->legend()->setAlignment(Qt::AlignRight); //图例显示在下方
}

void CHarts::on_itemChanged(QStandardItem *item) {
  qDebug() << __FUNCTION__;
  if (item->column() < ColNoMath || item->column() > ColNoEnglish)
    return;

  //获得行编号
  int rowIndex = item->row();
  qDebug() << "rowIndex" << rowIndex;
  //
  qreal avg = 0;
  QStandardItem *itemtmp = nullptr;
  for (int i = ColNoMath; i <= ColNoEnglish; i++) {
    itemtmp = stanModel->item(rowIndex, i);
    if (itemtmp == nullptr)
      continue;
    avg += itemtmp->text().toDouble();
  }
  avg = avg / 3;
  qDebug() << "avg" << avg;

  //更新平均分
  itemtmp = stanModel->item(rowIndex, ColNoAverage);
  itemtmp->setText(QString::number(avg));
}
