using UnityEngine;
using System.Collections;
using Manager;

public class EnemyMovent_Destory : MonoBehaviour 
{
	public Enemy_Manager newenemang=new Enemy_Manager(8.0f,100);
	private int last_level=0;
	private Player_Input_Script pis;
 	private GameController Gc;
	private int healthdecrate;
	public int Speed_Increae_Rate;

	void Start()
	{
		last_level = GameObject.FindWithTag("GameControllerObj").GetComponent<GameController>().Gm.LastLevel;
		pis = GameObject.FindWithTag("Player").GetComponent<Player_Input_Script>();
		healthdecrate = 20;
	}

	void Update () 
	{
		transform.Translate(new Vector3(0f,0f,Time.deltaTime*newenemang.EnemySpeed));
		Gc = GameObject.FindWithTag("GameControllerObj").GetComponent<GameController>();
		if (Gc.Gm.ExperienceLevel>last_level)
		{
			newenemang.EnemySpeed +=(float)last_level+(float)Speed_Increae_Rate;
			healthdecrate +=(Gc.Gm.ExperienceLevel/2);
			last_level +=1;
		}
	}

	void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag=="End")
		{
			Destroy(gameObject);
			if (last_level > 3)
				pis.pm.PlayerHealth -=10;
		}
		else if (other.gameObject.tag=="Player")
		{
			pis.pm.PlayerHealth -=healthdecrate;
			Destroy(gameObject);
		}
	}
}
