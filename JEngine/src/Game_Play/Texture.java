/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Game_Play;

import javax.imageio.*;
import java.awt.image.*;
import java.io.*;
/**
 *
 * @author amitabh
 */
public class Texture 
{
    BufferedImage main_img;
    
    public Texture(String file_name)
    {
        try
        {
            main_img = ImageIO.read(new File(file_name));
        }
        catch(IOException ex)
        {
            System.out.println("Texture not found : " + file_name);
        }
    }
    
    public Texture(BufferedImage newImage)
    {
        main_img = newImage;
    }
    
    public BufferedImage getImage()
    {
        return main_img;
    }
    
    public int getWidth()
    {
        return main_img.getWidth();
    }
    
    public int getHeight( )
    {
        return main_img.getHeight( );
    }
    
    public void dipose( )
    {
        main_img = null;
    }
}
