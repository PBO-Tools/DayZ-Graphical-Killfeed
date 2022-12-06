class KillFeedDeathType
{
	private string deathType;
	private bool active;
	private ref array<string> KillPhrases;

	void KillFeedDeathType(string type = "Unknown", array<string> arr = null)
	{
		deathType = type;
		active = true;
		KillPhrases = arr;
	}

	string GetPhrase()
	{
		return KillPhrases.GetRandomElement();
	}

	string GetType()
	{
		return deathType;
	}

	bool IsActive()
	{
		return active;
	}
}