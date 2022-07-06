# SiriusXM
![](https://i.pcmag.com/imagery/reviews/02NI5TtZ2SlHLoJdMkRtvwi-7.fit_scale.size_1028x578.v1582315481.png)

## This describes how to add your SXM subscription to your AmpliPi !

This solution utilizes the SiriusXM [Webservice](https://player.siriusxm.com/home/foryou) (SXM) to stream into the VLC that is installed on your AmpliPi.
Currently, it requires two python scripts, running in the background on your AmpliPi, and your SXM subscription credentials.  

The first file, [sxm.py](https://github.com/vszander/Amplipi/blob/main/python/sxm.py), creates a session with SXM and establishes a 'proxy' streaming service on a designated port.  This is currently the 1.0 version, based on a [fork](https://github.com/vszander/SiriusXM_Streamer) from another project and will be further customized to provide additional AmpliPi functionality (pause, channel listings ?  ).

The second file (runvlc.py) is already installed on your AmpliPi.  It leverages the VLC instance on the AmpliPi and connects to the local proxy streaming service.  Fortunately,  the AmpliPi web GUI, works nicely with these two running services - so you can add additional SXM channels as AmpliPi streams from the UI (presumably the API).
