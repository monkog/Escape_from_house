# pragma once
#include "kinect_audioStream.h"

#include <Windows.h>
#include "NuiApi.h"

// Speech interface
#include <sapi.h>
#include <sphelper.h>

// Audio interface
#include <propsys.h>
#include <wmcodecdsp.h>
#include <uuids.h>
#include <dmo.h>
#include <mfobjects.h>

#include <FaceTrackLib.h>

namespace mini
{
	class KinectService
	{
	public:
		KinectService();
		~KinectService();

		bool Initialize();
		void Shutdown();

		void Nui_GotSkeletonAlert();
		void SetSysMemSkeletonBuffer(BYTE* buffer);
		BYTE* GetSysMemSkeletonBuffer();
		float* GetFaceBuffers();
	private:
		static DWORD WINAPI Nui_ProcessThread(LPVOID pParam);
		HRESULT InitializeAudioStream();
		HRESULT LoadSpeechGrammar();
		HRESULT CreateSpeechRecognizer();
		HRESULT StartSpeechRecognition();
		void ProcessSpeech();

		void initFaceTracker();
		void storeFace();
		INuiSensor *m_nuiSensor;
		HANDLE m_nuiProcess;
		HANDLE m_nuiProcessStop;

		BYTE* m_skeletonBuffer;

		HANDLE m_skeletonEvent;
		HANDLE m_depthFrameEvent;
		HANDLE m_videoFrameEvent;

		HANDLE m_depthStreamHandle;
		HANDLE m_videoStreamHandle;

		KinectAudioStream *m_kinectAudioStream;
		HANDLE m_speechEvent;
		ISpStream *m_speechStream;
		ISpRecoContext *m_speechContext;
		ISpRecoGrammar *m_speechGrammar;
		ISpRecognizer *m_speechRecognizer;

		float faceScale;
		float faceR[3];
		float faceT[3];
		IFTFaceTracker *pFaceTracker;
		IFTResult *pFTResult;
		IFTImage *m_imageBuffer;
		IFTImage *m_depthBuffer;
		bool lastTrackSucceeded;
	};
}