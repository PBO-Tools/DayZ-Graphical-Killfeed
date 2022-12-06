enum DeathType
{
	UNKNOWN = 0,
	PVP,
	SUICIDE,
	BLEEDING,
	STARVING,
	ZOMBIE,
	ANIMAL,
	FALL
}

modded class PlayerBase
{
	private bool IsFallDeath = false;

	override override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (ammo == "FallDamage" && !IsAlive())
			IsFallDeath = true;
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void EEKilled( Object killer )
	{
		EntityAI weapon;
		PlayerBase target = PlayerBase.Cast(EntityAI.Cast(killer).GetHierarchyRootPlayer());
		DeathType deathType = DeathType.UNKNOWN;

		if (killer && killer == this)
		{
			if (GetHealth("","Blood") < PlayerConstants.BLOOD_THRESHOLD_FATAL)
				deathType = DeathType.BLEEDING;
			else if (IsFallDeath)
				deathType = DeathType.FALL;
			else if (GetStatWater().Get() <= PlayerConstants.LOW_WATER_THRESHOLD || GetStatEnergy().Get() <= PlayerConstants.LOW_ENERGY_THRESHOLD)
				deathType = DeathType.STARVING;
			else
				deathType = DeathType.SUICIDE;
		}
		else if (killer.IsInherited(ZombieBase))
			deathType = DeathType.ZOMBIE;
		else if (killer.IsInherited(AnimalBase))
			deathType = DeathType.ANIMAL;
		else if (target && target != this)
		{
			if (killer != target)
				weapon = killer;
			deathType = DeathType.PVP;
		}

		GetKillFeedHandle().OnPlayerKilled(deathType, this, target, weapon);
	
		super.EEKilled(killer);
	}
}