#include "label.h"
#include <QHBoxLayout>

Label::Label(MainWindow* mw, Log*log) : Widget(mw, log)
{
	l = new QLabel("asd", this);
	l->show();
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(l);
	setLayout(layout);
	setWindowTitle(tr("Label"));
}
Label::~Label()
{
    delete l;
}
//! set value (different for different widgets)
void Label::setValue(const QByteArray& data)
{
	QString str("");
	for(int i = 0; i < data.size(); i++)
	{
		switch(data[i])
		{
		case F:
			{
			int k = i + 1;
			i+= 4;
			float value = 0;
			if(i < data.size())
				memcpy(&value, data.data() + k, 4);
			str += QString::number(value);
			break;
			}
                case I:
                        {
                        int k = i + 1;
                        i+= 4;
                        qint32 value = 0;
                        if(i < data.size())
                                memcpy(&value, data.data() + k, 4);
                        str += QString::number(value);
                        break;
                        }
                case HEX:
                        {
                        int k = i + 1;
                        i+= 4;
                        qint32 value = 0;
                        if(i < data.size())
                                memcpy(&value, data.data() + k, 4);
                        str += "0x" + QString::number(value, 16);
                        break;
                        }
                default:
			str += QChar(data[i]);
		}
	}
	l->setText(str);
	addMsg(tr("Receive text: ") + str);
}
