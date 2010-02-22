#ifndef VIRTUODRIVEGUI_H
#define VIRTUODRIVEGUI_H

#include "vstgui.sf/vstgui/vstgui.h"
#include "vstcontrols.h"

class virtuodriveGui : public AEffGUIEditor , CControlListener
{
    public:
        virtuodriveGui(AudioEffect *effect);
        virtual ~virtuodriveGui();
        virtual void valueChanged(CDrawContext *pContext, CControl *pControl);
    protected:
        bool open(void* ptr);
        void close();
    private:
        void getDisplay(VstInt32 indx,char* labeltxt);
        CBitmap* bg;
        CTextLabel *label1,*label2,*label3;
        enum
        {
            knobGain = 0,
            knobAmt,
            knobOut,
            BmpBg = 100,
            BmpKnobBg,
            BmpKnobHandle
        };
};

#endif // VIRTUODRIVEGUI_H
