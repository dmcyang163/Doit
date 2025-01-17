#include "QtStreamBuffer.h"


// QtStreamBuffer
QtStreamBuffer::QtStreamBuffer(QTextEdit* textEdit) : m_textEdit(textEdit) {}


QtStreamBuffer::~QtStreamBuffer() {
	flushBuffer();
}


std::streambuf::int_type QtStreamBuffer::overflow(std::streambuf::int_type v) {
	if (v == std::streambuf::traits_type::eof())
	{
		return std::streambuf::traits_type::eof();
	}
	m_buffer.push_back(static_cast<char>(v));
	if (m_buffer.size() >= m_bufferSize)
	{
		flushBuffer();
	}
	return v;
}


std::streamsize QtStreamBuffer::xsputn(const char* s, std::streamsize n) {
	m_buffer.append(s, n);
	if (m_buffer.size() >= m_bufferSize)
	{
		flushBuffer();
	}
	return n;
}


void QtStreamBuffer::flushBuffer() {
	if (!m_buffer.empty())
	{
		QMetaObject::invokeMethod(m_textEdit, [this]() {
			m_textEdit->insertPlainText(QString::fromStdString(m_buffer));
			m_buffer.clear();
			}, Qt::QueuedConnection);
	}
}
