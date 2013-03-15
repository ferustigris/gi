#ifndef LABELF_H
#define LABELF_H
#include "label.h"

class LabelF : public Label
{
public:
    LabelF(MainWindow* mw, Log*log);
    virtual void setValue(const QByteArray& data);
};

#endif // LABELF_H
