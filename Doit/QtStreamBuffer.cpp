#include "QtStreamBuffer.h"


// QtStreamBuffer
QtStreamBuffer::QtStreamBuffer(QTextEdit* textEdit) : m_textEdit(textEdit), m_mutex(std::make_unique<std::mutex>()) {}


QtStreamBuffer::~QtStreamBuffer() {
	flushBuffer();
}


std::streambuf::int_type QtStreamBuffer::overflow(std::streambuf::int_type v) {
	if (v == std::streambuf::traits_type::eof())
	{
		return std::streambuf::traits_type::eof();
	}
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_buffer.push_back(static_cast<char>(v));
	if (m_buffer.size() >= m_bufferSize)
	{
		flushBuffer();
	}
	return v;
}


std::streamsize QtStreamBuffer::xsputn(const char* s, std::streamsize n) {
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_buffer.append(s, n);
	if (m_buffer.size() >= m_bufferSize)
	{
		flushBuffer();
	}
	return n;
}


void QtStreamBuffer::flushBuffer() {
	std::string bufferToFlush;
	{
		//std::lock_guard<std::mutex> lock(*m_mutex);
		std::swap(bufferToFlush, m_buffer);
	}
	if (!bufferToFlush.empty())
	{
		QMetaObject::invokeMethod(m_textEdit, [this, bufferToFlush]() {
			m_textEdit->insertPlainText(QString::fromStdString(bufferToFlush));
				}, Qt::QueuedConnection);
	}

}
