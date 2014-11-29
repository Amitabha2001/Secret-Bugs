using UnityEngine;
using System.Collections;

public class Enemy_Generator : MonoBehaviour 
{
	public GameObject Enemy_Prefab;
	private float next_enemy=0.0f;
	public float dif_rate=0.0f;
	
	// Update is called once per frame
	void Update () 
	{
		if (Time.time>next_enemy)
		{
			next_enemy = Time.time+dif_rate;
			int posx=Random.Range((int)2.235787,(int)23.32235);
			Instantiate(Enemy_Prefab,new Vector3((float)posx,Enemy_Prefab.transform.position.y,Enemy_Prefab.transform.position.z),Quaternion.Euler(0,180,0));
		}
	}
}
