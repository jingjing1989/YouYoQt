#pragma execution_character_set("utf-8")
#ifndef WEATHER_H
#define WEATHER_H

#include <QByteArray>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QMultiMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QVector>

class weather : public QObject {
  Q_OBJECT
public:
  explicit weather(QObject *parent = nullptr);
  explicit weather(QString cityname = "");

public:
  //设置城市
  void setCityName(QString strCityName);
  //获取城市名称
  QString getCityName();
  //获取当前日期
  QString getCurrentDate();
  //获取温度范围
  QString getTempratureRange();
  //获取当前温度
  QString getCurrentTemprature();
  //获取天气类型
  QString getWeatherType();
  //获取风向风力
  QString getWind();
  //获取感冒提示
  QString getColdInfo();
  //获取全部信息
  QString getAllData();
  //获取数据转为map
  QVector<QMap<QString, QString>> getAllDataMap();

signals:
  //获取数据结束的信号
  void getDataFinisedSignal();
  //获取数据成功的信号
  void getDataSuccessedSignal();
  //获取数据失败的信号
  void getDataFailedSignal();

private:
  //城市名
  QString strCityName;
  //网络请求
  QNetworkAccessManager *manager;

  //所有信息
  QByteArray allArray;

  //各种信息
  //当前日期
  QString currentDate;
  //温度
  QString tempratureRange;
  //当前温度
  QString currentTemprature;
  //类型
  QString weathertype;
  //风力
  QString wind;
  //感冒提示
  QString cold;
  //查询天气
  void weather::queryWeather();
  //槽函数
  void netReplyFinished(QNetworkReply *reply);

  //数据
  // QMap<QString, QMap<QString, QString>> dataMap;
  QVector<QMap<QString, QString>> dataMap;
};

#endif // WEATHER_H
