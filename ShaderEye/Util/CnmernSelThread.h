#ifndef CANMERNSELTHREAD_H
#define CANMERNSELTHREAD_H
/**
 * @date 2020/07/20
 * @author changyanlong github.com/numberwolf q531365872
 */

#include <QDebug>
#include <QString>
#include <QObject>

// 头文件
class CnmernSelThread : public QObject
{
    Q_OBJECT
private:
    // params

public:
    CnmernSelThread(QObject* parent = nullptr);
    ~CnmernSelThread();

    void setInput();

public slots:
    void start1();
    void doWork();

signals:
    void workFinished(int param1);
    void workStart();
};


#endif
