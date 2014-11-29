using UnityEngine;
using System.Collections;
using Manager;

public class GameController : MonoBehaviour
{
	public Game_Manager Gm=new Game_Manager(); //Create an instance of game_manager class with 30 exp increase rate.
	public GUIText Score_Text; //Declare the text for Score view
	public GUIText Health_Text; //Declare the text for Health view
	public GUIText Ammo_Text;  //Delcare the text for Ammo view
	public GUIText Reload_Text; //Delcare the text for reload alert
	public GUIText Level_Text;  //Declare the text for level view.
	public GUIText Time_Player_Text; //Declare the text for time played view (minutes).
	public GUIText Loose_Text;  //Delcare the text for loosed show
	private bool loose=false;

	private Player_Input_Script pman; //Declare the instance already declared in Player_Input_Script

	void Start()
	{
		pman=GameObject.FindWithTag("Player").GetComponent<Player_Input_Script>(); //Get the component from the player game objct.
	}
	
	void Update()
	{
		if (!loose)
		{
			Score_Text.guiText.text="Score :: "+Gm.GameScore; //View of score text
			Health_Text.guiText.text="Health :: "+pman.pm.PlayerHealth; //View of health text
			Ammo_Text.guiText.text="Ammo :: "+pman.pm.BulletsLeft+"/"+pman.pm.BulletsHave; //View for Ammo.
			Level_Text.guiText.text="Level :: "+Gm.ExperienceLevel;
			Time_Player_Text.guiText.text="Time Played :: "+pman.pm.TimePlayed+" secs";
			if (pman.pm.BulletsLeft<5)
			{
				Reload_Text.gameObject.SetActive(true);
			}
			else
			{
				Reload_Text.gameObject.SetActive(false);
			}
			if (pman.pm.PlayerHealth<1)
			{
				Loose_Text.gameObject.SetActive(true);
				loose=true;
				Invoke("ChangeScene",5);
			}
		}
	}

	void ChangeScene()
	{
		Application.LoadLevel("Menu");
	}
}
