# FormList Manipulator

This SKSE plugin allows you to add Forms to FormLists at game startup using configuration files.
With this mod, you can get rid of conflicts between mods that modify FormLists, and thus avoid creating compatibility patches. Examples of such situations are mods that add new plants to plant, add toys and gifts, new character voices, trophies, hair colors and races for head parts, etc.

## Config Files

Configuration files can have any name, but they must be INI files whose name ends with _FLM. Example: Toys_FLM.ini.
Or they can be any INI files located in the "FLM" directory.
Configuration files are processed in alphabetical order. First form the Data directory, then form the Data\FLM.

##  General usage

```FormList = FList|Form, Form, #Group, etc```

where,
* FList can be: EditorID or FormID~ESP or Alias.
* Form can be: EditorID or FormID~ESP.
* FormID - record ID. Example: 0xD80 or 0x03008246 or 0xFE00080A or 0x8246 (You no longer need to remove any digits from FormID, the plugin will do it automatically).
* ESP - name of the plugin with extension. Not required for base plugins and DLC. Example Unofficial Skyrim Special Edition Patch.esp. Not case-sensitive.
* EditorID - form editorID.

Keys: FormList, Plant, BToys, GToys are not case-sensitive.
FList  is skipped if is not found. Form is skipped if it already exists in FormList or is not found.

##  Aliases

```Alias = NameForAlias|FList, FList, etc```

Aliases are collections of FromLists. To use an Alias add the # sign before its name. Aliases are processed at the beginning of the configuration file, regardless of their position in the file. Only for FormList keyword.

##  Groups

```Group = NameForGroup|Form, Form, etc```

Groups are collections of Forms. To use a Group add the # sign before its name. Groups are processed at the beginning of the configuration file, regardless of their position in the file. For FormList , BToy, GToy keywords.

## Simplified usage for Plants:

```Plant = Form|Form```

where,
* first form is for Ingredient/Alchemy Item/Activator,
* second for Flora/Tree/Misc/Activator/Container.
* If you specify a different type of Form, a warning will be thrown into the log, but the Form will be added.

## Simplified usage for Boy's Toys:

```BToys = Form, Form, #Group, etc```

## Simplified usage for Girl's Toys:

```GToys = Form, Form, #Group, etc```

## Debug Mode

To reduce the amount of output to the log, debug mode was added. Thus, the log in its normal form is concise.
To enable debug mode to see more details, create the FormListManipulator_DEBUG.ini file.

## Examples:
```
Alias = TestAlias|0x8246~HearthFires.esm,0x03008246
Group = Dolls|BYOHChefDoll,BYOHDBDoll,BYOHDragonbornDoll,BYOHJesterDoll
FormList = #TestAlias|BYOHBlacksmithDoll,BYOHDragonPriestDoll,BYOHExecutionerDoll
BToys = #Dolls
Plant = zzzCHMountainFlower01White|zzzCHTreeFloraWhiteFlowers
FormList = 0x03008246|0x807~Plantable Animals.esp,PlantableAnimalsAlbinoSpiderNest
Formlist = #TestAlias|#Dolls
Plant = ChaurusEggs|PlantableAnimalsChaurusNest
```

## Validation for configuration files:
Take a look at the log: "[PATH to MY Documents]\My Games\Skyrim Special Edition\SKSE\FormListManipulator.log". It contains all the information about the processed files and records.

## Compability
Created with CommonLibSSE-NG, support SE, AE, VR, but only SE was tested.

## License
[MIT](LICENSE)
