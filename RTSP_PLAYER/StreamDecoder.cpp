#include "StreamDecoder.h"

#include "opencv2/core.hpp"

#pragma comment(lib,"opencv_core310d.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma warning(disable: 4996)

CStreamDecoder::CStreamDecoder()
{
}

CStreamDecoder::~CStreamDecoder()
{
	if (nullptr != m_pAvFrame)
		av_frame_free(&m_pAvFrame);

	if (nullptr != m_pAvCodecContext)
		avcodec_free_context(&m_pAvCodecContext);
}

bool CStreamDecoder::initialize()
{
	m_pAvCodecContext = allocateAvCodecContext(AV_CODEC_ID_H264);

	if (m_pAvCodecContext == nullptr)
		return false;
	
	m_pAvFrame = av_frame_alloc();

	if (m_pAvFrame == nullptr)
	{
		avcodec_free_context(&m_pAvCodecContext);

		return false;
	}

	return true;
}

void CStreamDecoder::push(const QByteArray& frame)
{
	QMutexLocker mutexLocker(&m_videoFrameQueueMutex);

	m_videoFrameQueue.push(frame);
}

bool CStreamDecoder::decode(QByteArray& decodeFrame)
{
	QByteArray frame;
	int gotPicture = 0;

	{
		QMutexLocker mutexLocker(&m_videoFrameQueueMutex);

		if (false == m_videoFrameQueue.empty())
		{
			frame = m_videoFrameQueue.front();
			m_videoFrameQueue.pop();
		}
	}

	if (frame.isEmpty() == true)
		return false;
	
	if (m_pAvCodecContext != nullptr)
	{
		AVPacket avPacket;
		av_init_packet(&avPacket);

		avPacket.data = (uint8_t *)frame.data();
		avPacket.size = frame.size();

		int frameSize = avcodec_decode_video2(m_pAvCodecContext, m_pAvFrame, &gotPicture, &avPacket);

		if (0 < frameSize && 0 != gotPicture)
		{
			//cv::Mat mat(m_pAvFrame->height, m_pAvFrame->width, CV_8UC1, m_pAvFrame->data[0]);

			decodeFrame = QByteArray((char*)m_pAvFrame->data[0], m_pAvFrame->height * m_pAvFrame->width);
		}
		else
			printf("Decode Failed\n");
	}

	return 0 != gotPicture ? true : false;
}

AVCodecContext* CStreamDecoder::allocateAvCodecContext(AVCodecID avCodecId)
{
	if (avCodecId != AV_CODEC_ID_H264)
		return nullptr;

	AVCodec* pAvCodec = avcodec_find_decoder(avCodecId);

	if (pAvCodec == nullptr)
		return nullptr;

	AVCodecContext* pAvcodecContext = avcodec_alloc_context3(pAvCodec);

	if (pAvcodecContext == nullptr)
		return nullptr;

	if (avcodec_open2(pAvcodecContext, pAvCodec, nullptr) < 0)
	{
		avcodec_free_context(&pAvcodecContext);
		
		return nullptr;
	}

	return pAvcodecContext;
}
