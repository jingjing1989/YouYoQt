#include "LineEditLabel.h"
#include "utility/CommonUtility.h"

#include <QApplication>
#include <QFile>
#include <QHBoxLayout>
#include <QPushButton>

LineEditLabel::LineEditLabel(QWidget *parent) : QLineEdit(parent) {
  pb_passwordvisible = new QPushButton(this);
  pb_passwordvisible->setCursor(Qt::PointingHandCursor);
  pb_passwordvisible->setCheckable(true);
  pb_passwordvisible->setObjectName("pb_password");

  //初始设置密码不可见
  setEchoMode(QLineEdit::Password);

  //信号槽
  connect(pb_passwordvisible, &QPushButton::toggled, [this](bool checked) {
    if (checked) {
      setEchoMode(QLineEdit::Normal);
    } else {
      setEchoMode(QLineEdit::Password);
    }
  });

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addStretch();
  layout->addWidget(pb_passwordvisible);
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  //设置样式
  CommonUtility::setStyleSheet(":/qss/res/qss/defaultstyle/LineEditLabel.css", this);
}
