iniDBI(IMPROVED) - A simple server-side database extension using INI files

Authors: 
	inidbi - v1.1 code34 - nicolas_boiteux@yahoo.fr
	inidb - v1.0 SicSemperTyrannis http://raiderbattalion.enjin.com/
	
How to use:
	To use "iniDBI" in your mission, install the extension in your ARMA2 or ARMA3 directory by copying the entire "@inidbi" folder included in the download to your root directory. 
	Don't forget to copy over over or create the /db/ folder.
		It should look like: /Arma 3/@inidbi/iniDB.dll
		It should look like: /Arma 3/@inidbi/db/
		It should look like: /Arma 3/@inidbi/Addons/inidbi.pbo
	
	Then in your mission init.sqf, somewhere before you want to use the functions do this:
		call compile preProcessFile "\inidbi\init.sqf";

	It should be noted that when you install the @inidbi folder you can delete the /examples/ directory from there if you please, they serve no purpose in that folder.

	You have permission to use, upload or otherwise distribute this as please, just mention differents authors.

----------------------------------------------------------------------------------------------

CHANGELOG

16-November-2013 - inidbi
	- check input/output data type
	- add log messages
	- add BOOL type function read

01-November-2013 - inidbi
	- increase buffer 8k
	- check size of written data
	- change output function

13-March-2013
	- Module
		- Initial Release
	- init.sqf
		- Initial Release