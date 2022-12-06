class CfgPatches
{
	class NulledKillfeed
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class NulledKillfeed
	{
		dir="NulledKillfeed";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="NulledKillfeed";
		credits="";
		author="";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"NulledKillfeed/scripts/4_World"
				};
			};
		};
	};
};
