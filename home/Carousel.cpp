#include "Carousel.h"
#include "ui_Carousel.h"
#include "utility/CommonUtility.h"

Carousel::Carousel(QWidget *parent) : QWidget(parent), ui(new Ui::Carousel) {
  ui->setupUi(this);
  initWidget();
}

Carousel::~Carousel() { delete ui; }

void Carousel::initWidget() {
  changeTimer = new QTimer(this);
  connect(changeTimer, &QTimer::timeout, this, &Carousel::ChangeImage);

  changeTimer->setInterval(CarouselSpace::INTERVAL_TIMER);
  changeTimer->start();

  //设置中间图片置于顶层
  ui->labelThird->raise();

  ui->labelFifth->lower();

  //每个图片数据，参考双向链表思想
  ImaData imaData1;
  imaData1.labelCurrent = ui->labelFIrst;
  imaData1.labelPre = ui->labelFifth;
  imaData1.labelNext = ui->labelSecond;
  imaData1.pushButton = ui->pushButtonFirst;
  imaData1.properAnimation =
      new QPropertyAnimation(ui->labelFIrst, CarouselSpace::ANIMATION_GEOMETRY);
  imaDataList.append(imaData1);

  ImaData imaData2;
  imaData2.labelCurrent = ui->labelSecond;
  imaData2.labelPre = ui->labelFIrst;
  imaData2.labelNext = ui->labelThird;
  imaData2.pushButton = ui->pushButtonSecond;
  imaData2.properAnimation = new QPropertyAnimation(
      ui->labelSecond, CarouselSpace::ANIMATION_GEOMETRY);
  imaDataList.append(imaData2);

  ImaData imaData3;
  imaData3.labelCurrent = ui->labelThird;
  imaData3.labelPre = ui->labelSecond;
  imaData3.labelNext = ui->labelForth;
  imaData3.pushButton = ui->pushButtonThird;
  imaData3.properAnimation =
      new QPropertyAnimation(ui->labelThird, CarouselSpace::ANIMATION_GEOMETRY);
  imaDataList.append(imaData3);

  ImaData imaData4;
  imaData4.labelCurrent = ui->labelForth;
  imaData4.labelPre = ui->labelThird;
  imaData4.labelNext = ui->labelFifth;
  imaData4.pushButton = ui->pushButtonForth;
  imaData4.properAnimation =
      new QPropertyAnimation(ui->labelForth, CarouselSpace::ANIMATION_GEOMETRY);
  imaDataList.append(imaData4);

  ImaData imaData5;
  imaData5.labelCurrent = ui->labelFifth;
  imaData5.labelPre = ui->labelForth;
  imaData5.labelNext = ui->labelFIrst;
  imaData5.pushButton = ui->pushButtonFifth;
  imaData5.properAnimation =
      new QPropertyAnimation(ui->labelFifth, CarouselSpace::ANIMATION_GEOMETRY);
  imaDataList.append(imaData5);

  QString styleSheetcarousel(":/qss/res/qss/defaultstyle/carousel.css");
  for (int i = 0; i < imaDataList.size(); i++) {
    imaDataList.at(i).labelCurrent->installEventFilter(this);
    imaDataList.at(i).properAnimation->setDuration(
        CarouselSpace::ANIMATION_DURTION);
    imaDataList.at(i).properAnimation->setEasingCurve(
        QEasingCurve::BezierSpline);
    animationGroup.addAnimation(imaDataList.at(i).properAnimation);

    qDebug() << "carousel: " << i;
    CommonUtility::setStyleSheet(styleSheetcarousel,
                                 imaDataList.at(i).labelCurrent);
  }

  ui->pushButtonPre->raise();
  ui->pushButtonNext->raise();
  connect(ui->pushButtonPre, &QPushButton::clicked, [=]() {
    if (animationGroup.state() != QParallelAnimationGroup::Running) {
      this->SetPreAnimation();
    }
  });
  connect(ui->pushButtonNext, &QPushButton::clicked, [=]() {
    if (animationGroup.state() != QParallelAnimationGroup::Running) {
      this->SetNextAnimation();
    }
  });
}
//每隔几秒切换图片
void Carousel::ChangeImage() {
  if (animationGroup.state() != QParallelAnimationGroup::Running) {
    this->SetNextAnimation();
  }

  return;
}

void Carousel::SetNextAnimation() {
  qDebug() << __FUNCTION__;
  qDebug() << imaDataList.size();
  //设置每个图片向后移动 每个图片的动画起始位置是当前Label的位置
  //结束位置是其记录的前一个Label的位置
  for (int i = 0; i < imaDataList.size(); i++) {
    imaDataList.at(i).properAnimation->setStartValue(
        imaDataList.at(i).labelCurrent->geometry());
    imaDataList.at(i).properAnimation->setEndValue(
        imaDataList.at(i).labelPre->geometry());
  }

  animationGroup.start();

  if (centerIndex == CarouselSpace::SORT_FIFTH) {
    centerIndex = CarouselSpace::SORT_FIRST;
  } else {
    centerIndex++;
  }
  //图层排序
  this->sortGeometry();
  return;
}

void Carousel::SetPreAnimation() {
  qDebug() << "SetPreAnimation:" << centerIndex;
  for (int i = 0; i < imaDataList.size(); i++) {
    imaDataList.at(i).properAnimation->setStartValue(
        imaDataList.at(i).labelCurrent->geometry());
    imaDataList.at(i).properAnimation->setEndValue(
        imaDataList.at(i).labelNext->geometry());
  }

  if (centerIndex == CarouselSpace::SORT_FIRST) {
    centerIndex = CarouselSpace::SORT_FIFTH;
  } else {
    centerIndex--;
  }
  qDebug() << "new:" << centerIndex;
  animationGroup.start();
  //图层排序
  this->sortGeometry();
  return;
}

//图片图层排序
//
void Carousel::sortGeometry() {
#if 0
  for (int i=0;i<imaDataList.size();i++) {
      if(centerIndex == i)
        {
          imaDataList.at(i).labelCurrent->raise();
          imaDataList.at(i).pushButton->setChecked(true);
        }else
        {
          imaDataList.at(i).labelCurrent->lower();
          imaDataList.at(i).pushButton->setChecked(false);
        }
    }
#endif

  qDebug() << "centerIndex:" << centerIndex;

  switch (centerIndex) {
    case CarouselSpace::SORT_FIRST: {
      imaDataList.at(3).labelCurrent->lower();
      imaDataList.at(2).labelCurrent->lower();
    } break;
    case CarouselSpace::SORT_SECOND: {
      imaDataList.at(3).labelCurrent->lower();
      imaDataList.at(4).labelCurrent->lower();
    } break;
    case CarouselSpace::SORT_THIRD: {
      imaDataList.at(4).labelCurrent->lower();
      imaDataList.at(0).labelCurrent->lower();
    } break;
    case CarouselSpace::SORT_FOURTH: {
      imaDataList.at(0).labelCurrent->lower();
      imaDataList.at(1).labelCurrent->lower();
    } break;
    case CarouselSpace::SORT_FIFTH: {
      imaDataList.at(1).labelCurrent->lower();
      imaDataList.at(2).labelCurrent->lower();
    } break;
  }

  imaDataList.at(centerIndex).labelPre->raise();
  imaDataList.at(centerIndex).labelNext->raise();
  imaDataList.at(centerIndex).labelCurrent->raise();
}
