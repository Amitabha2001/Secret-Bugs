using UnityEngine;
using System.Collections;
using Manager;

public class Player_Input_Script : MonoBehaviour
{
	public float speed=2.0f;
	public GameObject Bullet_Pref;
	public float next_shot_rate=0.2f;
	private float next_shot;
	public int force=0;
	public Player_Manager pm=new Player_Manager(100,20,100);  //Create an instacne of player_manager and set the values
	
	// Update is called once per frame
	void Update () 
	{
		//Check for inputs
		gameObject.transform.rotation=Quaternion.Euler(new Vector3(0f,0f,0f)); //Set the rotation of the gameobject to 0
		if (Input.GetKey(KeyCode.LeftArrow))
		{
			transform.Translate(new Vector3(-speed*Time.deltaTime,0f,0f));  //Move towards left
		}
		else if (Input.GetKey(KeyCode.RightArrow))
		{
			transform.Translate(new Vector3(speed*Time.deltaTime,0f,0f));  //Move towards right
		}
		else if (Input.GetKeyDown(KeyCode.Escape))
		{
			Invoke("ChangeScene",2); //Call the ChangeScene function after 2 seconds
		}
		if (Input.GetKey(KeyCode.Space) && Time.time>next_shot && pm.BulletsLeft>0)
		{
			next_shot = Time.time + next_shot_rate;  //Update the time for the next shot
			GameObject bul = (GameObject) Instantiate(Bullet_Pref,GameObject.FindWithTag("BulletStartPoint").transform.position,Quaternion.identity);  //Create a bullet in the front of the player
			bul.rigidbody.AddForce(GameObject.FindWithTag("BulletStartPoint").transform.forward*force);  //Add a force to the bullet
			Destroy(bul,3); //Destory the bullet after 3 seconds
			pm.BulletsLeft -=1; //Decrement 1 bullets from the bullets left.
		}
		if (Input.GetKeyDown(KeyCode.R))
		{
			pm.ReloadWeapon();  //Call the reload function
		}
		float pos_x=Mathf.Clamp(transform.position.x,0.9301373f,24.18906f); //Check for clamp
		transform.position=new Vector3(pos_x,transform.position.y,transform.position.z); //Execute the clamp/
	}

	void ChangeScene()
	{
		Application.LoadLevel("Menu");
	}
}

