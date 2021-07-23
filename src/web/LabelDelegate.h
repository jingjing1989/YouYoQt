#ifndef LABELDELEGATE_H
#define LABELDELEGATE_H
#include    <QItemDelegate>
#include <QObject>
#include <QLabel>

class LabelDelegate : public QItemDelegate
{
       Q_OBJECT
public:
    LabelDelegate(QObject *parent =nullptr);

    //自定义代理组件必须继承以下4个函数
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;


    void setEditorData(QWidget *editor,const QModelIndex &index)const Q_DECL_OVERRIDE;

    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget*editor,const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

#endif // LABELDELEGATE_H
