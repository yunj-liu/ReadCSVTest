#include <QCoreApplication>
#include <iostream>
#include <QTimer>
#include <QPointF>
#include <QFile>
#include <QDir>

using std::cout, std::endl;

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;
typedef QHash<QString, DataTable> FigureData;

FigureData getFigureDataHashMapFromCsvFile(QString sFoldName);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str = "Hello";
    cout << "abc123" << endl;
    cout << str.toStdString().data() << endl;
    //

//    QString path(QDir::currentPath());
//    path = path + "/projdata/";

//    QString sPathName;
//    //sPathName = QDir::currentPath();
//    sPathName = path;
//    QDir dir(sPathName);
//    if(dir.exists()){
//        qDebug() << "exist";
//        qDebug() << sPathName;
//    }
//    else{
//        qDebug() << "dir non exist";
//        qDebug() << sPathName;
//    }
//    QString filePathName = sPathName + "figure1" + ".csv";
//    //QString filePathName = QString("d:/abc/") + "figure1" + ".csv";
//    QFile file;
//    file.setFileName(filePathName);
//    if(file.exists()){
//        qDebug() << "exist - " + filePathName;
//    }
//    else{
//        qDebug() << "no exist - " + filePathName;
//    }

//    FigureData datatableHashMap;
//    DataTable datatable_figure1;
//    QString line;
//    QStringList lineitem;
//    int row=0;
//    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        QTextStream in_stream(&file);
//        /*
//        //while(!in_stream.atEnd()){
//            line = in_stream.readLine();
//            lineitem = line.split(',');

//            int listCount = lineitem.count() - 1;
//            qDebug() << "listCount:" << listCount;
//            qDebug() << lineitem.at(0);
//            double t1 = lineitem.at(0).toDouble();
//            qDebug() << "t1:" << t1;

//            DataList *datalistArray = new DataList[listCount];
//            qDebug() << "datatable_figure1.count():" << datatable_figure1.count();
//            for(int i(0); i<listCount; i++){
//                QPointF value(lineitem.at(0).toDouble(), lineitem.at(i+1).toDouble());
//                QString label = "Slice " + QString::number(i) + ":" + QString::number(row);
//                //datatable_figure1.at(i) << Data(value, label);
//                datalistArray[i] << Data(value, label);
//            }
//            qDebug() << datalistArray[0];
//            qDebug() << datalistArray[1];
//            qDebug() << datalistArray[2];
//            row++;
//        //}
//            qDebug() << "row:" << row;
//        */
//        int listCount=0;
//        if(!in_stream.atEnd()){ //Handle the first line first,for get listCount define datalistArray
//            line = in_stream.readLine();
//            if(!line.isEmpty()){
//                lineitem = line.split(',');
//                listCount = lineitem.count() - 1;  //the first col is the coordinate x, so the num of lists must sub 1
//                DataList *datalistArray = new DataList[listCount];
//                for(int j(0); j<listCount; j++){
//                    QPointF value(lineitem.at(0).toDouble(), lineitem.at(j+1).toDouble());
//                    QString label = "Slice " + QString::number(row) + ":" + QString::number(j);
//                    datalistArray[j] << Data(value, label);
//                }
//                row = row + 1;

//                //Continue with the remaining lines
//                while(!in_stream.atEnd()){
//                    line = in_stream.readLine();
//                    if(!line.isEmpty()){
//                        lineitem = line.split(',');
//                        for(int j(0); j<listCount; j++){
//                            if(!(lineitem.at(j+1).isEmpty() || lineitem.at(j+1).isNull())){
//                                QPointF value(lineitem.at(0).toDouble(), lineitem.at(j+1).toDouble());
//                                QString label = "Slice " + QString::number(row) + ":" + QString::number(j);
//                                datalistArray[j] << Data(value, label);
//                            }
//                        }
//                        row++;
//                    }
//                }
//                for(int j(0); j<listCount; j++){
//                    datatable_figure1 << datalistArray[j];
//                }
//            }
//        }
//        file.close();
//    }

//    qDebug() << row;
//    qDebug() << datatable_figure1.count();
//    int n = datatable_figure1.at(0).count();
//    qDebug() << datatable_figure1.at(0).at(n-1).first.x();
//    qDebug() << datatable_figure1.at(0).at(n-1).first.y();
//    qDebug() << datatable_figure1.at(0).at(n-1).second;
//    qDebug() << datatable_figure1.at(1).at(0).first.x();
//    qDebug() << datatable_figure1.at(1).at(0).first.y();
//    qDebug() << datatable_figure1.at(1).at(0).second;

//    DataTable dt;
//    qDebug() << dt.count();


    qDebug() << "----";
    FigureData dtmap = getFigureDataHashMapFromCsvFile("/projdata/");
    for(int i(1); i<=7; i++)
        qDebug() << dtmap["figure"+QString::number(i)].count();


    //Add this, otherwise the Qt console program will not end automatically
    QTimer t;
    t.connect(&t, SIGNAL(timeout()), &a, SLOT(quit()));
    t.start(3000);  // 20millisecond
    return a.exec();
}

DataTable getDataTableFromCsvFile(QString filePathName)
{
    DataTable dt;
    QFile file;
    file.setFileName(filePathName);
    if(!file.exists()){
        return dt;
    }
    QString line;
    QStringList lineitem;
    int row=0;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in_stream(&file);
        int listCount=0;
        if(!in_stream.atEnd()){ //Handle the first line first,for get listCount define datalistArray
            line = in_stream.readLine();
            if(!line.isEmpty()){
                lineitem = line.split(',');
                listCount = lineitem.count() - 1;  //the first col is the coordinate x, so the num of lists must sub 1
                DataList *datalistArray = new DataList[listCount];
                for(int j(0); j<listCount; j++){
                    QPointF value(lineitem.at(0).toDouble(), lineitem.at(j+1).toDouble());  //lineitem.at(0) is coordinate x
                    QString label = "Slice " + QString::number(row) + ":" + QString::number(j);
                    datalistArray[j] << Data(value, label);
                }
                row = row + 1;

                //Continue with the remaining lines
                while(!in_stream.atEnd()){
                    line = in_stream.readLine();
                    if(!line.isEmpty()){
                        lineitem = line.split(',');
                        for(int j(0); j<listCount; j++){
                            if(!(lineitem.at(j+1).isEmpty() || lineitem.at(j+1).isNull())){  //figure6 last col only has one number, so the remaining row in last col not append data in list
                                QPointF value(lineitem.at(0).toDouble(), lineitem.at(j+1).toDouble());
                                QString label = "Slice " + QString::number(row) + ":" + QString::number(j);
                                datalistArray[j] << Data(value, label);
                            }
                        }
                        row++;
                    }
                }
                for(int j(0); j<listCount; j++){
                    dt << datalistArray[j];
                }
            }
        }
        file.close();
    }
    return dt;
}

FigureData getFigureDataHashMapFromCsvFile(QString sFoldName)
{
    FigureData datatableMap;
    if(!sFoldName.startsWith('/')){
        sFoldName = "/" + sFoldName;
    }
    if(!sFoldName.endsWith('/')){
        sFoldName += "/";
    }
    QString sPathName;
    QString currend_path(QDir::currentPath());
    sPathName = currend_path + sFoldName;
    //not confirm the path exist or not, if the dir is not exist, so the getDataTableFromCsvFile return empty dt, the dt's count is 0
    //but key must in hash map, eg "figure1", etc, dt can be the empty, means it's count is zero
    //QDir dir(sPathName);
    //if(dir.exists())
    for(int i(1); i<=7; i++){
        DataTable dt = getDataTableFromCsvFile(sPathName+"figure"+QString::number(i)+".csv");
        datatableMap.insert("figure"+QString::number(i), dt);
    }

    return datatableMap;
}
