#pragma once

#include "EventManager.hpp"
#include "FormListType.hpp"
#include "InfoType.hpp"
#include "Keywords.hpp"

namespace flm
{
	/**
	 * \brief The main class that manages the mechanism for manipulating Forms.
	 */
	class Manipulator
	{
		public:
			Manipulator();
			/**
			 * \brief Returns debug mode state.
			 * \return              - Debug mode state.
			 */
			bool DebugMode() const;
			/**
			 * \brief Sets debug mode state.
			 * \param mode          - New debug mode state.
			 */
			void SetDebugMode(bool mode);
			/**
			 * \brief Finds FormLists whose use is simplified and config files.
			 */
			void FindAll();
			/**
			 * \brief Adds all Forms from config files.
			 */
			void AddAll();
			/**
			 * \brief Generates summary for config files.
			 */
			void Summary();

			/**
			 * \brief Sets current operating mode to NewGame.
			 */
			void SetNewGameMode();
			/**
			 * \brief Sets current operating mode to LoadGame.
			 */
			void SetLoadGameMode();

			/**
			 * \brief Returns manager for Mod Events.
			 * \return Manager for Mod Events.
			 */
			EventManager& GetEventManager();

		private:
			bool debug_mode_ = false;              /* Mode for more detailed information. */
			OperatingMode::OperatingMode mode_;    /* Current operating mode for FLM. */
			std::array<int, InfoType::ALL> infos_; /* Store values for types of countable statistics.*/
			std::vector<RE::BGSListForm*> lists_;  /* FormLists from Skyrim for use in simplified entries. */
			EventManager event_manager_;           /* Manages sending and receiving mod events. */

			const std::array<ParseEntryCallback, EntryType::ALL> add_callbacks_{
				std::bind(&Manipulator::parseAlias, this, std::placeholders::_1),         /* Aliases for FormLists. */
				std::bind(&Manipulator::parseGroup, this, std::placeholders::_1),         /* Groups for Forms. */
				std::bind(&Manipulator::parseModEvent, this, std::placeholders::_1),      /* Mod events. */
				std::bind(&Manipulator::parseFormList, this, std::placeholders::_1),      /* FromList. */
				std::bind(&Manipulator::parsePlant, this, std::placeholders::_1),         /* Plant. */
				std::bind(&Manipulator::parseBToys, this, std::placeholders::_1),         /* Boy's toys. */
				std::bind(&Manipulator::parseGToys, this, std::placeholders::_1),         /* Girl's toys. */
				std::bind(&Manipulator::parseHairColors, this, std::placeholders::_1),    /* Hair colors. */
				std::bind(&Manipulator::parseAtronachForge, this, std::placeholders::_1), /* Atronach forge. */
			};                                                                            /* Functions used to parse entries. */

			std::map<std::string, std::vector<RE::BGSListForm*>> aliases_;      /* All valid Aliases. */
			std::map<std::string, std::vector<RE::TESForm*>> groups_;           /* All valid Groups. */
			FormListsData form_lists_;                                          /* All valid Forms for FormLists. */
			std::vector<std::pair<RE::TESForm*, RE::TESForm*>> plants_;         /* All valid Forms with seeds and plants. */
			std::vector<RE::TESForm*> boy_toys_;                                /* All valid Forms with boy's toys. */
			std::vector<RE::TESForm*> girl_toys_;                               /* All valid Forms with girl's toys. */
			std::vector<RE::TESForm*> hair_colors_;                             /* All valid Forms with hair colors. */
			std::vector<std::pair<RE::TESForm*, RE::TESForm*>> atronach_forge_; /* All valid Forms with recipes and results for Atronach Forge. */

			/**
			 * \brief Finds all FormLists whose use is simplified.
			 */
			void findLists();

			/**
			 * \brief Finds all config files. Finds all configuration files. Reads data from configuration files and adds the correct entries to internal structures.
			 */
			void findConfigs();
			/**
			 * \brief Perform parsing of the entry if the key is in the type.
			 * \param key                   - Key to check.
			 * \param entry                 - Entry to parse.
			 * \param type                  - Entry type.
			 * \param valid                 - A variable that stores the number of valid entries.
			 * \param invalid               - A variable that stores the number of invalid entries.
			 * \return                      - True if the key is valid.
			 */
			bool addIfKeyIs(const std::string& key, const std::string& entry, const EntryType::EntryType type, int& valid, int& invalid);
			/**
			 * \brief Adds the correct plants to the game.
			 */
			void addPlants();
			/**
			 * \brief Adds the correct kids toys to the game.
			 */
			void addKidsToys();
			/**
			 * \brief Adds the correct hair colors to the game.
			 */
			void addHairColors();
			/**
			 * \brief Adds the correct pairs of recipes and results to the game.
			 */
			void addAtronachForgeRecipes();
			/**
			 * \brief Adds Form and FromList to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format FList|Form, Form, #Group, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseFormList(const std::string& entry);
			/**
			 * \brief Adds Seed end Plant to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Seed|Plant
			 * \return                          - True, if everything went fine.
			 */
			bool parsePlant(const std::string& entry);
			/**
			 * \brief Adds Boy's Toys to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Form, Form, #Group, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseBToys(const std::string& entry);

			/**
			 * \brief Adds Girl's Toys to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Form, Form, #Group, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseGToys(const std::string& entry);
			/**
			 * \brief Adds Alias to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format NameForAlias|FList, FList, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseAlias(const std::string& entry);
			/**
			 * \brief Adds Group to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format NameForGroup|From, From, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseGroup(const std::string& entry);
			/**
			 * \brief Adds ModEvent to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format FList|Form, Form, #Group, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseModEvent(const std::string& entry);
			/**
			 * \brief Adds Hair Colors to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Form, Form, #Group, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseHairColors(const std::string& entry);
			/**
			 * \brief Adds recipe and result to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Recipe|Result.
			 * \return                          - True, if everything went fine.
			 */
			bool parseAtronachForge(const std::string& entry);
			/**
			 * \brief Parse form entry.
			 * \param entry                 - Entry to parse.
			 * \param forms                 - Forms vector, where the found forms will be added.
			 * \return                      - 0 if the entry is valid, -1 if the form is missing, -2 if the group is missing.
			 */
			int parseFormEntry(std::string& entry, std::vector<RE::TESForm*>& forms);
			/**
			 * \brief Adds From to FormList. Duplicates are omitted.
			 * \param list                      - FromList where Form will be added.
			 * \param form                      - Form to add.
			 * \return                          - True, if everything went fine.
			 */
			bool addFormToFormList(RE::BGSListForm*& list, RE::TESForm* form) const;
	};

	inline Manipulator::Manipulator()
		: mode_(OperatingMode::INITIALIZE)
	{
		infos_.fill(0);
	}

	inline bool Manipulator::DebugMode() const
	{
		return debug_mode_;
	}

	inline void Manipulator::SetDebugMode(bool mode)
	{
		debug_mode_ = mode;
	}

	inline void Manipulator::FindAll()
	{
		findLists();
		findConfigs();
	}

	inline void Manipulator::AddAll()
	{
		addPlants();
		addKidsToys();
		addHairColors();
		addAtronachForgeRecipes();
		auto [added, duplicates] = AddGeneric(form_lists_, mode_, debug_mode_);
		infos_[InfoType::FORMS_ADD] += added;
		infos_[InfoType::FORMS_DUP] += duplicates;
	}

	inline void Manipulator::findLists()
	{
		for(int type = 0; type != FormListType::ALL; type++)
			lists_.emplace_back(FindForm<RE::BGSListForm>(FormListType::editor_id[type]));
	}

	inline void Manipulator::findConfigs()
	{
		const std::filesystem::directory_entry debug_mode_toggle(R"(Data\FormListManipulator_DEBUG.ini)");
		if(debug_mode_toggle.exists())
		{
			log::Header("DEBUG MODE ENABLED"sv);
			SetDebugMode(true);
		}

		log::Header("Looking for configs"sv);
		std::vector<std::string> files;
		auto constexpr folder = R"(Data\)";
		for(const auto& entry : std::filesystem::directory_iterator(folder))
			if(entry.exists() && !entry.path().empty() && entry.path().extension() == ".ini"sv)
				if(const auto path = entry.path().string(); path.rfind("_FLM") != std::string::npos)
					files.push_back(path);

		auto constexpr folderFLM = R"(Data\FLM)";
		if(std::filesystem::directory_entry(folderFLM).exists())
			for(const auto& entry : std::filesystem::directory_iterator(folderFLM))
				if(entry.exists() && !entry.path().empty() && entry.path().extension() == ".ini"sv)
					files.push_back(entry.path().string());

		if(files.empty())
		{
			log::Warn("Configs not found!");
			return;
		}
		else
			log::Info("Found {} configs.", files.size());

		log::level++;

		for(auto& path : files)
		{
			CSimpleIniA ini;
			ini.SetUnicode();
			ini.SetMultiKey();

			if(const auto rc = ini.LoadFile(path.c_str()); rc < 0)
			{
				log::Error("Can't read ini {}.", path);
				infos_[InfoType::CONFIGS_IN]++;
				continue;
			}

			infos_[InfoType::CONFIGS_V]++;

			log::Info("Processing {}...", path);
			log::level++;

			if(auto values = ini.GetSection(""); values)
			{
				int valid_entries = 0;   /* How many valid entries is. */
				int invalid_entries = 0; /* How many invalid entries is. */

				// Parse Aliases and Groups first.
				for(auto& [key, entry] : *values)
				{
					std::string sanitized_entry = Sanitize(entry);
					std::string lowercase_key = key.pItem;
					ToLower(lowercase_key);

					if(addIfKeyIs(lowercase_key, sanitized_entry, EntryType::ALIAS, valid_entries, invalid_entries))
						continue;

					if(addIfKeyIs(lowercase_key, sanitized_entry, EntryType::GROUP, valid_entries, invalid_entries))
						continue;
				}

				for(auto& [key, entry] : *values)
				{
					std::string sanitized_entry = Sanitize(entry);
					std::string lowercase_key = key.pItem;
					ToLower(lowercase_key);

					if(std::ranges::find(keywords, lowercase_key) == keywords.end())
					{
						log::Error("Unknown key {}!", key.pItem);
						invalid_entries++;
						continue;
					}

					for(int type = 2; type != EntryType::ALL; type++)
						if(addIfKeyIs(lowercase_key, sanitized_entry, static_cast<EntryType::EntryType>(type), valid_entries, invalid_entries))
							break;
				}

				log::Info("Finished, {} valid entries found, {} invalid.", valid_entries, invalid_entries);
				infos_[InfoType::ENTRIES_V] += valid_entries;
				infos_[InfoType::ENTRIES_IN] += invalid_entries;
			}
			else
				log::Info("Config file is empty.");

			log::level--;
		}
		log::level--;
		log::Info("Reading configs complete, {} valid configs found, {} invalid. {} valid entries found, {} invalid.",
				  infos_[InfoType::CONFIGS_V],
				  infos_[InfoType::CONFIGS_IN],
				  infos_[InfoType::ENTRIES_V],
				  infos_[InfoType::ENTRIES_IN]);
		log::Header();
	}

	inline bool Manipulator::addIfKeyIs(const std::string& key, const std::string& entry, const EntryType::EntryType type, int& valid, int& invalid)
	{
		if(key == keywords[type])
		{
			if(debug_mode_)
			{
				log::Info("Processing entry: {}.", entry);
				log::level++;
			}
			if((add_callbacks_[type])(entry))
			{
				infos_[InfoType::ENTRIES_V]++;
				if(debug_mode_)
					log::level--;
				valid++;
				return true;
			}
			else
			{
				infos_[InfoType::ENTRIES_IN]++;
				if(debug_mode_)
					log::level--;
				invalid++;
				return true;
			}
		}
		return false;
	}

	inline void Manipulator::addPlants()
	{
		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::Header("PLANTS"sv);
			log::level++;
		}
		for(auto& [seed, plant] : plants_)
		{
			if(lists_[FormListType::SEED]->HasForm(seed))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Seed"sv, seed);
				infos_[InfoType::PLANTS_DUP]++;
				continue;
			}

			if(lists_[FormListType::PLANT]->HasForm(plant))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Plant"sv, plant);
				infos_[InfoType::PLANTS_DUP]++;
				continue;
			}

			lists_[FormListType::SEED]->AddForm(seed);
			lists_[FormListType::PLANT]->AddForm(plant);
			infos_[InfoType::PLANTS_ADD]++;
			if(debug_mode_)
				log::AddedPair("Seed", seed, "Plant", plant);
		}
		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::level--;
			log::TotalAdded("Plants", infos_[InfoType::PLANTS_ADD], infos_[InfoType::PLANTS_DUP]);
			log::Header();
		}
	}

	inline void Manipulator::addKidsToys()
	{
		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::Header("BOY'S TOYS"sv);
			log::level++;
		}
		for(const auto& toy : boy_toys_)
		{
			if(lists_[FormListType::BTOYS]->HasForm(toy))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Boy's Toy"sv, toy);
				infos_[InfoType::BOY_TOYS_DUP]++;
				continue;
			}

			lists_[FormListType::BTOYS]->AddForm(toy);
			infos_[InfoType::B_TOYS]++;
			if(debug_mode_)
				log::Added("Boy's Toy", toy);
		}

		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::level--;
			log::TotalAdded("Boy's Toys", infos_[InfoType::B_TOYS], infos_[InfoType::BOY_TOYS_DUP]);
			log::Header();

			log::Header("GIRL'S TOYS"sv);
			log::level++;
		}

		for(const auto& toy : girl_toys_)
		{
			if(lists_[FormListType::GTOYS]->HasForm(toy))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Girls's Toy"sv, toy);
				infos_[InfoType::GIRL_TOYS_DUP]++;
				continue;
			}

			lists_[FormListType::GTOYS]->AddForm(toy);
			infos_[InfoType::G_TOYS]++;
			if(debug_mode_)
				log::Added("Girl's Toy", toy);
		}

		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::level--;
			log::TotalAdded("Girl's Toys", infos_[InfoType::G_TOYS], infos_[InfoType::GIRL_TOYS_DUP]);
			log::Header();
		}
	}

	inline void Manipulator::addHairColors()
	{
		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::Header("HAIR COLORS"sv);
			log::level++;
		}
		for(const auto& color : hair_colors_)
		{
			if(lists_[FormListType::HAIRC]->HasForm(color))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Hair color"sv, color);
				infos_[InfoType::HAIRC_DUP]++;
				continue;
			}

			lists_[FormListType::HAIRC]->AddForm(color);
			infos_[InfoType::HAIRC]++;
			if(debug_mode_)
				log::Added("Hair color", color);
		}

		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::level--;
			log::TotalAdded("Hair colors", infos_[InfoType::HAIRC], infos_[InfoType::HAIRC_DUP]);
			log::Header();
		}
	}

	inline void Manipulator::addAtronachForgeRecipes()
	{
		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::Header("ATRONACH FORGE"sv);
			log::level++;
		}

		for(auto& [recipe, result] : atronach_forge_)
		{
			if(lists_[FormListType::AFREC]->HasForm(recipe))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Recipe"sv, recipe);
				infos_[InfoType::AFORG_DUP]++;
				continue;
			}

			if(lists_[FormListType::AFRES]->HasForm(result))
			{
				if(mode_ == OperatingMode::INITIALIZE)
					log::DuplicateWarn("Result"sv, result);
				infos_[InfoType::AFORG_DUP]++;
				continue;
			}

			lists_[FormListType::AFREC]->AddForm(recipe);
			lists_[FormListType::AFRES]->AddForm(result);
			infos_[InfoType::AFORG_ADD]++;
			if(debug_mode_)
				log::AddedPair("Recipe", recipe, "Result", result);
		}
		if(mode_ == OperatingMode::INITIALIZE)
		{
			log::level--;
			log::TotalAdded("Recipes", infos_[InfoType::AFORG_ADD], infos_[InfoType::AFORG_DUP]);
			log::Header();
		}
	}

	inline void Manipulator::Summary()
	{
		log::Header("SUMMARY"sv);
		log::Info("{} valid configs, {} invalid. {} total entries, {} valid, {} invalid.",
				  infos_[InfoType::CONFIGS_V],
				  infos_[InfoType::CONFIGS_IN],
				  infos_[InfoType::ENTRIES_V] + infos_[InfoType::ENTRIES_IN],
				  infos_[InfoType::ENTRIES_V],
				  infos_[InfoType::ENTRIES_IN]);
		log::Info("{} FormLists, {} valid, {} invalid. {} total Forms, {} unique, {} missing, {} duplicates.",
				  form_lists_.size() + infos_[InfoType::FLIST_MIS],
				  form_lists_.size(),
				  infos_[InfoType::FLIST_MIS],
				  infos_[InfoType::FORMS] + infos_[InfoType::FORMS_MISS],
				  infos_[InfoType::FORMS] - infos_[InfoType::PLANTS_DUP] - infos_[InfoType::BOY_TOYS_DUP] - infos_[InfoType::GIRL_TOYS_DUP] - infos_[InfoType::FORMS_DUP],
				  infos_[InfoType::FORMS_MISS],
				  infos_[InfoType::FORMS_DUP] + infos_[InfoType::PLANTS_DUP] + infos_[InfoType::BOY_TOYS_DUP] + infos_[InfoType::GIRL_TOYS_DUP]);
		log::Info("{} FromLists Aliases added, {} duplicates, {} not existing.", aliases_.size(), infos_[InfoType::ALIASES_DUP], infos_[InfoType::ALIASES_NE]);
		log::Info("{} Forms Groups added, {} duplicates, {} not existing.", groups_.size(), infos_[InfoType::GROUPS_DUP], infos_[InfoType::GROUPS_NE]);
		log::Info("{} new plants added, skipped {} duplicates.", infos_[InfoType::PLANTS_ADD], infos_[InfoType::PLANTS_DUP]);
		log::Info("{} new Boy's Toys added, skipped {} duplicates.", infos_[InfoType::B_TOYS], infos_[InfoType::BOY_TOYS_DUP]);
		log::Info("{} new Girl's Toys added, skipped {} duplicates.", infos_[InfoType::G_TOYS], infos_[InfoType::GIRL_TOYS_DUP]);
		log::Info("{} new Hair Colors added, skipped {} duplicates.", infos_[InfoType::HAIRC], infos_[InfoType::HAIRC_DUP]);
		log::Info("{} new Atronach Forge recipes added, skipped {} duplicates.", infos_[InfoType::AFORG_ADD], infos_[InfoType::AFORG_DUP]);
		log::Info("{} new Forms added to {} FormLists, skipped {} duplicates.", infos_[InfoType::FORMS_ADD], form_lists_.size(), infos_[InfoType::FORMS_DUP]);
		log::Info("{} new Mod Events added, skipped {} invalid.", infos_[InfoType::MODEV], infos_[InfoType::MODEV_INV]);
		log::Header(" ^_^ "sv);
	}

	inline void Manipulator::SetNewGameMode()
	{
		mode_ = OperatingMode::NEW_GAME;
	}

	inline void Manipulator::SetLoadGameMode()
	{
		mode_ = OperatingMode::LOAD_GAME;
	}

	inline EventManager& Manipulator::GetEventManager()
	{
		return event_manager_;
	}

	inline bool Manipulator::parseFormList(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			log::Error("Wrong FormList format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool found_destination = true;

		auto form_list_info = sections[0];
		std::vector<RE::BGSListForm*> form_lists;

		if(form_list_info.starts_with("#"))
		{
			form_list_info.erase(0, 1);
			if(aliases_.contains(form_list_info))
				form_lists = aliases_[form_list_info];
			else
			{
				log::Error("Unknown Alias: {}.", form_list_info);
				infos_[InfoType::ALIASES_NE]++;
				found_destination = false;
			}
		}
		else
		{
			const auto form_list = FindForm<RE::BGSListForm>(form_list_info);
			if(!form_list)
			{
				log::Error("Unable to find FormList: {}.", form_list_info);
				infos_[InfoType::FLIST_MIS]++;
				found_destination = false;
			}
			else
				form_lists.emplace_back(form_list);
		}

		const auto forms_info = sections[1];
		auto forms_sections = string::split(forms_info, ",");
		std::vector<RE::TESForm*> forms;
		int missing = 0;
		for(auto& fs : forms_sections)
			if(parseFormEntry(fs, forms) == -1)
				missing++;

		if(!found_destination)
			return false;

		infos_[InfoType::FORMS] += forms.size();
		infos_[InfoType::FORMS_MISS] += missing;

		for(auto& fl : form_lists)
		{
			if(debug_mode_)
				log::Info("Found FormList \"{}\" [{:X}], {} Forms, {} missing Forms.", fl->GetName(), fl->formID, forms.size(), missing);
			if(form_lists_.contains(fl))
				form_lists_[fl].insert(form_lists_[fl].end(), forms.begin(), forms.end());
			else
				form_lists_.emplace(std::piecewise_construct, std::forward_as_tuple(fl), std::forward_as_tuple(forms));
		}
		return true;
	}

	inline bool Manipulator::parsePlant(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			log::Error("Wrong Plant format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		const auto seed_info = sections[0];
		const auto seed = FindForm(seed_info);
		if(!seed)
		{
			log::Error("Unable to find seed: {}.", seed_info);
			infos_[InfoType::FORMS_MISS]++;
		}

		const auto plant_info = sections[1];
		const auto plant = FindForm(plant_info);
		if(!plant)
		{
			log::Error("Unable to find plant: {}.", plant_info);
			infos_[InfoType::FORMS_MISS]++;
		}

		if(!seed || !plant)
			return false;

		if(seed->GetFormType() != RE::FormType::Ingredient && seed->GetFormType() != RE::FormType::AlchemyItem && seed->GetFormType() != RE::FormType::Activator)
			log::Warn("{} type {:X} is not Ingredient, AlchemyItem or Activator.", seed_info, static_cast<int>(seed->GetFormType()));

		if(plant->GetFormType() != RE::FormType::Flora && plant->GetFormType() != RE::FormType::Tree && plant->GetFormType() != RE::FormType::Container && plant->GetFormType() != RE::FormType::Activator && plant->GetFormType() != RE::FormType::Misc)
			log::Warn("{} type {:X} is not Flora, Tree, Activator, Misc or Container.", plant_info, static_cast<int>(plant->GetFormType()));

		if(debug_mode_)
			log::Info("Found Seed \"{}\" [{:X}], Plant \"{}\" [{:X}].", seed->GetName(), seed->formID, plant->GetName(), plant->formID);

		infos_[InfoType::FORMS] += 2;
		plants_.emplace_back(seed, plant);
		return true;
	}

	inline bool Manipulator::parseBToys(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 1)
		{
			log::Error("Wrong Boy's Toys format. Expected 1 sections, got {}.", sections.size());
			return false;
		}

		const auto forms_info = sections[0];
		auto forms_sections = string::split(forms_info, ",");
		int amount = 0;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			if(const int res = parseFormEntry(fs, boy_toys_); res == -1)
				missing++;
			else if(res == 0)
				amount++;
		}

		if(debug_mode_)
			log::Info("Boy's Toys: found {} Forms, {} missing Forms.", amount, missing);
		infos_[InfoType::FORMS] += amount;
		infos_[InfoType::FORMS_MISS] += missing;

		return true;
	}

	inline bool Manipulator::parseGToys(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 1)
		{
			log::Error("Wrong Girl's Toys format. Expected 1 sections, got {}.", sections.size());
			return false;
		}

		const auto forms_info = sections[0];
		auto forms_sections = string::split(forms_info, ",");
		int amount = 0;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			if(const int res = parseFormEntry(fs, girl_toys_); res == -1)
				missing++;
			else if(res == 0)
				amount++;
		}
		if(debug_mode_)
			log::Info("Girl's Toys: found {} Forms, {} missing Forms.", amount, missing);
		infos_[InfoType::FORMS] += amount;
		infos_[InfoType::FORMS_MISS] += missing;

		return true;
	}

	inline bool Manipulator::parseAlias(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			log::Error("Wrong Alias format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool duplicate = false;
		const auto alias_info = sections[0];
		if(aliases_.contains(alias_info))
		{
			log::Error("Alias {} exists.", alias_info);
			infos_[InfoType::ALIASES_DUP]++;
			duplicate = true;
		}

		const auto form_lists_info = sections[1];
		const auto form_lists_sections = string::split(form_lists_info, ",");
		std::vector<RE::BGSListForm*> form_lists;
		int missing = 0;
		for(auto& fs : form_lists_sections)
		{
			auto form_list = FindForm<RE::BGSListForm>(fs);
			if(!form_list)
			{
				log::Error("Unable to find FormList: {} for Alias.", fs);
				missing++;
				continue;
			}
			form_lists.emplace_back(form_list);
		}

		if(duplicate)
		{
			log::Warn("Entry will be omitted due to incorrect Alias name.");
			return false;
		}

		if(form_lists.size() > 0)
		{
			aliases_.emplace(std::piecewise_construct, std::forward_as_tuple(alias_info), std::forward_as_tuple(form_lists));
			if(debug_mode_)
				log::Info("FormLists Alias \"{}\" added with {} FormsLists, {} missing FormLists.", alias_info, form_lists.size(), missing);
		}
		else
		{
			log::Info("FormLists Alias \"{}\" was omitted because it does not have valid Forms.", alias_info);
			return false;
		}

		return true;
	}

	inline bool Manipulator::parseGroup(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			log::Error("Wrong Group format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool duplicate = false;
		const auto group_info = sections[0];

		if(groups_.contains(group_info))
		{
			log::Error("Group {} exists..", group_info);
			infos_[InfoType::GROUPS_DUP]++;
			duplicate = true;
		}

		const auto forms_info = sections[1];
		const auto forms_sections = string::split(forms_info, ",");
		std::vector<RE::TESForm*> forms;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			auto form = FindForm(fs);
			if(!form)
			{
				log::Error("Unable to find Form: {} for Group.", fs);
				missing++;
				continue;
			}
			forms.emplace_back(form);
		}

		if(duplicate)
		{
			log::Warn("Entry will be omitted due to incorrect Group name.");
			return false;
		}

		if(forms.size() > 0)
		{
			groups_.emplace(std::piecewise_construct, std::forward_as_tuple(group_info), std::forward_as_tuple(forms));
			if(debug_mode_)
				log::Info("Forms Group \"{}\" added with {} Forms, {} missing Forms.", group_info, forms.size(), missing);
		}
		else
		{
			log::Info("Forms Group \"{}\" was omitted because it does not have valid Forms.", group_info);
			return false;
		}

		return true;
	}

	inline bool Manipulator::parseModEvent(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 3)
		{
			log::Error("Wrong FormList format. Expected 3 sections, got {}.", sections.size());
			infos_[InfoType::MODEV_INV]++;
			return false;
		}

		bool found_destination = true;

		const auto event_name = sections[0];
		if(event_name.empty())
		{
			log::Error("The event name is empty, skipping!");
			infos_[InfoType::MODEV_INV]++;
			return false;
		}

		if(ContainsNonAlpha(event_name))
		{
			log::Error("The event name: {}, can only contain letters, skipping!", event_name);
			infos_[InfoType::MODEV_INV]++;
			return false;
		}

		auto form_list_info = sections[1];
		std::vector<RE::BGSListForm*> form_lists;

		if(form_list_info.starts_with("#"))
		{
			form_list_info.erase(0, 1);
			if(aliases_.contains(form_list_info))
				form_lists = aliases_[form_list_info];
			else
			{
				log::Error("Unknown Alias: {}.", form_list_info);
				infos_[InfoType::ALIASES_NE]++;
				found_destination = false;
			}
		}
		else
		{
			const auto form_list = FindForm<RE::BGSListForm>(form_list_info);
			if(!form_list)
			{
				log::Error("Unable to find FormList: {}.", form_list_info);
				infos_[InfoType::FLIST_MIS]++;
				found_destination = false;
			}
			else
				form_lists.emplace_back(form_list);
		}

		const auto forms_info = sections[2];
		auto forms_sections = string::split(forms_info, ",");
		std::vector<RE::TESForm*> forms;
		int missing = 0;
		for(auto& fs : forms_sections)
			if(parseFormEntry(fs, forms) == -1)
				missing++;

		if(!found_destination)
			return false;

		infos_[InfoType::FORMS] += forms.size();
		infos_[InfoType::FORMS_MISS] += missing;

		if(form_lists.size() > 0 && forms.size() > 0)
		{
			auto& events = event_manager_.Events();
			if(!events.contains(event_name))
				events.emplace(event_name, FormListsData());

			FormListsData& mod_event_data = events[event_name];

			for(auto& fl : form_lists)
			{
				if(debug_mode_)
					log::Info("Mod Event: {} => found FormList \"{}\" [{:X}], {} Forms, {} missing Forms.",
							  event_name,
							  fl->GetName(),
							  fl->formID,
							  forms.size(),
							  missing);
				if(mod_event_data.contains(fl))
					mod_event_data[fl].insert(mod_event_data[fl].end(), forms.begin(), forms.end());
				else
					mod_event_data.emplace(std::piecewise_construct, std::forward_as_tuple(fl), std::forward_as_tuple(forms));
			}
			infos_[InfoType::MODEV]++;
		}
		else
		{
			log::Info("Mod Event {} do not have any valid FormLists or Forms, skipping.", event_name);
			infos_[InfoType::MODEV_INV]++;
			return false;
		}

		return true;
	}

	inline bool Manipulator::parseHairColors(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 1)
		{
			log::Error("Wrong Hair Color format. Expected 1 sections, got {}.", sections.size());
			return false;
		}

		const auto forms_info = sections[0];
		auto forms_sections = string::split(forms_info, ",");
		int amount = 0;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			if(const int res = parseFormEntry(fs, hair_colors_); res == -1)
				missing++;
			else if(res == 0)
				amount++;
		}
		if(debug_mode_)
			log::Info("Hair Colors: found {} Forms, {} missing Forms.", amount, missing);
		infos_[InfoType::FORMS] += amount;
		infos_[InfoType::FORMS_MISS] += missing;

		return true;
	}

	inline bool Manipulator::parseAtronachForge(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			log::Error("Wrong Atronach Forge format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		const auto recipe_info = sections[0];
		const auto recipe = FindForm(recipe_info);
		if(!recipe)
		{
			log::Error("Unable to find recipe: {}.", recipe_info);
			infos_[InfoType::FORMS_MISS]++;
		}

		const auto result_info = sections[1];
		const auto result = FindForm(result_info);
		if(!result)
		{
			log::Error("Unable to find result for recipe: {}.", result_info);
			infos_[InfoType::FORMS_MISS]++;
		}

		if(!recipe || !result)
			return false;

		if(debug_mode_)
			log::Info("Found Recipe \"{}\" [{:X}], Result \"{}\" [{:X}].", recipe->GetName(), recipe->formID, result->GetName(), result->formID);

		infos_[InfoType::FORMS] += 2;
		atronach_forge_.emplace_back(recipe, result);
		return true;
	}

	inline bool Manipulator::addFormToFormList(RE::BGSListForm*& list, RE::TESForm* form) const
	{
		if(list->HasForm(form))
		{
			if(mode_ == OperatingMode::INITIALIZE)
				log::DuplicateWarn("Form"sv, form);
			return false;
		}

		list->AddForm(form);
		log::Info("Form \"{}\" [{:X}]  added!", form->GetName(), form->formID);

		return true;
	}

	inline int Manipulator::parseFormEntry(std::string& entry, std::vector<RE::TESForm*>& forms)
	{
		if(entry.starts_with("#"))
		{
			entry.erase(0, 1);
			if(groups_.contains(entry))
				forms.insert(forms.end(), groups_[entry].begin(), groups_[entry].end());
			else
			{
				log::Error("Unknown Group: {}.", entry);
				infos_[InfoType::GROUPS_NE]++;
				return -2;
			}
		}
		else
		{
			auto form = FindForm(entry);
			if(!form)
			{
				log::Error("Unable to find Form: {}.", entry);
				return -1;
			}
			forms.emplace_back(form);
		}

		return 0;
	}

	inline Manipulator manipulator;
}
