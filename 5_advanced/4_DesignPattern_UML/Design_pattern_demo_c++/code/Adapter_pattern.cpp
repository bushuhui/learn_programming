//
// Created by likun on 6/10/23.
//

#include <iostream>
#include <string.h>

using namespace std;

class MediaPlayer
{
public:
    virtual void play(string audioType, string filename) = 0;
};

class AdvanceMediaPlayer
{
public:
    virtual void play_vlc(string filename) =0;
    virtual void play_mp4(string filename) =0;
};

class vlc_player : public AdvanceMediaPlayer
{
public:
    void play_vlc(string filename){
        cout<<"play_vlc file is "<<filename<<endl;
    }
    void play_mp4(string filename){

    }
};

class mp4_player : public AdvanceMediaPlayer
{
public:
    void play_mp4(string filename){
        cout<<"play_mp4 file is "<<filename<<endl;
    }
    void play_vlc(string filename){

    }
};

class MediaAdapter : public MediaPlayer {
public:
    MediaAdapter(string audio_type) {
        if (audio_type == "vlc") {
            advance_music_player = new vlc_player();
        } else if (audio_type == "mp4") {
            advance_music_player = new mp4_player();
        }
    }

    void play(string audio_type, string file_name) {
        if (audio_type == "vlc") {
            advance_music_player->play_vlc(file_name);
        } else if (audio_type == "mp4") {
            advance_music_player->play_mp4(file_name);
        }
    }
private:
    AdvanceMediaPlayer* advance_music_player;
};

class audio_player : public MediaPlayer
{
public:
    void play(string audio_type, string file_name)
    {
        if(audio_type == "mp3"){
            cout<<"play mp3 file "<<file_name<<endl;
        }else if(audio_type  == "mp4" ||  audio_type == "vlc"){
            media_adapter = new MediaAdapter(audio_type);
            media_adapter->play(audio_type, file_name);
        }else{
            cout<<"Invalid media "+audio_type+file_name<<endl;
        }
    }
private:
    MediaAdapter* media_adapter;
};

int main(int argc, char** argv)
{
    audio_player* player = new audio_player();

    player->play("mp3", "beyond the horizon.mp3 ");
    player->play("mp4", "alone.mp4 ");
    player->play("vlc", "far far away.vlc ");
    player->play("avi", "mind me.avi ");
    return 0;
}






