#include "virtuodriveGui.h"
#include "virtuodrive-vst.h"
#include <stdio.h>

virtuodriveGui::virtuodriveGui(AudioEffect *effect) : AEffGUIEditor(effect)
{
    bg = new CBitmap(BmpBg);
    rect.left   = 0;
    rect.top    = 0;
    rect.right  = (VstInt16)bg->getWidth();
    rect.bottom = (VstInt16)bg->getHeight();
}

virtuodriveGui::~virtuodriveGui()
{
    bg->forget();
}

void virtuodriveGui::close()
{
    if (frame)
            delete frame;
    frame = NULL;
}

bool virtuodriveGui::open(void* ptr)
{
    AEffGUIEditor::open(ptr);
    CRect  size(0, 0, bg->getWidth(), bg->getHeight());
    frame = new CFrame(size, ptr, this);
    frame->setBackground(bg);
    size.inset (8, 8);
	size.top++;
	size.left++;

    CBitmap* knobBg = new CBitmap(BmpKnobBg);
    CBitmap* knobHandle = new CBitmap(BmpKnobHandle);
    CRect knobSize(0,0,knobBg->getWidth(),knobBg->getHeight());

    CRect knob1Size(knobSize);
        knob1Size.offset(55,130);
    CRect knob2Size(knobSize);
        knob2Size.offset(152,130);
    CRect knob3Size(knobSize);
        knob3Size.offset(244,130);

    CKnob* knob1 = new CKnob(knob1Size,this,knobGain,knobBg,knobHandle,CPoint(0,0));
    knob1->setValue(getEffect()->getParameter(kGain));
    CKnob* knob2 = new CKnob(knob2Size,this,knobAmt,knobBg,knobHandle,CPoint(0,0));
    knob2->setValue(getEffect()->getParameter(kAmount));
    CKnob* knob3 = new CKnob(knob3Size,this,knobOut,knobBg,knobHandle,CPoint(0,0));
    knob3->setValue(getEffect()->getParameter(kOutput));

    CRect txtRect(0,0,50,20);
    CRect txtRect1(txtRect);
    txtRect1.offset(55,200);
    CRect txtRect2(txtRect);
    txtRect2.offset(152,200);
    CRect txtRect3(txtRect);
    txtRect3.offset(244,200);

    CColor txtColor;
    txtColor.red = 120;
    txtColor.green = 145;
    txtColor.blue = 236;

    char txt[40];
    getDisplay(kGain,txt);
    label1 = new CTextLabel(txtRect1,txt);
    label1->setBackColor(txtColor);
    getDisplay(kAmount,txt);
    label2 = new CTextLabel(txtRect2,txt);
    label2->setBackColor(txtColor);
    getDisplay(kOutput,txt);
    label3 = new CTextLabel(txtRect3,txt);
    label3->setBackColor(txtColor);

    frame->addView(knob1);
    frame->addView(knob2);
    frame->addView(knob3);
    frame->addView(label1);
    frame->addView(label2);
    frame->addView(label3);

    knobBg->forget();
    knobHandle->forget();

    return true;
}

void virtuodriveGui::valueChanged(CDrawContext *pContext, CControl *pControl)
{
    char txt[10];
    switch (pControl->getTag())
    {
    	case knobGain:
            getEffect()->setParameter(kGain,pControl->getValue());
            getDisplay(kGain,txt);
            label1->setText(txt);
            label1->setDirty();
    		break;
        case knobAmt:
            getEffect()->setParameter(kAmount,pControl->getValue());
            getDisplay(kAmount,txt);
            label2->setText(txt);
            label2->setDirty();
            break;
        case knobOut:
            getEffect()->setParameter(kOutput,pControl->getValue());
            getDisplay(kOutput,txt);
            label3->setText(txt);
            label3->setDirty();
            break;
    }
}

void virtuodriveGui::getDisplay(VstInt32 indx,char* labeltxt)
{
    char display[5],label[3];

    effect->getParameterDisplay(indx,display);
    effect->getParameterLabel(indx,label);
    sprintf(labeltxt,"%s%s",display,label);
}

