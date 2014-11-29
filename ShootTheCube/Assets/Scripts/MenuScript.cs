using UnityEngine;
using System.Collections;

public class MenuScript : MonoBehaviour 
{
	private bool is_menu=true;
	private bool is_controls=false;
	private int score=0;

	void OnGUI() 
	{
		GUI.Box(new Rect((Screen.width/2)-250,(Screen.height/2)-250,500,500),"Shoot-The-Cube");
		if (is_menu)
		{
			if (GUI.Button(new Rect((Screen.width/2)-65,(Screen.height/2)-180,130,50),"Play Game"))
			{
				Application.LoadLevel("Game");
			}
			else if (GUI.Button(new Rect((Screen.width/2)-65,(Screen.height/2)-110,130,50),"Controls"))
			{
				is_menu=false;
				is_controls=true;
			}
			else if (GUI.Button(new Rect((Screen.width/2)-65,(Screen.height/2)-40,130,50),"Exit"))
			{
				Application.Quit();
			}
			GUI.Label(new Rect((Screen.width/2)-245,(Screen.height/2)+225,130,50),"High-Score :: "+score);
		}
		else if (is_controls)
		{
			GUI.Label(new Rect((Screen.width/2)-40,(Screen.height/2)-180,130,50),"Left-ward :: Left-Arrow");
			GUI.Label(new Rect((Screen.width/2)-40,(Screen.height/2)-150,150,50),"Right-ward :: Right-Arrow");
			GUI.Label(new Rect((Screen.width/2)-40,(Screen.height/2)-120,130,50),"Shoot :: Spacebar");
			GUI.Label(new Rect((Screen.width/2)-40,(Screen.height/2)-90,130,50),"Save :: Shift");
			GUI.Label(new Rect((Screen.width/2)-40,(Screen.height/2)-60,130,50),"Back :: Escape");
			if (GUI.Button(new Rect((Screen.width/2)-220,(Screen.height/2)+150,130,50),"Back"))
			{
				is_menu=true;
				is_controls=false;
			}
		}
	}
}
