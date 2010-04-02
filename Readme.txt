/******************************************************
*                 virtuodrive                         *
******************************************************/
Web:
====
    http://sourceforge.net/projects/virtuodrive/

What is:
========
virtuodrive is a distortion effect for electric guitar,
available in jesusonic, ladspa and vst format

License:
=======
virtuodrive is licensed under the gpl version 3 license

BUILD/INSTALL
=============
Linux/Ladspa:
for the ladspa port there is a makefile called makefile.ladspa
simply run
    make -f makefile.ladspa
    make -f makefile.ladspa install
you can change the prefix to install somewhere else
    make -f makefile.ladspa install $PREFIX=/somewhere/else

jesusonic:
you must copy the contents of the folder jesusonic to somewhere 
where the host can find it, like:
    C:\Program Files\REAPER\Effects\virtuosonic

VST:
TODO: document

