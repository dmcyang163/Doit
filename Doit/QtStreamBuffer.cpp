#include "QtStreamBuffer.h"


QtStreamBuffer::QtStreamBuffer(QTextEdit* textEdit) : m_textEdit(textEdit) {}


std::streambuf::int_type QtStreamBuffer::overflow(std::streambuf::int_type v) {
    if (v == std::streambuf::traits_type::eof())
    {
        return std::streambuf::traits_type::eof();
    }
    char c = static_cast<char>(v);
    if (c == '\n')
    {
        QMetaObject::invokeMethod(m_textEdit, [this]() {
            m_textEdit->append("");
            }, Qt::QueuedConnection);
    }
    else
    {
        QMetaObject::invokeMethod(m_textEdit, [this, c]() {
            m_textEdit->insertPlainText(QString(c));
            }, Qt::QueuedConnection);
    }
    return v;
}


std::streamsize QtStreamBuffer::xsputn(const char* s, std::streamsize n) {
    std::string str(s, s + n);
    QMetaObject::invokeMethod(m_textEdit, [this, str]() {
        m_textEdit->insertPlainText(QString::fromStdString(str));
        }, Qt::QueuedConnection);
    return n;
}