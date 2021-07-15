#pragma once

#include <QByteArray>
#include <queue>
#include <QMutex>

extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/frame.h>
}

class CStreamDecoder
{
public:
	CStreamDecoder();
	~CStreamDecoder();

	bool initialize();
	void push(const QByteArray& frame);
	bool decode(QByteArray &decodeFrame);

private:
	AVCodecContext* allocateAvCodecContext(AVCodecID avCodecId);

private:
	AVCodecContext* m_pAvCodecContext = nullptr;
	AVFrame* m_pAvFrame = nullptr;

	std::queue<QByteArray> m_videoFrameQueue;
	QMutex m_videoFrameQueueMutex;
};