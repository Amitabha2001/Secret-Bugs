using UnityEngine;
using System.Collections;

public class Player_Bullet_Script : MonoBehaviour 
{
	private GameController Gc;

	void Start()
	{
		Gc = GameObject.FindWithTag("GameControllerObj").GetComponent<GameController>();
	}

   void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag=="Enemy")
		{
			Gc.Gm.GameScore +=10;
			if (other.gameObject.GetComponent<EnemyMovent_Destory>().newenemang.EnemyHealth < 1)
			{
				Destroy(other.gameObject);
			}
			else
			{
				other.gameObject.GetComponent<EnemyMovent_Destory>().newenemang.EnemyHealth -=50;
			}
			Destroy(gameObject);
		}
	}
}
