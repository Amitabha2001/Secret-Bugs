/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Game_Play;

import java.awt.image.*;

/**
 *
 * @author amitabh
 */
public class TextureRect 
{
      Texture main_img;
      int startX;
      int startY;
      int endX;
      int endY;
      
      
      public TextureRect(Texture main_texture,int StartingPointX,int StartingPointY,int EndingPointX,int EndingPointY)
      {
          main_img = main_texture;
         
          if (StartingPointX > main_img.getWidth())
          {
              System.out.println("Starting Point X is out of range.");
              return;
          }
          
          if (StartingPointY > main_img.getHeight())
          {
              System.out.println("Starting Point Y is out of range.");
              return;
          }
          
          if (EndingPointX > main_img.getWidth())
          {
              System.out.println("Ending Point X is out of range.");
              return;
          }
          
          if (EndingPointY > main_img.getHeight())
          {
              System.out.println("Ending Point Y is out of range.");
              return;
          }
          
          startX = StartingPointX;
          startY = StartingPointY;
          endX = EndingPointX;
          endY = EndingPointY;
      }
      
      public int getStartingPointX( )
      {
         return startX;   
      }
      
      public int getStartingPointY( )
      {
         return startY;
      }
      
      public int getEndingPointX( )
      {
          return endX;
      }
      
      public int getEndingPointY( )
      {
          return endY;
      } 
      
      public void setStartingPointX(int newPointX)
      {
          if (newPointX > main_img.getWidth())
          {
              System.out.println("Starting Point X is out of range.");
              return;
          }
          else
          {
              startX = newPointX;
          }
      }
      
      public void setStaringPointY(int newPointY)
      {
          if (newPointY > main_img.getHeight())
          {
              System.out.println("Starting Point Y is out of range.");
              return;
          }
          else
          {
              startY = newPointY;
          }
      }
      
      public void setEndingPointX(int newPointX)
      {
          if (newPointX > main_img.getWidth())
          {
              System.out.println("Ending Point X is out of range.");
              return;
          }
          else
          {
              endX = newPointX;
          }
      }
      
      public void setEndingPointY(int newPointY)
      {
        if (newPointY > main_img.getHeight())
          {
              System.out.println("Ending Point Y is out of range.");
              return;
          }
        else
        {
            endY = newPointY;
        }
      }
      
      public BufferedImage getRequiredPart( )
      {
         if (startX > main_img.getWidth())
          {
              System.out.println("Starting Point X is out of range.");
              return null;
          }
         
         if (startY > main_img.getHeight())
          {
              System.out.println("Starting Point Y is out of range.");
              return null;
          }
         
         if (endX > main_img.getWidth())
          {
              System.out.println("Ending Point X is out of range.");
              return null;
          }
         
         if (endY > main_img.getHeight())
          {
              System.out.println("Ending Point Y is out of range.");
              return null;
          }
          
          if (startX > endX)
          {
              System.out.println("Ending Point X must be greater than starting X");
              return null;
          }
          
          if (startY > endY)
          {
              System.out.println("Ending Point Y must be greater than ending X");
              return null;
          }
          
         
           BufferedImage ret_img = new BufferedImage(endX - startX,endY - startY,1);
           
           for(int y = startY;y <= endY;y++)
           {
               for(int x = startX;x <= endX;x++)
               {
                   ret_img.setRGB(x, y, main_img.getImage().getRGB(x, y));
               }
           }
           
           return ret_img;
      }
}
