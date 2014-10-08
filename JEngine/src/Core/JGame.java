/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Core;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
/**
 *
 * @author amitabh
 */
public class JGame 
{
      private JFrame game_wnd;
      private Timer game_loop;
      
      public JGame(String game_NAME,JResolution game_SIZE,JResolution game_Startup_Location,boolean game_SHOW_FLAGS)
      {
          game_wnd = new JFrame(game_NAME);
          game_wnd.setSize(game_SIZE.width, game_SIZE.height);
          game_wnd.setLocation(game_Startup_Location.width,game_Startup_Location.height);
          game_wnd.setResizable(false);
          game_wnd.setVisible(game_SHOW_FLAGS);
      }
      
      public void JGame_Initialize(int game_FRAME,ActionListener game_update_code,JDraw_Code DrawCode)
      {
          game_loop = new Timer(game_FRAME,game_update_code);
          game_wnd.add(new JGame_Canvas(DrawCode));
          game_wnd.addKeyListener(new JKey_Input());
          game_loop.start();
      }
      
      public void JGame_Stop()
      {
          game_loop.stop();
          game_wnd.setVisible(false);
          game_wnd = null;
      }
      
      public void JGame_ChangeResolution(JResolution game_newResolution)
      {
          game_wnd.setSize(game_newResolution.width,game_newResolution.height);
      }
      
      public JKeyboard GetKeyDown()
      {
          Object[] key_handle = game_wnd.getKeyListeners();
          JKey_Input key_input = (JKey_Input) key_handle[0];
          JKeyboard key_ret = new JKeyboard();
          key_ret.isKeyDOWN = key_input.isKEY_DOWN;
          key_ret.Key_CHAR = key_input.KEY_CHAR;
          
          return key_ret;
      }
}

class JGame_Canvas extends JPanel
{
       JDraw_Code drawcode;
       
       public JGame_Canvas(JDraw_Code DrawCode)
       {
            this.drawcode = DrawCode;
       }
    
       @Override
       public void paintComponent(Graphics g)
       {
           drawcode.onDraw(g);
           repaint();
       }
}

class JKey_Input implements KeyListener
{
     public boolean isKEY_DOWN;
     public char  KEY_CHAR;
    
    @Override
    public void keyPressed(KeyEvent e)
    {
         isKEY_DOWN = true;
         KEY_CHAR = e.getKeyChar();
    }
    @Override
    public void keyReleased(KeyEvent e)
    {
        isKEY_DOWN = false;
    }
    @Override
    public void keyTyped(KeyEvent e)
    {
              
    }
 }
