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

MyTableWidget::MyTableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MyTableWidget) {
  ui->setupUi(this);
  //设置行数
  ui->tableWidget->setRowCount(10);
  //设置列数
  ui->tableWidget->setColumnCount(9);
  QHeaderView *header = ui->tableWidget->verticalHeader();
  header->setHidden(true); // 隐藏行号

  //设置表头
  SetHeaders();

  //设置隔行变色
  ui->tableWidget->setAlternatingRowColors(true);
  //设置整行选择
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  //设置最后一列贴边
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->lineEdit_search->setMaximumWidth(200);
  ui->lineEdit_search->setPlaceholderText("search");

  //信号槽
  connect(ui->pushButton_add, &QPushButton::clicked, this, &MyTableWidget::pushButtonAddClick);

  connect(ui->pushButton_del, &QPushButton::clicked, this, &MyTableWidget::pushButtonDelClick);

  connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &MyTableWidget::searchTextChanged);
}

MyTableWidget::~MyTableWidget() { delete ui; }

//添加行
void MyTableWidget::pushButtonAddClick() {
  int curRow = ui->tableWidget->currentRow();
  ui->tableWidget->insertRow(curRow + 1);
}

//删除行
void MyTableWidget::pushButtonDelClick() {
  int curRow = ui->tableWidget->currentRow();
  ui->tableWidget->removeRow(curRow);
}

void MyTableWidget::searchTextChanged(const QString &str) {
  qDebug() << "searchTextChanged";
  return;
}

//设置表头
void MyTableWidget::SetHeaders() {
  //设置表头内容
  QStringList header;
  header << tr("证券代码") << tr("证券名称") << tr("持仓数量") << tr("可用数量") << tr("成本价") << tr("最新价") << tr("市值") << tr("浮动盈亏")
         << tr("盈亏比");
  ui->tableWidget->setHorizontalHeaderLabels(header);
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
