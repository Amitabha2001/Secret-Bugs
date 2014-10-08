/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Game_Play;

import javax.sound.sampled.*;
import java.io.*;

/**
 *
 * @author amitabh
 */
public class Audio 
{
    Clip audio_clip;
    
    public Audio(String file_path)
    {
        AudioInputStream audio_stream;
        
        try
        {
            audio_stream  = AudioSystem.getAudioInputStream(new File(file_path));
            audio_clip = AudioSystem.getClip();
            audio_clip.open(audio_stream);
        }
        catch(UnsupportedAudioFileException ex )
        {
            System.out.println("Cannot open audio file : " + file_path);
            return;
        }
        catch(IOException eax)
        {
            System.out.println("Audio file not found : " + file_path);
            return;
        }   
        catch(javax.sound.sampled.LineUnavailableException er)
        {
            System.out.println("Erro Loading audio file : " + file_path);
        }
    }
    
    public void Start( )
    {
        audio_clip.start();
    }
    
    public void Stop( )
    {
        audio_clip.stop();
    }
    
    public boolean isPlaying( )
    {
        return audio_clip.isRunning();
    }
}
