#include "LabelDelegate.h"

LabelDelegate::LabelDelegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget *LabelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLabel *editor = new QLabel();
    return editor;
}

void LabelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index,Qt::EditRole).toString();
    QLabel *label = static_cast<QLabel*>(editor);
    label->setText(str);

}

void LabelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLabel *label = static_cast<QLabel*>(editor);
    QString str = label->text();
    model->setData(index,str,Qt::EditRole);


}

void LabelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);

}
