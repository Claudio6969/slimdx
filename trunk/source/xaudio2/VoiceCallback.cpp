/*
* Copyright (c) 2007-2009 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <xaudio2.h>
#include <vcclr.h>

#include "../ComObject.h"
#include "../Result.h"

#include "SourceVoice.h"
#include "VoiceCallback.h"

using namespace System;

namespace SlimDX
{
namespace XAudio2
{
	VoiceCallbackShim::VoiceCallbackShim( SourceVoice^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	void VoiceCallbackShim::OnBufferEnd( void *context )
	{
		m_WrappedInterface->InvokeBufferEnd( gcnew ContextEventArgs( IntPtr( context ) ) );
	}

	void VoiceCallbackShim::OnBufferStart( void *context )
	{
		m_WrappedInterface->InvokeBufferStart( gcnew ContextEventArgs( IntPtr( context ) ) );
	}

	void VoiceCallbackShim::OnLoopEnd( void *context )
	{
		m_WrappedInterface->InvokeLoopEnd( gcnew ContextEventArgs( IntPtr( context ) ) );
	}

	void VoiceCallbackShim::OnStreamEnd()
	{
		m_WrappedInterface->InvokeStreamEnd();
	}

	void VoiceCallbackShim::OnVoiceError( void *context, HRESULT error )
	{
		m_WrappedInterface->InvokeVoiceError( gcnew ErrorEventArgs( Result( error ), IntPtr( context ) ) );
	}

	void VoiceCallbackShim::OnVoiceProcessingPassStart( UINT32 bytesRequired )
	{
		m_WrappedInterface->InvokeVoiceProcessingPassStart( gcnew StartProcessingEventArgs( bytesRequired ) );
	}

	void VoiceCallbackShim::OnVoiceProcessingPassEnd()
	{
		m_WrappedInterface->InvokeVoiceProcessingPassEnd();
	}
}
}