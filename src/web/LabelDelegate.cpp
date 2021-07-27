#include "LabelDelegate.h"
const QString ICONSUNNY = ":/images/res/images/weather/sunny.png";
const QString ICONTEST = ":/images/res/images/login/add.png";
LabelDelegate::LabelDelegate(QObject *parent) : QItemDelegate(parent) {
  qDebug() << "LabelDelegate";
}

LabelDelegate::~LabelDelegate() {}

QWidget *LabelDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  qDebug() << __FUNCTION__;
  Q_UNUSED(option);
  Q_UNUSED(index);
  QLabel *editor = new QLabel(parent);

  // 图片不重复，可设置缩放比例，不可动态缩放
  QImage *img = new QImage;
  img->load(ICONTEST);
  QImage scaledimg;
  scaledimg =
      img->scaled(editor->width(), editor->height(), Qt::KeepAspectRatio);
  editor->setPixmap(QPixmap::fromImage(scaledimg));
  qDebug() << " ---------------------------ICONSUNNY";
  return editor;
}

void LabelDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const {
  QString str = index.model()->data(index, Qt::EditRole).toString();
  QLabel *label = static_cast<QLabel *>(editor);
  label->setText(str);
}

void LabelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const {
  qDebug() << __FUNCTION__;
  QLabel *label = static_cast<QLabel *>(editor);
  QString str = label->text();
  model->setData(index, str, Qt::EditRole);
}

void LabelDelegate::updateEditorGeometry(QWidget *editor,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  qDebug() << __FUNCTION__;
  editor->setGeometry(option.rect);
}

// bool LabelDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
//                                const QStyleOptionViewItem &option,
//                                const QModelIndex &index) const {
//  qDebug() << __FUNCTION__;
//  return true;
//}
