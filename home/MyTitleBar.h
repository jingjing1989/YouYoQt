#ifndef MyTitleBar_H
#define MyTitleBar_H

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>

class MyTitleBar : public QWidget {
  Q_OBJECT
public:
  explicit MyTitleBar(QWidget *parent = nullptr);
  ~MyTitleBar();

protected:
  // 双击标题栏进行界面的最大化/还原
  void mouseDoubleClickEvent(QMouseEvent *event);

  // 进行鼠界面的拖动
  void mousePressEvent(QMouseEvent *event);

  // 设置界面标题与图标
  bool eventFilter(QObject *obj, QEvent *event);

signals:

private slots:

  // 进行最小化、最大化/还原、关闭操作
  void onClicked();

private:
  // 最大化/还原
  void updateMaximize();

private:
  QLabel *logo;
  QLabel *m_pTitleLabel;
  QPushButton *minimizeBtn;
  QPushButton *maxBtn;
  QPushButton *closeBtn;
  QPushButton *selectPluginBtn;
  QPushButton *cloudBtn;
  QPushButton *skinBtn;
  QPushButton *cfgBtn;
  QPushButton *sizeBtn;
};

#endif // MyTitleBar_H
