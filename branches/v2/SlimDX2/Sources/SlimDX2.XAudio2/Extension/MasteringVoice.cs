// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;

namespace SlimDX2.XAudio2
{
    public partial class MasteringVoice
    {
        /// <summary>	
        /// Creates and configures a mastering voice on the default audio device, with stereo channels at 44100Hz.
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX2.XAudio2.XAudio2" /></param>
        /// <unmanaged>HRESULT IXAudio2::CreateMasteringVoice([Out] IXAudio2MasteringVoice** ppMasteringVoice,[None] UINT32 InputChannels,[None] UINT32 InputSampleRate,[None] UINT32 Flags,[None] UINT32 DeviceIndex,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public MasteringVoice(XAudio2 device)
            : this(device, 2)
        {            
        }

        /// <summary>	
        /// Creates and configures a mastering voice on the default audio device and 44100Hz.
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX2.XAudio2.XAudio2" /></param>
        /// <param name="inputChannels">[in]  Number of channels the mastering voice expects in its input audio. InputChannels must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. InputChannels can be set to XAUDIO2_DEFAULT_CHANNELS, with the default being determined by the current platform. Windows  Attempts to detect the system speaker configuration setup.  Xbox 360  Defaults to 5.1 surround.  </param>
        /// <unmanaged>HRESULT IXAudio2::CreateMasteringVoice([Out] IXAudio2MasteringVoice** ppMasteringVoice,[None] UINT32 InputChannels,[None] UINT32 InputSampleRate,[None] UINT32 Flags,[None] UINT32 DeviceIndex,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public MasteringVoice(XAudio2 device, int inputChannels)
            : this(device, 2, 44100)
        {            
        }

        /// <summary>	
        /// Creates and configures a mastering voice on the default audio device.
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX2.XAudio2.XAudio2" /></param>
        /// <param name="inputChannels">[in]  Number of channels the mastering voice expects in its input audio. InputChannels must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. InputChannels can be set to XAUDIO2_DEFAULT_CHANNELS, with the default being determined by the current platform. Windows  Attempts to detect the system speaker configuration setup.  Xbox 360  Defaults to 5.1 surround.  </param>
        /// <param name="inputSampleRate">[in]  Sample rate of the input audio data of the mastering voice. This rate must be a multiple of XAUDIO2_QUANTUM_DENOMINATOR. InputSampleRate must be between XAUDIO2_MIN_SAMPLE_RATE and XAUDIO2_MAX_SAMPLE_RATE. InputSampleRate can be set to XAUDIO2_DEFAULT_SAMPLERATE, with the default being determined by the current platform. Windows  Windows XP defaults to 44100. Windows Vista and Windows 7 default to the setting specified in the Sound Control Panel. The default for this setting is 44100 (or 48000 if required by the driver).  Xbox 360  Defaults to 48000.  </param>
        /// <unmanaged>HRESULT IXAudio2::CreateMasteringVoice([Out] IXAudio2MasteringVoice** ppMasteringVoice,[None] UINT32 InputChannels,[None] UINT32 InputSampleRate,[None] UINT32 Flags,[None] UINT32 DeviceIndex,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public MasteringVoice(XAudio2 device, int inputChannels, int inputSampleRate)
            : this(device, inputChannels, inputSampleRate, 0)
        {
            
        }

        /// <summary>	
        /// Creates and configures a mastering voice.	
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX2.XAudio2.XAudio2" /></param>
        /// <param name="inputChannels">[in]  Number of channels the mastering voice expects in its input audio. InputChannels must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. InputChannels can be set to XAUDIO2_DEFAULT_CHANNELS, with the default being determined by the current platform. Windows  Attempts to detect the system speaker configuration setup.  Xbox 360  Defaults to 5.1 surround.  </param>
        /// <param name="inputSampleRate">[in]  Sample rate of the input audio data of the mastering voice. This rate must be a multiple of XAUDIO2_QUANTUM_DENOMINATOR. InputSampleRate must be between XAUDIO2_MIN_SAMPLE_RATE and XAUDIO2_MAX_SAMPLE_RATE. InputSampleRate can be set to XAUDIO2_DEFAULT_SAMPLERATE, with the default being determined by the current platform. Windows  Windows XP defaults to 44100. Windows Vista and Windows 7 default to the setting specified in the Sound Control Panel. The default for this setting is 44100 (or 48000 if required by the driver).  Xbox 360  Defaults to 48000.  </param>
        /// <param name="deviceIndex">[in]  Index of the output device that will be sent input by the mastering voice. Specifying the default value of 0 causes XAudio2 to select the global default audio device. </param>
        /// <unmanaged>HRESULT IXAudio2::CreateMasteringVoice([Out] IXAudio2MasteringVoice** ppMasteringVoice,[None] UINT32 InputChannels,[None] UINT32 InputSampleRate,[None] UINT32 Flags,[None] UINT32 DeviceIndex,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public MasteringVoice(XAudio2 device, int inputChannels, int inputSampleRate, int deviceIndex) : base(IntPtr.Zero)
        {
            MasteringVoice temp;
            device.CreateMasteringVoice(out temp, inputChannels, inputSampleRate, 0, deviceIndex, null);
            NativePointer = temp.NativePointer;
        }
    }
}