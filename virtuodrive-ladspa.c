/************************************************
*Name:      virtuodrive-ladspa.c
*Created:       21-mar-2009
*Author:        Gabriel Espinoza
************************************************/

#include <ladspa.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define min(x,y) x > y ? y : x
#define max(x,y) x > y ? x : y

/*ports number*/
#define VD_GAIN 0
#define VD_AMT 1
#define VD_IN 2
#define VD_OUT 3

static LADSPA_Descriptor *vdDescriptor = NULL;

/* struct*/
typedef struct {
	LADSPA_Data* gain;
	LADSPA_Data* amt;
	LADSPA_Data* input;
	LADSPA_Data* output;
} ladspa_virtuodrive;

/* nueva instancia*/
LADSPA_Handle instantiateVirtuodrive(const LADSPA_Descriptor * Descriptor,
						 unsigned long SampleRate)
{
	return malloc(sizeof(ladspa_virtuodrive));
}

void connectPortVd(LADSPA_Handle Instance,
			 unsigned long Port,LADSPA_Data * DataLocation)
{
	ladspa_virtuodrive* psVirtuodrive;

	psVirtuodrive = (ladspa_virtuodrive*)Instance;
	switch (Port)
	{
		case VD_GAIN:
			psVirtuodrive->gain = DataLocation;
			break;
		case VD_AMT:
			psVirtuodrive->amt = DataLocation;
			break;
		case VD_IN:
			psVirtuodrive->input = DataLocation;
			break;
		case VD_OUT:
			psVirtuodrive->output = DataLocation;
			break;
	}
}

void runVirtuodrive(LADSPA_Handle Instance,unsigned long SampleCount)
{
	LADSPA_Data * pfInput;
	LADSPA_Data * pfOutput;
	LADSPA_Data fGain;
	LADSPA_Data fAmt;
	ladspa_virtuodrive* psVirtuodrive;
	unsigned long lSampleIndex;

	psVirtuodrive = (ladspa_virtuodrive*)Instance;

	pfInput = psVirtuodrive->input;
	pfOutput = psVirtuodrive->output;
	fGain = *(psVirtuodrive->gain);
	fAmt = *(psVirtuodrive->amt);
	LADSPA_Data k = 2 * fAmt / (1 - fAmt);
	//
	for (unsigned long i = 0; i < SampleCount; i++)
	{
		LADSPA_Data spl =*pfInput++;
		spl *= fGain;
		spl = (1+k) * spl / (1+k * fabs(spl));
		spl = min(max(spl,-1),.5);
		*pfOutput++ = spl;
	}
}

static void cleanupVirtuodrive(LADSPA_Handle instance) {
	free(instance);
}

void _init()
{
	char **port_names;
	LADSPA_PortDescriptor *port_descriptors;
	LADSPA_PortRangeHint *port_range_hints;
	//
	vdDescriptor = (LADSPA_Descriptor *)malloc(sizeof(LADSPA_Descriptor));
	if (vdDescriptor)
	{
		vdDescriptor->UniqueID = 7003;
		vdDescriptor->Label = "Virtuodrive";
		vdDescriptor->Properties =
			LADSPA_PROPERTY_HARD_RT_CAPABLE;
		vdDescriptor->Name =
			"Virtuodrive";
		vdDescriptor->Maker =
			"Gabriel Espinoza a.k.a. virtuoso";
		vdDescriptor->Copyright =
			"GPLv3";
		vdDescriptor->PortCount = 4;

		port_descriptors = (LADSPA_PortDescriptor *)calloc(4,
					 sizeof(LADSPA_PortDescriptor));
		vdDescriptor->PortDescriptors =
			(const LADSPA_PortDescriptor *)port_descriptors;

		port_range_hints = (LADSPA_PortRangeHint *)calloc(4,
					 sizeof(LADSPA_PortRangeHint));
		vdDescriptor->PortRangeHints =
			(const LADSPA_PortRangeHint *)port_range_hints;

		port_names = (char **)calloc(4, sizeof(char*));
		vdDescriptor->PortNames =
			(const char **)port_names;

		/* Parameters for  gain (dB) */
		port_descriptors[VD_GAIN] =
			LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
		strcpy(port_names[VD_GAIN],"Gain (dB)");

		port_range_hints[VD_GAIN].HintDescriptor =
			LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0;
		port_range_hints[VD_GAIN].LowerBound = 0;
		port_range_hints[VD_GAIN].UpperBound = 60;
		/* Parameters for Amount */
		port_descriptors[VD_AMT] =
			LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
		strcpy(port_names[VD_AMT],"Amount (%)");
		port_range_hints[VD_AMT].HintDescriptor =
			LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_0;
		port_range_hints[VD_GAIN].LowerBound = 0;
		port_range_hints[VD_GAIN].UpperBound = 99;
		/* Parameters for Output */
		port_descriptors[VD_IN] =
			LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
		strcpy(port_names[VD_IN],"Input");
		port_range_hints[VD_IN].HintDescriptor = 0;
		/* Parameters for Output */
		port_descriptors[VD_OUT] =
			LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
		strcpy(port_names[VD_OUT],"Output");
		port_range_hints[VD_OUT].HintDescriptor = 0;
		//
		vdDescriptor->activate = NULL;
		vdDescriptor->cleanup = cleanupVirtuodrive;
		vdDescriptor->connect_port = connectPortVd;
		vdDescriptor->deactivate = NULL;
		vdDescriptor->instantiate = instantiateVirtuodrive;
		vdDescriptor->run = runVirtuodrive;
		vdDescriptor->run_adding = NULL;
		vdDescriptor->set_run_adding_gain = NULL;
	}
}

void _fini()
{
	if (vdDescriptor) {
		free((LADSPA_PortDescriptor *)vdDescriptor->PortDescriptors);
		free((char **)vdDescriptor->PortNames);
		free((LADSPA_PortRangeHint *)vdDescriptor->PortRangeHints);
		free(vdDescriptor);
	}

}


const LADSPA_Descriptor* ladspa_descriptor(unsigned long Index)
{
	switch (Index)
	{
		case 0:
			return vdDescriptor;
			break;
		default:
			return NULL;
			break;
	}
}
