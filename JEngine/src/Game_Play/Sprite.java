/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Game_Play;

import java.util.*;
import Core.Vector2;

/**
 *
 * @author amitabh
 */
public class Sprite 
{
    Texture mainTexture;
    List<Animation> animation_list = new ArrayList<Animation>();
    Vector2 position;
    
    public Sprite(Texture sprite_texture,Vector2 start_position)
    {
        this.mainTexture = sprite_texture;
        this.position = start_position;
    }
    
    public Vector2 getPosition()
    {
        return position;
    }
    
    public void setPosition(Vector2 newPosition)
    {
        position = newPosition;
    }
    
    public void Translate(int trans_x,int trans_y)
    {
        position.X += trans_x;
        position.Y += trans_y; 
    }
    
    public void AddAnimation(Animation newAnimation)
    {
        animation_list.add(newAnimation);
    }
    
    public void RemoveAnimation(int AnimationID)
    {
        animation_list.remove(AnimationID);
    }
}
