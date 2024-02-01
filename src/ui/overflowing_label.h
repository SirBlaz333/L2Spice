#ifndef OVERFLOWING_LABEL_H
#define OVERFLOWING_LABEL_H

#include <QFrame>

class OverflowingLabel : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool isElided READ isElided)

public:
    explicit OverflowingLabel(QWidget *parent = nullptr);
    explicit OverflowingLabel(const QString &text, QWidget *parent = nullptr);
    ~OverflowingLabel();

    void setText(const QString &text);
    const QString & text() const { return content; }
    bool isElided() const { return elided; }

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void elisionChanged(bool elided);

private:
    bool elided;
    QString content;
};

#endif // OVERFLOWING_LABEL_H
