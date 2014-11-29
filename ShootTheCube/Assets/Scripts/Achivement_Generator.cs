using UnityEngine;
using System.Collections;

public class Achivement_Generator : MonoBehaviour 
{
	[Range(0.1f,100.0f)] public float next_bul_achive_rate;  //Create a slider with range.
	[Range(0.1f,100.0f)] public float next_health_achive_rate; //Create a slider with range.
	private float next_bul_achive; //Declare the float vars
	private float next_health_achive;
	public GameObject Health_Pref; //Declare the game objects
	public GameObject Bul_Pref;

	// Update is called once per frame
	void Update () 
	{
	  if (Time.time > next_bul_achive)
		{
			next_bul_achive = Time.time + next_bul_achive_rate; //Increment the next time to creation
			Instantiate(Bul_Pref,new Vector3(Random.Range((int)1.993502,(int)22.79078),Bul_Pref.transform.position.y,Bul_Pref.transform.position.z),Quaternion.identity); //Create the object.
		}
	  else if (Time.time > next_health_achive) 
		{
			next_health_achive = Time.time + next_health_achive_rate;  //Increment the next time to creation
			Instantiate(Health_Pref,new Vector3(Random.Range((int)1.993502,(int)22.79078),Health_Pref.transform.position.y,Health_Pref.transform.position.z),Quaternion.identity);  //Create the object.
		}
	}
}
