#include <stdio.h>
#include <string.h>
#include <math.h>

#include "virtuodrive-vst.h"

/*
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new VirtuodriveVst (audioMaster);
}*/

virtuodriveProgram::virtuodriveProgram()
{
	// default Program Values
    fGain = 0.5;
	fAmount = 0.5;
	fOutput = 1;

	strcpy (name, "Default");
}

VirtuodriveVst::VirtuodriveVst (audioMasterCallback audioMaster)
	: AudioEffectX (audioMaster, kNumPrograms, kNumParams)
{
	// init
	editor = new virtuodriveGui(this);
	setEditor(editor);
	programs = new virtuodriveProgram[numPrograms];
	fGain = fAmount = fOutput = 0;

    virtuodrive1 = new virtuodrive();
    virtuodrive2 = new virtuodrive();

	if (programs)
		setProgram (0);

	setNumInputs (2);	// stereo input
	setNumOutputs (2);	// stereo output
	setUniqueID ('vtd1');	// this should be unique, use the Steinberg web page for plugin Id registration

	resume ();		// flush buffer
}

VirtuodriveVst::~VirtuodriveVst ()
{
	if (programs)
		delete[] programs;
}

void VirtuodriveVst::SetGain(float gain)
{
    fGain = gain;
    programs[curProgram].fGain=gain;
    Gain = pow(10,(gain*3));
    virtuodrive1->SetGain(Gain);
    virtuodrive2->SetGain(Gain);
}

void VirtuodriveVst::SetAmount(float amt)
{
    fAmount = amt;
    programs[curProgram].fAmount=amt;
    Amount =  amt * 99;
    virtuodrive1->SetAmount(Amount/100);
    virtuodrive2->SetAmount(Amount/100);
}

void VirtuodriveVst::setProgram (VstInt32 program)
{
	virtuodriveProgram* ap = &programs[program];

	curProgram = program;
	setParameter (kGain, ap->fGain);
	setParameter (kAmount, ap->fAmount);
	setParameter (kOutput, ap->fOutput);
}

void VirtuodriveVst::setProgramName (char *name)
{
	strcpy (programs[curProgram].name, name);
}

void VirtuodriveVst::getProgramName (char *name)
{
	if (!strcmp (programs[curProgram].name, "Default"))
		sprintf (name, "%s %d", programs[curProgram].name, curProgram + 1);
	else
		strcpy (name, programs[curProgram].name);
}

bool VirtuodriveVst::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if (index < kNumPrograms)
	{
		strcpy (text, programs[index].name);
		return true;
	}
	return false;
}

void VirtuodriveVst::setParameter (VstInt32 index, float value)
{
	virtuodriveProgram* ap = &programs[curProgram];

	switch (index)
	{
		case kGain :
            SetGain(value);
            break;
		case kAmount:
            SetAmount(value);
            break;
		case kOutput :
            fOutput = ap->fOutput = value;
            break;
	}
}

float VirtuodriveVst::getParameter (VstInt32 index)
{
	float v = 0;

	switch (index)
	{
		case kGain :
            v = fGain;
            break;
        case kAmount:
            v = fAmount;
            break;
		case kOutput :
            v = fOutput;
            break;
	}
	return v;
}

void VirtuodriveVst::getParameterName (VstInt32 index, char *label)
{
	switch (index)
	{
        case kGain :
            strcpy (label, "Gain");
            break;
        case kAmount:
            strcpy(label, "Amount");
            break;
		case kOutput :
            strcpy (label, "Output");
            break;
	}
}

void VirtuodriveVst::getParameterDisplay (VstInt32 index, char *text)
{
	switch (index)
	{
		case kGain :
            dB2string (Gain, text, 5);
            break;
        case kAmount:
            float2string(Amount,text,2);
            if (!Amount) strcpy(text,"0");
            break;
		case kOutput :
            dB2string (fOutput, text, 5);
            break;
	}
}

void VirtuodriveVst::getParameterLabel (VstInt32 index, char *label)
{
	switch (index)
	{
        case kGain :
            strcpy (label, "dB");
            break;
        case kAmount:
            strcpy (label, "%");
            break;
		case kOutput :
            strcpy (label, "dB");
            break;
	}
}

bool VirtuodriveVst::getEffectName (char* name)
{
	strcpy (name, "Virtuodrive");
	return true;
}

bool VirtuodriveVst::getProductString (char* text)
{
	strcpy (text, "Virtuodrive");
	return true;
}

bool VirtuodriveVst::getVendorString (char* text)
{
	strcpy (text, "Virtuosonic Software");
	return true;
}

void VirtuodriveVst::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float* in1 = inputs[0];
	float* in2 = inputs[1];
	float* out1 = outputs[0];
	float* out2 = outputs[1];

	while (--sampleFrames >= 0)
	{
		*out1++ = fOutput * virtuodrive1->forSample(*in1++);
		if (out2)
			*out2++ = fOutput * virtuodrive2->forSample(*in2++);
	}
}
