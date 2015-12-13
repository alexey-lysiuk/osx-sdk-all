/*
     File:       AudioUnitParameters.h
 
     Contains:   Parameter constants for Apple AudioUnits
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AudioUnitParameters
#define __AudioUnitParameters


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following file specifies the parameter IDs for the various audio units that apple ships,
allowing code to directly interact with these parameters without first discovering them
through the AUParameterInfo mechanism (see AudioUnitProperties.h)

Each parameter listed below is preceeded by a comment that indicates:
    // Scope, UnitOfMeasurement, minValue, maxValue, defaultValue
    
See AudioUnitProperties for additional information that a parameter may report

When displaying to the user information about a parameter an application SHOULD ALWAYS
get the parameter information from the AudioUnit itself
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


// Effects units
// Some parameters of effects units are dependent on the sample rate of the audio unit
// (ie. the maximum value is typically the Nyquist limit, or half the sample rate)

// These are the parameters for the BandpassFilter Unit
enum {
		// Global, Hz, 20->(SampleRate/2), 5000
	kBandpassParam_CenterFrequency 			= 0,

		// Global, Cents, 100->12000, 600
	kBandpassParam_Bandwidth 				= 1
};

// These are the parameters of the AUHipass Unit
enum {
		// Global, Hz, 10->(SampleRate/2), 6900
	kHipassParam_CutoffFrequency 			= 0,
		
		// Global, dB, -20->40, 0
	kHipassParam_Resonance					= 1
};

// These are the parameters of the AULowpass Unit
enum {
		// Global, Hz, 10->(SampleRate/2), 6900
	kLowPassParam_CutoffFrequency 			= 0,
		
		// Global, dB, -20->40, 0
	kLowPassParam_Resonance 				= 1
};

// These are the parameters of the AUHighShelfFilter
enum {
		// Global, Hz, 10000->(SampleRate/2), 10000
	kHighShelfParam_CutOffFrequency 		= 0,
		
		// Global, dB, -40->40, 0
	kHighShelfParam_Gain 					= 1
};

// These are the parameters of the AULowShelfFilter
enum {
		// Global, Hz, 10->200, 80
	kAULowShelfParam_CutoffFrequency = 0,
		
		// Global, dB, -40->40, 0
	kAULowShelfParam_Gain = 1
};

// These are the parameters of the AUParametricEQ
enum {
		// Global, Hz, 20->(SampleRate/2), 2000
    kParametricEQParam_CenterFreq = 0,
		
		// Global, Hz, 0.1->20, 1.0
    kParametricEQParam_Q = 1,
		
		// Global, dB, -20->20, 0
    kParametricEQParam_Gain = 2
};

// These are the parameters of the AUMatrixReverb
enum {
		// Global, EqPow CrossFade, 0->100, 100
	kReverbParam_DryWetMix 							= 0,
		
		// Global, EqPow CrossFade, 0->100, 50
	kReverbParam_SmallLargeMix						= 1,
		
		// Global, Secs, 0.005->0.020, 0.06
	kReverbParam_SmallSize							= 2,
		
		// Global, Secs, 0.4->10.0, 3.07
	kReverbParam_LargeSize							= 3,
		
		// Global, Secs, 0.001->0.03, 0.025
	kReverbParam_PreDelay							= 4,
		
		// Global, Secs, 0.001->0.1, 0.035
	kReverbParam_LargeDelay							= 5,
		
		// Global, Genr, 0->1, 0.28
	kReverbParam_SmallDensity						= 6,
		
		// Global, Genr, 0->1, 0.82
	kReverbParam_LargeDensity						= 7,
		
		// Global, Genr, 0->1, 0.3
	kReverbParam_LargeDelayRange					= 8,
		
		// Global, Genr, 0.1->1, 0.96
	kReverbParam_SmallBrightness					= 9,
		
		// Global, Genr, 0.1->1, 0.49
	kReverbParam_LargeBrightness					= 10,

		// Global, Genr, 0->1 0.5
	kReverbParam_SmallDelayRange					= 11,

		// Global, Hz, 0.001->2.0, 1.0
	kReverbParam_ModulationRate						= 12,

		// Global, Genr, 0.0 -> 1.0, 0.2
	kReverbParam_ModulationDepth					= 13
};

// These are the parameters for the Delay Unit
enum {
		// Global, EqPow Crossfade, 0->100, 50
	kDelayParam_WetDryMix 				= 0,
		
		// Global, Secs, 0->2, 1
	kDelayParam_DelayTime				= 1,
		
		// Global, Percent, -100->100, 50
	kDelayParam_Feedback 				= 2,
		
		// Global, Hz, 10->(SampleRate/2), 15000
	kDelayParam_LopassCutoff	 		= 3
};

// These are the parameters for the AUPeakLimiter
enum {
		// Global, Secs, 0.001->0.03, 0.012
	kLimiterParam_AttackTime 			= 0,
		
		// Global, Secs, 0.001->0.06, 0.024
	kLimiterParam_DecayTime 			= 1,
		
		// Global, dB, -40->40, 0
	kLimiterParam_PreGain 				= 2
};


// These are the parameters for the AUDynamicsProcessor
enum {
		// Global, dB, -40->20, -20
	kDynamicsProcessorParam_Threshold 			= 0,
		
		// Global, rate, 1->50.0, 2
	kDynamicsProcessorParam_CompressionRatio	 = 1,
		
		// Global, rate, 1->50.0, 2
	kDynamicsProcessorParam_ExpansionRatio		 = 2,
		
		// Global, secs, 0.0001->0.2, 0.001
	kDynamicsProcessorParam_AttackTime 			= 3,
		
		// Global, secs, 0.01->3, 0.05
	kDynamicsProcessorParam_DecayTime 			= 4,
		
		// Global, dB, -40->40, 0
	kDynamicsProcessorParam_MasterGain 			= 5
};


// Mixer Units
// These are the parameters for the 3DMixer AudioUnit
enum {
        // Input, Degrees, -180->180, 0
    k3DMixerParam_Azimuth		= 0,
        
		// Input, Degrees, -90->90, 0
    k3DMixerParam_Elevation		= 1,
        
		// Input, Metres, 0->10000, 1
    k3DMixerParam_Distance		= 2,
        
		// Input/Output, dB, -120->20, 0
    k3DMixerParam_Gain			= 3
};

// These are the parameters for the Stereo Mixer AudioUnit
enum {
		// Input/Output, Mixer Fader Curve, 0->1, 1
	kStereoMixerParam_Volume 	= 0,
		
		// Input, Pan, 0->1, 0.5
	kStereoMixerParam_Pan		= 1
};

// Output Units
// These are the parameters for the HAL Output Unit (and Default and System Output units)
enum {
		// Global, LinearGain, 0->1, 1
	kHALOutputParam_Volume 		= 14 
};

// Music Device
// These are the parameters for the DLSMusicDevice Unit - defined and reported in the global scope
enum {
		// Global, Cents, -1200, 1200, 0
	kMusicDeviceParam_Tuning 	= 0,

		// Global, dB, -120->40, 0
	kMusicDeviceParam_Volume	= 1,

		// Global, dB, -120->40, 0
	kMusicDeviceParam_ReverbVolume	= 2
};
// The music device does NOT currently report parameters in the GroupScope
// but a parameter value can get set (not get) that corresponds to 
// controller values that are defined by the MIDI specification
// This includes the specified MIDI Controller values (for eg. Volume, Mod Wheel, etc)
// as well as the MIDI status messages (such as PitchWheel 0xE0, ChannelPressure 0xD0 - make sure
// you pass in zero for the "channel part" when using these as parameterID - to distinguish this 
// from 0-127 values for midi controllers that will take up the first byte) and the MIDI RPN control messages.
// Remember, the elementID represents the group or channel number... You can use of course, MusicDeviceMIDIEvent to
// send a MIDI formatted control command to the device.

// Using AudioUnitParameterSet with this protocol is done as follows:
//	scope == kAudioUnitScope_Group
//	element == groupID -> in MIDI equivalent to channel number 0->15, 
//			but this is not a limitation of the MusicDevice and values greater than 15 can be specified
//	paramID == midi controller value (0->127), (status bytes corresponding to pitch bend, channel pressure)
//	value == typically the range associated with the corresponding MIDI message	(7 bit, 0->127)
//			pitch bend is specified as a 14 bit value
	
// See MusicDevice.h for more comments about using the extended control semantics of this component.	
	
	
	
	
	
#endif //__AudioUnitParameters