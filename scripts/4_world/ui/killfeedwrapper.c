class KillFeedWrapper
{
	private Widget root;
	private ref array<ref KillFeedItem> items;

	void KillFeedWrapper()
	{
		root = GetGame().GetWorkspace().CreateWidgets("NulledKillfeed/assets/FeedWrapper.layout", null);
		items = new array<ref KillFeedItem>();
	}

	Widget GetRoot()
	{
		return root;
	}

	void AddItem(Param6<string, string, string, int, string, int> data)
	{
		items.Insert(new KillFeedItem(this, data.param1, data.param2, data.param3, data.param4, data.param5, data.param6));
	}

	void RemoveItem(KillFeedItem item)
	{
		int idx = items.Find(item);
		if (idx + 1)
		{
			items.Remove(idx);
		}
	}

}