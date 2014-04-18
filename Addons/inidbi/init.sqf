	/*
		v 1.5 : IniDBI by code34 - nicolas_boiteux@yahoo.fr
		v 1.4 : IniDBI by code34 - nicolas_boiteux@yahoo.fr
		v 1.3 : IniDBI by code34 - nicolas_boiteux@yahoo.fr
		v 1.2 : IniDBI by code34 - nicolas_boiteux@yahoo.fr
		v 1.1 : IniDBI by code34 - nicolas_boiteux@yahoo.fr
		v 1.0 : IniDB by SicSemperTyrannis http://raiderbattalion.enjin.com/
	*/
	
	iniDB_version = {
		private["_data", "_version"];
		_version = "1.5";
		_data = "iniDB" callExtension "version";
		_data = format["Inidbi: %1 Dll: %2", _version, _data];
		_data;
	};
	
	iniDB_HashFunction = {
		private["_mode", "_data"];
		_mode = _this select 0;
		_data = _this select 1;
		
		if((typeName _data) == "STRING") then {	
			_data = "iniDB" callExtension format["%1;%2", _mode, _data];
			_data = call compile _data;
	
			if((_data select 0)) then {
				_data select 1;
			} else {
				nil;
			};
		} else {
			nil;
		};
	};
	
	iniDB_CRC32 = {
		_this = ["crc", _this] call iniDB_HashFunction;
		_this;
	};
	
	iniDB_MD5 = {
		_this = ["md5", _this] call iniDB_HashFunction;
		_this;
	};
	
	iniDB_Base64Encode = {
		_this = ["b64_enc", _this] call iniDB_HashFunction;
		_this;
	};
	
	iniDB_Base64Decode = {
		_this = ["b64_dec", _this] call iniDB_HashFunction;
		_this;
	};

	iniDB_cast = {
		private["_data", "_type"];
		_data = _this select 0;
		_type = _this select 1;
		
		switch (toupper(_type)) do {
			case "ARRAY": {
				if(_data == "") then {
					_data = [];
				} else {
					_data = call compile _data;
				};
			};
	
			case "SCALAR": {
				if(_data == "") then {
					_data = 0;
				} else {
					_data = parseNumber _data;
				};
			};

			case "BOOL": {
				if(_data == "") then {
					_data = false;
				} else {
					_data = call compile _data;
				};
			};
	
			default {
				if(_data == "") then {
					_data = "";
				} else {
					_data = format["%1", _data];
				};
			};
			
		};
		_data;
	};

	iniDB_chunk = {
		private ["_array", "_count", "_chunk", "_data"];
		_data = (toarray(format["%1", _this select 0]);
		_array = [];
		_chunk = [];
		_count = 0;

		{
			if(_count > 8191) then {
				_array = _array + _chunk;
				_chunk = [];
				_count = 0;
			};			
			_chunk = _chunk + [_x];
			_count = _count + 1;
		}foreach _data;
		_array = tostring(_array);
		_array;
	};
	
	iniDB_delete = {
		private["_data"];
		_data = "iniDB" callExtension format["delete;%1", _this];
		_data = call compile _data;
		
		if((_data select 0)) then {
			true;
		} else {
			false;
		};
	};

	iniDB_deletesection = {
		private["_file", "_section", "_result"];
		_file 		= _this select 0;
		_section 	= _this select 1;

		if(isnil "_file") exitWith { ["IniDBI: deletesection failed, databasename is empty"] call iniDB_log;};
		if(isnil "_section") exitWith { ["IniDBI: deletesection failed, sectionname is empty"] call iniDB_log;};
	
		_result = "iniDB" callExtension format["deletesection;%1;%2", _file, _section];
		_result = call compile _result;
		
		if((_result select 0)) then {
			true;
		} else {
			false;
		};
	};

	iniDB_deletekey = {
		private["_file", "_section", "_key", "_result"];
		_file 		= _this select 0;
		_section 	= _this select 1;
		_key 		= _this select 1;

		if(isnil "_file") exitWith { ["IniDBI: deletekey failed, databasename is empty"] call iniDB_log;};
		if(isnil "_section") exitWith { ["IniDBI: deletekey failed, sectionname is empty"] call iniDB_log;};
		if(isnil "_key") exitWith { ["IniDBI: deletekey failed, key is empty"] call iniDB_log;};
	
		_result = "iniDB" callExtension format["deletekey;%1;%2;%3", _file, _section, _key];
		_result = call compile _result;
		
		if((_result select 0)) then {
			true;
		} else {
			false;
		};
	};

	iniDB_exists = {
		private["_data"];
		_data = "iniDB" callExtension format["exists;%1", _this];
		_data = call compile _data;
		
		if((_data select 0) && (_data select 1)) then {
			true;
		} else {
			false;
		};
	};

	iniDB_log = {
		hint format["%1", _this select 0];
		diag_log format["%1", _this select 0];
	};
	
	iniDB_read = {
		private["_file", "_section", "_key", "_type", "_data", "_ret", "_result"];
		if(count _this < 4) exitwith { 
			["Inidb: read failed not enough parameter"] call iniDB_log;
		};

		_file 		= _this select 0;
		_section 	= _this select 1;
		_key 		= _this select 2;
		_type		= _this select 3;

		if(isnil "_file") exitWith { ["IniDBI: read failed, databasename is empty"] call iniDB_log;};
		if(isnil "_section") exitWith { ["IniDBI: read failed, sectionname is empty"] call iniDB_log;};
		if(isnil "_key") exitWith { ["IniDBI: read failed, keyname is empty"] call iniDB_log;};
		if(isnil "_type") then { _type = "STRING";};
		if!(_type in ["ARRAY", "SCALAR", "STRING", "BOOL"]) exitWith {["IniDBI: read failed, data type parameter must be ARRAY, SCALAR, STRING, BOOL"] call iniDB_log;};
	
		_result = "iniDB" callExtension format["read;%1;%2;%3", _file, _section, _key];
		_result = call compile _result;
	
		_ret = _result select 0;
		if(count _result > 1) then {
			_data = _result select 1;
		} else {
			_data = "";
		};
		_data = [_data, _type] call iniDB_cast;
		inidb_errno = _ret;
		_data;
	};

		
	iniDB_write = {
		private["_file", "_section", "_key", "_data", "_exit"];
		_file = _this select 0;
		_section = _this select 1;
		_key = _this select 2;
		_data = _this select 3;
		_exit = false;

		if(isnil "_file") exitWith { ["IniDBI: write failed, databasename is empty"] call iniDB_log;};
		if(isnil "_section") exitWith { ["IniDBI: write failed, sectionname is empty"] call iniDB_log;};
		if(isnil "_key") exitWith { ["IniDBI: write failed, keyname is empty"] call iniDB_log;};
		if(isnil "_data") exitWith {["IniDBI: write failed, data is empty"] call iniDB_log;};
		if!(typename _data in ["BOOL", "ARRAY", "STRING", "SCALAR"]) then {_exit = true;};
		if(typename _data == "ARRAY") then {
				{
					if!(typename _x in ["BOOL", "ARRAY", "STRING", "SCALAR"]) then {
						_exit = true;
					};
				}foreach _data;
		};
		if(_exit) exitWith { _log = format["IniDBI: write failed, %1 %2 data contains object should be ARRAY, SCALAR, STRING type", _section, _key]; [_log] call iniDB_log;};
	
		if(count (toarray(format["%1", _data])) > 8191) then {
			_data = false;
			_log = format["IniDBI: write failed %1 %2 data too big > 8K", _section, _key];
			[_log] call iniDB_log;
		} else {
			_data = format['"%1"', _data];
			_data = "iniDB" callExtension format["write;%1;%2;%3;%4", _file, _section, _key, _data];
			_data = (call compile _data) select 0;
		};
		_data;
	};

	