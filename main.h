#ifndef __VirtuodriveVst__
#define __VirtuodriveVst__

#include "audioeffectx.h"
#include "virtuodrive.h"
#include "virtuodriveGui.h"

enum
{
	// Global
	kNumPrograms = 6,

	// Parameters Tags
	kGain = 0,
	kAmount,
	kOutput,

	kNumParams
};

class ADelay;

//------------------------------------------------------------------------
class virtuodriveProgram
{
friend class VirtuodriveVst;
public:
	virtuodriveProgram ();
	~virtuodriveProgram () {}

private:
	float fGain;
	float fAmount;
	float fOutput;
	char name[24];
};

//------------------------------------------------------------------------
class VirtuodriveVst : public AudioEffectX
{
public:
	VirtuodriveVst (audioMasterCallback audioMaster);
	~VirtuodriveVst ();
	//---from AudioEffect-----------------------
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual void setProgram (VstInt32 program);
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);
	virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);
	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion () { return 1000; }
	virtual VstPlugCategory getPlugCategory () { return kPlugCategEffect; }

protected:
	virtuodriveProgram* programs;
	float fGain;
	float fAmount;
	float fOutput;
	virtuodrive* virtuodrive1;
	virtuodrive* virtuodrive2;
	float Gain;
	float Amount;
	void SetGain(float gain);
	void SetAmount(float amt);
	
	AEffEditor* editor;
};

#endif //__VirtuodriveVst__
