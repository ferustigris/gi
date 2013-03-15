#ifndef LABELI_H
#define LABELI_H
#include "label.h"

class LabelI : public Label
{
public:
    LabelI(MainWindow* mw, Log*log);
    virtual void setValue(const QByteArray& data);
};

#endif // LABELI_H
