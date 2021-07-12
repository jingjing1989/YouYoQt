#pragma execution_character_set("utf-8")
#include "MyTableWidget.h"
#include "ui_MyTableWidget.h"

#include <QAbstractItemView>
#include <QCompleter>
#include <QDebug>
#include <QHeaderView>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <iostream>

//实现效果:点击右侧table行,在左侧一显示数据,左侧二刷新且实施增加

MyTableWidget::MyTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MyTableWidget) {
  ui->setupUi(this);

  //需要splitter水平策略设置为fixed
  //  ui->splitter->setStretchFactor(0, 1);
  //  ui->splitter->setStretchFactor(1, 1);
  //  ui->splitter->setStretchFactor(2, 1);
  //  ui->splitter->setStretchFactor(3, 3);

  initTableAbstract();

  initTableTotal();

  initTableSale();

  initTableBuy();

  initTableData();

  //设置行数
  //  ui->tableWidget->setRowCount(10);
  //  //设置列数
  //  ui->tableWidget->setColumnCount(9);
  //  QHeaderView *header = ui->tableWidget->verticalHeader();
  //  header->setHidden(true); // 隐藏行号

  //设置表头
  // SetHeaders();

  //设置隔行变色
  // ui->tableWidget->setAlternatingRowColors(true);

  ui->lineEdit_search->setMaximumWidth(200);
  ui->lineEdit_search->setPlaceholderText("search");

  //信号槽
  connect(ui->pushButton_add, &QPushButton::clicked, this, &MyTableWidget::pushButtonAddClick);

  connect(ui->pushButton_del, &QPushButton::clicked, this, &MyTableWidget::pushButtonDelClick);

  connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &MyTableWidget::searchTextChanged);

  connect(ui->toolButton_OpenFile, &QToolButton::clicked, this, &MyTableWidget::OpenFile);

  //点击tabledata
  connect(ui->tableView_Data, &QTableView::clicked, this, &MyTableWidget::updateTableAbstract);

  connect(ui->tableView_Data, &QTableView::clicked, this, &MyTableWidget::updateWidgetSelect);

  connect(ui->tableView_Data, &QTableView::clicked, this, &MyTableWidget::updateTableInfo);

  //选择卖出数量比例 信号槽
  connect(ui->radioButton_All, &QRadioButton::toggled, this, &MyTableWidget::GrossAmountRatio);
  connect(ui->radioButton_Half, &QRadioButton::toggled, this, &MyTableWidget::GrossAmountRatio);
  connect(ui->radioButton_OneThird, &QRadioButton::toggled, this, &MyTableWidget::GrossAmountRatio);
  connect(ui->radioButton_Quater, &QRadioButton::toggled, this, &MyTableWidget::GrossAmountRatio);

  //选择卖出数量 信号槽
  connect(ui->doubleSpinBox_Number, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double dblNumber) {
    double dblPrice = ui->doubleSpinBox_Price->value();
    std::cout << "Price:" << dblPrice << std::endl;

    //清空Radio'button选择
    ui->radioButton_All->setChecked(false);
    ui->radioButton_Half->setChecked(false);
    ui->radioButton_OneThird->setChecked(false);
    ui->radioButton_Quater->setChecked(false);

    //计算总金额
    double dblSum = dblNumber * dblPrice;
    std::cout << "dblSum:" << dblSum << std::endl;
    QString strSum = QString::number(dblSum, 10, 2);

    ui->lineEdit_Sum->setText(strSum);
  });
}

MyTableWidget::~MyTableWidget() { delete ui; }

//添加行
void MyTableWidget::pushButtonAddClick() {
  //  int curRow = ui->tableView_Data->currentRow();
  //  ui->tableWidget->insertRow(curRow + 1);
}

//删除行
void MyTableWidget::pushButtonDelClick() {
  //  int curRow = ui->tableWidget->currentRow();
  //  ui->tableWidget->removeRow(curRow);
}

void MyTableWidget::searchTextChanged(const QString &str) {
  qDebug() << "searchTextChanged";
  return;
}

//设置模糊搜索匹配
void MyTableWidget::SetCompleter(QStringList word_list) {
  //构建模糊查询对象
  // word_list<<"Java"<<"C++"<<"C#"<<"PHP"<<"Perl"<<"Python"<<"Delphi"<<"Ruby";
  QCompleter *completer = new QCompleter(word_list);

  //设置Eidt的模糊查询对象
  ui->lineEdit_search->setCompleter(completer);
  completer->setCaseSensitivity(Qt::CaseInsensitive); //·这个属性可设置进行匹配时的大小写敏感性
  // completer->setCompletionMode(QCompleter::InlineCompletion);//设置匹配时弹出的形式。PopupCompletion
  completer->setMaxVisibleItems(6); // defuat 7
}

void MyTableWidget::initTableAbstract() {
  //设置自适应窗口宽度 高度
  ui->tableView_Abstract->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_Abstract->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  QHeaderView *header = ui->tableView_Abstract->verticalHeader();
  header->setHidden(true); // 隐藏行号

  header = ui->tableView_Abstract->horizontalHeader();
  header->setHidden(true); // 隐藏表头

  //创建QStandardItemModel
  QStandardItemModel *stanModel = new QStandardItemModel(2, 2, this); //数据模型

  //设置item
  stanModel->setItem(0, 0, new QStandardItem("--"));
  stanModel->setItem(0, 1, new QStandardItem("--"));
  stanModel->setItem(1, 0, new QStandardItem("0.00"));
  stanModel->setItem(1, 1, new QStandardItem("--(0.00)"));

  //设置不可选择 不可编辑
  stanModel->item(0, 0)->setFlags(Qt::NoItemFlags);
  stanModel->item(0, 1)->setFlags(Qt::NoItemFlags);
  stanModel->item(1, 0)->setFlags(Qt::NoItemFlags);
  stanModel->item(1, 1)->setFlags(Qt::NoItemFlags);

  //设置居中
  stanModel->item(0, 0)->setTextAlignment(Qt::AlignCenter);
  stanModel->item(0, 1)->setTextAlignment(Qt::AlignCenter);
  stanModel->item(1, 0)->setTextAlignment(Qt::AlignCenter);
  stanModel->item(1, 1)->setTextAlignment(Qt::AlignCenter);

  //设置字体字号
  stanModel->item(0, 0)->setFont(QFont("", 17, QFont::Black));
  stanModel->item(1, 0)->setFont(QFont("", 17, QFont::Black));
  stanModel->item(0, 1)->setFont(QFont("", 12, QFont::Black));
  stanModel->item(1, 1)->setFont(QFont("", 12, QFont::Black));

  ui->tableView_Abstract->setModel(stanModel);
}

void MyTableWidget::initTableSale() {

  //设置表头内容
  //  QStringList header;
  //  header << tr("总卖") << tr("0.00") << tr("0");
  // QHeaderView *header = new QHeaderView(Qt::Horizontal, ui->tableView_Sale);
  // ui->tableView_Sale->setHorizontalHeader(header);

  std::cout << "header" << std::endl;

  //设置自适应窗口宽度 高度
  ui->tableView_Sale->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_Sale->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //创建QStandardItemModel
  QStandardItemModel *stanModel = new QStandardItemModel(10, 3, this); //数据模型

  //设置表头
  stanModel->setHeaderData(0, Qt::Horizontal, QString("总卖"));
  stanModel->setHeaderData(1, Qt::Horizontal, QString("0.00"));
  stanModel->setHeaderData(2, Qt::Horizontal, QString("0"));

  //设置item
  stanModel->setItem(0, 0, new QStandardItem("十"));
  stanModel->setItem(1, 0, new QStandardItem("九"));
  stanModel->setItem(2, 0, new QStandardItem("八"));
  stanModel->setItem(3, 0, new QStandardItem("七"));
  stanModel->setItem(4, 0, new QStandardItem("六"));
  stanModel->setItem(5, 0, new QStandardItem("五"));
  stanModel->setItem(6, 0, new QStandardItem("四"));
  stanModel->setItem(7, 0, new QStandardItem("三"));
  stanModel->setItem(8, 0, new QStandardItem("二"));
  stanModel->setItem(9, 0, new QStandardItem("一"));
  std::cout << "set item" << std::endl;
  for (int i = 0; i < 10; i++) {
    stanModel->setItem(i, 1, new QStandardItem("--"));
    stanModel->setItem(i, 2, new QStandardItem("--"));
  }
  std::cout << "set item  ---" << std::endl;
  //设置格式
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      //设置可选择 不可编辑
      stanModel->item(i, j)->setFlags(stanModel->item(i, j)->flags() & (~Qt::ItemIsEditable));
      //设置居中
      stanModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
      //设置字体
      stanModel->item(i, j)->setFont(QFont("", 8, QFont::Normal));
    }
  }
  std::cout << "set font  ---" << std::endl;

  ui->tableView_Sale->setModel(stanModel);
}

void MyTableWidget::initTableBuy() {

  //设置自适应窗口宽度 高度
  ui->tableView_Buy->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_Buy->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  //创建QStandardItemModel
  QStandardItemModel *stanModel = new QStandardItemModel(11, 3, this); //数据模型

  //设置表头
  //  stanModel->setHeaderData(0, Qt::Horizontal, QString("总卖"));
  //  stanModel->setHeaderData(1, Qt::Horizontal, QString("0.00"));
  //  stanModel->setHeaderData(2, Qt::Horizontal, QString("0"));

  //设置item
  stanModel->setItem(10, 0, new QStandardItem("总计"));
  stanModel->setItem(9, 0, new QStandardItem("十"));
  stanModel->setItem(8, 0, new QStandardItem("九"));
  stanModel->setItem(7, 0, new QStandardItem("八"));
  stanModel->setItem(6, 0, new QStandardItem("七"));
  stanModel->setItem(5, 0, new QStandardItem("六"));
  stanModel->setItem(4, 0, new QStandardItem("五"));
  stanModel->setItem(3, 0, new QStandardItem("四"));
  stanModel->setItem(2, 0, new QStandardItem("三"));
  stanModel->setItem(1, 0, new QStandardItem("二"));
  stanModel->setItem(0, 0, new QStandardItem("一"));
  std::cout << "set item" << std::endl;

  for (int i = 0; i < 10; i++) {
    stanModel->setItem(i, 1, new QStandardItem("--"));
    stanModel->setItem(i, 2, new QStandardItem("--"));
  }

  //总计行
  stanModel->setItem(10, 1, new QStandardItem("0.00"));
  stanModel->setItem(10, 2, new QStandardItem("0"));
  std::cout << "set item  ---" << std::endl;
  //设置格式
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 10) {
        //设置不可选择 不可编辑
        stanModel->item(i, j)->setFlags(stanModel->item(i, j)->flags() & (~Qt::NoItemFlags));

      } else {
        //设置可选择 不可编辑
        stanModel->item(i, j)->setFlags(stanModel->item(i, j)->flags() & (~Qt::ItemIsEditable));
      }

      //设置居中
      stanModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
      //设置字体
      stanModel->item(i, j)->setFont(QFont("", 8, QFont::Normal));
    }
  }
  std::cout << "set font  ---" << std::endl;

  ui->tableView_Buy->setModel(stanModel);
}

void MyTableWidget::initTableTotal() {
  //设置自适应窗口宽度 高度
  ui->tableView_Total->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_Total->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //表头
  QHeaderView *header = ui->tableView_Total->verticalHeader();
  header->setHidden(true); // 隐藏行号

  header = ui->tableView_Total->horizontalHeader();
  header->setHidden(true); // 隐藏表头

  //创建QStandardItemModel
  QStandardItemModel *stanModel = new QStandardItemModel(3, 4, this); //数据模型

  //设置item
  stanModel->setItem(0, 0, new QStandardItem("昨收"));
  stanModel->setItem(0, 1, new QStandardItem("--"));
  stanModel->setItem(0, 2, new QStandardItem("开盘"));
  stanModel->setItem(0, 3, new QStandardItem("--"));

  stanModel->setItem(1, 0, new QStandardItem("涨停"));
  stanModel->setItem(1, 1, new QStandardItem("--"));
  stanModel->setItem(1, 2, new QStandardItem("跌停"));
  stanModel->setItem(1, 3, new QStandardItem("--"));

  stanModel->setItem(2, 0, new QStandardItem("最高"));
  stanModel->setItem(2, 1, new QStandardItem("--"));
  stanModel->setItem(2, 2, new QStandardItem("最低"));
  stanModel->setItem(2, 3, new QStandardItem("--"));

  //设置格式
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      //设置不可选择 不可编辑
      stanModel->item(i, j)->setFlags(Qt::NoItemFlags);
      //设置居中
      stanModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
      //设置字体
      stanModel->item(i, j)->setFont(QFont("", 8, QFont::Normal));
    }
  }

  ui->tableView_Total->setModel(stanModel);
}

void MyTableWidget::initTableInfo() {
  //设置自适应窗口宽度 高度
  //  ui->tableView_Info->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  //  ui->tableView_Info->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MyTableWidget::initTableData() {
  //设置自适应窗口宽度 高度
  ui->tableView_Data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  // ui->tableView_Data->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //设置整行选择
  ui->tableView_Data->setSelectionBehavior(QAbstractItemView::SelectRows);
  //设置最后一列贴边
  ui->tableView_Data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  //表头
  QHeaderView *header = ui->tableView_Data->verticalHeader();
  header->setHidden(true); // 隐藏行号

  //创建QStandardItemModel
  /*QStandardItemModel*/ stanModel = new QStandardItemModel(10, 9, this); //数据模型
  //设置表头
  stanModel->setHeaderData(0, Qt::Horizontal, QString(tr("对象代号")));
  stanModel->setHeaderData(1, Qt::Horizontal, QString(tr("证券名称")));
  stanModel->setHeaderData(2, Qt::Horizontal, QString(tr("持仓数量")));
  stanModel->setHeaderData(3, Qt::Horizontal, QString(tr("可用数量")));
  stanModel->setHeaderData(4, Qt::Horizontal, QString(tr("成本价")));
  stanModel->setHeaderData(5, Qt::Horizontal, QString(tr("最新价")));
  stanModel->setHeaderData(6, Qt::Horizontal, QString(tr("市值")));
  stanModel->setHeaderData(7, Qt::Horizontal, QString(tr("浮动盈亏")));
  stanModel->setHeaderData(8, Qt::Horizontal, QString(tr("盈亏比")));

  std::cout << "setHeaderData ok" << std::endl;
  // stanModel->setItem(1, 0, new QStandardItem("涨停"));
  //  stanModel->setItem(1, 1, new QStandardItem("--"));
  //  stanModel->setItem(1, 2, new QStandardItem("跌停"));
  //  stanModel->setItem(1, 3, new QStandardItem("--"));

  //  stanModel->setItem(2, 0, new QStandardItem("最高"));
  //  stanModel->setItem(2, 1, new QStandardItem("--"));
  //  stanModel->setItem(2, 2, new QStandardItem("最低"));
  //  stanModel->setItem(2, 3, new QStandardItem("--"));

#if 0
  //设置格式
  for (int i = 0; i < 10; i++) {
    std::cout << " i:" << i << std::endl;
    for (int j = 0; j < 9; j++) {
      std::cout << " j:" << j << std::endl;
      //设置可选择 不可编辑
      stanModel->item(i, j)->setFlags(stanModel->item(i, j)->flags() & (~Qt::ItemIsEditable));
      //设置居中
      stanModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
      //设置字体
      stanModel->item(i, j)->setFont(QFont("", 8, QFont::Normal));
    }
    std::cout << " i:" << i << std::endl;
  }
#endif

  ui->tableView_Data->setModel(stanModel);
}

void MyTableWidget::OpenFile() {
  //打开文件
  QString curPath = QCoreApplication::applicationDirPath(); //获取应用程序的路径
  //调用打开文件对话框打开一个文件
  QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "井数据文件(*.txt);;所有文件(*.*)");
  if (aFileName.isEmpty())
    return; //如果未选择文件，退出

  QStringList fFileContent;                              //文件内容字符串列表
  QFile aFile(aFileName);                                //以文件方式读出
  if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
  {
    QTextStream aStream(&aFile); //用文本流读取文件
    // ui->plainTextEdit->clear();  //清空
    while (!aStream.atEnd()) {
      QString str = aStream.readLine(); //读取文件的一行
      // ui->plainTextEdit->appendPlainText(str); //添加到文本框显示
      fFileContent.append(str); //添加到 StringList
    }
    aFile.close(); //关闭文件

#if 0
    this->LabCurFile->setText("当前文件：" + aFileName); //状态栏显示
    ui->actAppend->setEnabled(true);                     //更新Actions的enable属性
    ui->actInsert->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actSave->setEnabled(true);

#endif

    initTableDataFromStringList(fFileContent); //从StringList的内容初始化数据模型
  }
}

void MyTableWidget::initTableDataFromStringList(QStringList &aFileContent) { //一个或多个空格、TAB等分隔符隔开的字符串， 分解为一个StringList
  //设置表头
  QString header = aFileContent.at(0); //第1行是表头
  QStringList headerList = header.split(QRegExp("\\s+"), QString::SkipEmptyParts);

  int rowCnt = aFileContent.count();  //文本行数，第1行是标题
  stanModel->setRowCount(rowCnt - 1); //实际数据行数
  // QStandardItemModel *stanModel = new QStandardItemModel(10, 9, this); //数据模型

  // stanModel->setHorizontalHeaderLabels(headerList); //设置表头文字

  //设置表格数据
  int j;
  QStandardItem *aItem;
  for (int i = 1; i < rowCnt; i++) {
    std::cout << " i :" << i << std::endl;
    QString aLineText = aFileContent.at(i); //获取 数据区 的一行
    //一个或多个空格、TAB等分隔符隔开的字符串， 分解为一个StringList
    QStringList tmpList = aLineText.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for (j = 0; j < 9; j++) // tmpList的行数等于FixedColumnCount, 固定的
    {
      if (j >= tmpList.size())
        continue;
      std::cout << " j:" << j << std::endl;
      aItem = new QStandardItem(tmpList.at(j)); //创建item
      stanModel->setItem(i - 1, j, aItem);      //为模型的某个行列位置设置Item

      //设置可选择 不可编辑
      stanModel->item(i - 1, j)->setFlags(stanModel->item(i - 1, j)->flags() & (~Qt::ItemIsEditable));
      std::cout << "00" << std::endl;
      //设置居中
      stanModel->item(i - 1, j)->setTextAlignment(Qt::AlignCenter);
      std::cout << "11" << std::endl;
      //设置字体
      stanModel->item(i - 1, j)->setFont(QFont("", 8, QFont::Normal));
      std::cout << "22" << std::endl;
    }

    /*  aItem = new QStandardItem(headerList.at(j)); //最后一列是Checkable,需要设置
      aItem->setCheckable(true);                   //设置为Checkable
      if (tmpList.at(j) == "0")
        aItem->setCheckState(Qt::Unchecked); //根据数据设置check状态
      else
        aItem->setCheckState(Qt::Checked);
      theModel->setItem(i - 1, j, aItem); *///为模型的某个行列位置设置Item
  }
}

//更新TableAbstract 左上角表格
void MyTableWidget::updateTableAbstract(QModelIndex index) {
  //获得tableview的model
  QStandardItemModel *modelAbstract = qobject_cast<QStandardItemModel *>(ui->tableView_Abstract->model());
  QStandardItemModel *modelData = qobject_cast<QStandardItemModel *>(ui->tableView_Data->model());
}

//更新TableInfo 第二列Widget的第二个表格
void MyTableWidget::updateTableInfo(QModelIndex index) {
  //获得tableview的model
  QStandardItemModel *modelAbstract = qobject_cast<QStandardItemModel *>(ui->tableView_Abstract->model());
  QStandardItemModel *modelData = qobject_cast<QStandardItemModel *>(ui->tableView_Data->model());

  //设置名称
  QString strName = modelData->item(index.row(), MyTableWidgetSpace::Data_Name)->text();
  modelAbstract->item(0, 0)->setText(strName);

  //设置单价
  QString strPrice = modelData->item(index.row(), MyTableWidgetSpace::Data_Price)->text();
  modelAbstract->item(1, 0)->setText(strPrice);

  //设置号码
  QString strNo = modelData->item(index.row(), MyTableWidgetSpace::Data_No)->text();
  modelAbstract->item(0, 1)->setText(strNo);

  //设置单价增减比例
  double dblPrice = strPrice.toDouble();
  double dblCOst = modelData->item(index.row(), MyTableWidgetSpace::Data_Cost)->text().toDouble();
  double dblLoss = dblPrice - dblCOst;
  double percent = dblLoss / dblCOst;
  QString strPer = QString::number(percent * 100, 10, 2) + "%";
  strPer = strPer + "(" + QString::number(dblLoss, 10, 2) + ")";
  modelAbstract->item(1, 1)->setText(strPer);
}

void MyTableWidget::updateWidgetSelect(QModelIndex index) {
  //清除
  ui->lineEdit_No->clear();
  ui->label_Name->clear();
  //  ui->doubleSpinBox_Price->clear();
  //  ui->doubleSpinBox_Number->clear();
  ui->lineEdit_Sum->clear();
  ui->lineEdit_Max->clear();

  //号码
  int rowIndex = index.row();
  QString strNo = stanModel->item(rowIndex, MyTableWidgetSpace::Data_No)->text();
  ui->lineEdit_No->setText(strNo);
  //名称
  QString strName = stanModel->item(rowIndex, MyTableWidgetSpace::Data_Name)->text();
  ui->label_Name->setText(strName);
  //价格
  QString strPrice = stanModel->item(rowIndex, MyTableWidgetSpace::Data_Price)->text();
  ui->doubleSpinBox_Price->setValue(strPrice.toDouble());
  //数量
  QString strNUm = stanModel->item(rowIndex, MyTableWidgetSpace::Data_Number)->text();
  ui->doubleSpinBox_Number->setValue(strNUm.toDouble());

  //最大可卖
  QString strMax = stanModel->item(rowIndex, MyTableWidgetSpace::Data_Available)->text();
  ui->lineEdit_Max->setText(strMax);
}

void MyTableWidget::GrossAmountRatio(bool ischecked) {
  std::cout << __FUNCTION__ << std::endl;
  if (ischecked) {
    std::cout << "ischecked" << std::endl;
    double dblPrice = ui->doubleSpinBox_Price->value();
    std::cout << "Price:" << dblPrice << std::endl;

    double dblNum = ui->lineEdit_Max->text().toDouble();
    std::cout << "dblNum:" << dblNum << std::endl;
    double dblSum = dblNum;

    if (ui->radioButton_All->isChecked()) {
      dblSum = dblNum;

    } else if (ui->radioButton_Half->isChecked()) {
      dblSum = dblNum * 0.5;

    } else if (ui->radioButton_OneThird->isChecked()) {
      dblSum = dblNum / 3;

    } else if (ui->radioButton_Quater->isChecked()) {
      dblSum = dblNum / 4;
    }
    //设置数量
    ui->doubleSpinBox_Number->setValue(dblSum);

    dblSum = dblSum * dblPrice;
    std::cout << "dblSum:" << dblSum << std::endl;
    QString strSum = QString::number(dblSum, 10, 2);

    ui->lineEdit_Sum->setText(strSum);
  }
}

void MyTableWidget::GrossAmountNumber(double dblNumber) {
  std::cout << __FUNCTION__ << std::endl;

  double dblPrice = ui->doubleSpinBox_Price->value();
  std::cout << "Price:" << dblPrice << std::endl;

  //清空Radio'button选择
  ui->radioButton_All->setChecked(false);
  ui->radioButton_Half->setChecked(false);
  ui->radioButton_OneThird->setChecked(false);
  ui->radioButton_Quater->setChecked(false);

  //计算总金额
  double dblSum = dblNumber * dblPrice;
  std::cout << "dblSum:" << dblSum << std::endl;
  QString strSum = QString::number(dblSum, 10, 2);

  ui->lineEdit_Sum->setText(strSum);
}
