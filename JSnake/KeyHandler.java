import java.awt.event.*;

public class KeyHandler implements KeyListener
{
    char key_num = 0;
    
    @Override
    public void keyReleased(KeyEvent e)
    {
      
    }
    
    @Override
    public void keyPressed(KeyEvent e )
    {
        key_num = e.getKeyChar( );   
    }
    
    @Override
    public void keyTyped(KeyEvent e)
    {
        key_num = e.getKeyChar( );
    }
    
    public char getKey( )
    {
        return key_num;
    }
}
