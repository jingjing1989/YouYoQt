#ifndef LABELDELEGATE_H
#define LABELDELEGATE_H
#include <QDebug>
#include <QItemDelegate>
#include <QLabel>
#include <QObject>

class LabelDelegate : public QItemDelegate {
  Q_OBJECT
public:
  LabelDelegate(QObject *parent = nullptr);
  ~LabelDelegate();

  //自定义代理组件必须继承以下4个函数
  //创建编辑组件
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;

  //从数据模型获取数据，显示到代理组件中
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;

  //将代理组件的数据，保存到数据模型中
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

  //更新代理编辑组件的大小
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;

  //  bool editorEvent(QEvent *event, QAbstractItemModel *model,
  //                   const QStyleOptionViewItem &option,
  //                   const QModelIndex &index) const override;

  //  void paint(QPainter *painter, const QStyleOptionViewItem &option,
  //             const QModelIndex &index) const override;
};

#endif // LABELDELEGATE_H
