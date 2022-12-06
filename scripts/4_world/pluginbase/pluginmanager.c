modded class PluginManager
{
	override void Init()
	{
		super.Init();

		RegisterPlugin("KillFeedHandle", false, true);
	}
}