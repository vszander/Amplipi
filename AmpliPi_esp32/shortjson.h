#ifndef _SHORTJSON_H    // Put these two lines at the top of your file.
#define _SHORTJSON_H    // (Use a suitable name, usually based on the file name.)

 
 char json[] =
      "{\"sources\":[{\"id\":0,\"name\":\"NC\",\"input\":\"stream=1001\",\"info\":{\"name\":\"97.1 The River - internet radio\",\"state\":\"playing\",\"track\":\"atl971-sgplayer-aac\",\"station\":\"atl971-sgplayer-aac\",\"img_url\":\"https://www.971theriver.com/pf/resources/images/sites/cmg-rd-20023/station-logo.png?d=408\",\"supported_cmds\":[\"play\",\"stop\"]}},{\"id\":1,\"name\":\"Mixer\",\"input\":\"local\",\"info\":{\"name\":\"Mixer - rca\",\"state\":\"unknown\",\"img_url\":\"static/imgs/rca_inputs.svg\",\"supported_cmds\":[]}},{\"id\":2,\"name\":\"PHONE\",\"input\":\"local\",\"info\":{\"name\":\"PHONE - rca\",\"state\":\"unknown\",\"img_url\":\"static/imgs/rca_inputs.svg\",\"supported_cmds\":[]}},{\"id\":3,\"name\":\"TV\",\"input\":\"local\",\"info\":{\"name\":\"TV - rca\",\"state\":\"unknown\",\"img_url\":\"static/imgs/rca_inputs.svg\",\"supported_cmds\":[]}}],\"zones\":[{\"id\":0,\"name\":\"Office\",\"source_id\":0,\"mute\":false,\"vol\":-30,\"vol_f\":0.625,\"vol_min\":-80,\"vol_max\":0,\"disabled\":false}],\"groups\":[{\"id\":100,\"name\":\"Shed\",\"zones\":[0,1,2],\"mute\":false,\"vol_delta\":-34,\"vol_f\":0.56875}],\"streams\":[{\"id\":1000,\"name\":\"Groove Salad\",\"type\":\"internetradio\",\"url\":\"http://ice6.somafm.com/groovesalad-32-aac\",\"logo\":\"https://somafm.com/img3/groovesalad-400.jpg\"},{\"id\":1001,\"name\":\"97.1 The River\",\"type\":\"internetradio\",\"url\":\"https://ad-oom-cmg.streamguys1.com/atl971/atl971-sgplayer-aac\",\"logo\":\"https://www.971theriver.com/pf/resources/images/sites/cmg-rd-20023/station-logo.png?d=408\"},{\"id\":1002,\"name\":\"Fox News Radio\",\"type\":\"internetradio\",\"url\":\"https://streaming-ent.shoutcast.com/foxnews\",\"logo\":\"\"}],\"presets\":[{\"id\":10000,\"name\":\"Mute All\",\"state\":{\"zones\":[{\"mute\":true,\"id\":0},{\"mute\":true,\"id\":1},{\"mute\":true,\"id\":2},{\"mute\":true,\"id\":3},{\"mute\":true,\"id\":4},{\"mute\":true,\"id\":5}]},\"last_used\":1643501334}],\"info\":{\"config_file\":\"house.json\",\"version\":\"0.1.8\",\"mock_ctrl\":false,\"mock_streams\":false}}";


#endif //  _SHORTJSON_H        
