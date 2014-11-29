using UnityEngine;
using System.Collections;

public class Get_Achivement_Script : MonoBehaviour 
{
	private Player_Input_Script pis; //Declare the player input script under a variable

	void Start()
	{
		pis = GameObject.FindWithTag("Player").GetComponent<Player_Input_Script>(); //Get the current status of the script and place it under the variable
	}

    void OnCollisionEnter(Collision other) //Check for collision and assign other as the collider collided with.
	{
		if (other.gameObject.tag=="Bullet+")
		{
			if (pis.pm.BulletsHave<100 && pis.pm.BulletsHave+20<=100) 	//Check weather the bullets have is less than 100  . if then check weather adding 20 bullets will make it greator than 100
			{
				pis.pm.BulletsHave +=20;   //Add 20 bullets.
			}
			else if (pis.pm.BulletsHave<100 && pis.pm.BulletsHave+20>100) //Check weather bullets have is less than 100 . if then check weather adding 20 bullets is more than 100 . 
			{
				pis.pm.BulletsHave +=(100-pis.pm.BulletsHave); // Add the bullets with the 100 - currentbullets.
			}
			Destroy(other.gameObject); //Destroy the object
		}
		else if (other.gameObject.tag=="Health+")
		{
			if (pis.pm.PlayerHealth<100 && pis.pm.PlayerHealth+20<=100)  //Check weather the health is less than 100  . if then check weather adding 20 more healths will make it greator than 100
			{
				pis.pm.PlayerHealth +=20; //Add 20 healths.
			}
			else if (pis.pm.PlayerHealth<100 && pis.pm.PlayerHealth+20>100)  //Check weather health have is less than 100 . if then check weather adding 20 healths is more than 100 .
			{
				pis.pm.PlayerHealth +=(100-pis.pm.BulletsHave);  // Add the health with the 100 - currenthealth.
			}
			Destroy(other.gameObject); //Destroy the object
		}
	}
}
