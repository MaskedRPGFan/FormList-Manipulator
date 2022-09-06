#pragma once

namespace flm::OperatingMode
{
	/**
	 * Modes of operating for FLM.
	 */
	enum OperatingMode
	{
		INITIALIZE = 0, /* When Skyrim.exe starts. */
		NEW_GAME,       /* When user starts new game. */
		LOAD_GAME,      /* When user loads existing game. */

		ALL /* Amount of Entry types. */
	};
}
