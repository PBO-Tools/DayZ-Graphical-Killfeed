modded class PlayerBase
{
	private ref KillFeedWrapper killFeed;

	void PlayerBase()
	{
		if (GetGame().IsClient())
		{
			killFeed = new KillFeedWrapper();
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		if (GetGame().IsClient())
		{
			if (rpc_type == -74700005)
			{
				Param6<string, string, string, int, string, int> data;
				if (!ctx.Read(data))
					return;
				killFeed.AddItem(data);
			}
		}
	}
}