#pragma once

#include "Utility.hpp"

namespace flm
{
	/**
	 * \brief The main class that manages the mechanism for manipulating Forms.
	 */
	class Manipulator
	{
		public:
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
			 * \brief Finds all FormLists whose use is simplified.
			 */
			void FindLists();
			/**
			 * \brief Finds all config files.
			 */
			void FindConfigs();
			/**
			 * \brief Reads plants from configuration files and adds the correct ones to internal structures.
			 */
			void AddPlants();
			/**
			 * \brief Reads toys from configuration files and adds the correct ones to internal structures.
			 */
			void AddToys();
			/**
			 * \brief Reads general forms from configuration files and adds the correct ones to internal structures.
			 */
			void AddToFormLists();
			/**
			 * \brief Generates summary for config files.
			 */
			void Summary();

			bool reload = false;

		private:
			std::vector<std::string_view> keywords_ = { "formlist"sv, "plant"sv, "btoys"sv, "gtoys"sv, "alias"sv, "group"sv }; /** Keywords for usage in the configuration files. */

			bool debug_mode_ = false;                   /** Mode for more detailed information. */
			RE::BGSListForm* seeds_list_ = nullptr;     /** Forms with seeds to plant. */
			RE::BGSListForm* plants_list_ = nullptr;    /** Forms with plants to grow. */
			RE::BGSListForm* boy_toys_list_ = nullptr;  /** Forms with boy's toys. */
			RE::BGSListForm* girl_toys_list_ = nullptr; /** Forms with girl's toys. */

			std::map<std::string, std::vector<RE::BGSListForm*>> aliases_;     /** All valid Aliases. */
			std::map<std::string, std::vector<RE::TESForm*>> groups_;          /** All valid Groups. */
			std::map<RE::BGSListForm*, std::vector<RE::TESForm*>> form_lists_; /** All valid Forms for FormLists. */
			std::vector<std::pair<RE::TESForm*, RE::TESForm*>> plants_;        /** All valid Forms with seeds and plants. */
			std::vector<RE::TESForm*> boy_toys_;                               /** All valid Forms with boy's toys. */
			std::vector<RE::TESForm*> girl_toys_;                              /** All valid Forms with girl's toys. */

			int total_valid_entries_ = 0;      /** How many valid entries is. */
			int total_invalid_entries_ = 0;    /** How many invalid entries is. */
			int valid_configs_ = 0;            /** How many valid configs is. */
			int invalid_configs_ = 0;          /** How many invalid configs is. */
			int non_existent_aliases_ = 0;     /** How many valid aliases is. */
			int non_existent_groups_ = 0;      /** How many in valid aliases is. */
			int total_missing_form_lists_ = 0; /** How many missing FormLists is. */
			int fl_total_duplicates_ = 0;      /** Total amount of FromLists duplicates. */
			int fl_total_added_ = 0;           /** Total amount of added FormLists. */
			int plants_duplicates_ = 0;        /** Total amount of Plants duplicates. */
			int plants_added_ = 0;             /** Total amount of added Plants. */
			int boy_toys_added_ = 0;           /** Total amount of added boy's toys. */
			int boy_toys_duplicates_ = 0;      /** Total amount of boy's toys duplicates. */
			int girl_toys_added_ = 0;          /** Total amount of added girl's toys. */
			int girl_toys_duplicates_ = 0;     /** Total amount of girl's toys duplicates. */
			int total_found_forms_ = 0;        /** Total amount of found Forms during configs parse. */
			int total_missing_forms_ = 0;      /** Total amount of missing Forms. */
			int total_aliases_ = 0;            /** Total amount of found Aliases. */
			int aliases_duplicates_ = 0;       /** Total amount of Aliases duplicates. */
			int total_groups_ = 0;             /** Total amount of found Groups. */
			int groups_duplicates_ = 0;        /** Total amount of Groups duplicates. */

			/**
			 * \brief Finds FormList based on FormEditorID.
			 * \param fei                       - FormEditorID of the FormList.
			 * \param formList                  - A pointer to the FormList to be filled in.
			 */
			void findList(const std::string_view& fei, RE::BGSListForm*& formList) const;
			/**
			 * \brief Adds Form and FromList to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format FList|Form, Form, #Group, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool addFormList(const std::string& entry);
			/**
			 * \brief Adds Seed end Plant to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format Seed|Plant
			 * \return                          - True, if everything went fine.
			 */
			bool addPlant(const std::string& entry);
			/**
			 * \brief Adds Toys to internal structure based on string entry. String is validated. If parameter Boy is set to false, toys are for girls.
			 * \param entry                     - String in the format Form, Form, #Group, etc.
			 * \param boy                       - If true toys are for boys, if false for girls.
			 * \return                          - True, if everything went fine.
			 */
			bool addToys(const std::string& entry, bool boy = true);
			/**
			 * \brief Adds Alias to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format NameForAlias|FList, FList, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool addAlias(const std::string& entry);
			/**
			 * \brief Adds Group to internal structure based on string entry. String is validated.
			 * \param entry                     - String in the format NameForGroup|From, From, etc.
			 * \return                          - True, if everything went fine.
			 */
			bool addGroup(const std::string& entry);
			/**
			 * \brief Adds From to FormList. Duplicates are omitted.
			 * \param list                      - FromList where Form will be added.
			 * \param form                      - Form to add.
			 * \return                          - True, if everything went fine.
			 */
			bool addFormToFormList(RE::BGSListForm*& list, RE::TESForm* form);
	};

	inline bool Manipulator::DebugMode() const
	{
		return debug_mode_;
	}

	inline void Manipulator::SetDebugMode(bool mode)
	{
		debug_mode_ = mode;
	}

	inline void Manipulator::FindLists()
	{
		findList("flPlanterPlantableItem"sv, seeds_list_);
		findList("flPlanterPlantedFlora"sv, plants_list_);
		findList("BYOHRelationshipAdoptionPlayerGiftChildMale"sv, boy_toys_list_);
		findList("BYOHRelationshipAdoptionPlayerGiftChildFemale"sv, girl_toys_list_);
	}

	inline void Manipulator::FindConfigs()
	{
		const std::filesystem::directory_entry debug_mode_toggle(R"(Data\FormListManipulator_DEBUG.ini)");
		if(debug_mode_toggle.exists())
		{
			logger::info("{:-^47}", "DEBUG MODE ENABLED");
			SetDebugMode(true);
		}

		logger::info("{:-^47}", "Looking for configs");
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
			logger::warn("Configs not found!");
			return;
		}
		else
			logger::info("Found {} configs.", files.size());

		for(auto& path : files)
		{
			CSimpleIniA ini;
			ini.SetUnicode();
			ini.SetMultiKey();

			if(const auto rc = ini.LoadFile(path.c_str()); rc < 0)
			{
				logger::error("Can't read ini {}.", path);
				invalid_configs_++;
				continue;
			}

			valid_configs_++;

			logger::info("    Processing {}...", path);

			if(auto values = ini.GetSection(""); values)
			{
				// How many valid entries is.
				int valid_entries = 0;
				// How many invalid entries is.
				int invalid_entries = 0;

				// Parse Aliases and Groups first.
				for(auto& [key, entry] : *values)
				{
					auto sanitized_str = Sanitize(entry);
					std::string sanitized_key = key.pItem;
					std::ranges::transform(sanitized_key, sanitized_key.begin(), [](unsigned char c)
										   { return std::tolower(c); });

					if(sanitized_key == keywords_.at(4))
					{
						if(!addAlias(sanitized_str))
						{
							logger::error("        Unable to parse: {}.", sanitized_str);
							invalid_entries++;
						}
						else
							valid_entries++;
					}
					else if(sanitized_key == keywords_.at(5))
					{
						if(!addGroup(sanitized_str))
						{
							logger::error("        Unable to parse: {}.", sanitized_str);
							invalid_entries++;
						}
						else
							valid_entries++;
					}
				}

				for(auto& [key, entry] : *values)
				{
					auto sanitized_str = Sanitize(entry);
					std::string sanitized_key = key.pItem;
					std::ranges::transform(sanitized_key, sanitized_key.begin(), [](unsigned char c)
										   { return std::tolower(c); });

					// Skip parsed Aliases and Groups.
					if(sanitized_key == keywords_.at(4) || sanitized_key == keywords_.at(5))
						continue;
					else if(sanitized_key == keywords_.at(0))
					{
						if(!addFormList(sanitized_str))
						{
							logger::error("        Unable to parse: {}.", sanitized_str);
							invalid_entries++;
						}
						else
							valid_entries++;
					}
					else if(sanitized_key == keywords_.at(1))
					{
						if(!addPlant(sanitized_str))
						{
							logger::error("        Unable to parse: {}.", sanitized_str);
							invalid_entries++;
						}
						else
							valid_entries++;
					}
					else if(sanitized_key == keywords_.at(2))
					{
						if(!addToys(sanitized_str))
						{
							logger::error("        Unable to parse: {}.", sanitized_str);
							invalid_entries++;
						}
						else
							valid_entries++;
					}
					else if(sanitized_key == keywords_.at(3))
					{
						if(!addToys(sanitized_str, false))
						{
							logger::error("        Unable to parse: {}.", sanitized_str);
							invalid_entries++;
						}
						else
							valid_entries++;
					}
					else
					{
						logger::error("        Unknown key {}!", key.pItem);
						invalid_entries++;
					}
				}

				logger::info("        Finished, {} valid entries found, {} invalid.", valid_entries, invalid_entries);
				total_valid_entries_ += valid_entries;
				total_invalid_entries_ += invalid_entries;
			}
			else
				logger::info("        Config file is empty.");
		}

		logger::info("Reading configs complete, {} valid configs found, {} invalid. {} valid entries found, {} invalid.",
					 valid_configs_,
					 invalid_configs_,
					 total_valid_entries_,
					 total_invalid_entries_);
		logger::info("{:-^47}", "");
	}

	inline void Manipulator::AddPlants()
	{
		if(!reload)
			logger::info("{:-^47}", "PLANTS");
		for(auto& [seed, plant] : plants_)
		{
			if(seeds_list_->HasForm(seed))
			{
				if(!reload)
					logger::warn("    Seed \"{}\" [{:X}] already on the list!", seed->GetName(), seed->formID);
				plants_duplicates_++;
				continue;
			}

			if(plants_list_->HasForm(plant))
			{
				if(!reload)
					logger::warn("    Plant \"{}\" [{:X}] already on the list!", plant->GetName(), plant->formID);
				plants_duplicates_++;
				continue;
			}

			seeds_list_->AddForm(seed);
			plants_list_->AddForm(plant);
			plants_added_++;
			if(debug_mode_)
				logger::info("Seed: \"{}\" [{:X}] and Plant: \"{}\" [{:X}] added!", seed->GetName(), seed->formID, plant->GetName(), plant->formID);
		}
		if(!reload)
		{
			logger::info("Total {} new plants added, skipped {} duplicates.", plants_added_, plants_duplicates_);
			logger::info("{:-^47}", "");
		}
	}

	inline void Manipulator::AddToys()
	{
		if(!reload)
			logger::info("{:-^47}", "BOY'S TOYS");
		for(auto& toy : boy_toys_)
		{
			if(boy_toys_list_->HasForm(toy))
			{
				if(!reload)
					logger::warn("    Toy \"{}\" [{:X}] already on the list of a boy's toys!", toy->GetName(), toy->formID);
				boy_toys_duplicates_++;
				continue;
			}

			boy_toys_list_->AddForm(toy);
			boy_toys_added_++;
			if(debug_mode_)
				logger::info("    Toy \"{}\" [{:X}] added to the list of a boy's toys!", toy->GetName(), toy->formID);
		}

		if(!reload)
		{
			logger::info("Total {} new toys added, skipped {} duplicates.", boy_toys_added_, boy_toys_duplicates_);
			logger::info("{:-^47}", "");

			logger::info("{:-^47}", "GIRL'S TOYS");
		}

		for(auto& toy : girl_toys_)
		{
			if(girl_toys_list_->HasForm(toy))
			{
				if(!reload)
					logger::warn("Toy \"{}\" [{:X}] already on the list of a girl's toys!", toy->GetName(), toy->formID);
				girl_toys_duplicates_++;
				continue;
			}

			girl_toys_list_->AddForm(toy);
			girl_toys_added_++;
			if(debug_mode_)
				logger::info("Toy \"{}\" [{:X}] added to the list of a girl's toys!", toy->GetName(), toy->formID);
		}

		if(!reload)
		{
			logger::info("Total {} new toys added, skipped {} duplicates.", girl_toys_added_, girl_toys_duplicates_);
			logger::info("{:-^47}", "");
		}
	}

	inline void Manipulator::AddToFormLists()
	{
		if(!reload)
			logger::info("{:-^47}", "FORMLISTS");

		for(auto& [form_list, forms] : form_lists_)
		{
			int duplicates = 0;
			int added = 0;
			RE::BGSListForm* fl = form_list;
			logger::info("    FormList \"{}\" [{:X}]", fl->GetName(), fl->formID);
			for(const auto& f : forms)
			{
				if(fl->HasForm(f))
				{
					if(!reload)
						logger::warn("        Form \"{}\" [{:X}] already on the list!", f->GetName(), f->formID);
					duplicates++;
					continue;
				}
				else
				{
					fl->AddForm(f);
					added++;
					if(debug_mode_)
						logger::info("        Form: \"{}\" [{:X}] added!", f->GetName(), f->formID);
				}
			}

			logger::info("        {} new Forms added, skipped {} duplicates.", added, duplicates);
			fl_total_added_ += added;
			fl_total_duplicates_ += duplicates;
		}

		if(!reload)
		{
			logger::info("Total {} new Forms added to {} FormLists, skipped {} duplicates.", fl_total_added_, form_lists_.size(), fl_total_duplicates_);
			logger::info("{:-^47}", "");
		}
	}

	inline void Manipulator::Summary()
	{
		logger::info("{:-^47}", "SUMMARY");
		logger::info("{} valid configs, {} invalid. {} total entries, {} valid, {} invalid.",
					 valid_configs_,
					 invalid_configs_,
					 total_valid_entries_ + total_invalid_entries_,
					 total_valid_entries_,
					 total_invalid_entries_);
		logger::info("{} FormLists, {} valid, {} invalid. {} total Forms, {} unique, {} missing, {} duplicates.",
					 form_lists_.size() + total_missing_form_lists_,
					 form_lists_.size(),
					 total_missing_form_lists_,
					 total_found_forms_ + total_missing_forms_,
					 total_found_forms_ - fl_total_duplicates_ - plants_duplicates_ - boy_toys_duplicates_ - girl_toys_duplicates_,
					 total_missing_forms_,
					 fl_total_duplicates_ + plants_duplicates_ + boy_toys_duplicates_ + girl_toys_duplicates_);
		logger::info("{} FromLists Aliases added, {} duplicates, {} not existing.", aliases_.size(), aliases_duplicates_, non_existent_aliases_);
		logger::info("{} Forms Groups added, {} duplicates, {} not existing.", groups_.size(), groups_duplicates_, non_existent_groups_);
		logger::info("{} new plants added, skipped {} duplicates.", plants_added_, plants_duplicates_);
		logger::info("{} new Boy's Toys added, skipped {} duplicates.", boy_toys_added_, boy_toys_duplicates_);
		logger::info("{} new Girl's Toys added, skipped {} duplicates.", girl_toys_added_, girl_toys_duplicates_);
		logger::info("{} new Forms added to {} FormLists, skipped {} duplicates.", fl_total_added_, form_lists_.size(), fl_total_duplicates_);
		logger::info("{:-^47}", " ^_^ ");
	}

	inline void Manipulator::findList(const std::string_view& fei, RE::BGSListForm*& formList) const
	{
		formList = RE::TESForm::LookupByEditorID<RE::BGSListForm>(fei);

		if(formList)
		{
			if(debug_mode_)
				logger::info("Found FormList {} \"{}\" [{:X}]", fei, formList->GetName(), formList->formID);
		}
		else
			logger::error("Unable to find FormList {}.", fei);
	}

	inline bool Manipulator::addFormList(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			logger::error("            Wrong FormList format. Expected 2 sections, got {}.", sections.size());
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
				logger::error("        Unknown Alias: {}.", form_list_info);
				non_existent_aliases_++;
				found_destination = false;
			}
		}
		else
		{
			const auto form_list = FindFormList(form_list_info);
			if(!form_list)
			{
				logger::error("            Unable to find FormList: {}.", form_list_info);
				total_missing_form_lists_++;
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
		{
			if(fs.starts_with("#"))
			{
				fs.erase(0, 1);
				if(groups_.contains(fs))
					forms.insert(forms.end(), groups_[fs].begin(), groups_[fs].end());
				else
				{
					logger::error("            Unknown Group: {}.", fs);
					non_existent_groups_++;
				}
			}
			else
			{
				auto form = FindForm(fs);
				if(!form)
				{
					logger::error("            Unable to find Form: {}.", fs);
					missing++;
					continue;
				}
				forms.emplace_back(form);
			}
		}

		if(!found_destination)
			return false;

		total_found_forms_ += forms.size();
		total_missing_forms_ += missing;

		for(auto& fl : form_lists)
		{
			if(debug_mode_)
				logger::info("        Found FormList \"{}\" [{:X}], {} Forms, {} missing Forms.", fl->GetName(), fl->formID, forms.size(), missing);
			if(form_lists_.contains(fl))
				form_lists_[fl].insert(form_lists_[fl].end(), forms.begin(), forms.end());
			else
				form_lists_.emplace(std::piecewise_construct, std::forward_as_tuple(fl), std::forward_as_tuple(forms));
		}
		return true;
	}

	inline bool Manipulator::addPlant(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			logger::error("            Wrong Plant format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		const auto seed_info = sections[0];
		const auto seed = FindForm(seed_info);
		if(!seed)
		{
			logger::error("            Unable to find seed: {}.", seed_info);
			total_missing_forms_++;
		}

		const auto plant_info = sections[1];
		const auto plant = FindForm(plant_info);
		if(!plant)
		{
			logger::error("            Unable to find plant: {}.", plant_info);
			total_missing_forms_++;
		}

		if(!seed || !plant)
			return false;

		if(seed->GetFormType() != RE::FormType::Ingredient && seed->GetFormType() != RE::FormType::AlchemyItem && seed->GetFormType() != RE::FormType::Activator)
			logger::warn("            {} type {:X} is not Ingredient, AlchemyItem or Activator.", seed_info, static_cast<int>(seed->GetFormType()));

		if(plant->GetFormType() != RE::FormType::Flora && plant->GetFormType() != RE::FormType::Tree && plant->GetFormType() != RE::FormType::Container && plant->GetFormType() != RE::FormType::Activator && plant->GetFormType() != RE::FormType::Misc)
			logger::warn("            {} type {:X} is not Flora, Tree, Activator, Misc or Container.", plant_info, static_cast<int>(plant->GetFormType()));

		if(debug_mode_)
			logger::info("        Found Seed \"{}\" [{:X}], Plant \"{}\" [{:X}].", seed->GetName(), seed->formID, plant->GetName(), plant->formID);

		plants_.emplace_back(seed, plant);
		return true;
	}

	inline bool Manipulator::addToys(const std::string& entry, bool boy)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 1)
		{
			logger::error("            Wrong Toys format. Expected 1 sections, got {}.", sections.size());
			return false;
		}

		const auto forms_info = sections[0];
		auto forms_sections = string::split(forms_info, ",");
		int amount = 0;
		int missing = 0;
		for(auto& fs : forms_sections)
		{
			if(fs.starts_with("#"))
			{
				fs.erase(0, 1);
				if(groups_.contains(fs))
				{
					for(auto& f : groups_[fs])
					{
						if(boy)
							boy_toys_.emplace_back(f);
						else
							girl_toys_.emplace_back(f);
						amount++;
					}
				}
				else
				{
					logger::error("            Unknown Group: {}.", fs);
					non_existent_groups_++;
				}
			}
			else
			{
				auto form = FindForm(fs);
				if(!form)
				{
					logger::error("            Unable to find Form: {} for Toys.", fs);
					missing++;
					continue;
				}
				if(boy)
					boy_toys_.emplace_back(form);
				else
					girl_toys_.emplace_back(form);
				amount++;
			}
		}
		if(debug_mode_)
			logger::info("        Toys: found {} Forms, {} missing Forms.", amount, missing);
		total_found_forms_ += amount;
		total_missing_forms_ += missing;

		return true;
	}

	inline bool Manipulator::addAlias(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			logger::error("            Wrong Alias format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool duplicate = false;
		const auto alias_info = sections[0];
		if(aliases_.contains(alias_info))
		{
			logger::error("            Alias {} exists.", alias_info);
			aliases_duplicates_++;
			duplicate = true;
		}

		const auto form_lists_info = sections[1];
		const auto form_lists_sections = string::split(form_lists_info, ",");
		std::vector<RE::BGSListForm*> form_lists;
		int missing = 0;
		for(auto& fs : form_lists_sections)
		{
			auto form_list = FindFormList(fs);
			if(!form_list)
			{
				logger::error("            Unable to find FormList: {} for Alias.", fs);
				missing++;
				continue;
			}
			form_lists.emplace_back(form_list);
		}

		if(duplicate)
		{
			logger::warn("Entry will be omitted due to incorrect Alias name.");
			return false;
		}

		aliases_.emplace(std::piecewise_construct, std::forward_as_tuple(alias_info), std::forward_as_tuple(form_lists));
		if(debug_mode_)
			logger::info("        FormLists Alias \"{}\" added with {} FormsLists, {} missing FormLists.", alias_info, form_lists.size(), missing);

		return true;
	}

	inline bool Manipulator::addGroup(const std::string& entry)
	{
		const auto sections = string::split(entry, "|");
		if(sections.size() != 2)
		{
			logger::error("            Wrong Group format. Expected 2 sections, got {}.", sections.size());
			return false;
		}

		bool duplicate = false;
		const auto group_info = sections[0];

		if(groups_.contains(group_info))
		{
			logger::error("            Group {} exists..", group_info);
			groups_duplicates_++;
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
				logger::error("            Unable to find Form: {} for Group.", fs);
				missing++;
				continue;
			}
			forms.emplace_back(form);
		}

		if(duplicate)
		{
			logger::warn("Entry will be omitted due to incorrect Group name.");
			return false;
		}

		groups_.emplace(std::piecewise_construct, std::forward_as_tuple(group_info), std::forward_as_tuple(forms));
		if(debug_mode_)
			logger::info("        Forms Group \"{}\" added with {} Forms, {} missing Forms.", group_info, forms.size(), missing);

		return true;
	}

	inline bool Manipulator::addFormToFormList(RE::BGSListForm*& list, RE::TESForm* form)
	{
		if(list->HasForm(form))
		{
			if(!reload)
				logger::warn("Form \"{}\" [{:X}] already on the list!", form->GetName(), form->formID);
			return false;
		}

		list->AddForm(form);
		logger::info("Form \"{}\" [{:X}]  added!", form->GetName(), form->formID);

		return true;
	}

	inline Manipulator manipulator;
}
