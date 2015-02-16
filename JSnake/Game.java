import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

public class Game
{
    class Vector2
    {
        public int x = 0;
        public int y = 0;
    }
    
    class SnakeBody
    {
        Vector2 pos = new Vector2( );
        Target target;
   
        int dir = 0;
        SnakeBody node;
    }
    
    class Target
    {
        Vector2 pos = new Vector2( );
        int chg_dir = 0;
        Target node;
    }
    
    class Food
    {
        Vector2 pos = new Vector2( );
        int pnts = 0;
    }
    
    class Canvas extends JPanel implements Runnable
    {
        boolean isRunning = true;
        SnakeBody snakeBody;
        Food cur_food;
        int game_score = 0;
        JFrame gameWindow;
        
        public Canvas(JFrame handle )
        {
            snakeBody = new SnakeBody( );
            snakeBody.pos.x = 50;
            snakeBody.pos.y = 200;
            snakeBody.dir = 3;
            cur_food = new Food( );
            cur_food.pos.x = 200;
            cur_food.pos.y = 200;
            cur_food.pnts = 10;
            gameWindow = handle;
            
            Thread t = new Thread(this );
            
            t.start( );
        }
        
        @Override
        public void paintComponent(Graphics g)
        {
            SnakeBody snk_handle = snakeBody;
            
             g.setColor(Color.BLACK);
             g.fillRect(0,0,500,500);
            
            g.setColor(Color.RED);
            g.setFont(new Font("Consolas",12,12));
            
            g.drawString("Score : " + game_score,50,50);
            
            g.setColor(Color.YELLOW);
            
            while(snk_handle != null)
            {
                g.drawLine(snk_handle.pos.x,snk_handle.pos.y,snk_handle.pos.x,snk_handle.pos.y);
                snk_handle = snk_handle.node;
            }
            
            g.setColor(Color.GREEN);
            
            g.drawLine(cur_food.pos.x,cur_food.pos.y,cur_food.pos.x,cur_food.pos.y);
            
            repaint( );
        }
        
        @Override
        public void run( )
        {
            while (isRunning)
            {
               onUpdate( );
               System.gc( );
               
               try
               { 
                   Thread.sleep(10 );
               }
               catch(InterruptedException x )
               { 
                   
               }
            }
            
            
            System.exit(1);
        }
        
        private void onUpdate( )
        {
            SnakeBody snk_handle = snakeBody;
            KeyListener[] handle_array = gameWindow.getKeyListeners( );
            Object handle_obj = handle_array[0];
            KeyHandler handle = (KeyHandler) handle_obj;
            
            while(snk_handle != null)
            {
                if (snk_handle.target != null)
                {
                    if (snk_handle.pos.x == snk_handle.target.pos.x && snk_handle.pos.y == snk_handle.target.pos.y)
                    {
                        snk_handle.dir = snk_handle.target.chg_dir;
                        snk_handle.target = snk_handle.target.node;
                    }
                }
                
               
                if (snk_handle.dir == 0)
                {
                    snk_handle.pos.y--;
                }
                else if (snk_handle.dir == 1)
                {
                    snk_handle.pos.y++;
                }
                else if (snk_handle.dir == 2)
                {
                    snk_handle.pos.x--;
                }
                else if (snk_handle.dir == 3)
                {
                    snk_handle.pos.x++;
                }
                
                snk_handle = snk_handle.node;
            }
            
            if (snakeBody.pos.x == cur_food.pos.x && snakeBody.pos.y == cur_food.pos.y)
            {
                // Add body.
                SnakeBody s_handle = snakeBody;
                
                while(s_handle.node != null)
                {
                    s_handle = s_handle.node;
                }
                
                s_handle.node = new SnakeBody( );
                
                if (s_handle.dir == 0)
                {
                    s_handle.node.pos.x = s_handle.pos.x;
                    s_handle.node.pos.y = s_handle.pos.y + 5;
                }
                else if (s_handle.dir == 1)
                {
                    s_handle.node.pos.x = s_handle.pos.x;
                    s_handle.node.pos.y = s_handle.pos.y - 5;
                }
                else if (s_handle.dir == 2)
                {
                    s_handle.node.pos.x = s_handle.pos.x + 5;
                    s_handle.node.pos.y = s_handle.pos.y;
                }
                else if (s_handle.dir == 3)
                {
                    s_handle.node.pos.x = s_handle.pos.x - 5;
                    s_handle.node.pos.y = s_handle.pos.y;
                }
                
                s_handle.node.dir = s_handle.dir;
                s_handle.node.target = s_handle.target;
                
                game_score += cur_food.pnts;
                
                // Change food.
                Random rand = new Random(5);
                
                cur_food = new Food( );
                
                cur_food.pnts = rand.nextInt(10) + 1;
                cur_food.pos.x = rand.nextInt(501) + 1;
                cur_food.pos.y = rand.nextInt(501) + 1;
            }
            
            if (handle.getKey( ) == 'w')
            {
               SnakeBody hnd = snakeBody.node; 
                
               while(hnd != null)
               { 
                   Target nd = hnd.target;
                   
                   while(nd != null)
                   {
                       nd = nd.node;
                   }
                   
                   nd = new Target( );
                   
                   nd.pos.x = snakeBody.pos.x;
                   nd.pos.y = snakeBody.pos.y;
                   nd.chg_dir = 0;
                   
                   Target t = hnd.target;
                   
                   if (t == null)
                   { 
                       hnd.target = nd;
                   }
                   else
                   {
                   
                       while(t.node != null)
                       {     
                           t = t.node;
                        }
                        
                       t.node = new Target( );
                          t.node = nd;
                    }
                   
                   hnd = hnd.node;
               }
               
               snakeBody.dir = 0;
            }
            else if (handle.getKey( ) == 's')
            { 
                 SnakeBody hnd = snakeBody.node; 
                
               while(hnd != null)
               { 
                   Target nd = hnd.target;
                   
                   while(nd != null)
                   {
                       nd = nd.node;
                   }
                   
                   nd = new Target( );
                   
                   nd.pos.x = snakeBody.pos.x;
                   nd.pos.y = snakeBody.pos.y;
                   nd.chg_dir = 1;
                   
                   Target t = hnd.target;
                   
                   if (t == null)
                   { 
                       hnd.target = nd;
                   }
                   else
                   {
                   
                       while(t.node != null)
                       {     
                           t = t.node;
                        }
                        
                       t.node = new Target( );
                          t.node = nd;
                    }
                   
                   hnd = hnd.node;
               }
               
               snakeBody.dir = 1;
            }
            else if (handle.getKey( ) == 'a')
            {
                 SnakeBody hnd = snakeBody.node; 
                
               while(hnd != null)
               { 
                   Target nd = hnd.target;
                   
                   while(nd != null)
                   {
                       nd = nd.node;
                   }
                   
                   nd = new Target( );
                   
                   
                   nd.pos.x = snakeBody.pos.x;
                   nd.pos.y = snakeBody.pos.y;
                   nd.chg_dir = 2;
                   
                   Target t = hnd.target;
                   
                   if (t == null)
                   { 
                       hnd.target = nd;
                   }
                   else
                   {
                   
                       while(t.node != null)
                       {     
                           t = t.node;
                        }
                        
                       t.node = new Target( );
                          t.node = nd;
                    }
                   
                   hnd = hnd.node;
               }
               
               snakeBody.dir = 2;
            }
            else if (handle.getKey( ) == 'd')
            {
                 SnakeBody hnd = snakeBody.node; 
                
               while(hnd != null)
               { 
                   Target nd = hnd.target;
                   
                   while(nd != null)
                   {
                       nd = nd.node;
                   }
                   
                   nd = new Target( );
                   
                   
                   nd.pos.x = snakeBody.pos.x;
                   nd.pos.y = snakeBody.pos.y;
                   nd.chg_dir = 3;
                   
                   Target t = hnd.target;
                   
                   if (t == null)
                   { 
                       hnd.target = nd;
                   }
                   else
                   {
                       while(t.node != null)
                       {     
                           t = t.node;
                       }
                       
                       t.node = new Target( );
                       t.node = nd;
                    }
                    
                   hnd = hnd.node;
               }
               
               snakeBody.dir = 3;
            }
        }
    }
    
    public void startGame( )
    {
        JFrame gameWindow = new JFrame("JSnake!");
        
        gameWindow.setSize(500,500);
        gameWindow.setVisible(true);
        gameWindow.setResizable(false);
        
        gameWindow.addKeyListener(new KeyHandler ( ) );
        gameWindow.add(new Canvas(gameWindow ) );
    }
}
