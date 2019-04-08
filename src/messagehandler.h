#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QtGlobal>
#include <QString>
#include <QByteArray>

class Suppress
{
public:
	Suppress();
//	bool operator <<(bool b);
	~Suppress();
	
private:
	static bool suppress;
	friend void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);
};

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

#endif // MESSAGEHANDLER_H
