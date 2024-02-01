#include "overflowing_label.h"

#include <QPainter>
#include <QTextLayout>

OverflowingLabel::OverflowingLabel(const QString &text, QWidget *parent)
    : QFrame(parent)
    , elided(false)
    , content(text)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

OverflowingLabel::OverflowingLabel(QWidget *parent)
    : QFrame(parent)
    , elided(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

OverflowingLabel::~OverflowingLabel() {}

void OverflowingLabel::setText(const QString &newText)
{
    content = newText;
    update();
}

void OverflowingLabel::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QFontMetrics fontMetrics = painter.fontMetrics();

    bool didElide = false;

    QTextLayout textLayout(content, painter.font());
    textLayout.beginLayout();
    QTextLine line = textLayout.createLine();

    if (line.isValid()) {
        line.setLineWidth(width());
        QString lastLine = content.mid(line.textStart());
        int leftMargin = 5;
        int rightMargin = 10;
        int topMargin = this->height() / 2;
        QString elidedLine = fontMetrics.elidedText(lastLine, Qt::ElideMiddle, width() - rightMargin);
        painter.drawText(QPoint(leftMargin, topMargin + fontMetrics.ascent()), elidedLine);
        line = textLayout.createLine();
        didElide = line.isValid();
    }

    textLayout.endLayout();
    if (didElide != elided) {
        elided = didElide;
        emit elisionChanged(didElide);
    }
}
