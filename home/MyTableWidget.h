#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QDoubleSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QRadioButton>
#include <QStandardItem>
#include <QWidget>

namespace Ui {
class MyTableWidget;
}

namespace MyTableWidgetSpace {

const int INTERVAL_TIMER = 3000;
const int ANIMATION_DURTION = 200;
const QByteArray ANIMATION_GEOMETRY = "geometry";

enum TableAbstract {
  //      Data_No,
  //      Data_Name,
  //      Data_Number,
  //      Data_Available,
  //      Data_Cost,
  //      Data_Price,
  //      Data_MarketValue,
  //      Data_ProfitLoss,
  //      Data_ProfitLossRatio,
};

enum TableDataHeader {
  Data_No,
  Data_Name,
  Data_Number,
  Data_Available,
  Data_Cost,
  Data_Price,
  Data_MarketValue,
  Data_ProfitLoss,
  Data_ProfitLossRatio,
};
} // namespace MyTableWidgetSpace

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

  //设置模糊搜索匹配
  void SetCompleter(QStringList word_list);

  //初始化表格
  void initTableAbstract();

  void initTableSale();

  void initTableBuy();
  //
  void initTableTotal();

  void initTableInfo();

  void initTableData();

  void OpenFile();

  void initTableDataFromStringList(QStringList &aFileContent);

  void updateTableAbstract(QModelIndex index);

  //更新TableInfo 第二列Widget的第二个表格
  void updateTableInfo(QModelIndex index);

  void updateWidgetSelect(QModelIndex index);

  void GrossAmountRatio(bool ischecked);

  void GrossAmountNumber(double dblNumber);

  QStandardItemModel *stanModel = nullptr;
};

#endif // MYTABLEWIDGET_H
