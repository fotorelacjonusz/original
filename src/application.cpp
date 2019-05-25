#define _SYS_SYSMACROS_H // conflicts with major() and minor() 

#include "application.h"
#include "exception.h"
#include <QCursor>
#include <QStringList>

Application::Application(int &argc, char **argv):
	QApplication(argc, argv)
{
	#if defined(Q_OS_MACOS)
	this->setAttribute(Qt::AA_DontShowIconsInMenus, true);
	#endif
}

QString Application::applicationSettingsName()
{
	return applicationName() + QString::number(Version(applicationVersion()).major);
}

QString Application::applicationNameAndVersion()
{
	return applicationName() + " " + applicationVersion();
}

void Application::busy()
{
	qApp->processEvents();
	setOverrideCursor(Qt::WaitCursor);
}

void Application::idle()
{
	while (overrideCursor())
		restoreOverrideCursor();
	qApp->processEvents();
}

bool Application::notify(QObject *object, QEvent *event)
{
	try
	{
		return QApplication::notify(object, event);
	}
	catch (const Exception &e)
	{
		e.showMessage(nullptr);
	}
	return false;
}

Version::Version(QString version):
	major (version.section('.', 0, 0).toInt()),
	format(version.section('.', 1, 1).toInt()),
	minor (version.section('.', 2, 2).toInt())
{
	Q_ASSERT(QRegExp("\\d+\\.\\d+\\.\\d+").exactMatch(version));
}

bool Version::isPhrCompatible(const Version &other)
{
	return major == other.major && format == other.format;
}
