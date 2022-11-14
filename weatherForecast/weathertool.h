#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H

#include <QMap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class weathTool
{
public:
    static QString getCityCode(QString cityName)
    {
        if(mCityMap.isEmpty())
            initCityMap();

        auto it=mCityMap.find(cityName);
        //北京/北京市
        if(it==mCityMap.end())
            it=mCityMap.find(cityName+"市");
        if(it!=mCityMap.end())
            return it.value();

        return "";
    }

private:
    static QMap<QString,QString>mCityMap;

    static void initCityMap()
    {
        //1读取文件
        QString filePath=".//citycode-2019-08-23.json";
        QFile file(filePath);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray json=file.readAll();
        file.close();
        //2解析写入map
        QJsonParseError err;
        QJsonDocument doc=QJsonDocument::fromJson(json,&err);
        if(err.error!=QJsonParseError::NoError){return;}
        if(!doc.isArray()){return ;}

        QJsonArray cities=doc.array();
        for(int i=0;i<cities.size();i++)
        {
            QString city=cities[i].toObject().value("city_name").toString();
            QString code=cities[i].toObject().value("city_code").toString();
            if(code.size()>0)
                mCityMap.insert(city,code);
        }
    }

};
//全局变量进行初始化
QMap<QString,QString> weathTool::mCityMap={};

#endif // WEATHERTOOL_H
