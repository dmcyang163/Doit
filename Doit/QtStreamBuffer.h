#ifndef QTSTREAMBUFFER_H
#define QTSTREAMBUFFER_H

#include <iostream>
#include <QTextEdit>
#include <QMetaObject>
#include <QString>
#include <streambuf>


class QtStreamBuffer : public std::streambuf {
public:
    QtStreamBuffer(QTextEdit* textEdit);

protected:
    virtual std::streambuf::int_type overflow(std::streambuf::int_type v) override;
    virtual std::streamsize xsputn(const char* s, std::streamsize n) override;

private:
    QTextEdit* m_textEdit;
};

#endif // QTSTREAMBUFFER_H