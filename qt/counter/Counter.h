// ======================================================================
//  Counter.h
// ======================================================================
//                   This file is a part of the book 
//             "Qt 5.3 Professional programming with C++"
// ======================================================================
//  Copyright (c) 2014 by Max Schlee
//
//  Email : Max.Schlee@neonway.com
//  Blog  : http://www.maxschlee.com
//
//  Social Networks
//  ---------------
//  FaceBook : http://www.facebook.com/mschlee
//  Twitter  : http://twitter.com/Max_Schlee
//  2Look.me : http://2look.me/NW100003
//  Xing     : http://www.xing.com/profile/Max_Schlee
//  vk.com   : https://vk.com/max.schlee
// ======================================================================

#pragma once

#include <QObject>

// ======================================================================
class Counter : public QObject {
    Q_OBJECT
private:
    int m_nValue;

public:
    Counter();

public slots:
    void slotShowAction(const QString&);
    void slotInc();

signals:
    void goodbye       (   );
    void counterChanged(int);
    //void mappedString(QString&);
};
