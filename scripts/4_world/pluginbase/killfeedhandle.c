class KillFeedHandle : PluginBase
{
	private ref array<ref KillFeedDeathType> KillFeedPhrases;

	void KillFeedHandle()
	{
		LoadPhrases();
	}

	void LoadPhrases()
	{
		string modDir = "$profile:/KillFeed";
		string configPath = modDir + "/" + "Settings.json"; 
		if (!FileExist(modDir))
			MakeDirectory(modDir);
		if (FileExist(configPath))
			JsonFileLoader<ref array<ref KillFeedDeathType>>.JsonLoadFile( configPath, KillFeedPhrases );
		else
		{
			FillDefault();
			JsonFileLoader<ref array<ref KillFeedDeathType>>.JsonSaveFile( configPath, KillFeedPhrases );
		}
	}

	void OnPlayerKilled(int deathType, PlayerBase victim = null, PlayerBase murder = null, EntityAI weapon = null)
	{
		KillFeedDeathType ktype = GetDeathConfigByType(deathType);
		string msg;
		int type;
		if (ktype.GetType() == "PVP")
			type = 1;
		else if (ktype.IsActive())
			msg = ktype.GetPhrase();
		else
			return;

		SendKillInfo(murder, victim, type, weapon, msg);	
	}

	void SendKillInfo(PlayerBase murder, PlayerBase victim, int type, EntityAI weapon = null, string msg = "")
	{
		string murderName, targetName, murderWeaponType, message;
		int dst;
		PlayerBase recipient;
		array<Man> players;

		targetName = "Unknown";
		if (victim.GetIdentity())
			targetName = victim.GetIdentity().GetName();

		if (type)
		{
			murderName = murder.GetIdentity().GetName();

			dst = vector.Distance(victim.GetPosition(), murder.GetPosition());
			murderWeaponType = string.Empty;
			if (weapon)
				murderWeaponType = weapon.GetType();
		}
		else
		{
			message = msg;
		}

		players = new array<Man>();
		GetGame().GetWorld().GetPlayerList(players);

		for (int i = 0; i < players.Count(); i++)
		{
			recipient = PlayerBase.Cast(players[i]);
			if (recipient != victim && recipient.IsAlive())
				recipient.RPCSingleParam(-74700005, new Param6<string, string, string, int, string, int>(murderName, targetName, murderWeaponType, dst, message, type), true, recipient.GetIdentity());
		}
	}

	string GetDate()
	{
		int hour = 0;
		int minute = 0;
		int second = 0;
		int year = 0;
		int month = 0;
		int day = 0;

		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		return string.Format("%1.%2.%3 %4:%5:%6", day.ToString(), month.ToString(), year.ToString(), hour.ToString(), minute.ToString(), second.ToString());
	}

	void FillDefault()
	{
		KillFeedPhrases = new array<ref KillFeedDeathType>();
		KillFeedPhrases.Insert(new KillFeedDeathType("UNKNOWN", {"fell on a grenade"}));
		KillFeedPhrases.Insert(new KillFeedDeathType("PVP", {""}));
		KillFeedPhrases.Insert(new KillFeedDeathType("SUICIDE", {"killed themselves."}));
		KillFeedPhrases.Insert(new KillFeedDeathType("BLEEDING", {"bleed to death."}));
		KillFeedPhrases.Insert(new KillFeedDeathType("STARVING", {"starved to death."}));
		KillFeedPhrases.Insert(new KillFeedDeathType("ZOMBIE", {"took on zombies and lost."}));
		KillFeedPhrases.Insert(new KillFeedDeathType("ANIMAL", {"fought a bear and the bear won."}));
		KillFeedPhrases.Insert(new KillFeedDeathType("FALL", {"fell to thier death."}));
	}

	KillFeedDeathType GetDeathConfigByType(DeathType type)
	{
		foreach (KillFeedDeathType ktype : KillFeedPhrases)
		{
			if (typename.EnumToString(DeathType, type) == ktype.GetType())
				return ktype;
		}
		return null;
	}
}

KillFeedHandle GetKillFeedHandle()
{
	return KillFeedHandle.Cast(GetPlugin(KillFeedHandle));
}