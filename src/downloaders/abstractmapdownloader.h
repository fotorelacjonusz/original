#pragma once

#include <QObject>
#include <QPointF>
#include <QRect>
#include <QPair>

class QNetworkReply;
class GpsData;
class GeoMap;
class OverlayImage;

class AbstractMapDownloader
{
protected:
	typedef QPair<OverlayImage *, qreal> DistancePair;
	AbstractMapDownloader();

public:
	virtual ~AbstractMapDownloader();
	virtual void finished(QNetworkReply *reply);
	virtual bool makeMap(GeoMap *map) = 0;

protected:
	QSize maxSize() const;
	static const int margin;
};

/*
 * Class bypasses direct calling of makeMap using signal-slot connection,
 * so the subclass can block in makeMapSlot using QEventLoop.
 * It assumes map creation will always succeed.
 */
class AsyncMapDownloader : public QObject, public AbstractMapDownloader
{
	Q_OBJECT

protected:
	AsyncMapDownloader();

public:
	virtual bool makeMap(GeoMap *map); // final

signals:
	void makeMapSignal(GeoMap *map);

protected slots:
	virtual void makeMapSlot(GeoMap *map) = 0;
};

inline uint qHash(QPointF point)
{
	return point.toPoint().x() << 16 | point.toPoint().y();
}

QRect centered(const QPoint &center, const QSize &size);
QRect centered(const QPoint &center, const int size);

QRect resized(const QRect &rect, const qreal factor);
QRect resized(const QRect &rect, QSize size);
