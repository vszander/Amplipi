# SiriusXM
![](https://i.pcmag.com/imagery/reviews/02NI5TtZ2SlHLoJdMkRtvwi-7.fit_scale.size_1028x578.v1582315481.png)
0
## This describes how to add your SXM subscription to your AmpliPi !

This solution utilizes the SiriusXM [Webservice](https://player.siriusxm.com/home/foryou) (SXM) to stream into the VLC that is installed on your AmpliPi.
Currently, it requires two python scripts, running in the background on your AmpliPi, and your SXM subscription credentials.  

The first file, [sxm.py](https://github.com/vszander/Amplipi/blob/main/python/sxm.py), creates a session with SXM and establishes a 'proxy' streaming service on a designated port.  This is currently the 1.0 version, based on a [fork](https://github.com/vszander/SiriusXM_Streamer) from another project and will be further customized to provide additional AmpliPi functionality (pause, channel listings ?  ).

The second file (runvlc.py) is already installed on your AmpliPi.  It leverages the VLC instance on the AmpliPi and connects to the local proxy streaming service.  Fortunately,  the AmpliPi web GUI, works nicely with these two running services - so you can add additional SXM channels as AmpliPi streams from the UI (presumably the API).

## Instructions

1.  get to a command prompt on your AmpliPi
2.  start a python virtual envirionment
`cd ~/amplipi-dev/`
`source venv/bin/activate `  

3.  move to a preferred directory to download the sxm script

`cd streams`
`wget https://raw.githubusercontent.com/vszander/Amplipi/main/python/sxm.py`

4a.   test your credentials and access to the SiriusXM webservice by getting the current list of channels

`python3 sxm.py [your sxm accountname] [your sxm password] -l`

4b.  you may want to save this list to a text file.   You will need the channel id or channel name when creating a stream

`python3 sxm.py [your sxm accountname] [your sxm password] -l  > ~/Desktop/sxmchannels.txt`

5.   If these work,  we can start the proxy streamer.   Currently, this is manually started - so you will need to restart if you re-boot your AmpliPi.
In this case, we will use port 8888.

`python3 sxm.py [your sxm accountname] [your sxm password] -p 8888`

if you do not get errors, there will not be another command prompt.. as the proxy is running and waiting.

6.  start the vlc service.    
6a.   open an additional (new) command prompt
6b.  start an additional virtual environment
`cd ~/amplipi-dev/`
`source venv/bin/activate `  

6c.  move to the streams directory

`cd streams`

6d.  start the vlc service.   Use a valid channel name, but later, you can change / add channels in the AmpliPi web UI.

`python3 runvlc.py http://127.0.0.1:8888/siriusnflradio.m3u8`

if this is successfull,  your first terminal window will log activity of the sxm webservice.
![](https://github.com/vszander/Amplipi/blob/main/docs/img/SiriusXMstep21.png)

and this second terminal is now 'serving' the  sxm service in VLC.
![](https://github.com/vszander/Amplipi/blob/main/docs/img/SiriusXMstep22.png)

## Create a SXM stream in AmpliPi

Navigate to your AmpliPi web page.  1. Click the 'Settings' tab  2.  Click 'Add a New Stream'
![](https://github.com/vszander/Amplipi/blob/main/docs/img/SiriusXMstep31.png)

Fill in the fields as you like for your desired channel (list of channels created in step 4b above).  The Station Audio URL (highlighted below) is important.
![](https://github.com/vszander/Amplipi/blob/main/docs/img/SiriusXMstep32.png)
the channel name from the list should replace `siriusnflradio`.  
For example to add CNN use:  `http://127.0.0.1:8888/cnn.m3u8`

and 'Save Changes'

Finally, select your new stream in your source tab.
![](https://github.com/vszander/Amplipi/blob/main/docs/img/SiriusXMstep33.png)
