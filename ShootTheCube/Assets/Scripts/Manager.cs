using UnityEngine;
using System.Collections;

namespace Manager
{
	public class Player_Manager
	{
		private int bullet_ammo_left;
		private int bullet_ammo_have;
		private int health;
		private int time_played=0;

		public void ReloadWeapon()
		{
			if (bullet_ammo_have>bullet_ammo_left)
			{
				int dif = bullet_ammo_have-bullet_ammo_left;
				if (dif>20)
				{
					bullet_ammo_left += 20;
					bullet_ammo_have -= 20;
				}
				else
				{
					bullet_ammo_left +=dif;
					bullet_ammo_have -=dif; 
				}
			}
			else 
			{
				bullet_ammo_left +=bullet_ammo_have;
				bullet_ammo_have -=bullet_ammo_have;
			}
		}

		public Player_Manager(int bullet_have,int bullet_left,int player_health)
		{
			bullet_ammo_have=bullet_have;
			bullet_ammo_left=bullet_left;
			health = player_health;
		}

		public Player_Manager(int bullet_have,int bullet_left)
		{
			bullet_ammo_have=bullet_have;
			bullet_ammo_left=bullet_left;
			health=100;
		}

		public Player_Manager()
		{
			bullet_ammo_have=100;
			bullet_ammo_left=20;
			health=100;
		}

		public int BulletsLeft
		{
			get
			{
				return bullet_ammo_left;
			}
			set
			{
				bullet_ammo_left=value;
			}
		}

		public int BulletsHave
		{
			get
			{
				return bullet_ammo_have;
			}
			set
			{
				bullet_ammo_have = value;
			}
		}

		public int PlayerHealth
		{
			get
			{
				return health;
			}
			set
			{
				health = value;
			}
		}

		public int TimePlayed
		{
			get
			{
				time_played +=1;
				return (time_played/60);
			}
		}
	
	}

	public class Enemy_Manager
	{
		private float speed;
		private int health;

		public Enemy_Manager(float movement_speed,int start_health)
		{
			speed = movement_speed;
			health = start_health;
		}

		public Enemy_Manager()
		{
			speed = 6.0f;
			health = 100;
		}

		public float EnemySpeed
		{
			get
			{
				return speed;
			}
			set
			{
				speed = value;
			}
		}

		public int EnemyHealth
		{
			get
			{
				return health;
			}
			set
			{
				health = value;
			}
		}
	}

	public class Game_Manager
	{
		private int game_score;
		private int exp_level;
		private int exp_change_score;
		private int exp_mul_rate;
		private int last_explevel;

		public Game_Manager()  //Constructor 
		{
			game_score=0;
			exp_level=1;
			exp_change_score=25;
		}

		public int GameScore
		{
		   get
			{
				return game_score;
			}
			set
			{
				game_score = value;
			}
		}

		public int ExperienceLevel
		{
			get
			{
				if (game_score>exp_change_score)
				{
					exp_change_score +=2*game_score;
					last_explevel = exp_level;
					exp_level +=1;
				}
				return exp_level;
			}
		}

		public int LastLevel
		{
			get
			{
				return last_explevel;
			}
		}
	}
}
