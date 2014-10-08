/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Game_Play;

import java.util.*;
import java.awt.event.*;

/**
 *
 * @author amitabh
 */
public class Animation 
{          
      List<TextureRect> frame_list = new ArrayList<TextureRect>();
      javax.swing.Timer timer_source;
      int current_frame = 0;
      boolean repeating = false;
      Sprite object_inst;
      
      public Animation(Sprite instance,float frame_delay)
      {
          timer_source = new javax.swing.Timer((int) frame_delay,new ActionListener(){
                    
                   @Override
                   public void actionPerformed(ActionEvent e)
                   {
                       if (current_frame <= frame_list.size() - 1)
                       {
                           object_inst.mainTexture = new Texture(frame_list.get(current_frame).getRequiredPart());
                       }
                       else
                       {
                           current_frame = 0;
                           
                           if (!repeating)
                           {
                               timer_source.stop();
                           }
                       }
                   }
          });
          
          object_inst = instance;
      }
      
      public void Play(boolean isRepeating)
      {
          repeating = isRepeating;
          
          if (frame_list.size() < 1)
          {
              System.out.println("Cannot play animation.");
              return;
          }
          else
          {
              if (!timer_source.isRunning())
              {
                current_frame = 0;
                timer_source.stop();
                timer_source.start();
              }
              else
              {
                 System.out.println("Animation is already playing.");
              }
          }
      }
      
      public void AddFrame(TextureRect txtRect)
      {
          frame_list.add(txtRect);
      }
      
      public void RemoveFrame(int txtRect_ID)
      {
          frame_list.remove(txtRect_ID);
      }
}
