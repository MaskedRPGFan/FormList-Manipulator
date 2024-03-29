#pragma once

#include "Utility/Types/FormType.hpp"
#include "Utility/Types/Types.hpp"
#include "Utility/Utility.hpp"

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
			 * \brief Finds FormLists whose use is simplified and config files.
			 */
			void FindAll();
			/**
			 * \brief Adds all Forms from config files.
			 */
			void AddAll();

			/**
			 * \brief Returns manager for Mod Events.
			 * \return Manager for Mod Events.
			 */
			MapModEvents& GetModEvents();

			/**
			 * \brief Sending a mod event to inform other mods that the FLM has completed its work.
			 */
			static void SendEventDone();

		private:
			std::array<int, ift::ALL> infos_{}; /* Store values for types of countable statistics.*/
			FormsLists lists_;                  /* FormLists from Skyrim for use in simplified entries. */

			const std::array<ParseEntryCallback, EntryType::ALL> add_callbacks_{
				std::bind(&Manipulator::parseAlias, this, std::placeholders::_1),                    /* Aliases for FormLists. */
				std::bind(&Manipulator::parseGroup, this, std::placeholders::_1),                    /* Groups for Forms. */
				std::bind(&Manipulator::parseCollection, this, std::placeholders::_1),               /* Collections for Forms with specific keyword. */
				std::bind(&Manipulator::parseFilter, this, std::placeholders::_1),                   /* Filters for Entries. */
				std::bind(&Manipulator::parseModEvent, this, std::placeholders::_1),                 /* Mod events. */
				std::bind(&Manipulator::parseFormList, this, std::placeholders::_1),                 /* FromList. */
				std::bind(&Manipulator::parsePlant, this, std::placeholders::_1),                    /* Plant. */
				std::bind(&Manipulator::parseBToys, this, std::placeholders::_1),                    /* Boy's toys. */
				std::bind(&Manipulator::parseGToys, this, std::placeholders::_1),                    /* Girl's toys. */
				std::bind(&Manipulator::parseHairColors, this, std::placeholders::_1),               /* Hair colors. */
				std::bind(&Manipulator::parseAtronachForge, this, std::placeholders::_1),            /* Atronach forge. */
				std::bind(&Manipulator::parseAtronachForgeSigil, this, std::placeholders::_1),       /* Atronach forge with Sigil Stone. */
				std::bind(&Manipulator::parseDragonbornSpiderCrafting, this, std::placeholders::_1), /* Dragonborn Spider Crafting. */
			};                                                                                       /* Functions used to parse entries. */

			StringMap<FormsLists> aliases_;     /* All valid Aliases. */
			MapForms groups_;                   /* All valid Groups. Share names with Collections. */
			MapForms collections_;              /* All valid Collections. Share names with Groups. */
			MapModEvents mod_events_;           /* All valid Forms with ModEvents. */
			StringMap<bool> filters_;           /* All valid Filters. */
			FormListsData form_lists_;          /* All valid Forms for FormLists. */
			FormsPairs plants_;                 /* All valid Forms with seeds and plants. */
			Forms boy_toys_;                    /* All valid Forms with boy's toys. */
			Forms girl_toys_;                   /* All valid Forms with girl's toys. */
			Forms hair_colors_;                 /* All valid Forms with hair colors. */
			FormsPairs atronach_forge_;         /* All valid Forms with recipes and results for Atronach Forge. */
			FormsPairs atronach_sigil_forge_;   /* All valid Forms with recipes and results for Atronach Forge with Sigil. */
			FormsPairs dragon_spider_crafting_; /* All valid Forms with recipes and results for Dragonborn Spider Crafting. */
			CollectionData collections_data_;   /* All valid data for Collections. */
			MapKeywords keywords_cache_;        /* All valid keywords. */

			/* All valid Collections names for FormTypes. */
			StringMapSet collections_form_types_;

			/**
			 * \brief Clears data related to added game forms.
			 */
			void clearDataInfo();
			/**
			 * \brief Generates summary for config files.
			 */
			void summary();
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
			 * \return                      - True if the key is valid.
			 */
			bool addIfKeyIs(const std::string& key, const std::string& entry, EntryType::EntryType type);
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
			 * \brief Adds the correct pairs of recipes and results with Sigil Stone to the game.
			 */
			void addAtronachForgeSigilRecipes();
			/**
			 * \brief Adds the correct pairs of recipes and results for Dragonborn Spider Crafting to the game.
			 */
			void addDragonbornSpiderCrafting();
			/**
			 * \brief Adds forms to the game.
			 * \param header                    - Header of Forms that are added.
			 * \param name                      - Name of Forms that are added.
			 * \param forms                     - Vector of Forms to add.
			 * \param formType                  - Type of Forms that are added.
			 * \param infos                     - The type of information referring to the type of added and duplicated forms, is used to count correctly added/duplicated forms.
			 */
			void addForms(const std::string_view header, const std::string_view name, const Forms& forms, const Flt formType, InfoTPair infos);
			/**
			 * \brief Adds pair of forms to the game.
			 * \param header                    - Header of Forms that are added.
			 * \param names                     - Name of Forms that are added.
			 * \param forms                     - A vector of form pairs to add.
			 * \param formTypes                 - Forms pair types that are added.
			 * \param infos                     - The type of information referring to the type of added and duplicated forms, is used to count correctly added/duplicated forms.
			 */
			void addFormPair(const std::string_view header, const StringViewPair& names, FormsPairs& forms, FltPair formTypes, InfoTPair infos);
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
			 * \brief Adds Collection to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Collection = NameForCollection|FormType|Keyword/s[|Filter]
			 * \return                          - True, if everything went fine.
			 */
			bool parseCollection(const std::string& entry);
			/**
			 * \brief Adds Forms to collections of specific type (Armor, Weapon, etc) based on tags.
			 * \tparam T                        - Class of collection type (RE::TESObjectARMO, RE::TESObjectWEAP, etc).
			 * \param formType                  - Collection type (Armor, Weapon, etc).
			 * \return 
			 */
			template<class T>
			bool addParsedCollection(std::string_view formType);
			/**
			 * \brief Adds Forms to collections based on tags.
			 * \return                          - True, if all collections were created successfully.
			 */
			bool addAllParsedCollections();
			/**
			 * \brief Adds Filter to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format NameFilter|+/-Plugin, +/-Plugin, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool parseFilter(const std::string& entry);
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
			 * \brief Adds recipe and result to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Recipe|Result.
			 * \return                          - True, if everything went fine.
			 */
			bool parseAtronachForgeSigil(const std::string& entry);
			/**
			 * \brief Adds recipe and result to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Recipe|Result.
			 * \return                          - True, if everything went fine.
			 */
			bool parseDragonbornSpiderCrafting(const std::string& entry);
			/**
			 * \brief Adds recipe and result to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Form, Form, #Group, etc.
			 * \param entryName                 - Name of the entry.
			 * \param list                      - The list to which the correct Forms will be added.
			 * \return                          - True, if everything went fine.
			 */
			bool parseList(const std::string entry, std::string_view entryName, Forms& list);
			/**
			 * \brief Adds recipe and result to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Recipe|Result.
			 * \param names                     - Names of: the entry, first pair element, second pair element.
			 * \param list                      - The list to which the correct pair will be added.
			 * \param plantTypesWarn            - If True, checks pair form types for seed and plant.
			 * \return                          - True, if everything went fine.
			 */
			bool parsePair(const std::string& entry, const PairEntryNames& names, FormsPairs& list, bool plantTypesWarn = false);
			/**
			 * \brief Parse form entry.
			 * \param entry                 - Entry to parse.
			 * \param forms                 - Forms vector, where the found forms will be added.
			 * \return                      - 0 if the entry is valid, -1 if the form is missing, -2 if the group is missing.
			 */
			int parseFormEntry(std::string& entry, Forms& forms);
			/**
			 * \brief Adds From to FormList. Duplicates are omitted.
			 * \param list                      - FromList where Form will be added.
			 * \param form                      - Form to add.
			 * \return                          - True, if everything went fine.
			 */
			bool addFormToFormList(RE::BGSListForm*& list, RE::TESForm* form) const;
			/**
			 * \brief Evaluate Filter.
			 * \param filter                    - Filter to evaluate in format: #FilterName or +/-ESP[&+-ESP], +/-ESP[&+-ESP], itd.
			 * \return                          - 1, if Filter meet criteria, 0 if invalid, -1 if did not meet criteria.
			 */
			inline int evaluateFilter(const std::string& filter);
	};

	inline Manipulator::Manipulator()
	{
		infos_.fill(0);
	}

	inline void Manipulator::FindAll()
	{
		findLists();
		findConfigs();
	}

	inline void Manipulator::AddAll()
	{
		clearDataInfo();
		addPlants();
		addKidsToys();
		addHairColors();
		addAtronachForgeRecipes();
		addAtronachForgeSigilRecipes();
		auto [added, duplicates] = AddGeneric(form_lists_);
		infos_[ift::FORMS_ADD] += added;
		infos_[ift::FORMS_DUP] += duplicates;
		summary();
	}

	inline MapModEvents& Manipulator::GetModEvents()
	{
		return mod_events_;
	}

	inline void Manipulator::SendEventDone()
	{
		const SKSE::ModCallbackEvent mod_event{ "FLM_SetupDone", {}, 0.0f, nullptr };
		SKSE::GetModCallbackEventSource()->SendEvent(&mod_event);
	}

	inline void Manipulator::clearDataInfo()
	{
		infos_[ift::FORMS_ADD] = 0;
		infos_[ift::FORMS_DUP] = 0;

		infos_[ift::PLANTS_ADD] = 0;
		infos_[ift::PLANTS_DUP] = 0;

		infos_[ift::B_TOYS] = 0;
		infos_[ift::B_TOYS_DUP] = 0;

		infos_[ift::G_TOYS] = 0;
		infos_[ift::G_TOYS_DUP] = 0;

		infos_[ift::HAIRC] = 0;
		infos_[ift::HAIRC_DUP] = 0;

		infos_[ift::AFORG_ADD] = 0;
		infos_[ift::AFORG_DUP] = 0;

		infos_[ift::ASFRG_ADD] = 0;
		infos_[ift::ASFRG_DUP] = 0;

		infos_[ift::DSREC_ADD] = 0;
		infos_[ift::DSREC_DUP] = 0;
	}

	inline void Manipulator::findLists()
	{
		for(int type = 0; type != FormListType::ALL; type++)
		{
			lists_.emplace_back(FindForm<RE::BGSListForm>(FormListType::editor_id[type]));
			if(lists_.back() == nullptr)
				log::Error("Error: unable to find list: {}.", FormListType::editor_id[type]);
		}
	}

	inline void Manipulator::findConfigs()
	{
		const std::filesystem::directory_entry debug_mode_toggle(R"(Data\FormListManipulator_DEBUG.ini)");
		const std::filesystem::directory_entry debug_mode_toggle1(R"(Data\FLM\FormListManipulator_DEBUG.ini)");
		const std::filesystem::directory_entry debug_mode_toggle2(R"(Data\SKSE\Plugins\FormListManipulator_DEBUG.ini)");
		if(debug_mode_toggle.exists() || debug_mode_toggle1.exists() || debug_mode_toggle2.exists())
		{
			log::Header("DEBUG MODE ENABLED"sv);
			log::debug_mode = true;
		}

		log::Header("Looking for configs"sv);
		Strings configs = clib_util::distribution::get_configs(R"(Data\)", "_FLM"sv);

		if(auto constexpr folder_flm = R"(Data\FLM)"; std::filesystem::directory_entry(folder_flm).exists())
			for(const auto iterator = std::filesystem::directory_iterator(folder_flm); const auto& entry : iterator)
				if(entry.exists() && !entry.path().empty() && entry.path().extension() == ".ini"sv)
				{
					if(entry.path().string() == "FormListManipulator_DEBUG.ini"sv)
						continue;
					configs.push_back(entry.path().string());
				}

		if(configs.empty())
		{
			log::Warn("Configs not found!");
			return;
		}
		else
			log::Info("Found {} configs.", configs.size());

		if(log::debug_mode)
			log::Header("Looking for keywords"sv);

		LoadKeywords(keywords_cache_);

		if(log::debug_mode)
		{
			log::Info("Found {} keywords.", keywords_cache_.size());
            log::Header();
		}

		log::Header("Processing configs for filters & collections"sv);
		log::indent_level++;

		for(auto& path : configs)
		{
			CSimpleIniA ini;
			ini.SetUnicode();
			ini.SetMultiKey();

			if(const auto rc = ini.LoadFile(path.c_str()); rc < 0)
			{
				log::Error("Can't read ini {}.", path);
				continue;
			}


			log::Info("Processing {}...", path);
			log::indent_level++;

			if(auto values = ini.GetSection(""); values)
			{
				int valid_entries = infos_[ift::ENTRIES_V];    /* How many valid entries is. */
				int invalid_entries = infos_[ift::ENTRIES_IN]; /* How many invalid entries is. */
				int filtered_out = infos_[ift::ENTRIES_FO];    /* How many entries did not meet criteria. */

				// Parse Filters first.
				for(auto& [key, entry] : *values)
				{
					std::string sanitized_entry = Sanitize(entry);
					std::string lowercase_key = key.pItem;
					ToLower(lowercase_key);

					if(addIfKeyIs(lowercase_key, sanitized_entry, EntryType::FILTR))
						continue;
				}

				// Parse Collections next.
				for(auto& [key, entry] : *values)
				{
					std::string sanitized_entry = Sanitize(entry);
					std::string lowercase_key = key.pItem;
					ToLower(lowercase_key);

					if(addIfKeyIs(lowercase_key, sanitized_entry, EntryType::COLLE))
						continue;
				}

				valid_entries = infos_[ift::ENTRIES_V] - valid_entries;
				invalid_entries = infos_[ift::ENTRIES_IN] - invalid_entries;
				filtered_out = infos_[ift::ENTRIES_FO] - filtered_out;
				log::Info("Finished, {} valid entries found, {} invalid, {} filtered out.", valid_entries, invalid_entries, filtered_out);
			}
			else
				log::Info("Config file is empty.");

			log::indent_level--;
		}

		log::indent_level--;
        log::Header();

		if(addAllParsedCollections())
		{
			if(log::debug_mode)
			{
                log::Header("Adding forms to collections");
				log::indent_level++;
				log::Info("Added {} Collections.", collections_.size());
				for(const auto& c : collections_)
					log::Info("Collection {} ==> forms: {}.", c.first, c.second.size());
				log::indent_level--;
                log::Header();
			}

		}
		else
			log::Error("Error during Collections adding.");

		log::Header("Processing configs"sv);
		log::indent_level++;

		for(auto& path : configs)
		{
			CSimpleIniA ini;
			ini.SetUnicode();
			ini.SetMultiKey();

			if(const auto rc = ini.LoadFile(path.c_str()); rc < 0)
			{
				log::Error("Can't read ini {}.", path);
				infos_[ift::CONFIGS_IN]++;
				continue;
			}

			infos_[ift::CONFIGS_V]++;

			log::Info("Processing {}...", path);
			log::indent_level++;

			if(auto values = ini.GetSection(""); values)
			{
				int valid_entries = infos_[ift::ENTRIES_V];    /* How many valid entries is. */
				int invalid_entries = infos_[ift::ENTRIES_IN]; /* How many invalid entries is. */
				int filtered_out = infos_[ift::ENTRIES_FO];    /* How many entries did not meet criteria. */

				// Parse Aliases and Groups next.
				for(auto& [key, entry] : *values)
				{
					std::string sanitized_entry = Sanitize(entry);
					std::string lowercase_key = key.pItem;
					ToLower(lowercase_key);

					if(addIfKeyIs(lowercase_key, sanitized_entry, EntryType::ALIAS))
						continue;

					if(addIfKeyIs(lowercase_key, sanitized_entry, EntryType::GROUP))
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

					for(int type = EntryType::MODEV; type != EntryType::ALL; type++)
						if(addIfKeyIs(lowercase_key, sanitized_entry, static_cast<EntryType::EntryType>(type)))
							break;
				}
				valid_entries = infos_[ift::ENTRIES_V] - valid_entries;
				invalid_entries = infos_[ift::ENTRIES_IN] - invalid_entries;
				filtered_out = infos_[ift::ENTRIES_FO] - filtered_out;
				log::Info("Finished, {} valid entries found, {} invalid, {} filtered out.", valid_entries, invalid_entries, filtered_out);
			}
			else
				log::Info("Config file is empty.");

			log::indent_level--;
		}
		log::indent_level--;
		log::Info("Reading configs complete, {} valid configs found, {} invalid. {} valid entries found, {} invalid, {} filtered out.",
				  infos_[ift::CONFIGS_V],
				  infos_[ift::CONFIGS_IN],
				  infos_[ift::ENTRIES_V],
				  infos_[ift::ENTRIES_IN],
				  infos_[ift::ENTRIES_FO]);
		log::Header();
	}

	inline bool Manipulator::addIfKeyIs(const std::string& key, const std::string& entry, const EntryType::EntryType type)
	{
		if(key == keywords[type])
		{
			if(log::debug_mode)
			{
				log::Info("Processing entry: {}.", entry);
				log::indent_level++;
			}
			if((add_callbacks_[type])(entry))
			{
				infos_[ift::ENTRIES_V]++;
				if(log::debug_mode)
					log::indent_level--;
				return true;
			}
			else
			{
				infos_[ift::ENTRIES_IN]++;
				if(log::debug_mode)
					log::indent_level--;
				return true;
			}
		}
		return false;
	}

	inline void Manipulator::addPlants()
	{
		addFormPair("PLANTS"sv, std::make_pair("Seed"sv, "Plant"sv), plants_, std::make_pair(FormListType::SEED, FormListType::PLANT), std::make_pair(ift::PLANTS_ADD, ift::PLANTS_DUP));
	}

	inline void Manipulator::addKidsToys()
	{
		addForms("BOY'S TOYS"sv, "Boy's Toy"sv, boy_toys_, FormListType::BTOYS, std::make_pair(ift::B_TOYS, ift::B_TOYS_DUP));
		addForms("GIRL'S TOYS"sv, "Girls's Toy"sv, girl_toys_, FormListType::GTOYS, std::make_pair(ift::G_TOYS, ift::G_TOYS_DUP));
	}

	inline void Manipulator::addHairColors()
	{
		addForms("HAIR COLORS"sv, "Hair Color"sv, hair_colors_, FormListType::HAIRC, std::make_pair(ift::HAIRC, ift::HAIRC_DUP));
	}

	inline void Manipulator::addAtronachForgeRecipes()
	{
		addFormPair("ATRONACH FORGE"sv, std::make_pair("Recipe"sv, "Result"sv), atronach_forge_, std::make_pair(FormListType::AFREC, FormListType::AFRES), std::make_pair(ift::AFORG_ADD, ift::AFORG_DUP));
	}

	inline void Manipulator::addAtronachForgeSigilRecipes()
	{
		addFormPair("ATRONACH FORGE WITH SIGIL STONE"sv, std::make_pair("Recipe"sv, "Result"sv), atronach_sigil_forge_, std::make_pair(FormListType::ASFRC, FormListType::ASFRS), std::make_pair(ift::ASFRG_ADD, ift::ASFRG_DUP));
	}

	inline void Manipulator::addDragonbornSpiderCrafting()
	{
		addFormPair("DRAGONBORN SPIDER CRAFTING"sv, std::make_pair("Recipe"sv, "Result"sv), dragon_spider_crafting_, std::make_pair(FormListType::DSREC, FormListType::DSRES), std::make_pair(ift::DSREC_ADD, ift::DSREC_DUP));
	}

	inline void Manipulator::addForms(const std::string_view header, const std::string_view name, const Forms& forms, const Flt formType, const InfoTPair infos)
	{
		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::Header(header);
			log::indent_level++;
		}
		for(const auto& form : forms)
		{
			if(lists_[formType]->HasForm(form))
			{
				if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
					log::DuplicateWarn(name, form);
				infos_[infos.second]++;
				continue;
			}

			lists_[formType]->AddForm(form);
			infos_[infos.first]++;
			if(log::debug_mode)
				log::Added(name, form);
		}

		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::indent_level--;
			log::TotalAdded(name, infos_[infos.first], infos_[infos.second]);
			log::Header();
		}
	}

	inline void Manipulator::addFormPair(const std::string_view header, const StringViewPair& names, FormsPairs& forms, const FltPair formTypes, const InfoTPair infos)
	{
		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::Header(header);
			log::indent_level++;
		}
		for(auto& [first_form, second_form] : forms)
		{
			if(lists_[formTypes.first]->HasForm(first_form))
			{
				if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
					log::DuplicateWarn(names.first, first_form);
				infos_[infos.second]++;
				continue;
			}

			if(lists_[formTypes.second]->HasForm(second_form))
			{
				if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
					log::DuplicateWarn(names.second, second_form);
				infos_[infos.second]++;
				continue;
			}

			lists_[formTypes.first]->AddForm(first_form);
			lists_[formTypes.second]->AddForm(second_form);
			infos_[infos.first]++;

			if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
				log::AddedPair(names.first, first_form, names.second, second_form);
		}
		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::indent_level--;
			log::TotalAdded(names.second, infos_[infos.first], infos_[infos.second]);
			log::Header();
		}
	}

	inline void Manipulator::summary()
	{
		const int total_added_forms = infos_[ift::FORMS_ADD] +
									  infos_[ift::PLANTS_ADD] +
									  infos_[ift::B_TOYS] +
									  infos_[ift::G_TOYS] +
									  infos_[ift::HAIRC] +
									  infos_[ift::AFORG_ADD] +
									  infos_[ift::ASFRG_ADD] +
									  infos_[ift::DSREC_ADD];
		const int total_dup_forms = infos_[ift::FORMS_DUP] +
									infos_[ift::PLANTS_DUP] +
									infos_[ift::B_TOYS_DUP] +
									infos_[ift::G_TOYS_DUP] +
									infos_[ift::HAIRC_DUP] +
									infos_[ift::AFORG_DUP] +
									infos_[ift::ASFRG_DUP] +
									infos_[ift::DSREC_DUP];
		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::Header("SUMMARY"sv);
			log::Info("{} valid configs, {} invalid. {} total entries, {} valid, {} invalid, {} filtered out.",
					  infos_[ift::CONFIGS_V],
					  infos_[ift::CONFIGS_IN],
					  infos_[ift::ENTRIES_V] + infos_[ift::ENTRIES_IN],
					  infos_[ift::ENTRIES_V],
					  infos_[ift::ENTRIES_IN],
					  infos_[ift::ENTRIES_FO]);
			log::Info("{} FormLists, {} valid, {} invalid. {} total Forms, {} unique, {} missing, {} duplicates.",
					  form_lists_.size() + infos_[ift::FLIST_MIS],
					  form_lists_.size(),
					  infos_[ift::FLIST_MIS],
					  infos_[ift::FORMS] + infos_[ift::FORMS_MISS],
					  infos_[ift::FORMS] - total_dup_forms,
					  infos_[ift::FORMS_MISS],
					  total_dup_forms);
			log::Info("{} Filters added, {} duplicates, {} not existing/invalid.", filters_.size(), infos_[ift::FILTERS_DUP], infos_[ift::FILTERS_NE]);
			log::Info("{} Forms Collections added, {} duplicates, {} not existing/invalid.", collections_.size(), infos_[ift::COLLE_DUP], infos_[ift::COLLE_NE]);
			log::Info("{} FromLists Aliases added, {} duplicates, {} not existing.", aliases_.size(), infos_[ift::ALIASES_DUP], infos_[ift::ALIASES_NE]);
			log::Info("{} Forms Groups added, {} duplicates, {} not existing/invalid.", groups_.size(), infos_[ift::GROUPS_DUP], infos_[ift::GROUPS_NE]);
			log::Info("{} new Mod Events added, skipped {} invalid.", infos_[ift::MODEV], infos_[ift::MODEV_INV]);
		}
		else if(log::operating_mode == OperatingMode::NEW_GAME)
		{
			log::Header();
			log::Header("NEW GAME - SYNCHRONIZES FORM LISTS"sv);
		}
		else if(log::operating_mode == OperatingMode::LOAD_GAME)
		{
			log::Header();
			log::Header("GAME LOADED - SYNCHRONIZES FORM LISTS"sv);
		}
		else
			return;

		log::Info("{} new plants added, skipped {} duplicates.", infos_[ift::PLANTS_ADD], infos_[ift::PLANTS_DUP]);
		log::Info("{} new Boy's Toys added, skipped {} duplicates.", infos_[ift::B_TOYS], infos_[ift::B_TOYS_DUP]);
		log::Info("{} new Girl's Toys added, skipped {} duplicates.", infos_[ift::G_TOYS], infos_[ift::G_TOYS_DUP]);
		log::Info("{} new Hair Colors added, skipped {} duplicates.", infos_[ift::HAIRC], infos_[ift::HAIRC_DUP]);
		log::Info("{} new Atronach Forge recipes added, skipped {} duplicates.", infos_[ift::AFORG_ADD], infos_[ift::AFORG_DUP]);
		log::Info("{} new Atronach Forge recipes with Sigil Stone added, skipped {} duplicates.", infos_[ift::ASFRG_ADD], infos_[ift::ASFRG_DUP]);
		log::Info("{} new Dragonborn Spider Crafting recipes added, skipped {} duplicates.", infos_[ift::DSREC_ADD], infos_[ift::DSREC_DUP]);
		log::Info("{} new Forms added to {} FormLists, skipped {} duplicates.", infos_[ift::FORMS_ADD], form_lists_.size(), infos_[ift::FORMS_DUP]);

		if(log::operating_mode != OperatingMode::INITIALIZE)
			log::Info("Total {} new Forms added, skipped {} duplicates.", total_added_forms, total_dup_forms);

		log::Header(" ^_^ "sv);
	}

	inline bool Manipulator::parseFormList(const std::string& entry)
	{
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 2 && sections.size() != 3)
		{
			log::Error("Wrong FormList format. Expected 2 or 3 sections, got {}.", sections.size());
			return false;
		}

		bool found_destination = true;

		if(sections.size() == 3)
			if(const auto res = evaluateFilter(sections[2]); res != 1)
				return res == 0 ? false : true;

		auto form_list_info = sections[0];
		FormsLists form_lists;

		if(form_list_info.starts_with("#"))
		{
			form_list_info.erase(0, 1);
			if(aliases_.contains(form_list_info))
				form_lists = aliases_[form_list_info];
			else
			{
				log::Error("Unknown Alias: {}.", form_list_info);
				infos_[ift::ALIASES_NE]++;
				found_destination = false;
			}
		}
		else
		{
			if(const auto form_list = FindForm<RE::BGSListForm>(form_list_info); !form_list)
			{
				log::Error("Unable to find FormList: {}.", form_list_info);
				infos_[ift::FLIST_MIS]++;
				found_destination = false;
			}
			else
				form_lists.emplace_back(form_list);
		}

		const auto& forms_info = sections[1];
		Strings forms_sections = string::split(forms_info, ",");
		Forms forms;
		int missing = 0;
		for(auto& fs : forms_sections)
			if(parseFormEntry(fs, forms) == -1)
				missing++;

		if(!found_destination)
			return false;

		infos_[ift::FORMS] += static_cast<int>(forms.size());
		infos_[ift::FORMS_MISS] += missing;

		for(auto& fl : form_lists)
		{
			if(log::debug_mode)
				log::Info("Found FormList {} \"{}\" [{:X}], {} Forms, {} missing Forms.", GetEditorId(fl), fl->GetName(), fl->formID, forms.size(), missing);
			if(form_lists_.contains(fl))
				form_lists_[fl].insert(form_lists_[fl].end(), forms.begin(), forms.end());
			else
				form_lists_.emplace(std::piecewise_construct, std::forward_as_tuple(fl), std::forward_as_tuple(forms));
		}
		return true;
	}

	inline bool Manipulator::parsePlant(const std::string& entry)
	{
		return parsePair(entry, std::make_tuple("Plant"sv, "Seed"sv, "Plant"sv), plants_, true);
	}

	inline bool Manipulator::parseBToys(const std::string& entry)
	{
		return parseList(entry, "Boy's Toys", boy_toys_);
	}

	inline bool Manipulator::parseGToys(const std::string& entry)
	{
		return parseList(entry, "Girl's Toys", girl_toys_);
	}

	inline bool Manipulator::parseAlias(const std::string& entry)
	{
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 2)
		{
			log::Error("Wrong Alias format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool duplicate = false;
		const auto& alias_info = sections[0];
		if(aliases_.contains(alias_info))
		{
			log::Error("Alias {} exists.", alias_info);
			infos_[ift::ALIASES_DUP]++;
			duplicate = true;
		}

		const auto& form_lists_info = sections[1];
		const Strings form_lists_sections = string::split(form_lists_info, ",");
		FormsLists form_lists;
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

		if(!form_lists.empty())
		{
			aliases_.emplace(std::piecewise_construct, std::forward_as_tuple(alias_info), std::forward_as_tuple(form_lists));
			if(log::debug_mode)
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
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 2)
		{
			log::Error("Wrong Group format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool duplicate = false;
		const auto& group_info = sections[0];

		if(groups_.contains(group_info))
		{
			log::Error("Group {} exists.", group_info);
			infos_[ift::GROUPS_DUP]++;
			duplicate = true;
		}

		const auto& forms_info = sections[1];
		const Strings forms_sections = string::split(forms_info, ",");
		Forms forms;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			if(fs.starts_with("*"))
			{
				std::string tmp = fs;
				tmp.erase(0, 1);
				if(const auto form_list = FindForm<RE::BGSListForm>(tmp); !form_list)
				{
					log::Error("Unable to find FormList: {}.", tmp);
					missing++;
				}
				else
				{
					for(auto form : form_list->forms)
						forms.emplace_back(form);
				}
			}
			else if(fs.starts_with("#"))
			{
				std::string tmp = fs;
				tmp.erase(0, 1);
				if(collections_.contains(tmp))
				{
					forms.insert(forms.end(), collections_[tmp].begin(), collections_[tmp].end());
				}
				else
				{
					log::Error("Unknown Collection: {}.", tmp);
					infos_[ift::COLLE_NE]++;
				}
			}
			else
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
		}

		if(duplicate)
		{
			log::Warn("Entry will be omitted due to incorrect Group name.");
			return false;
		}

		if(!forms.empty())
		{
			groups_.emplace(std::piecewise_construct, std::forward_as_tuple(group_info), std::forward_as_tuple(forms));
			if(log::debug_mode)
				log::Info("Forms Group \"{}\" added with {} Forms, {} missing Forms.", group_info, forms.size(), missing);
		}
		else
		{
			log::Info("Forms Group \"{}\" was omitted because it does not have valid Forms.", group_info);
			return false;
		}

		return true;
	}

	inline bool flm::Manipulator::parseCollection(const std::string& entry)
	{
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 3 && sections.size() != 4)
		{
			log::Error("Wrong Collection format. Expected 3 or 4 sections, got {}.", sections.size());
			return false;
		}

		const auto& name = sections[0];

		if(collections_.contains(name) || groups_.contains(name))
		{
			log::Error("Collection {} exists.", name);
			infos_[ift::COLLE_DUP]++;

			log::Warn("Entry will be omitted due to incorrect Collection name.");
			return false;
		}

		auto form_type = sections[1];
		ToLower(form_type);
		if(!FORM_TYPES.contains(form_type))
		{
			log::Error("Collection {} has not supported FormType {}.", name, form_type);
			infos_[ift::COLLE_NE]++;

			log::Warn("Entry will be omitted due to incorrect FormType name.");
			return false;
		}

		const auto& keywords_info = sections[2];
		for(const Strings keywords_list = string::split(keywords_info, ","); std::string keyword : keywords_list)
		{
			bool remove = false;
			if(keyword[0] == '-')
			{
				keyword.erase(0, 1);
				remove = true;
			}

            bool found = false;
            RE::BGSKeyword* form = nullptr;
            const auto& it = keywords_cache_.find(keyword);
			found = (it != keywords_cache_.end());

            if(found)
	            form = it->second;
			else
                found = (form = FindForm<RE::BGSKeyword>(keyword))!= nullptr;

			if(!found)
			{
				log::Error("Keyword {} do not exist!", keyword);
				if(collections_data_.contains(name))
					collections_data_.erase(name);
				return false;
			}
			else
			{
				if(remove)
					collections_data_[name].second.push_back(form);
				else
					collections_data_[name].first.push_back(form);
			}
		}

		if(sections.size() == 4)
			if(const auto res = evaluateFilter(sections[3]); res != 1)
				return res == 0 ? false : true;

		collections_form_types_[form_type].emplace(name);
		collections_[name] = {};
		if(log::debug_mode)
			log::Info("[{}-{}] Collection \"{}\" with [+]{} [-]{} keywords added.", form_type, collections_form_types_[form_type].size(), name, collections_data_[name].first.size(), collections_data_[name].second.size());

		return true;
	}

	inline bool Manipulator::addAllParsedCollections()
	{
		return addParsedCollection<RE::TESObjectARMO>("armor"sv) &&
			   addParsedCollection<RE::TESObjectWEAP>("weapon"sv) &&
			   addParsedCollection<RE::TESAmmo>("ammo"sv) &&
			   addParsedCollection<RE::TESObjectARMO>("magiceffect"sv) &&
			   addParsedCollection<RE::AlchemyItem>("alchemyitem"sv) &&
			   addParsedCollection<RE::ScrollItem>("scroll"sv) &&
			   addParsedCollection<RE::BGSLocation>("location"sv) &&
			   addParsedCollection<RE::IngredientItem>("ingredient"sv) &&
			   addParsedCollection<RE::TESObjectBOOK>("book"sv) &&
			   addParsedCollection<RE::TESObjectMISC>("misc"sv) &&
			   addParsedCollection<RE::TESKey>("key"sv) &&
			   addParsedCollection<RE::TESSoulGem>("soulgem"sv) &&
			   addParsedCollection<RE::TESObjectACTI>("activator"sv) &&
			   addParsedCollection<RE::TESFlora>("flora"sv) &&
			   addParsedCollection<RE::TESFurniture>("furniture"sv) &&
			   addParsedCollection<RE::TESRace>("race"sv) &&
			   addParsedCollection<RE::BGSTalkingActivator>("talkingactivator"sv) &&
			   addParsedCollection<RE::EnchantmentItem>("enchantment"sv) &&
			   addParsedCollection<RE::TESNPC>("npc"sv) &&
			   addParsedCollection<RE::SpellItem>("spell"sv);
	}

	template<class T>
	inline bool Manipulator::addParsedCollection(std::string_view formType)
	{
		static const auto data_handler = RE::TESDataHandler::GetSingleton();
		if(!data_handler)
			return false;

		const auto it = collections_form_types_.find(formType);
		if(log::debug_mode)
		{
			if(it != collections_form_types_.end())
				log::Info("{} {} collections found.", it->second.size(), formType);
			else if(log::debug_mode)
				log::Info("{} collections do not exist in any ini file.", formType);
		}

		if(it == collections_form_types_.end())
			return true;

		for(RE::TESForm* form : data_handler->GetFormArray<T>())
		{
			if(!form)
				continue;

			const auto bgs_keyword_form = form->As<RE::BGSKeywordForm>();
			Set<RE::BGSKeyword*> form_keywords = { bgs_keyword_form->keywords, bgs_keyword_form->keywords + bgs_keyword_form->numKeywords };

			// if(log::debug_mode)
			// 	log::Info("[{}] {} >>>> {}", GetEditorId(form), form->GetName(), form_keywords.size());

			if(form_keywords.empty())
				continue;

			for(const auto& [name, filter_keywords] : collections_data_)
			{
				// if(log::debug_mode)
				// {
				// 	log::Info("Collection {} [{} | {}]", name, filter_keywords.first.size(), filter_keywords.second.size());
				// }

				bool add = true;

				if(!filter_keywords.first.empty())
					for(const auto& k : filter_keywords.first)
						if(!form_keywords.contains(k))
						{
							add = false;
							break;
						}

				if(!filter_keywords.second.empty())
					for(const auto& k : filter_keywords.second)
						if(form_keywords.contains(k))
						{
							add = false;
							break;
						}

				if(add)
				{
					if(log::debug_mode)
						log::Info("Collection {} <== [{}] {}", name, GetEditorId(form), form->GetName());

					collections_[name].push_back(form);
				}
			}
		}

		return true;
	}

	inline bool Manipulator::parseFilter(const std::string& entry)
	{
		const Strings sections = string::split(SanitizeFilter(entry), "|"sv);
		if(sections.size() != 2)
		{
			log::Error("Wrong Filter format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		const std::string& filter_info = sections[0];

		if(filters_.contains(filter_info))
		{
			log::Error("Filter {} exists.", filter_info);
			infos_[ift::FILTERS_DUP]++;
			log::Warn("Filter {} will be omitted due to incorrect Filter name.", filter_info);
			return false;
		}

		if(const int meet_criteria = EvaluateFilter(sections[1]); meet_criteria == 1 || meet_criteria == -1)
		{
			filters_.emplace(std::piecewise_construct, std::forward_as_tuple(filter_info), std::forward_as_tuple(meet_criteria == 1 ? true : false));
			if(log::debug_mode)
				log::Info("Filter \"{}\" added with status {}.", filter_info, meet_criteria == 1 ? true : false);
		}
		else
		{
			infos_[ift::FILTERS_NE]++;
			log::Warn("Filter \"{}\" was omitted because it is invalid.", filter_info);
			return false;
		}

		return true;
	}

	inline bool Manipulator::parseModEvent(const std::string& entry)
	{
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 3)
		{
			log::Error("Wrong FormList format. Expected 3 sections, got {}.", sections.size());
			infos_[ift::MODEV_INV]++;
			return false;
		}

		bool found_destination = true;

		const auto& event_name = sections[0];
		if(event_name.empty())
		{
			log::Error("The event name is empty, skipping!");
			infos_[ift::MODEV_INV]++;
			return false;
		}

		if(ContainsNonAlpha(event_name))
		{
			log::Error("The event name: {}, can only contain letters, skipping!", event_name);
			infos_[ift::MODEV_INV]++;
			return false;
		}

		auto form_list_info = sections[1];
		FormsLists form_lists;

		if(form_list_info.starts_with("#"))
		{
			form_list_info.erase(0, 1);
			if(aliases_.contains(form_list_info))
				form_lists = aliases_[form_list_info];
			else
			{
				log::Error("Unknown Alias: {}.", form_list_info);
				infos_[ift::ALIASES_NE]++;
				found_destination = false;
			}
		}
		else
		{
			if(const auto form_list = FindForm<RE::BGSListForm>(form_list_info); !form_list)
			{
				log::Error("Unable to find FormList: {}.", form_list_info);
				infos_[ift::FLIST_MIS]++;
				found_destination = false;
			}
			else
				form_lists.emplace_back(form_list);
		}

		const auto& forms_info = sections[2];
		Strings forms_sections = string::split(forms_info, ",");
		Forms forms;
		int missing = 0;
		for(auto& fs : forms_sections)
			if(parseFormEntry(fs, forms) == -1)
				missing++;

		if(!found_destination)
			return false;

		infos_[ift::FORMS] += static_cast<int>(forms.size());
		infos_[ift::FORMS_MISS] += missing;

		if(!form_lists.empty() && !forms.empty())
		{
			if(!mod_events_.contains(event_name))
				mod_events_.emplace(event_name, FormListsData());

			FormListsData& mod_event_data = mod_events_[event_name];

			for(auto& fl : form_lists)
			{
				if(log::debug_mode)
					log::Info("Mod Event: {} => found FormList {} \"{}\" [{:X}], {} Forms, {} missing Forms.",
							  event_name,
							  GetEditorId(fl),
							  fl->GetName(),
							  fl->formID,
							  forms.size(),
							  missing);
				if(mod_event_data.contains(fl))
					mod_event_data[fl].insert(mod_event_data[fl].end(), forms.begin(), forms.end());
				else
					mod_event_data.emplace(std::piecewise_construct, std::forward_as_tuple(fl), std::forward_as_tuple(forms));
			}
			infos_[ift::MODEV]++;
		}
		else
		{
			log::Info("Mod Event {} do not have any valid FormLists or Forms, skipping.", event_name);
			infos_[ift::MODEV_INV]++;
			return false;
		}

		return true;
	}

	inline bool Manipulator::parseHairColors(const std::string& entry)
	{
		return parseList(entry, "Hair Colors", hair_colors_);
	}

	inline bool Manipulator::parseAtronachForge(const std::string& entry)
	{
		return parsePair(entry, std::make_tuple("Atronach Forge"sv, "Recipe"sv, "Result"sv), atronach_forge_);
	}

	inline bool Manipulator::parseAtronachForgeSigil(const std::string& entry)
	{
		return parsePair(entry, std::make_tuple("Atronach Forge with Sigil Stone"sv, "Recipe"sv, "Result"sv), atronach_sigil_forge_);
	}

	inline bool Manipulator::parseDragonbornSpiderCrafting(const std::string& entry)
	{
		return parsePair(entry, std::make_tuple("Dragonborn Spider Crafting"sv, "Recipe"sv, "Result"sv), dragon_spider_crafting_);
	}

	inline bool Manipulator::parseList(const std::string entry, const std::string_view entryName, Forms& list)
	{
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 1 && sections.size() != 2)
		{
			log::Error("Wrong {} format. Expected 1 or 2 sections, got {}.", entryName, sections.size());
			return false;
		}

		if(sections.size() == 2)
			if(const auto res = evaluateFilter(sections[1]); res != 1)
				return res == 0 ? false : true;

		const auto& forms_info = sections[0];
		Strings forms_sections = string::split(forms_info, ",");
		int amount = 0;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			if(const int res = parseFormEntry(fs, list); res == -1)
				missing++;
			else if(res == 0)
				amount++;
		}
		if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
			log::Info("{}: found {} Forms, {} missing Forms.", entryName, amount, missing);
		infos_[ift::FORMS] += amount;
		infos_[ift::FORMS_MISS] += missing;

		return true;
	}

	inline bool Manipulator::parsePair(const std::string& entry, const PairEntryNames& names, FormsPairs& list, const bool plantTypesWarn)
	{
		const Strings sections = string::split(entry, "|"sv);
		if(sections.size() != 2 && sections.size() != 3)
		{
			log::Error("Wrong {} format. Expected 2 or 3 sections, got {}.", std::get<0>(names), sections.size());
			return false;
		}

		if(sections.size() == 3)
			if(const auto res = evaluateFilter(sections[2]); res != 1)
				return res == 0 ? false : true;

		const auto& first_info = sections[0];
		const auto first = FindForm(first_info);
		if(!first)
		{
			log::Error("Unable to find {}: {}.", std::get<1>(names), first_info);
			infos_[ift::FORMS_MISS]++;
		}

		const auto& second_info = sections[1];
		const auto second = FindForm(second_info);
		if(!second)
		{
			log::Error("Unable to find {}: {}.", std::get<2>(names), second_info);
			infos_[ift::FORMS_MISS]++;
		}

		if(!first || !second)
			return false;

		if(log::operating_mode == OperatingMode::INITIALIZE && plantTypesWarn)
		{
			if(first->GetFormType() != RE::FormType::Ingredient && first->GetFormType() != RE::FormType::AlchemyItem && first->GetFormType() != RE::FormType::Activator)
				log::Warn("{} type {:X} is not Ingredient, AlchemyItem or Activator.", first_info, static_cast<int>(first->GetFormType()));

			if(second->GetFormType() != RE::FormType::Flora && second->GetFormType() != RE::FormType::Tree && second->GetFormType() != RE::FormType::Container && second->GetFormType() != RE::FormType::Activator && second->GetFormType() != RE::FormType::Misc)
				log::Warn("{} type {:X} is not Flora, Tree, Activator, Misc or Container.", second_info, static_cast<int>(second->GetFormType()));
		}

		if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
			log::Info(R"(Found {} "{}" [{:X}], {} "{}" [{:X}].)", std::get<1>(names), first->GetName(), first->formID, std::get<2>(names), second->GetName(), second->formID);

		infos_[ift::FORMS] += 2;
		list.emplace_back(first, second);
		return true;
	}

	inline bool Manipulator::addFormToFormList(RE::BGSListForm*& list, RE::TESForm* form) const
	{
		if(list->HasForm(form))
		{
			if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
				log::DuplicateWarn("Form"sv, form);
			return false;
		}

		list->AddForm(form);
		log::Info("Form {} \"{}\" [{:X}]  added!", GetEditorId(form), form->GetName(), form->formID);

		return true;
	}

	inline int Manipulator::evaluateFilter(const std::string& filter)
	{
		int meet_criteria;
		if(filter[0] == '#')
		{
			auto filter_name = filter.substr(1);
			ToLower(filter_name);
			if(filters_.contains(filter_name))
				meet_criteria = filters_[filter_name] ? 1 : -1;
			else
			{
				log::Error("Filter {} was not found!", filter_name);
				meet_criteria = 0;
			}
		}
		else
			meet_criteria = EvaluateFilter(SanitizeFilter(filter));

		if(meet_criteria == 1)
		{
			if(log::debug_mode)
				log::Info("Filter \"{}\" is valid", filter);
		}
		else if(meet_criteria == -1)
		{
			if(log::debug_mode)
				log::Info("Filter \"{}\" does not meet the conditions.", filter);
			infos_[ift::ENTRIES_FO]++;
		}
		else if(meet_criteria == 0)
		{
			infos_[ift::FILTERS_NE]++;
			log::Warn("Filter \"{}\" was omitted because it is invalid.", filter);
		}

		return meet_criteria;
	}

	inline int Manipulator::parseFormEntry(std::string& entry, Forms& forms)
	{
		if(entry.starts_with("#"))
		{
			bool not_found = true;
			entry.erase(0, 1);
			if(groups_.contains(entry))
			{
				forms.insert(forms.end(), groups_[entry].begin(), groups_[entry].end());
				not_found = false;
			}

			if(collections_.contains(entry))
			{
				forms.insert(forms.end(), collections_[entry].begin(), collections_[entry].end());
				not_found = false;
			}

			if(not_found)
			{
				log::Error("Unknown Group/Collection: {}.", entry);
				infos_[ift::GROUPS_NE]++;
				infos_[ift::COLLE_NE]++;
				return -2;
			}
		}
		else if(entry.starts_with("*"))
		{
			entry.erase(0, 1);
			if(const auto form_list = FindForm<RE::BGSListForm>(entry); !form_list)
			{
				log::Error("Unable to find FormList: {}.", entry);
				return -1;
			}
			else
			{
				for(auto form : form_list->forms)
					forms.emplace_back(form);
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
