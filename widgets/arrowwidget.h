#ifndef ARROWWIDGET_H
#define ARROWWIDGET_H

#include <QWidget>
#include "selectablewidget.h"

class LineEdit;
class ImageLabel;

class ArrowWidget : public SelectableWidget<ArrowWidget> // QWidget
{
	Q_OBJECT
public:
	explicit ArrowWidget(QPoint start, QPoint end, QWidget *parent);
	void invert();
	void setColor(QColor newColor);
	
//signals:
//	void selected(ArrowWidget *widget);
	
public slots:
	void setEnd(QPoint _end);
	void showEdit(QString text = QString());
//	void unselected();

protected:
//	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	
//	void focusOutEvent(QFocusEvent *e);

private slots:
	void updateGeometries();

private:
	QColor color;
	QPoint start, end;
	QSize arrowSize;
//	LineEdit *lineEdit;
	bool inverted;
	static const int margin;

	friend QDataStream &operator >> (QDataStream &stream, ImageLabel &imageLabel);
	friend QDataStream &operator << (QDataStream &stream, const ImageLabel &imageLabel);
};

#endif // ARROWWIDGET_H