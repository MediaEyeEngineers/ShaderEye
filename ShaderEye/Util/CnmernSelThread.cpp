#include "CnmernSelThread.h"
/**
 * @date 2020/07/20
 * @author changyanlong github.com/numberwolf q531365872
 */

CnmernSelThread::CnmernSelThread(QObject* parent) : QObject (parent) {

}

CnmernSelThread::~CnmernSelThread() {
}

void CnmernSelThread::setInput() {

}

void CnmernSelThread::start1() {
    qDebug()<< "CnmernSelThread::start1" << endl;
    emit workStart();
    doWork();
}

void CnmernSelThread::doWork() {
    emit workFinished(1);
}
